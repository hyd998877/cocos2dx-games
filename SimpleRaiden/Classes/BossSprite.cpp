//
//  BossSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-17.
//
//

#include "BossSprite.h"
#include "GameConfig.h"
#include "GameManagerLayer.h"
#include "BulletSprite.h"

using namespace std;
using namespace cocos2d;

CBossSprite* CBossSprite::create(int iType)
{
    CBossSprite *pRet = new CBossSprite();
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

bool CBossSprite::init(int iType)
{
    char buf[100] = {0};
    
    m_iType = iType;
    sprintf(buf, "Boss%d_0.png", m_iType);
    
    if (!CCSprite::initWithSpriteFrameName(buf))
    {
        return false;
    }
    
    setBossDatas();
    
    this->scheduleUpdate();
    
    this->schedule(schedule_selector(CBossSprite::shoot), m_fShootSpace);
    this->schedule(schedule_selector(CBossSprite::shoot2), m_fShoot2Space);
    
    this->scheduleOnce(schedule_selector(CBossSprite::setBossMoveAction), 5.0f);
    
    return true;
}

void CBossSprite::onEnter()
{
    CCSprite::onEnter();
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    m_pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
}

void CBossSprite::update(float dt)
{
    if (!m_bHpChange2 && m_iHp < m_iHpMax*2/3.0f)
    {
        m_bHpChange2 = true;
        m_iBulletNum = 5;
    }
    if (!m_bHpChange1 && m_iHp < m_iHpMax/3.0f)
    {
        m_bHpChange1 = true;
        m_fShootSpace /= 2.0f;
        
        this->unschedule(schedule_selector(CBossSprite::shoot));
        this->schedule(schedule_selector(CBossSprite::shoot), m_fShootSpace);
    }
    
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

void CBossSprite::setBossDatas()
{
    switch (m_iType)
    {
        case BOSS_TYPE_ONE:
            m_iHpMax = 600;
            
            m_iBulletNum = 3;
            m_iBulletType = BULLET_MONSTER;
            m_fShootSpace = 3.0f;
            
            m_iBullet2Num = 18;
            m_iBullet2Type = BULLET_YELLOW;
            m_fShoot2Space = 5.0f;
            
            m_iMoveType = BOSS_MOVE_ONE;

            m_iScore = 50;
            break;
            
        case BOSS_TYPE_TWO:
            m_iHpMax = 800;
            
            m_iBulletNum = 3;
            m_iBulletType = BULLET_HELPER;
            m_fShootSpace = 3.0f;
            
            m_iBullet2Num = 18;
            m_iBullet2Type = BULLET_SILVER;
            m_fShoot2Space = 5.0f;
            
            m_iMoveType = BOSS_MOVE_TWO;
            
            m_iScore = 150;
            break;
            
        case BOSS_TYPE_THREE:
            m_iHpMax = 1200;
            
            m_iBulletNum = 3;
            m_iBulletType = BULLET_PURPLE;
            m_fShootSpace = 3.0f;
            
            m_iBullet2Num = 18;
            m_iBullet2Type = BULLET_GREEN;
            m_fShoot2Space = 5.0f;
            
            m_iMoveType = BOSS_MOVE_THREE;
            
            m_iScore = 350;
            break;
            
        default:
            break;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_iLife = 0;
    m_iHp = m_iHpMax;
    m_bHpChange1 = false;
    m_bHpChange2 = false;
    this->setPosition(ccp(size.width/2, size.height+this->getContentSize().height/2));
    this->runAction(CCMoveTo::create(5.0f, ccp(size.width/2, size.height*3/4)));
}

void CBossSprite::setBossMoveAction(float dt)
{
    CCPointArray *pArray = getBossMoveArray(m_iMoveType, this->getContentSize().height, this->getContentSize().width);
    CCCatmullRomTo *pAction = CCCatmullRomTo::create(20.0f, pArray);
    CCRepeatForever *pMove = CCRepeatForever::create(pAction);
    this->runAction(pMove);
}

void CBossSprite::shoot(float dt)
{
    CCPoint pos = this->getPosition();
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getBulletManager()->createBullet(ENEMY, m_iBulletType, m_iBulletNum, pos.x, pos.y);
    }
}

void CBossSprite::shoot2(float dt)
{
    CCPoint pos = this->getPosition();
    float fWidth = this->getContentSize().width;
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getBulletManager()->createBullet(ENEMY, m_iBullet2Type, m_iBullet2Num, pos.x - fWidth/4, pos.y);
        m_pGameLayer->getBulletManager()->createBullet(ENEMY, m_iBullet2Type, m_iBullet2Num, pos.x + fWidth/4, pos.y);
    }
}

void CBossSprite::destroy(cocos2d::CCNode *pSender)
{
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getPlayer()->addScore(m_iScore);
        m_pGameLayer->getPlayer()->showWinAnim();
    }

    this->removeFromParentAndCleanup(true);
}

