//
//  GameManagerLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#include "GameManagerLayer.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "GameMessageLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* CGameManagerLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    CGameManagerLayer *pLayer = CGameManagerLayer::create();
    pLayer->setTag(GAME_MANAGER_LAYER_TAG);
    pScene->addChild(pLayer);
    
    return pScene;
}

#define MAP_LAYER_TAG 100
#define ITEM_LAYER_TAG 101
#define BULLET_LAYER_TAG 102
#define ENEMY_LAYER_TAG 103
#define PLAYER_LAYER_TAG 104
#define MESSAGE_LAYER_TAG 105

bool CGameManagerLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    char szPath[32];
    sprintf(szPath,"Music/Stage%d.mp3", g_iGameLevel);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szPath, true);
    
    srand(time(NULL));
    
    // Load animation
    loadExplosionAnim();
    loadItemsAnim();
    
    // Load game
    
    m_pGameMap = CGameMapLayer::create();
    this->addChild(m_pGameMap, 0, MAP_LAYER_TAG);
    
    m_pItemManager = CItemManagerLayer::create();
    this->addChild(m_pItemManager, 1, ITEM_LAYER_TAG);
    
    m_pBulletManager = CBulletManagerLayer::create();
    this->addChild(m_pBulletManager, 2, BULLET_LAYER_TAG);
    
    m_pEnemyManager = CEnemyManagerLayer::create();
    this->addChild(m_pEnemyManager, 3, ENEMY_LAYER_TAG);
    
    m_pPlayer = (CPlayerSprite*) CPlayerSprite::create(PLAYER);
    this->addChild(m_pPlayer, 4, PLAYER_LAYER_TAG);
    
    CGameMessageLayer *pGameMessage = CGameMessageLayer::create();
    this->addChild(pGameMessage, 5, MESSAGE_LAYER_TAG);
    
    // Menu
    CCMenuItemImage *pBack = CCMenuItemImage::create();
    pBack->initWithTarget(this, menu_selector(CGameManagerLayer::menuBackCallback));
    pBack->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Back.png"));
    pBack->setPosition(ccp(size.width - 39, 21));
    
    CCMenu *pMenu = CCMenu::create(pBack, NULL);
    pMenu->setPosition(ccp(0, 0));
    this->addChild(pMenu, 6, 6);
    
    this->scheduleUpdate();
    
    return true;
}

void CGameManagerLayer::startNextLevelGame()
{
    g_iGameLevel++;
    if (g_iGameLevel > LEVEL_THREE)
    {
        g_iGameLevel = LEVEL_ONE;
    }
    
    char szPath[32];
    sprintf(szPath,"Music/Stage%d.mp3", g_iGameLevel);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(szPath, true);
    
    this->removeChildByTag(MAP_LAYER_TAG, true);
    m_pGameMap = CGameMapLayer::create();
    this->addChild(m_pGameMap, 0, MAP_LAYER_TAG);
    
    this->removeChildByTag(ITEM_LAYER_TAG, true);
    m_pItemManager = CItemManagerLayer::create();
    this->addChild(m_pItemManager, 1, ITEM_LAYER_TAG);
    
    this->removeChildByTag(BULLET_LAYER_TAG, true);
    m_pBulletManager = CBulletManagerLayer::create();
    this->addChild(m_pBulletManager, 2, BULLET_LAYER_TAG);
    
    this->removeChildByTag(ENEMY_LAYER_TAG, true);
    m_pEnemyManager = CEnemyManagerLayer::create();
    this->addChild(m_pEnemyManager, 3, ENEMY_LAYER_TAG);
    
    this->removeChildByTag(PLAYER_LAYER_TAG, true);
    m_pPlayer = (CPlayerSprite*) CPlayerSprite::create(PLAYER);
    this->addChild(m_pPlayer, 4, PLAYER_LAYER_TAG);
}


void CGameManagerLayer::menuBackCallback(cocos2d::CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/Title.mp3", true);
    startFlipInterface(GAME_LEVEL);
}