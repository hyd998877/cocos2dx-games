//
//  ChangeBullet.cpp
//  PlaneBattle
//
//  Created by zhouf369 on 14-8-28.
//
//

#include "ChangeBullet.h"

using namespace cocos2d;

ChangeBullet::ChangeBullet()
{
    m_pProp = NULL;
    m_eBulletType = BULLET_TYPE_BULLET;
}

ChangeBullet::~ChangeBullet()
{
    
}
    
void ChangeBullet::initWithType(_BULLET_TYPE eType)
{
    m_eBulletType = eType;
    
    char buf[255];
    sprintf(buf, "enemy%d_fly_1.png", eType);
    m_pProp = CCSprite::createWithSpriteFrameName(buf);
    m_pProp->setPosition(ccp(arc4random()%268 + 23, 732));
}

void ChangeBullet::propAnimation()
{
    CCMoveTo *pMove1 = CCMoveTo::create(1.0f, ccp(m_pProp->getPosition().x, 250));
    CCMoveTo *pMove2 = CCMoveTo::create(.4f, ccp(m_pProp->getPosition().x, 252));
    CCMoveTo *pMove3 = CCMoveTo::create(1.0f, ccp(m_pProp->getPosition().x, 732));
    CCMoveTo *pMove4 = CCMoveTo::create(2.0f, ccp(m_pProp->getPosition().x, -55));
    
    m_pProp->runAction(CCSequence::create(pMove1, pMove2, pMove3, pMove4, NULL));
}