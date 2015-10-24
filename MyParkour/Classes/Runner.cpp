//
//  Runner.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-18.
//
//

#include "Runner.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension;

#define RUNNING_ANIMATION "running"
#define JUMPUP_ANIMATION "jumpUp"
#define JUMPDOWN_ANIMATION "jumpDown"
#define CROUCH_ANIMATION "crouch"

Runner::Runner()
{
    m_pRunnerSprite = NULL;
    m_pRunningAction = NULL;
    m_pRunnerBatchNode = NULL;
    
    m_pWorld = NULL;
}

Runner::~Runner()
{
    
}

Runner* Runner::create(b2World *world, cocos2d::CCSpriteBatchNode *batchNode)
{
    Runner *pRunner = new Runner();
    if (pRunner && pRunner->init(world, batchNode))
    {
        pRunner->autorelease();
        return pRunner;
    }
    else
    {
        delete pRunner;
        pRunner = NULL;
        
        return NULL;
    }
}

bool Runner::init(b2World *world, cocos2d::CCSpriteBatchNode *batchNode)
{
    if (!CCNode::init())
    {
        return false;
    }
    
    m_eState = RunnerStateRunning;
    
    this->m_pWorld = world;
    this->m_pRunnerBatchNode = batchNode;
    
    m_pRunnerSprite = CCPhysicsSprite::createWithSpriteFrameName(runner0);
    m_cRunnerSize = m_pRunnerSprite->getContentSize();
    
    CCSprite *pCrouchSprite = CCSprite::createWithSpriteFrameName(runnerCrouch);
    m_cCrouchSize = pCrouchSprite->getContentSize();
    
    initAction();
    initBody();
    initShape("running");
    
    runAction(RUNNING_ANIMATION);
    
    m_pRunnerBatchNode->addChild(m_pRunnerSprite);
    
    return true;
}

void Runner::update(float dt)
{
    if (m_eState == RunnerStateDie)
    {
        return;
    }
    
    b2Vec2 vel = m_pRunnerBody->GetLinearVelocity();
    if (m_eState == RunnerStateJumpUp)
    {
        if (vel.y <= 0.0f)
        {
            m_pRunnerSprite->stopAllActions();
            runAction(JUMPDOWN_ANIMATION);
            
            m_eState = RunnerStateJumpDown;
        }
    }
    else if (m_eState == RunnerStateJumpDown)
    {
        if (vel.y == 0)
        {
            m_pRunnerSprite->stopAllActions();
            runAction(RUNNING_ANIMATION);
            
            m_eState = RunnerStateRunning;
        }
    }
}

void Runner::jump()
{
    if (m_eState == RunnerStateDie)
    {
        return;
    }
    
    if (m_eState == RunnerStateRunning)
    {
        float fImpluse = m_pRunnerBody->GetMass() * 7;
        m_pRunnerBody->ApplyLinearImpulse(b2Vec2(0, fImpluse), m_pRunnerBody->GetWorldCenter());
        
        m_eState = RunnerStateJumpUp;
        
        m_pRunnerSprite->stopAllActions();
        runAction(JUMPUP_ANIMATION);
        
        SimpleAudioEngine::sharedEngine()->playEffect(JUMP_MUSIC);
    }
}

void Runner::crouch()
{
    if (m_eState == RunnerStateDie)
    {
        return;
    }
    
    if (m_eState == RunnerStateRunning)
    {
        this->initShape("crouch");
        
        m_eState = RunnerStateCrouch;
        
        m_pRunnerSprite->stopAllActions();
        runAction(CROUCH_ANIMATION);
        
        scheduleOnce(schedule_selector(Runner::restoreRunningStatus), 1.2f);
        
        SimpleAudioEngine::sharedEngine()->playEffect(CROUCH_MUSIC);
    }
}

void Runner::die()
{
    m_eState = RunnerStateDie;
    
    m_pRunnerSprite->stopAllActions();
    unscheduleUpdate();
}

void Runner::restoreRunningStatus()
{
    initShape("running");
    
    m_pRunnerSprite->stopAllActions();
    runAction(RUNNING_ANIMATION);
    
    m_eState = RunnerStateRunning;
}

