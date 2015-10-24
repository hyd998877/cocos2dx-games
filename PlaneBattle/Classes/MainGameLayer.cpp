//
//  MainGameLayer.cpp
//  PlaneBattle
//
//  Created by zhouf369 on 14-8-28.
//
//

#include "AppDelegate.h"
#include "MainGameLayer.h"
#include "SimpleAudioEngine.h"
#include "FeoPlane.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

MainGameLayer::MainGameLayer()
{
    m_pFoePlanesList = NULL;
    m_pProp = NULL;
}

MainGameLayer::~MainGameLayer()
{
    if (m_pFoePlanesList != NULL)
    {
        m_pFoePlanesList->removeAllObjects();
        m_pFoePlanesList->release();
        m_pFoePlanesList = NULL;
    }
    
    if (m_pProp != NULL)
    {
        m_pProp->getSprite()->removeFromParentAndCleanup(true);
        m_pProp->release();
        m_pProp = NULL;
    }
}

cocos2d::CCScene* MainGameLayer::scene()
{
    CCScene *pGameScene = CCScene::create();
    
    MainGameLayer *pGameLayer = MainGameLayer::create();
    pGameScene->addChild(pGameLayer);
    
    return pGameScene;
}
    
bool MainGameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gameArts.plist");
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_music.mp3", true);
    
    this->initDatas();
    this->loadBackground();
    this->loadPlayerPlane();
    this->madeBullets();
    this->resetBullets();
    
    this->scheduleUpdate();
    
    this->setTouchEnabled(true);
    
    return true;
}

void MainGameLayer::onEnter()
{
    CCLayer::onEnter();
}

void MainGameLayer::onExit()
{
    CCLayer::onExit();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("gameArts.plist");
}

void MainGameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool MainGameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_ptPreTouch = pTouch->getLocation();
    
    return true;
}

void MainGameLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint ptPrev = m_ptPreTouch;
    CCPoint ptCurrent = pTouch->getLocation();
    m_ptPreTouch = ptCurrent;
    
    CCPoint translation = ccpSub(ptCurrent, ptPrev);
    if (!m_bIsGameOver)
    {
        setPlayerPlanePos(translation);
    }
}

void MainGameLayer::update(float dt)
{
    if (!m_bIsGameOver)
    {
        // Moving background
        this->scrollBackground();
        
        this->firingBullest();
        
        this->addFeoPlane();
        this->moveFoePlane();
        
        this->bulletLastTime();
        
        this->addBulletTypeTip();
        
        this->collisionDetection();
    }
}

#define PLAYER_BULLET_INIT_SPEED 25
#define PLAYER_SPECIAL_BULLET_DURATION 1200

void MainGameLayer::initDatas()
{
    m_bIsGameOver = false;
    
    m_iBulletSpeed = PLAYER_BULLET_INIT_SPEED;
    
    m_iSmallPlaneTime = 0;
    m_iMediumPlaneTime = 0;
    m_iBigPlaneTime = 0;
    
    m_iBulletLastTime = PLAYER_SPECIAL_BULLET_DURATION;
    
    m_iPropTime = 0;
    m_bIsPropVisible = false;
    
    m_iScores = 0;
    
    m_bIsBigBullet = false;
    m_bIsChangeBullet = false;
    
    if (m_pFoePlanesList != NULL)
    {
        m_pFoePlanesList->removeAllObjects();
        m_pFoePlanesList->release();
        m_pFoePlanesList = NULL;
    }
    
    m_pFoePlanesList = CCArray::create();
    m_pFoePlanesList->retain();
}

#define BACKGROUND_ADJUSTMENT_INIT_VALUE 568

void MainGameLayer::loadBackground()
{
    m_iAdjustmentBg = BACKGROUND_ADJUSTMENT_INIT_VALUE;
    
    m_pBg1 = CCSprite::createWithSpriteFrameName("background_2.png");
    m_pBg1->setAnchorPoint(ccp(0, 0));
    m_pBg1->setPosition(ccp(0, 0));
    this->addChild(m_pBg1, 0);
    
    m_pBg2 = CCSprite::createWithSpriteFrameName("background_2.png");
    m_pBg2->setAnchorPoint(ccp(0, 0));
    m_pBg2->setPosition(ccp(0, m_iAdjustmentBg-1));
    this->addChild(m_pBg2, 0);
    
    m_pScoreLabel = CCLabelTTF::create("0000", "MarkerFelt-Thin", 20);
    m_pScoreLabel->setColor(ccc3(0, 0, 0));
    m_pScoreLabel->setPosition(ccp(75.0f, RESOLUTION_HEIGHT - 25));
    this->addChild(m_pScoreLabel, 4);
    
    CCMenuItem *pPauseMenuItem = CCMenuItemImage::create("BurstAircraftPause.png", "BurstAircraftPause.png", this, menu_selector(MainGameLayer::btnGamePauseCallback));
    pPauseMenuItem->setAnchorPoint(ccp(0, 1));
    pPauseMenuItem->setPosition(ccp(10, RESOLUTION_HEIGHT - 10));
    
    CCMenu *pPauseMenu = CCMenu::create(pPauseMenuItem, NULL);
    pPauseMenu->setPosition(CCPointZero);
    this->addChild(pPauseMenu, 4);
    m_pPauseMenu = pPauseMenu;
}

