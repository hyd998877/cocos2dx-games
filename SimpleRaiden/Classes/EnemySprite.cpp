//
//  EnemySprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-16.
//
//

#include "EnemySprite.h"
#include "GameConfig.h"
#include "GameManagerLayer.h"
#include "ItemSprite.h"
#include "BulletSprite.h"

using namespace std;
using namespace cocos2d;

CEnemySprite* CEnemySprite::create(int iType)
{
    CEnemySprite *pRet = new CEnemySprite();
    if (pRet && pRet->init(iType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    
    return NULL;
}

bool CEnemySprite::init(int iType)
{
    if (!CCSprite::initWithSpriteFrameName("Plane1_0.png"))
    {
        return false;
    }
    
    m_iType = iType;
    m_iDirection = STRAIGHT;
    
    setEnemyDatas();
    setFlyAnimation(m_iDirection);
    
    setEnemyMoveAction(0);
    
    this->scheduleUpdate();
    this->schedule(schedule_selector(CEnemySprite::shoot), m_fShootSpace);
    this->schedule(schedule_selector(CEnemySprite::changeFlyAnimation), 0.1f);
    
    m_pGameLayer = NULL;
    
    return true;
}

void CEnemySprite::onEnter()
{
    CCSprite::onEnter();
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    m_pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
}

void CEnemySprite::update(float dt)
{
    if (m_pGameLayer != NULL)
    {
        CPlayerSprite *pPlayer = m_pGameLayer->getPlayer();
        if(pPlayer->isShield() == false)
        {
            if(pPlayer->boundingBox().intersectsRect(this->boundingBox()))
            {
                hurt(1);
                pPlayer->hurt(1);
            }
        }
    }
}

void CEnemySprite::setEnemyDatas()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_iLife = 0;
    
    switch (m_iType)
    {
        case ENEMY_TYPE_ONE:
            m_ptLastPos.x = (float) (rand()%(int)(size.width-64) + 32);
            m_ptLastPos.y = size.height + 32;
            m_iMoveType = ENEMY_MOVE_ONE;
            m_iHpMax = 15;
            m_iFlyStraightNum = 1;
            m_iFlyLeftNum = 1;
            m_fShootSpace = 4.0f;
            m_iBulletType = BULLET_BLUE;
            m_iScore = 1;
            switch (g_iGameLevel)
            {
                case LEVEL_ONE:
                    m_iBulletNum = 3;
                    break;
                    
                case LEVEL_TWO:
                    m_iBulletNum = 9;
                    break;
                    
                case LEVEL_THREE:
                    m_iBulletNum = 18;
                    break;
            }
            break;
            
        case ENEMY_TYPE_TWO:
            m_ptLastPos.x = -32;
            m_ptLastPos.y = float(rand()%(int)(size.height/2) + size.height/2);
            m_iMoveType = ENEMY_MOVE_TWO;
            m_iHpMax = 10;
            m_iFlyStraightNum = 1;
            m_iFlyLeftNum = 1;
            m_fShootSpace = 2.0f;
            m_iBulletType = BULLET_BLUE;
            m_iScore = 1;
            switch (g_iGameLevel)
            {
                case LEVEL_ONE:
                    m_iBulletNum = 1;
                    break;
                    
                case LEVEL_TWO:
                    m_iBulletNum = 2;
                    break;
                    
                case LEVEL_THREE:
                    m_iBulletNum = 2;
                    break;
            }
            break;
            
        case ENEMY_TYPE_THREE:
            m_ptLastPos.x = size.width + 32;
            m_ptLastPos.y = float(rand()%(int)(size.height/2) + size.height/2);
            m_iMoveType = ENEMY_MOVE_THREE;
            m_iHpMax = 10;
            m_iFlyStraightNum = 1;
            m_iFlyLeftNum = 1;
            m_fShootSpace = 2.0f;
            m_iBulletType = BULLET_BLUE;
            m_iScore = 1;
            switch (g_iGameLevel)
            {
                case LEVEL_ONE:
                    m_iBulletNum = 2;
                    break;
                    
                case LEVEL_TWO:
                    m_iBulletNum = 2;
                    break;
                    
                case LEVEL_THREE:
                    m_iBulletNum = 3;
                    break;
            }
            break;
            
        default:
            break;
    }
    
    m_iHp = m_iHpMax;
    this->setPosition(m_ptLastPos);
}

void CEnemySprite::setEnemyMoveAction(float dt)
{
    CCPointArray *pArray = getEnemyMoveArray(m_iMoveType);
    this->runAction(CCSequence::create(CCCardinalSplineBy::create(10, pArray, 0), CCCallFuncN::create(this, callfuncN_selector(CEnemySprite::setDelFunc)), NULL));
}

void CEnemySprite::shoot(float dt)
{
    CCPoint pos = this->getPosition();
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getBulletManager()->createBullet(ENEMY, m_iBulletType, m_iBulletNum, pos.x, pos.y);
    }
}

void CEnemySprite::destroy(cocos2d::CCNode *pSender)
{
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getPlayer()->addScore(m_iScore);
    }
    
    CCPoint pos = this->getPosition();
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    CItemManagerLayer *pItemManagerLayer = pLayer->getItemManager();
    switch (rand() % 20)
    {
        case 0:
            // ITEM_RUBY, ITEM_SAPPHIRE, ITEM_AMETHYST
            pItemManagerLayer->createItem(rand()%3 + 1, pos.x, pos.y);
            break;
            
        case 1:
            // ITEM_MISSILE
            pItemManagerLayer->createItem(ITEM_MISSILE, pos.x, pos.y);
            break;
            
        default:
            // ITEM_GOLD
            pItemManagerLayer->createItem(ITEM_GOLD, pos.x, pos.y);
            break;
    }
    
    this->removeFromParentAndCleanup(true);
}

void CEnemySprite::setDelFunc(cocos2d::CCNode *pSender)
{
    this->removeFromParentAndCleanup(true);
}
