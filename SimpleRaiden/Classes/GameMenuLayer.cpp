//
//  GameMenuLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#include "GameMenuLayer.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* CGameMenuLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    CGameMenuLayer *pLayer = CGameMenuLayer::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CGameMenuLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/GameMenu.plist");
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::createWithSpriteFrameName("Background.png");
    pBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pBg);
    
    CCSprite* pStar = CCSprite::create("Image/Star.png");
    pStar->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pStar);
    
    CCActionInterval* actionFade = CCFadeOut::create(2.0f);
    CCActionInterval* actionFadeBack = actionFade->reverse();
    CCActionInterval* seq2 = (CCActionInterval*)CCSequence::create(actionFade, actionFadeBack, NULL);
    CCRepeatForever* pRepeatForever = CCRepeatForever::create(seq2);
    pStar->runAction(pRepeatForever);
    
    CCSprite* pTitle = CCSprite::create("Image/Title.png");
    pTitle->setPosition(ccp(size.width/2, size.height - 70));
    this->addChild(pTitle, 2);
    
    // Menu
    CCMenuItemImage *pMenuStart = CCMenuItemImage::create();
    pMenuStart->initWithTarget(this, menu_selector(CGameMenuLayer::menuStartCallback));
    pMenuStart->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartNormal.png"));
    pMenuStart->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartSelected.png"));
    pMenuStart->setPosition(ccp(size.width/2, 110));
    
    CCMenuItemImage *pMenuOption = CCMenuItemImage::create();
    pMenuOption->initWithTarget(this, menu_selector(CGameMenuLayer::menuOptionCallback));
    pMenuOption->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("OptionNormal.png"));
    pMenuOption->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("OptionSelected.png"));
    pMenuOption->setPosition(ccp(size.width/2, 75));
    
    CCMenuItemImage *pMenuExit = CCMenuItemImage::create();
    pMenuExit->initWithTarget(this, menu_selector(CGameMenuLayer::menuExitCallback));
    pMenuExit->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExitNormal.png"));
    pMenuExit->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ExitSelected.png"));
    pMenuExit->setPosition(ccp(size.width/2, 40));
    
    CCMenu *pMenu = CCMenu::create(pMenuStart,pMenuOption, pMenuExit, NULL);
    pMenu->setPosition(ccp(0, 0));
    this->addChild(pMenu, 3);
    
    CCSprite* pPlane = CCSprite::create("Image/PlaneIco.png");
    pPlane->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pPlane, 2);
    
    m_pMeteorolite = CCParticleSun::create();
    m_pMeteorolite->setTexture(CCTextureCache::sharedTextureCache()->addImage("Image/Fire.png"));
    this->addChild(m_pMeteorolite, 1);
    
    move(0);
    this->schedule(schedule_selector(CGameMenuLayer::move), 5.0f);
    
    return true;
}

void CGameMenuLayer::move(float dt)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int iStartX = rand() % (int)winSize.width + winSize.width/2;
    int iStartY = rand() % (int)winSize.height + winSize.height;
    
    int iEndX = rand() % (int)winSize.width;
    int iEndY = rand() % (int)(winSize.height/2) - winSize.height;
    
    m_pMeteorolite->setPosition(ccp(iStartX, iStartY));
    m_pMeteorolite->runAction(CCMoveTo::create(5.0f, ccp(iEndX, iEndY)));
}
    
void CGameMenuLayer::menuStartCallback(cocos2d::CCObject* pSender)
{
    startFlipInterface(GAME_LEVEL);
}

void CGameMenuLayer::menuOptionCallback(cocos2d::CCObject* pSender)
{
    
}

void CGameMenuLayer::menuExitCallback(cocos2d::CCObject* pSender)
{
    exit(0);
}

