//
//  LoadLogo.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#include "LoadLogo.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* CLoadLogoLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    CLoadLogoLayer *pLayer = CLoadLogoLayer::create();
    pScene->addChild(pLayer);

    return pScene;
}

bool CLoadLogoLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSprite *pImgBg = CCSprite::create("Image/LoadLogo.png");
    pImgBg->setPosition(ccp(RESOLUTION_WIDTH/2, RESOLUTION_HEIGHT/2));
    this->addChild(pImgBg);
    
    this->scheduleOnce(schedule_selector(CLoadLogoLayer::transitionLayerCallback), 0.2f);
    
    return true;
}

void CLoadLogoLayer::transitionLayerCallback(float dt)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Title.mp3", true);
    
    startFlipInterface(GAME_MENU);
}