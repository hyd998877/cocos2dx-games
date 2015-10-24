//
//  GameLevelLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#include "GameLevelLayer.h"
#include "CCRadioMenu.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* CGameLevelLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    CGameLevelLayer *pLayer = CGameLevelLayer::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

bool CGameLevelLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/GameLevel.plist");
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::createWithSpriteFrameName("GameLevelBG.png");
    pBg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pBg);
    
    CCParticleSystemQuad *emitter = new CCParticleSystemQuad();
    emitter->autorelease();
    emitter->initWithFile("Image/Phoenix.plist");
    emitter->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(emitter, 1);
    
    // Radio Menu
    cocos2d::CCMenuItemImage *pLevelOne = cocos2d::CCMenuItemImage::create();
    pLevelOne->initWithTarget(this, menu_selector(CGameLevelLayer::menuSetLevelModeCallback));
    pLevelOne->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel1Normal.png"));
    pLevelOne->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel1Selected.png"));
    pLevelOne->setPosition(ccp(size.width*0.14f, size.height/2));
    pLevelOne->setTag(LEVEL_ONE);
    
    cocos2d::CCMenuItemImage *pLevelTwo = cocos2d::CCMenuItemImage::create();
    pLevelTwo->initWithTarget(this, menu_selector(CGameLevelLayer::menuSetLevelModeCallback));
    pLevelTwo->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel2Normal.png"));
    pLevelTwo->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel2Selected.png"));
    pLevelTwo->setPosition(ccp(size.width/2, size.height*0.8f));
    pLevelTwo->setTag(LEVEL_TWO);
    
    cocos2d::CCMenuItemImage *pLevelThree = cocos2d::CCMenuItemImage::create();
    pLevelThree->initWithTarget(this, menu_selector(CGameLevelLayer::menuSetLevelModeCallback));
    pLevelThree->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel3Normal.png"));
    pLevelThree->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("StartLevel3Selected.png"));
    pLevelThree->setPosition(ccp(size.width*0.86f, size.height/2));
    pLevelThree->setTag(LEVEL_THREE);
    
    CCRadioMenu *pRadioMenu = CCRadioMenu::create(pLevelOne, pLevelTwo, pLevelThree, NULL);
    pRadioMenu->setPosition(ccp(0,0));
    pRadioMenu->setSelectedItem_(pLevelOne);
    pLevelOne->selected();
    g_iGameLevel = LEVEL_ONE;
    this->addChild(pRadioMenu,2);
    
    m_pSun = CCParticleSun::create();
    this->addChild(m_pSun, 1);
    m_pSun->setTexture(CCTextureCache::sharedTextureCache()->addImage("Image/Fire.png") );
    m_pSun->setPosition(ccp(45, size.height/2));
    m_pSun->setStartSize(110);

    // Menu
    cocos2d::CCMenuItemImage *pStart = cocos2d::CCMenuItemImage::create();
    pStart->initWithTarget(this, menu_selector(CGameLevelLayer::menuSetLevelStartCallback));
    pStart->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GameStartNormal.png"));
    pStart->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GameStartSelected.png"));
    pStart->setPosition(ccp(size.width/2, size.height*0.2f));
    
    CCMenuItemImage *pBack = CCMenuItemImage::create();
    pBack->initWithTarget(this, menu_selector(CGameLevelLayer::menuBackCallback));
    pBack->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setAnchorPoint(ccp(1,0));
    pBack->setPosition(ccp(size.width, 0));
    
    CCMenu *pMenu = CCMenu::create(pStart, pBack, NULL);
    pMenu->setPosition(ccp(0, 0));
    this->addChild(pMenu, 3);
    
    return true;
}

void CGameLevelLayer::menuSetLevelModeCallback(cocos2d::CCObject* pSender)
{
    g_iGameLevel = ((CCNode*) pSender)->getTag();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	switch(g_iGameLevel)
	{
        case LEVEL_ONE:
            m_pSun->setPosition(ccp(45, size.height/2));
            break;
        case LEVEL_TWO:
            m_pSun->setPosition(ccp(size.width/2, size.height - 100));
            break;
        case LEVEL_THREE:
            m_pSun->setPosition(ccp(size.width - 45, size.height/2));
            break;
        default:
            break;
	}
}

void CGameLevelLayer::menuSetLevelStartCallback(cocos2d::CCObject* pSender)
{
    startFlipInterface(GAME_START);
}

void CGameLevelLayer::menuBackCallback(cocos2d::CCObject* pSender)
{
    startFlipInterface(GAME_MENU);
}