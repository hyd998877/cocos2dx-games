//
//  Runner.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-18.
//
//

#ifndef __MyParkour__Runner__
#define __MyParkour__Runner__

#include "cocos2d.h"
#include "Box2D.h"
#include "resources.h"
#include "CCPhysicsSprite.h"

enum RunnerState
{
    RunnerStateJumpUp,
    RunnerStateJumpDown,
    RunnerStateRunning,
    RunnerStateCrouch,
    RunnerStateIncredible,
    RunnerStateDie,
};

class Runner : public cocos2d::CCNode
{
public:
    
    Runner();
    virtual ~Runner();
    
    virtual void update(float dt);
    
    bool init(b2World *world, cocos2d::CCSpriteBatchNode *batchNode);
    
    static Runner* create(b2World *world, cocos2d::CCSpriteBatchNode *batchNode);
    
public:
    
    void jump();
    void crouch();
    void die();
    
    float getOffsetPx() { return 100.0f; }
    
    float getRunnerPosX()
    {
        if (m_pRunnerSprite != NULL)
        {
            return m_pRunnerSprite->getPositionX();
        }
        return 0.0f;
    }
    cocos2d::extension::CCPhysicsSprite* getRunnerSprite()
    {
        return m_pRunnerSprite;
    }
    
private:
    
    void restoreRunningStatus();
    void runAction(const char *action);
    void initAction();
    void initBody();
    void initShape(std::string type);
    
private:
    
    cocos2d::extension::CCPhysicsSprite *m_pRunnerSprite;
    cocos2d::CCAction *m_pRunningAction;
    cocos2d::CCSpriteBatchNode *m_pRunnerBatchNode;
    
    cocos2d::CCSize m_cRunnerSize;
    cocos2d::CCSize m_cCrouchSize;
    
    b2Body *m_pRunnerBody;
    
    b2World *m_pWorld;
    
    RunnerState m_eState;
};

#endif /* defined(__MyParkour__Runner__) */
