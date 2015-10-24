//
//  EnemyManagerLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-17.
//
//

#include "EnemyManagerLayer.h"
#include "GameConfig.h"
#include "EnemySprite.h"
#include "BossSprite.h"

using namespace cocos2d;

bool CEnemyManagerLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Plane.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Boss.plist");
    
    m_pEnemyList = CCSpriteBatchNode::create("Image/Plane.png");
    this->addChild(m_pEnemyList);
    
    this->schedule(schedule_selector(CEnemyManagerLayer::createEnemy), 1.0f);
    this->scheduleOnce(schedule_selector(CEnemyManagerLayer::createBoss), 100.0f);
    
    return true;
}
    
void CEnemyManagerLayer::createEnemy(float dt)
{
    int iEnemyType = rand() % 3 + 1;
    CEnemySprite *pEnemy = (CEnemySprite *) CEnemySprite::create(iEnemyType);
    m_pEnemyList->addChild(pEnemy);
}

#define BOSS_TAG 100

void CEnemyManagerLayer::createBoss(float dt)
{
    this->unschedule(schedule_selector(CEnemyManagerLayer::createEnemy));
    
    int iBossType = g_iGameLevel - 1;
    CBossSprite *pBoss = CBossSprite::create(iBossType);
    this->addChild(pBoss, 1, BOSS_TAG);
}

CBossSprite* CEnemyManagerLayer::getBoss()
{
    CBossSprite *pBoss = (CBossSprite *) this->getChildByTag(BOSS_TAG);
    return pBoss;
}
