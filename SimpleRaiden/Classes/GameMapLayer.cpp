//
//  GameMapLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#include "GameMapLayer.h"
#include "GameConfig.h"

USING_NS_CC;

bool CGameMapLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    char szText[128];
    sprintf(szText, "Image/Map%d.png", g_iGameLevel);
    m_pMap = CCSprite::create(szText);
    m_pMap->setPosition(ccp(size.width/2, 600));
    this->addChild(m_pMap);
    
    m_pMap->runAction(CCMoveTo::create(100.0f, ccp(size.width/2, -(600-size.height))));
    
    return true;
}
    
void CGameMapLayer::shake()
{
    m_pMap->runAction(CCJumpBy::create(1.0f, ccp(0, 0), 8, 6));
}