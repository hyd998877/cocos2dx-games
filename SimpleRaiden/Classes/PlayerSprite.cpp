//
//  PlayerSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-20.
//
//

#include "PlayerSprite.h"
#include "GameConfig.h"
#include "GameManagerLayer.h"
#include "BulletSprite.h"
#include "SimpleAudioEngine.h"
#include "ItemSprite.h"
#include "BossSprite.h"
#include "BulletManagerLayer.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

CPlayerSprite* CPlayerSprite::create(int iType)
{
    CPlayerSprite *pRet = new CPlayerSprite();
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

bool CPlayerSprite::init(int iType)
{
    if (!CCSprite::initWithSpriteFrameName("Plane0_0.png"))
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Plane.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Shield.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Shoot.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Missile.plist");
    
    m_iType = iType;
    
    m_iHpMax = 10;
    m_iFlyStraightNum = 2;
    m_iFlyLeftNum = 2;
    m_iScore = 0;
    m_iLife = 3;
    
    m_iAddLifeScore = 100;
    
    m_bWin = false;
    m_bMissile = false;
    
    recreatePlayerPlane();
    
    return true;
}

void CPlayerSprite::onEnter()
{
    CCSprite::onEnter();
    
    registerWithTouchDispatcher();
}

void CPlayerSprite::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    pDispatcher->addTargetedDelegate(this, kCCMenuHandlerPriority + 1, true);
}

bool CPlayerSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bWin)
    {
        return false;
    }
    
    m_PosBack = pTouch->getLocation();
    return true;
}

void CPlayerSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint ptCurPos = pTouch->getLocation();
    
    float dx = ptCurPos.x - m_PosBack.x;
    float dy = ptCurPos.y - m_PosBack.y;
    m_PosBack = ptCurPos;
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint ptSelfPos = this->getPosition();
    ptSelfPos.x += dx;
    ptSelfPos.y += dy;
    
    if (ptSelfPos.x < this->getContentSize().width/2)
    {
        ptSelfPos.x = this->getContentSize().width/2;
    }
    else if (ptSelfPos.x > (winSize.width - this->getContentSize().width/2))
    {
        ptSelfPos.x = winSize.width - this->getContentSize().width/2;
    }
    
    if (ptSelfPos.y < this->getContentSize().height/2)
    {
        ptSelfPos.y = this->getContentSize().height/2;
    }
    else if (ptSelfPos.y > (winSize.height - this->getContentSize().height/2))
    {
        ptSelfPos.y = winSize.height - this->getContentSize().height/2;
    }
    this->setPosition(ptSelfPos);
}

void CPlayerSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void CPlayerSprite::recreatePlayerPlane()
{
    this->setVisible(true);
    
    m_fShootSpace = 0.2f;
    m_iBulletType = BULLET_ORANGE;
    m_iBulletNum = 3;
    m_iMissileNum = 2;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(size.width/2, -size.height/10));
    this->runAction(CCMoveBy::create(2.0f, ccp(0, size.height/5)));
    
    m_iHp = m_iHpMax;
    m_iDirection = STRAIGHT;
    
    setFlyAnimation(m_iDirection);
    setShield();
    setShoot();
    
    this->schedule(schedule_selector(CPlayerSprite::shoot), m_fShootSpace);
    this->schedule(schedule_selector(CPlayerSprite::changeFlyAnimation), 0.1f);
}



#define SHIELD_TAG_1 1000
#define SHIELD_TAG_2 1001

