//
//  ItemSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-14.
//
//

#include "ItemSprite.h"
#include "GameConfig.h"
#include "GameManagerLayer.h"
#include "PlayerSprite.h"

using namespace std;
using namespace cocos2d;

CItemSprite* CItemSprite::create(int iType, float x, float y)
{
    CItemSprite *pRet = new CItemSprite();
    if (pRet && pRet->init(iType, x, y))
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

bool CItemSprite::init(int iType, float x, float y)
{
    m_iType = iType;
    resetItemDatas();
    
    char szPath[64];
    sprintf(szPath, m_szPathHeader.c_str(), 1);
    
    if (!CCSprite::initWithSpriteFrameName(szPath))
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setPosition(ccp(x, y));
    
    switch (m_iType)
    {
        case ITEM_GOLD:
        {
            CCAnimation *pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(GOLD_ANIMATION_NAME);
            this->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));
            
            CCMoveBy *pMove = CCMoveBy::create(5, ccp(0, -size.height - 40));
            this->runAction(CCSequence::create(pMove, CCCallFuncN::create(this, callfuncN_selector(CItemSprite::setDelFunc)), NULL));
            break;
        }
            
        case ITEM_RUBY:
        case ITEM_SAPPHIRE:
        case ITEM_AMETHYST:
            reloadAnimation();
            randomMove(0);
            
            this->schedule(schedule_selector(CItemSprite::randomMove), 1.0f);
            this->schedule(schedule_selector(CItemSprite::changeType), 5.0f);
            
            break;
            
        case ITEM_MISSILE:
            randomMove(0);
            this->schedule(schedule_selector(CItemSprite::randomMove), 1.0f);
            break;
    }
    
    this->scheduleUpdate();
    
    return true;
}

void CItemSprite::update(float dt)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pLayer != NULL)
    {
        CPlayerSprite *pPlayer = pLayer->getPlayer();
        if(pPlayer->boundingBox().intersectsRect(this->boundingBox()))
        {
            this->removeFromParentAndCleanup(true);
            pPlayer->gainItem(m_iType, m_iScore);
        }
    }
}

void CItemSprite::resetItemDatas()
{
    switch (m_iType)
    {
        case ITEM_GOLD:
            m_iScore = 5;
            m_szPathHeader = "Gold_%02d.png";
            break;
            
        case ITEM_RUBY:
            m_iScore = 10;
            m_szPathHeader = "Ruby_%02d.png";
            break;
            
        case ITEM_SAPPHIRE:
            m_iScore = 10;
            m_szPathHeader = "Sapphire_%02d.png";
            break;
            
        case ITEM_AMETHYST:
            m_iScore = 10;
            m_szPathHeader = "Amethyst_%02d.png";
            break;
            
        case ITEM_MISSILE:
            m_iScore = 10;
            m_szPathHeader = "MissileItem_%02d.png";
            break;
            
        default:
            m_iScore = 0;
            m_szPathHeader = "";
            break;
    }
}

#define REPEAT_ANIM_TAG 10
#define MOVE_ANIM_TAG 11

void CItemSprite::reloadAnimation()
{
    CCArray *pAnimFrames = CCArray::create();
    char buf[64] = { 0 };
    
    for (int i = 1; i < 5; i++)
    {
        sprintf(buf, m_szPathHeader.c_str(), i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        pAnimFrames->addObject(pFrame);
    }
    
    CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pAnimFrames, 0.2f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    CCRepeatForever *pRepeat = CCRepeatForever::create(pAnimate);
    pRepeat->setTag(REPEAT_ANIM_TAG);
    
    this->stopActionByTag(REPEAT_ANIM_TAG);
    this->runAction(pRepeat);
}

void CItemSprite::changeType(float dt)
{
    m_iType++;
    if (m_iType >= ITEM_MISSILE)
    {
        m_iType = ITEM_RUBY;
    }
    
    resetItemDatas();
    reloadAnimation();
}

void CItemSprite::randomMove(float dt)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int iWidth = this->getContentSize().width;
    int iHeight = this->getContentSize().height;
    float x, y, fDis;
    
    do
    {
        x = rand() % (int)(size.width - iWidth) + iWidth/2;
        y = rand() % (int)(size.height - iHeight) + iHeight/2;
        fDis = getDis(x, y);
    }
    while (fDis < 50);
    
    CCMoveTo *pMove = CCMoveTo::create(fDis / 50, ccp(x, y));
    
    this->stopActionByTag(MOVE_ANIM_TAG);
    this->runAction(pMove);
}

void CItemSprite::setDelFunc(cocos2d::CCNode *pSender)
{
    this->removeFromParentAndCleanup(true);
}
