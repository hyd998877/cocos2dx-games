//
//  GameOverLayer.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-27.
//
//

#include "GameOverLayer.h"
#include "PlayScene.h"

bool GameOverLayer::init()
{
    if (!CCLayerColor::init()) {
        return false;
    }
    this->initWithColor(ccc4(0, 0, 0, 180));
    CCPoint center = ccp(CCDirector::sharedDirector()->getVisibleSize().width / 2, CCDirector::sharedDirector()->getVisibleSize().height / 2);
    
    CCMenuItemSprite* menuItem = CCMenuItemSprite::create(CCSprite::create("restart_n.png"), CCSprite::create("restart_s.png"), this, menu_selector(GameOverLayer::onRestart));
    // 必须以NULL结尾
    CCMenu* menu = CCMenu::create(menuItem, NULL);
    menu->setPosition(center);
    this->addChild(menu);
    
    return true;
}

void GameOverLayer::onRestart(CCObject *pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1, PlayScene::scene()));
}