//
//  GameOverLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#include "GameOverLayer.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* CGameOverLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    CGameOverLayer *pLayer = CGameOverLayer::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CGameOverLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::create("Image/GameOver.png");
    pBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pBg);
    
    CCMenuItemImage *pBack = CCMenuItemImage::create();
    pBack->initWithTarget(this, menu_selector(CGameOverLayer::menuBackCallback));
    pBack->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setPosition(ccp(size.width - 39, 21));
    
    CCMenu *pMenu = CCMenu::create(pBack, NULL);
    pMenu->setPosition(ccp(0, 0));
    this->addChild(pMenu, 6);
    
    return true;
}

void CGameOverLayer::menuBackCallback(cocos2d::CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Title.mp3", false);
    startFlipInterface(GAME_MENU);
}