void CPlayerSprite::setShield()
{
    m_bShield = true;
    
    CCSprite *pShield1 = CCSprite::createWithSpriteFrameName("Shield_10.png");
    CCSprite *pShield2 = CCSprite::createWithSpriteFrameName("Shield_10.png");
    pShield1->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    pShield2->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height/2));
    
    CCArray *animFrames = CCArray::create();
    char str[64] = {0};
    for (int i = 1; i < 11; i++)
    {
        sprintf(str, "Shield_%02d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
    CCRepeatForever *pAciton = CCRepeatForever::create(CCAnimate::create(animation));
    pShield2->runAction(pAciton);
    
    this->addChild(pShield1, -1, SHIELD_TAG_1);
    this->addChild(pShield2, -1, SHIELD_TAG_2);
    
    this->scheduleOnce(schedule_selector(CPlayerSprite::clearShield), 10.0f);
}

void CPlayerSprite::clearShield()
{
    if (!m_bShield)
    {
        return;
    }
    
    m_bShield = false;
    this->removeChildByTag(SHIELD_TAG_1);
    this->removeChildByTag(SHIELD_TAG_2);
}

#define SHOOT_ANIM_TAG 1005

void CPlayerSprite::setShoot()
{
    CCSprite *pShoot = CCSprite::createWithSpriteFrameName("Shoot_01.png");
    pShoot->setPosition(ccp(this->getContentSize().width/2, this->getContentSize().height));
    
    CCArray *animFrames = CCArray::create();
    char str[64] = {0};
    for (int i = 1; i < 5; i++)
    {
        sprintf(str, "Shoot_%02d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, m_fShootSpace/4.0);
    CCRepeatForever *pAciton = CCRepeatForever::create(CCAnimate::create(animation));
    pShoot->runAction(pAciton);
    
    this->addChild(pShoot, -2, SHOOT_ANIM_TAG);
}

void CPlayerSprite::clearShoot()
{
    this->removeChildByTag(SHOOT_ANIM_TAG);
}

void CPlayerSprite::shoot(float dt)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Music/Shoot.mp3");
    
    CCPoint pos = this->getPosition();
    
    if (m_pGameLayer == NULL)
    {
        CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
        m_pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    }
    
    if (m_pGameLayer != NULL)
    {
        m_pGameLayer->getBulletManager()->createBullet(PLAYER, m_iBulletType, m_iBulletNum, pos.x, pos.y);
    }
    
}

void CPlayerSprite::destroy(cocos2d::CCNode *pSender)
{
    this->removeChild(m_pExplosion, true);
    
    clearShield();
    clearShoot();
    
    if (m_iLife <= 0)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/GameOver.mp3");
        startFlipInterface(GAME_OVER);
    }
    else
    {
        recreatePlayerPlane();
    }
}

void CPlayerSprite::gainItem(int iType, int iScore)
{
    m_iScore += iScore;
    switch (iType)
    {
        case ITEM_GOLD:
            SimpleAudioEngine::sharedEngine()->playEffect("Music/GainGold.mp3");
            break;
            
        case ITEM_RUBY:
            SimpleAudioEngine::sharedEngine()->playEffect("Music/GainJewel.mp3");
            if (m_iBulletNum < 6)
            {
                m_iBulletNum++;
            }
            break;
            
        case ITEM_SAPPHIRE:
            SimpleAudioEngine::sharedEngine()->playEffect("Music/GainJewel.mp3");
            if (m_bShield)
            {
                this->unschedule(schedule_selector(CPlayerSprite::clearShield));
                this->scheduleOnce(schedule_selector(CPlayerSprite::clearShield), 10.0f);
            }
            else
            {
                setShield();
            }
            break;
            
        case ITEM_AMETHYST:
            SimpleAudioEngine::sharedEngine()->playEffect("Music/GainJewel.mp3");
            m_iHp = m_iHpMax;
            break;
            
        case ITEM_MISSILE:
            SimpleAudioEngine::sharedEngine()->playEffect("Music/GainMissile.mp3");
            m_iMissileNum++;
            break;
            
        default:
            break;
    }
}

void CPlayerSprite::addScore(int iValue)
{
    m_iScore += iValue;
    while (m_iScore >= m_iAddLifeScore)
    {
        m_iLife++;
        m_iAddLifeScore += 100;
    }
}

void CPlayerSprite::showWinAnim()
{
    m_bWin = true;
    SimpleAudioEngine::sharedEngine()->playEffect("Music/Fly.mp3");
    
    this->unscheduleAllSelectors();
    this->stopAllActions();
    
    setFlyAnimation(STRAIGHT);
    clearShoot();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMoveBy *pMove = CCMoveBy::create(size.height/300.0f, ccp(0, size.height));
    this->runAction(CCSequence::create(pMove, CCCallFuncN::create(this, callfuncN_selector(CPlayerSprite::winAnimCallback)), NULL));
}

void CPlayerSprite::winAnimCallback(cocos2d::CCNode *pSender)
{
    clearShield();
    
    m_pGameLayer->startNextLevelGame();
}

void CPlayerSprite::shootMissile()
{
    if (m_bMissile || m_iMissileNum <= 0 || !this->isVisible())
    {
        return;
    }
    
    m_bMissile = true;
    m_iMissileNum--;
    
    createMissile();
}

void CPlayerSprite::createMissile()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint pos = this->getPosition();
    m_pMissile = CCSprite::createWithSpriteFrameName("Missile_00.png");
    m_pMissile->setPosition(ccp(pos.x, pos.y));
    m_pGameLayer->addChild(m_pMissile, 10);
    
    CCMoveBy *pMoveBy = CCMoveBy::create(0.2f, ccp(0, size.height/4));
    CCCallFuncN *Func= CCCallFuncN::create(this, callfuncN_selector(CPlayerSprite::MissileExplore));
    
    CCFiniteTimeAction *pMove = CCSequence::create(pMoveBy, Func, NULL);
    m_pMissile->runAction(pMove);
}

void CPlayerSprite::MissileExplore(cocos2d::CCNode *pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Music/MissileExplosion.mp3");
    
    CCArray *pAnimFrames = CCArray::create();
    char str[64] = {0};
    for (int i = 1; i < 13; i++)
    {
        sprintf(str, "Missile_%02d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        pAnimFrames->addObject(frame);
    }
    CCAnimate *pAnimate = CCAnimate::create(CCAnimation::createWithSpriteFrames(pAnimFrames, 0.07f));
    CCCallFuncN *Func = CCCallFuncN::create(this, callfuncN_selector(CPlayerSprite::MissileDestroy));
    CCFiniteTimeAction *pExplore = CCSequence::create(pAnimate, Func, NULL);
    m_pMissile->runAction(pExplore);
    
    m_pGameLayer->getGameMap()->shake();
    hurtEnemy();
}

void CPlayerSprite::MissileDestroy(cocos2d::CCNode *pSender)
{
    m_bMissile = false;
    m_pMissile->removeFromParentAndCleanup(true);
}

void CPlayerSprite::hurtEnemy()
{
    CEnemyManagerLayer *pEnemyLayer = m_pGameLayer->getEnemyManager();
    
    CCSpriteBatchNode *pEnemyList = pEnemyLayer->getEnemyList();
    CCObject *pObj = NULL;
    CCARRAY_FOREACH(pEnemyList->getChildren(), pObj)
    {
        if (dynamic_cast<CRoleSprite *>(pObj))
        {
            CRoleSprite *pEnemyPlane = (CRoleSprite *) pObj;
            pEnemyPlane->hurt(20);
        }
    }
    
    CBossSprite *pBoss = pEnemyLayer->getBoss();
    if (pBoss != NULL && pBoss->isVisible())
    {
        pBoss->hurt(20);
    }
    
    CBulletManagerLayer* pBulletLayer = m_pGameLayer->getBulletManager();
    pBulletLayer->removeAllChildren();
}