void MainGameLayer::loadPlayerPlane()
{
    char buf[255];
    CCArray * arrFrames = CCArray::create();
    for (int i = 1; i < 3; i++)
    {
        sprintf(buf, "hero_fly_%d.png", i);
        CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        arrFrames->addObject(pFrame);
    }
    
    CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    
    m_pPlayerPlane = CCSprite::createWithSpriteFrameName("hero_fly_1.png");
    m_pPlayerPlane->setPosition(ccp(160, 50));
    this->addChild(m_pPlayerPlane, 3);
    
    m_pPlayerPlane->runAction(CCRepeatForever::create(pAnimate));
}

void MainGameLayer::madeBullets()
{
    string szBulletPath = "bullet1.png";
    if (m_bIsBigBullet)
    {
        szBulletPath = "bullet2.png";
    }
    
    m_pBullet = CCSprite::createWithSpriteFrameName(szBulletPath.c_str());
    m_pBullet->setAnchorPoint(ccp(0.5, 0.5));
    this->addChild(m_pBullet);
    
    this->playFireSound();
}

void MainGameLayer::resetBullets()
{
    if ((m_bIsBigBullet && m_bIsChangeBullet) || (!m_bIsBigBullet && m_bIsChangeBullet))
    {
        m_pBullet->removeFromParentAndCleanup(true);
        
        this->madeBullets();
        m_bIsChangeBullet = false;
    }
    
    m_iBulletSpeed = (RESOLUTION_HEIGHT - (m_pPlayerPlane->getPosition().y + 50)) / 15;
    
    if (m_iBulletSpeed < 5)
    {
        m_iBulletSpeed = 5;
    }
    
    m_pBullet->setPosition(ccp(m_pPlayerPlane->getPosition().x, m_pPlayerPlane->getPosition().y + 50));
    
    this->playFireSound();
}

void MainGameLayer::firingBullest()
{
    m_pBullet->setPosition(ccp(m_pBullet->getPosition().x, m_pBullet->getPosition().y + m_iBulletSpeed));
    if (m_pBullet->getPosition().y > RESOLUTION_HEIGHT - 20)
    {
        this->resetBullets();
    }
}

void MainGameLayer::scrollBackground()
{
    m_iAdjustmentBg--;
    
    if (m_iAdjustmentBg <= 0)
    {
        m_iAdjustmentBg = BACKGROUND_ADJUSTMENT_INIT_VALUE;
    }
    
    m_pBg1->setPosition(ccp(0, m_iAdjustmentBg - BACKGROUND_ADJUSTMENT_INIT_VALUE));
    m_pBg2->setPosition(ccp(0, m_iAdjustmentBg - 1));
}

void MainGameLayer::addFeoPlane()
{
    m_iSmallPlaneTime++;
    m_iMediumPlaneTime++;
    m_iBigPlaneTime++;
    
    if (m_iSmallPlaneTime > 25)
    {
        FeoPlane *pSmallPlane = this->makeSmallFoePlane();
        this->addChild(pSmallPlane, 3);
        
        m_pFoePlanesList->addObject(pSmallPlane);
        m_iSmallPlaneTime = 0;
    }
    
    if (m_iMediumPlaneTime > 400)
    {
        FeoPlane *pMediumPlane = this->makeMediumFoePlane();
        this->addChild(pMediumPlane, 3);
        
        m_pFoePlanesList->addObject(pMediumPlane);
        m_iMediumPlaneTime = 0;
    }
    
    if (m_iBigPlaneTime > 700)
    {
        FeoPlane *pBigPlane = this->makeBigFoePlane();
        this->addChild(pBigPlane, 3);
        
        m_pFoePlanesList->addObject(pBigPlane);
        m_iBigPlaneTime = 0;
        
        this->scheduleOnce(schedule_selector(MainGameLayer::bigPlaneOutSound), 0.5f);
    }
}

