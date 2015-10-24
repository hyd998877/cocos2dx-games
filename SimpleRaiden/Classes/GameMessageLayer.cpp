//
//  GameMessageLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-21.
//
//

#include "GameMessageLayer.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "GameManagerLayer.h"

USING_NS_CC;
using namespace CocosDenshion;

bool CGameMessageLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Message.plist");
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBox = CCSprite::createWithSpriteFrameName("Box.png");
    pBox->setPosition(ccp(size.width/2, size.height - pBox->getContentSize().height/2));
    this->addChild(pBox, 0);
    
    m_pScore = CCLabelAtlas::create("0", "Image/Num.plist");
    this->addChild(m_pScore, 0);
    m_pScore->setPosition(ccp(100, size.height - 24));
    
    m_pLife = CCLabelAtlas::create("3", "Image/Num.plist");
    this->addChild(m_pLife, 0);
    m_pLife->setPosition(ccp(236, size.height - 20));
    
    m_pHp = CCSprite::createWithSpriteFrameName("Hp.png");
    this->addChild(m_pHp, 0);
    m_pHp->setAnchorPoint(ccp(0, 0));
    m_iWidth = m_pHp->getContentSize().width;
    m_iHeight = m_pHp->getContentSize().height;
    m_pHp->setPosition(ccp(97, size.height - 49));
    m_fMinX = m_pHp->getTextureRect().getMinX();
    m_fMinY = m_pHp->getTextureRect().getMinY();
    
    m_pMissileItem = CCMenuItemImage::create();
    m_pMissileItem->initWithTarget(this, menu_selector(CGameMessageLayer::shootMissile));
    m_pMissileItem->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MissileIco.png"));
    m_pMissileItem->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("MissileIco.png"));
    m_pMissileItem->setPosition(ccp(15, 80));
    
    CCMenu *pMissile = CCMenu::create(m_pMissileItem, NULL);
    pMissile->setPosition(ccp(0, 0));
    this->addChild(pMissile, 0);
    
    m_pMissileNum = CCLabelAtlas::create("2", "Image/Num.plist");
    m_pMissileItem->addChild(m_pMissileNum, 0);
    
    this->scheduleUpdate();
    
    return true;
}

void CGameMessageLayer::update(float dt)
{
    showScore();
    showHp();
    showLife();
    showMissile();
}

void CGameMessageLayer::showScore()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pGameLayer == NULL)
    {
        return;
    }
    
    int iScore = pGameLayer->getPlayer()->getScore();
    char szData[16];
    sprintf(szData,"%d",iScore);
    m_pScore->setString(szData);
}

void CGameMessageLayer::showHp()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pGameLayer == NULL)
    {
        return;
    }
    
    int iHp = pGameLayer->getPlayer()->getHp();
    int iHpMax = pGameLayer->getPlayer()->getHpMax();
    CCRect rect;
    rect.setRect(m_fMinX, m_fMinY, m_iWidth*(float)iHp/iHpMax, m_iHeight);
    m_pHp->setTextureRect(rect);
}

void CGameMessageLayer::showLife()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pGameLayer == NULL)
    {
        return;
    }
    
    char szData[16];
    int iLife = pGameLayer->getPlayer()->getLife();
    if(iLife > 0)
    {
        sprintf(szData, "%d", iLife - 1);
        m_pLife->setString(szData);
    }
}

void CGameMessageLayer::showMissile()
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pGameLayer == NULL)
    {
        return;
    }
    
    char szData[16];
    int iMissileNum = pGameLayer->getPlayer()->getMissileNum();
    if(iMissileNum > 0)
    {
        m_pMissileItem->setOpacity(255);
        m_pMissileNum->setVisible(true);
        sprintf(szData, "%d", iMissileNum);
        m_pMissileNum->setString(szData);
    }
    else
    {
        m_pMissileItem->setOpacity(150);
        m_pMissileNum->setVisible(false);
    }
}

void CGameMessageLayer::shootMissile(CCObject* pSender)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    CGameManagerLayer *pGameLayer = (CGameManagerLayer *) pScene->getChildByTag(GAME_MANAGER_LAYER_TAG);
    if (pGameLayer == NULL)
    {
        return;
    }
    
    pGameLayer->getPlayer()->shootMissile();
}


