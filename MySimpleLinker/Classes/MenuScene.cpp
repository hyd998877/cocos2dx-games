//
//  MenuScene.cpp
//  MySimpleLinker
//
//  Created by zhouf369 on 14-8-7.
//
//

#include "MenuScene.h"
#include "GameLayer.h"
#include "CCControlButton.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;

Menu::Menu()
{
    
}

Menu::~Menu()
{
    
}

cocos2d::CCScene* Menu::scene()
{
    CCScene *pScene = CCScene::create();
    
    Menu *pMenu = Menu::create();
    pScene->addChild(pMenu);
    
    return pScene;
}

bool Menu::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::create("bg.png");
    pBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pBg);
    
    CCLabelTTF *pTitle = CCLabelTTF::create("连连看", "Marker Felt", 48);
    pTitle->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pTitle);
    
    CCLabelTTF *pEmpty = CCLabelTTF::create("", "Arial", 10);
    CCScale9Sprite *pBtnBg = CCScale9Sprite::create("play.png");
    CCControlButton *pPlayBtn = CCControlButton::create(pEmpty, pBtnBg);
//    pPlayBtn->setContentSize(CCSizeMake(203, 89));
    pPlayBtn->setPreferredSize(CCSizeMake(203, 89));
    pPlayBtn->setPosition(ccp(size.width/2, size.height/2-80));
    pPlayBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(Menu::btnPlayCallback), CCControlEventTouchDown);
    this->addChild(pPlayBtn);
    
    return true;
}

void Menu::btnPlayCallback(CCObject *pSender)
{
    CCScene *pGameScene = GameLayer::scene();
    
    CCTransitionFade *pFadeScene = CCTransitionFade::create(1.0f, pGameScene, ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pFadeScene);
}

void Menu::btnCloseCallback(CCObject *pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}