FeoPlane * MainGameLayer::makeSmallFoePlane()
{
    FeoPlane *pSmallPlane = FeoPlane::create();
    pSmallPlane->initWithSpriteFrameName("enemy1_fly_1.png");
    pSmallPlane->setPosition(ccp((arc4random()%290) + 17, 568));
    pSmallPlane->setPlaneType(PLANE_TYPE_SMALL);
    pSmallPlane->setHp(1);
    pSmallPlane->setSpeed(arc4random() % 4 + 2);
    return pSmallPlane;
}

FeoPlane * MainGameLayer::makeMediumFoePlane()
{
    FeoPlane *pMediumPlane = FeoPlane::create();
    pMediumPlane->initWithSpriteFrameName("enemy3_fly_1.png");
    pMediumPlane->setPosition(ccp((arc4random()%280) + 23, 568));
    pMediumPlane->setPlaneType(PLANE_TYPE_MIDDLE);
    pMediumPlane->setHp(15);
    pMediumPlane->setSpeed(arc4random() % 3 + 2);
    return pMediumPlane;
}

FeoPlane * MainGameLayer::makeBigFoePlane()
{
    char buf[255];
    CCArray * arrFrames = CCArray::create();
    for (int i = 1; i < 3; i++)
    {
        sprintf(buf, "enemy2_fly_%d.png", i);
        CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        arrFrames->addObject(pFrame);
    }
    
    CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    
    FeoPlane *pBigPlane = FeoPlane::create();
    pBigPlane->initWithSpriteFrameName("enemy2_fly_1.png");
    pBigPlane->setPosition(ccp((arc4random()%210) + 55, 700));
    pBigPlane->setPlaneType(PLANE_TYPE_LARGE);
    pBigPlane->setHp(25);
    pBigPlane->setSpeed(arc4random() % 2 + 2);
    
    pBigPlane->runAction(CCRepeatForever::create(pAnimate));
    
    return pBigPlane;
}

void MainGameLayer::moveFoePlane()
{
    CCObject *pItor = NULL;
    CCARRAY_FOREACH(m_pFoePlanesList, pItor)
    {
        FeoPlane *pTmpPlane = dynamic_cast<FeoPlane *>(pItor);
        
        pTmpPlane->setPosition(ccp(pTmpPlane->getPosition().x, pTmpPlane->getPosition().y - pTmpPlane->getSpeed()));
        if (pTmpPlane->getPosition().y < -75)
        {
            m_pFoePlanesList->removeObject(pTmpPlane);
            pTmpPlane->removeFromParentAndCleanup(true);
        }
    }
}

void MainGameLayer::bulletLastTime()
{
    if (m_bIsBigBullet)
    {
        if (m_iBulletLastTime > 0)
        {
            m_iBulletLastTime--;
        }
        else
        {
            m_iBulletLastTime = 1200;
            m_bIsBigBullet = false;
            m_bIsChangeBullet = true;
        }
    }
}

void MainGameLayer::addBulletTypeTip()
{
    m_iPropTime++;
    if (m_iPropTime > 1500)
    {
        if (m_pProp != NULL)
        {
            m_pProp->getSprite()->removeFromParentAndCleanup(true);
            m_pProp->release();
            m_pProp = NULL;
        }
        
        m_pProp = ChangeBullet::create();
        m_pProp->initWithType((_BULLET_TYPE)(arc4random()%2+4));
        this->addChild(m_pProp->getSprite());
        m_pProp->propAnimation();
        
        m_pProp->retain();
        
        m_bIsPropVisible = true;
        m_iPropTime = 0;
    }
}

void MainGameLayer::setPlayerPlanePos(cocos2d::CCPoint ptAddPos)
{
    CCPoint ptNewPos = CCPointZero;
    ptNewPos.x = m_pPlayerPlane->getPosition().x + ptAddPos.x;
    ptNewPos.y = m_pPlayerPlane->getPosition().y + ptAddPos.y;
    
    if (ptNewPos.x >= 286)
    {
        ptNewPos.x = 286;
    }
    else if (ptNewPos.x <= 33)
    {
        ptNewPos.x = 33;
    }
    
    if (ptNewPos.y >= RESOLUTION_HEIGHT - 50)
    {
        ptNewPos.y = RESOLUTION_HEIGHT - 50;
    }
    else if (ptNewPos.y <= 43)
    {
        ptNewPos.y = 43;
    }
    
    m_pPlayerPlane->setPosition(ptNewPos);
}

