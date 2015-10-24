//
//  PlayScene.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-16.
//
//

#include "PlayScene.h"
#include "Runner.h"
#include "InfosLayer.h"
#include "MapManager.h"
#include "resources.h"
#include "SimpleRecognizer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

PlayScene::PlayScene()
{
    m_eGameState = GameState_Normal;
    m_fLastEyeX = 0;
}

PlayScene::~PlayScene()
{
    delete m_pRecognizer;
    m_pRecognizer = NULL;
    
}

CCScene* PlayScene::scene()
{
    CCScene *pScene = CCScene::create();
    
    PlayScene *pPlayLayer = PlayScene::create();
    pScene->addChild(pPlayLayer);
    
    CCLayer* pInfoLayer = InfosLayer::create();
    pScene->addChild(pInfoLayer);
    
    return pScene;
}

bool PlayScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(BACK_MUSIC, true);
    
    initPhysics();
    
    m_pMapMgr = MapManager::create(this, m_pWorld);
    this->addChild(m_pMapMgr);
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(spritesheet);
    CCSpriteBatchNode *pSpriteBatchNode = CCSpriteBatchNode::create(spritePacker);
    this->addChild(pSpriteBatchNode);
    
    m_pRunner = Runner::create(m_pWorld, pSpriteBatchNode);
    // You MUST add to the layer, or m_pRunner will be autorelease!!!
    this->addChild(m_pRunner);
    
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    m_pRecognizer = new SimpleRecognizer();
    
    
    // Call this->update(dt) every frame;
    this->scheduleUpdate();
    
    return true;
}

bool PlayScene::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    if (m_eGameState == GameState_Normal)
    {
        CCPoint pos = touch->getLocation();
        m_pRecognizer->beginPoint(pos.x, pos.y);
    }
    
    return true;
}

void PlayScene::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    CCPoint pos = touch->getLocation();
    m_pRecognizer->movePoint(pos.x, pos.y);
}

void PlayScene::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    SimpleGestures gesture = m_pRecognizer->endPoint();
    switch (gesture)
    {
        case SimpleGesturesUp:
            m_pRunner->jump();
            break;
            
        case SimpleGesturesDown:
            m_pRunner->crouch();
            break;
            
        case SimpleGesturesRight:
        case SimpleGesturesLeft:
            break;
            
        case SimpleGesturesError:
        case SimpleGesturesNotSupport:
        default:
            break;
    }
}

void PlayScene::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    CCLOG("onTouchCancelled!!!");
}

void PlayScene::initPhysics()
{
    m_pWorld = new b2World(b2Vec2(0, -10));
    
    m_pWorld->SetAllowSleeping(true);
    m_pWorld->SetContinuousPhysics(true);
//    m_pWorld->SetContactListener(this);
    
    // Create ground body
    b2Body *pGround = NULL;
    b2BodyDef bd;
    pGround = m_pWorld->CreateBody(&bd);
    
    // Create body fixture
    b2EdgeShape shape;
    shape.Set(b2Vec2(0, GROUND_HEIGHT/RATIO), b2Vec2(INT32_MAX, GROUND_HEIGHT/RATIO));
    pGround->CreateFixture(&shape, 0.0f);
    
//    b2FixtureDef groundFixtureDef;
//    groundFixtureDef.shape = &shape;
//    groundFixtureDef.density = 0.0f;
//    groundFixtureDef.friction = 0.0f;
//    groundFixtureDef.userData = NULL;
//    pGround->CreateFixture(&groundFixtureDef);
    
    setDebug(true);
}

void PlayScene::update(float dt)
{
    m_pWorld->Step(dt, 10, 8);
    
    m_pMapMgr->checkReloadMap(m_fLastEyeX);
    
    CCScene *pScene = (CCScene *)this->getParent();
    InfosLayer *pInfoLayer = (InfosLayer *) pScene->getChildByTag(INFOS_LAYER_TAG);
    pInfoLayer->updateMeter(m_fLastEyeX);
    
    // Focus on the runner;
    m_fLastEyeX = m_pRunner->getRunnerPosX() - m_pRunner->getOffsetPx();
    
    CCCamera *pCamera = this->getCamera();
    float fEyeZ = pCamera->getZEye();
//    CCLog("%f", fEyeZ);
    pCamera->setEyeXYZ(m_fLastEyeX, 0, fEyeZ);
    pCamera->setCenterXYZ(m_fLastEyeX, 0, 0);
    
    m_pRunner->update(dt);
}

void PlayScene::draw()
{
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    
    kmGLPushMatrix();
    
    m_pWorld->DrawDebugData();
    
    kmGLPopMatrix();
}

void PlayScene::setDebug(bool isDebug)
{
    if (isDebug)
    {
        m_pDebugDraw = new GLESDebugDraw(RATIO);
        m_pWorld->SetDebugDraw(m_pDebugDraw);
        
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        flags += b2Draw::e_jointBit;
        flags += b2Draw::e_pairBit;
        flags += b2Draw::e_centerOfMassBit;
        m_pDebugDraw->SetFlags(flags);
        
//        draw();
    }
    else
    {
        m_pWorld->SetDebugDraw(NULL);
    }
}