void Runner::runAction(const char *action)
{
    CCAnimation *pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(action);
    m_pRunnerSprite->runAction(CCAnimate::create(pAnimation));
}

void Runner::initAction()
{
    CCArray *pAnimateFrames = CCArray::create();
    char buf[50] = {0};
    
    // Running animation
    for (int i = 0; i < 8; i++)
    {
        sprintf(buf, "runner%d.png", i);
        pAnimateFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
    }
    CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pAnimateFrames, 0.1);
    pAnimation->setLoops(-1);
    pAnimation->setRestoreOriginalFrame(true);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimation, RUNNING_ANIMATION);
    
    // Jump up animation
    pAnimateFrames->removeAllObjects();
    for (int i = 0; i < 4; i++)
    {
        sprintf(buf, "runnerJumpUp%d.png", i);
        pAnimateFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
    }
    CCAnimation *pAnimationJumpUp = CCAnimation::createWithSpriteFrames(pAnimateFrames, 0.2);
    pAnimationJumpUp->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimationJumpUp, JUMPUP_ANIMATION);
    
    // Jump down animation
    pAnimateFrames->removeAllObjects();
    for (int i = 0; i < 2; i++)
    {
        sprintf(buf, "runnerJumpDown%d.png", i);
        pAnimateFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf));
    }
    CCAnimation *pAnimationJumpDown = CCAnimation::createWithSpriteFrames(pAnimateFrames, 0.3);
    pAnimationJumpDown->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimationJumpDown, JUMPDOWN_ANIMATION);
    
    // Crouch animation
    pAnimateFrames->removeAllObjects();
    pAnimateFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runnerCrouch0.png"));
    CCAnimation *pAnimationCrouch = CCAnimation::createWithSpriteFrames(pAnimateFrames, 0.3);
    pAnimationCrouch->setRestoreOriginalFrame(false);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(pAnimationCrouch, CROUCH_ANIMATION);
}

void Runner::initBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearVelocity = b2Vec2(5, 0);
    bodyDef.position = b2Vec2(getOffsetPx() / RATIO, (GROUND_HEIGHT + m_cRunnerSize.height/2) / RATIO);
    
    m_pRunnerBody = m_pWorld->CreateBody(&bodyDef);
    
    // Link the sprite to the body just created!
    m_pRunnerSprite->setB2Body(m_pRunnerBody);
    m_pRunnerSprite->setPTMRatio(RATIO);
}

// 这个Runner的碰撞区域需要优化，因为Runner的图片是一个矩形，但是人体是一个不规则的多边形
// 简单用图片的边框来做碰撞区域，碰撞区域比实际人体碰撞区域大
void Runner::initShape(std::string type)
{
    // Destroy the fixture before.
    if (m_pRunnerBody->GetFixtureList() != NULL)
    {
        m_pRunnerBody->DestroyFixture(m_pRunnerBody->GetFixtureList());
    }
    
    b2PolygonShape shape;
    
    if (type == "running")
    {
        m_pRunnerBody->SetTransform(b2Vec2(m_pRunnerBody->GetPosition().x, (GROUND_HEIGHT + m_cRunnerSize.height/2) / RATIO), m_pRunnerBody->GetAngle());
        
        // Define the shape of the runner
        shape.SetAsBox(m_cRunnerSize.width / 2 / RATIO, m_cRunnerSize.height / 2 / RATIO);
    }
    else
    {
        m_pRunnerBody->SetTransform(b2Vec2(m_pRunnerBody->GetPosition().x, (GROUND_HEIGHT + m_cCrouchSize.height/2) / RATIO), m_pRunnerBody->GetAngle());
        
        shape.SetAsBox(m_cCrouchSize.width / 2 / RATIO, m_cCrouchSize.height / 2 / RATIO);
    }
    
    b2FixtureDef fixDef;
    fixDef.shape = &shape;
    fixDef.friction = 0.0f;
    
    m_pRunnerBody->CreateFixture(&fixDef);
}

