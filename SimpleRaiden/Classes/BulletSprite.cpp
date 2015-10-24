//
//  BulletSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#include "BulletSprite.h"
#include "GameConfig.h"
#include "GameManagerLayer.h"
#include "EnemyManagerLayer.h"
#include "RoleSprite.h"
#include "BossSprite.h"
#include "PlayerSprite.h"

using namespace std;
using namespace cocos2d;

CBulletSprite* CBulletSprite::create(int iPlaneType, int iType, int iAllNum, int iCurNum, float x, float y)
{
    CBulletSprite *pRet = new CBulletSprite();
    if (pRet && pRet->init(iPlaneType, iType, iAllNum, iCurNum, x, y))
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

bool CBulletSprite::init(int iPlaneType, int iType, int iAllNum, int iCurNum, float x, float y)
{
    m_iPlaneType = iPlaneType;
    m_iType = iType;
    
    resetBulletDatas();
    
    if (!CCSprite::initWithSpriteFrameName(m_szFilePath.c_str()))
    {
        return false;
    }
    
    this->setPosition(ccp(x, y));
    
    setMoveTrack(iAllNum, iCurNum);
    
    this->scheduleUpdate();
    
    return true;
}
    
void CBulletSprite::update(float dt)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pLayer == NULL)
    {
        return;
    }
    
    if (m_iPlaneType == PLAYER)
    {
        CEnemyManagerLayer *pEnemyLayer = pLayer->getEnemyManager();
        
        CCSpriteBatchNode *pEnemyList = pEnemyLayer->getEnemyList();
        CCObject *pObj = NULL;
        CCARRAY_FOREACH(pEnemyList->getChildren(), pObj)
        {
            if (dynamic_cast<CRoleSprite *>(pObj))
            {
                CRoleSprite *pEnemyPlane = (CRoleSprite *) pObj;
                if (pEnemyPlane->isVisible() && pEnemyPlane->boundingBox().intersectsRect(this->boundingBox()))
                {
                    this->removeFromParentAndCleanup(true);
                    pEnemyPlane->hurt(m_iHarm);
                }
            }
        }
        
        CBossSprite *pBoss = pEnemyLayer->getBoss();
        if (pBoss != NULL && pBoss->isVisible())
        {
            if (pBoss->boundingBox().intersectsRect(this->boundingBox()))
            {
                this->removeFromParentAndCleanup(true);
                pBoss->hurt(m_iHarm);
            }
        }
    }
    else
    {
        CPlayerSprite *pPlayer = pLayer->getPlayer();
        if(!pPlayer->isWin())
        {
            if(this->boundingBox().containsPoint(pPlayer->getPosition()))
            {
                this->removeFromParentAndCleanup(true);
                if(pPlayer->isShield() == false)
                {
                    pPlayer->hurt(m_iHarm);
                }
            }
        }
    }
}

void CBulletSprite::resetBulletDatas()
{
    switch (m_iType)
    {
        case BULLET_ORANGE:
            m_iHarm = 1;
            m_szFilePath = "orangeCircle.png";
            break;
            
        case BULLET_BLUE:
            m_iHarm = 1;
            m_szFilePath = "blueBall2.png";
            break;
            
        case BULLET_MONSTER:
            m_iHarm = 1;
            m_szFilePath = "monsterBullet1.png";
            break;
            
        case BULLET_HELPER:
            m_iHarm = 1;
            m_szFilePath = "helperBullet.png";
            break;
            
        case BULLET_PURPLE:
            m_iHarm = 1;
            m_szFilePath = "purpleCircle.png";
            break;
            
        case BULLET_YELLOW:
            m_iHarm = 1;
            m_szFilePath = "yellowBall.png";
            break;
            
        case BULLET_SILVER:
            m_iHarm = 1;
            m_szFilePath = "silverBall.png";
            break;
            
        case BULLET_GREEN:
            m_iHarm = 1;
            m_szFilePath = "greenBall.png";
            break;
            
        default:
            m_iHarm = 0;
            m_szFilePath = "";
            break;
    }
}

void CBulletSprite::setMoveTrack(int iAllNum, int iCurNum)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCActionInterval *pAction;
    
    if (m_iPlaneType == PLAYER)
    {
        float x, y;
        if (m_iType == BULLET_YELLOW)
        {
            x = 0;
            y = size.height/5;
        }
        else
        {
            x = (iCurNum - 1) * 20 - (iAllNum - 1) * 10;
            y = size.height;
        }
        pAction = CCMoveBy::create(1.0f, ccp(x, y));
    }
    else
    {
        float iSpan = 20;
        float r = size.height*5/4;
        float iRadians = CC_DEGREES_TO_RADIANS(270 + (iCurNum - iAllNum/2 - 0.5 - iAllNum%2/2.0) * iSpan);
        float x = r*cos(iRadians);
        float y = r*sin(iRadians);
        pAction = CCMoveBy::create(4.0f, ccp(x, y));
    }
    
    this->runAction(CCSequence::create(pAction, CCCallFuncN::create(this, callfuncN_selector(CBulletSprite::setDelFunc)), NULL));
}

void CBulletSprite::setDelFunc(cocos2d::CCNode *pSender)
{
    // The bullet has moved out of the screen.
    this->removeFromParentAndCleanup(true);
}

