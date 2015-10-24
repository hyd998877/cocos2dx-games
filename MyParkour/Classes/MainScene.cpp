//
//  MainScene.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-15.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "resources.h"
#include "PlayScene.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    CCScene *pScene = CCScene::create();
    
    MainScene *pSceneLayer = MainScene::create();
    pScene->addChild(pSceneLayer);
    
    return pScene;
}

bool MainScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    preloadMusic();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint ptCenter = ccp(winSize.width/2, winSize.height/2);
    
    CCSprite *pBg = CCSprite::create("MainBG.png");
    pBg->setPosition(ptCenter);
    this->addChild(pBg);
    
    CCMenuItemSprite *pStartBtn = CCMenuItemSprite::create(CCSprite::create("start_n.png"), CCSprite::create("start_s.png"), this, menu_selector(MainScene::onBtnPlay));
    
    CCMenu *pMenu = CCMenu::create(pStartBtn, NULL);
    pMenu->setPosition(ptCenter);
    this->addChild(pMenu);
    
    return true;
}

void MainScene::preloadMusic()
{
    SimpleAudioEngine *pAudioEngine = SimpleAudioEngine::sharedEngine();
    pAudioEngine->preloadBackgroundMusic(BACK_MUSIC);
    pAudioEngine->preloadEffect(JUMP_MUSIC);
    pAudioEngine->preloadEffect(CROUCH_MUSIC);
}

void MainScene::onBtnPlay()
{
    CCScene *pScene = CCTransitionFade::create(1.0f, PlayScene::scene());
//    CCScene *pScene = PlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}