//
//  Icon.cpp
//  MyLinker
//
//  Created by zhouf369 on 14-8-15.
//
//

#include "Icon.h"

using namespace cocos2d;

Icon::Icon()
{
    
}

Icon::~Icon()
{
    
}

bool Icon::init()
{
    if (!CCSprite::init())
    {
        return false;
    }
    
    return true;
}

void Icon::initSkinWithType(const int &type)
{
    char buf[255];
    
    m_iIconType = type;
    if (type < 0)
    {
        m_iIconType = 0;
    }
    else if (type > 35)
    {
        m_iIconType = 35;
    }
    
    setDestroyed(false);
    
    sprintf(buf, "point%d.png", m_iIconType);
    this->initWithSpriteFrameName(buf);
    setAnchorPoint(ccp(0.0f, 0.0f));
    
//    CCFadeIn *pFadeIn = CCFadeIn::create(1.5f);
//    this->runAction(pFadeIn);
}

void Icon::changeIconViewWithType(ICON_SEL type)
{
    char buff[256];
    if (type == SELECTED)
    {
        sprintf(buff, "point_h_%d.png", m_iIconType);
    }
    else
    {
        sprintf(buff, "point%d.png", m_iIconType);
    }
    this->initWithSpriteFrameName(buff);
    setAnchorPoint(ccp(0.0f, 0.0f));
}

void Icon::updatePositionInParent()
{
    CCPoint ptPos = ccp(m_iCol * getContentSize().width, m_iRow * getContentSize().height);
    this->setPosition(ptPos);
}

void Icon::fadeOutAction(float dt)
{
    dispose();
    
    CCLog("Fade out one!");
}

void Icon::dispose()
{
    if (this->getParent() != NULL)
    {
        this->removeFromParentAndCleanup(true);
    }
}

void Icon::playAction()
{
    CCScaleTo *pScale = CCScaleTo::create(0.5f, 1.05f);
    CCScaleTo *pScaleBack = CCScaleTo::create(0.5f, 0.95f);
    
    this->runAction(CCRepeatForever::create(CCSequence::create(pScale, pScaleBack, NULL)));
}

void Icon::unplayAction()
{
    this->stopAllActions();
    
    CCScaleTo *pScaleBack = CCScaleTo::create(0.5f, 1.0f);
    this->runAction(CCSequence::create(pScaleBack, NULL));
}

const int& Icon::getIconType()
{
    return m_iIconType;
}

