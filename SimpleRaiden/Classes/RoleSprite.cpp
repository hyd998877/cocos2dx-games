//
//  RoleSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#include "RoleSprite.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "GameManagerLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;

int CRoleSprite::getDirection()
{
    float dx = this->getPosition().x - m_ptLastPos.x;
    m_ptLastPos = this->getPosition();
    
    if (dx < 0)
    {
        return LEFT;
    }
    else if (dx == 0)
    {
        return STRAIGHT;
    }
    
    return RIGHT;
}

void CRoleSprite::changeFlyAnimation(float dt)
{
    int iDirection = getDirection();
    if (m_iDirection != iDirection)
    {
        this->stopActionByTag(m_iDirection);
        setFlyAnimation(iDirection);
        m_iDirection = iDirection;
    }
}
    
void CRoleSprite::setFlyAnimation(int iDirection)
{
    int iBegin, iEnd;
    if (iDirection == STRAIGHT)
    {
        iBegin = 0;
        iEnd = m_iFlyStraightNum;
    }
    else
    {
        iBegin = m_iFlyStraightNum;
        iEnd = m_iFlyStraightNum + m_iFlyLeftNum;
        
        if (iDirection == RIGHT)
        {
            this->setFlipX(true);
        }
        else
        {
            this->setFlipX(false);
        }
    }
    
    CCArray *pArray = CCArray::create();
    char buf[100] = {0};
    for (int i = iBegin; i < iEnd; i++)
    {
        sprintf(buf, "Plane%d_%d.png", m_iType, i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buf);
        pArray->addObject(pFrame);
    }
    
    CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pArray, 0.2f);
    CCAnimate *pAnimate = CCAnimate::create(pAnimation);
    CCRepeatForever *pAction = CCRepeatForever::create(pAnimate);
    pAction->setTag(iDirection);
    
    this->runAction(pAction);
}

void CRoleSprite::hurt(int iHarm)
{
    if (this->isVisible() == false)
    {
        return;
    }
    
    m_iHp -= iHarm;
    if (m_iHp <= 0)
    {
        m_iLife--;
        
        this->setVisible(false);
        this->stopAllActions();
        
        this->unscheduleAllSelectors();
        
        SimpleAudioEngine::sharedEngine()->playEffect("Music/Explosion.mp3");
        explosion();
    }
}

void CRoleSprite::explosion()
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
    m_pExplosion = CCSprite::createWithSpriteFrame(pFrame);
    m_pExplosion->setPosition(this->getPosition());
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    pLayer->addChild(m_pExplosion);
    
    CCAnimation *pAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(EXPLOSION_ANIMATION_NAME);
    CCAnimate *pExplosionAnimate = CCAnimate::create(pAnimation);
    m_pExplosion->runAction(CCSequence::create(pExplosionAnimate, CCCallFunc::create(this, callfunc_selector(CRoleSprite::finishExplosionAnim)), NULL));
}

void CRoleSprite::finishExplosionAnim()
{
    m_pExplosion->removeFromParentAndCleanup(true);
    destroy(this);
}

void CRoleSprite::setDelFunc(cocos2d::CCNode *pSender)
{
    this->setVisible(false);
}