void MainGameLayer::collisionDetection()
{
    CCRect rBulletRect = m_pBullet->boundingBox();
    CCObject *pItor = NULL;
    CCARRAY_FOREACH(m_pFoePlanesList, pItor)
    {
        FeoPlane *pTmpPlane = dynamic_cast<FeoPlane *>(pItor);
        if (pTmpPlane != NULL && rBulletRect.intersectsRect(pTmpPlane->boundingBox()))
        {
            this->resetBullets();
            
            int iLostHp = m_bIsBigBullet ? 2 : 1;
            pTmpPlane->setHp(pTmpPlane->getHp() - iLostHp);
            if (pTmpPlane->getHp() <= 0)
            {
                // Plane blows up
                this->foePlaneBlowupAnimation(pTmpPlane);
                m_pFoePlanesList->removeObject(pTmpPlane);
            }
            else
            {
                this->hitAnimationToFoePlane(pTmpPlane);
            }
        }
    }
    
    CCRect rPlayerRect = m_pPlayerPlane->boundingBox();
    rPlayerRect.origin.x += 25;
    rPlayerRect.size.width -= 50;
    rPlayerRect.origin.y -= 10;
    rPlayerRect.size.height -= 10;
    CCARRAY_FOREACH(m_pFoePlanesList, pItor)
    {
        FeoPlane *pTmpPlane = dynamic_cast<FeoPlane *>(pItor);
        if (pTmpPlane != NULL && rPlayerRect.intersectsRect(pTmpPlane->boundingBox()))
        {
            this->playerBlowupAnimation();
            this->foePlaneBlowupAnimation(pTmpPlane);
            m_pFoePlanesList->removeObject(pTmpPlane);
            
            this->gameOver();
        }
    }
    
    if (m_bIsPropVisible)
    {
        CCRect rPlayerRect1 = m_pPlayerPlane->boundingBox();
        CCRect pPropRect = m_pProp->getSprite()->boundingBox();
        
        if (pPropRect.origin.y <= -55)
        {
            m_bIsPropVisible = false;
            
            if (m_pProp != NULL)
            {
                m_pProp->getSprite()->removeFromParentAndCleanup(true);
                m_pProp->release();
                m_pProp = NULL;
            }
        }
        else if (rPlayerRect1.intersectsRect(pPropRect))
        {
            m_bIsPropVisible = false;
            m_pProp->getSprite()->stopAllActions();
            
            if (m_pProp->getBulletType() == BULLET_TYPE_BULLET)
            {
                m_bIsBigBullet = true;
                m_bIsChangeBullet = true;
            }
            else
            {
                CCARRAY_FOREACH(m_pFoePlanesList, pItor)
                {
                    FeoPlane *pTmpPlane = dynamic_cast<FeoPlane *>(pItor);
                    if (pTmpPlane != NULL)
                    {
                        this->foePlaneBlowupAnimation(pTmpPlane);
                    }
                }
                m_pFoePlanesList->removeAllObjects();
            }
            
            if (m_pProp != NULL)
            {
                m_pProp->getSprite()->removeFromParentAndCleanup(true);
                m_pProp->release();
                m_pProp = NULL;
            }
        }
    }
}

void MainGameLayer::hitAnimationToFoePlane(FeoPlane *pFoePlane)
{
    char buf[255];
    
    if (pFoePlane->getPlaneType() == PLANE_TYPE_MIDDLE)
    {
        if (pFoePlane->getHp() == 10)
        {
            CCArray * arrFrames = CCArray::create();
            for (int i = 1; i < 3; i++)
            {
                sprintf(buf, "enemy3_hit_%d.png", i);
                CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
                arrFrames->addObject(pFrame);
            }
            
            CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
            CCAnimate *pAnimate = CCAnimate::create(pAnimation);
            
            pFoePlane->stopAllActions();
            pFoePlane->runAction(CCRepeatForever::create(pAnimate));
        }
    }
    else if (pFoePlane->getPlaneType() == PLANE_TYPE_LARGE)
    {
        if (pFoePlane->getHp() == 15)
        {
            CCArray * arrFrames = CCArray::create();
            for (int i = 1; i < 1; i++)
            {
                sprintf(buf, "enemy2_hit_%d.png", i);
                CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
                arrFrames->addObject(pFrame);
            }
            
            CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
            CCAnimate *pAnimate = CCAnimate::create(pAnimation);
            
            pFoePlane->stopAllActions();
            pFoePlane->runAction(CCRepeatForever::create(pAnimate));
        }
    }
}

void MainGameLayer::blowupEnd(cocos2d::CCNode *pSender)
{
    pSender->removeFromParentAndCleanup(true);
}

void MainGameLayer::playerBlowupAnimation()
{
    char buf[255];
    CCArray * arrFrames = CCArray::create();
    for (int i = 1; i < 5; i++)
    {
        sprintf(buf, "hero_blowup_%d.png", i);
        CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        arrFrames->addObject(pFrame);
    }
    
    CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    
    m_pPlayerPlane->stopAllActions();
    m_pPlayerPlane->runAction(CCSequence::create(pAnimate, CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::blowupEnd)), NULL));
}

void MainGameLayer::foePlaneBlowupAnimation(FeoPlane *pFoePlane)
{
    int iAnimationNum = 0;
    
    if (pFoePlane->getPlaneType() == PLANE_TYPE_SMALL)
    {
        iAnimationNum = 4;
        m_iScores += 2000;
        
        this->smallPlaneDownSound();
    }
    else if (pFoePlane->getPlaneType() == PLANE_TYPE_MIDDLE)
    {
        iAnimationNum = 4;
        m_iScores += 10000;
        
        this->mediumPlaneDownSound();
    }
    else if (pFoePlane->getPlaneType() == PLANE_TYPE_LARGE)
    {
        iAnimationNum = 7;
        m_iScores += 40000;
        
        this->bigPlaneDownSound();
    }
    
    char buf[255];
    sprintf(buf, "%d", m_iScores);
    m_pScoreLabel->setString(buf);
    
    CCArray * arrFrames = CCArray::create();
    for (int i = 1; i <= iAnimationNum; i++)
    {
        sprintf(buf, "enemy%d_blowup_%d.png", pFoePlane->getPlaneType(), i);
        CCSpriteFrame * pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        arrFrames->addObject(pFrame);
    }
    
    CCAnimation * pAnimation = CCAnimation::createWithSpriteFrames(arrFrames, 0.1f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    
    pFoePlane->stopAllActions();
    pFoePlane->runAction(CCSequence::create(pAnimate, CCCallFuncN::create(this, callfuncN_selector(MainGameLayer::blowupEnd)), NULL));
}

void MainGameLayer::gameOver()
{
    m_bIsGameOver = true;
    
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    
    CCLabelTTF *pGameOverLabel = CCLabelTTF::create("GameOver", "MarkerFelt-Thin", 35);
    pGameOverLabel->setPosition(ccp(160, 300));
    this->addChild(pGameOverLabel, 4);
    
    CCMenuItemFont *pGameOverItem = CCMenuItemFont::create("RESTART GAME", this, menu_selector(MainGameLayer::btnGameRestartCallback));
    pGameOverItem->setFontName("MarkerFelt-Thin");
    pGameOverItem->setFontSize(30);
    pGameOverItem->setPosition(ccp(160, 200));
    
    CCMenu *pGameOverMenu = CCMenu::create(pGameOverItem, NULL);
    pGameOverMenu->setPosition(CCPointZero);
    this->addChild(pGameOverMenu, 4);
}

void MainGameLayer::btnGamePauseCallback(cocos2d::CCObject *pSender)
{
    if (!m_bIsGameOver)
    {
        m_bIsGameOver = true;
        
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        
        CCMenuItemFont *pStartMenuItem = CCMenuItemFont::create("START GAME", this, menu_selector(MainGameLayer::btnGameStartCallback));
        pStartMenuItem->setFontName("MarkerFelt-Thin");
        pStartMenuItem->setFontSize(30);
        pStartMenuItem->setPosition(ccp(160, RESOLUTION_HEIGHT / 2));
        
        m_pRestartMenu = CCMenu::create(pStartMenuItem, NULL);
        m_pRestartMenu->setPosition(CCPointZero);
        this->addChild(m_pRestartMenu, 4);
    }
}

void MainGameLayer::btnGameStartCallback(cocos2d::CCObject *pSender)
{
    if (m_bIsGameOver)
    {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        
        m_pRestartMenu->removeFromParentAndCleanup(true);
        m_pRestartMenu = NULL;
        
        m_bIsGameOver = false;
    }
}

void MainGameLayer::btnGameRestartCallback(cocos2d::CCObject *pSender)
{
    this->removeAllChildrenWithCleanup(true);

    // Reset game
    this->initDatas();
    this->loadBackground();
    this->loadPlayerPlane();
    this->madeBullets();
    this->resetBullets();
}

void MainGameLayer::playFireSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("bullet.mp3");
}

void MainGameLayer::smallPlaneDownSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("enemy1_down.mp3");
}

void MainGameLayer::mediumPlaneDownSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("enemy3_down.mp3");
}

void MainGameLayer::bigPlaneDownSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("enemy2_down.mp3");
}

void MainGameLayer::bigPlaneOutSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("enemy2_out.mp3");
}
