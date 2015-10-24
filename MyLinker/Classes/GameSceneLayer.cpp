//
//  GameSceneLayer.cpp
//  MyLinker
//
//  Created by zhouf369 on 14-8-19.
//
//

#include "GameSceneLayer.h"
#include "Icon.h"
#include "LinkAssetsManager.h"
#include "LinkLogic.h"
#include "GameMapLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

cocos2d::CCScene* GameSceneLayer::createScene()
{
    CCScene *pScene = CCScene::create();
    
    GameSceneLayer *pLayer = GameSceneLayer::create();
    pScene->addChild(pLayer);
    
    return pScene;
}
    
bool GameSceneLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    LinkAssetsManager::initAssets();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::create("backMain.jpg");
    pBg->setAnchorPoint(ccp(0, 0));
    this->addChild(pBg);
    
    CCSprite *pAlphaBg = CCSprite::create("gameFace.png");
    pAlphaBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pAlphaBg);
    
    initSelIconToNull();
    
    m_pGameMapLayer = GameMapLayer::create();
    m_pGameMapLayer->initMapWithRowAndCol(8, 12);
    this->addChild(m_pGameMapLayer);
    
    float fX = winSize.width/2 - m_pGameMapLayer->getMapSize().width/2;
    float fY = winSize.height/2 - m_pGameMapLayer->getMapSize().height/2;
    
    m_pGameMapLayer->setPosition(ccp(fX, fY));
    
    this->setTouchEnabled(true);
    
    return true;
}

void GameSceneLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
    
bool GameSceneLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocation();
    
    CCLog("touchLoc: %f, %f", touchLocation.x, touchLocation.y);
    
    touchLocation = m_pGameMapLayer->convertToNodeSpace(touchLocation);
    
    CCLog("===== touchLoc: %f, %f", touchLocation.x, touchLocation.y);
    
    if (touchLocation.x < 0 || touchLocation.y < 0)
    {
        return false;
    }
    
    int iTouchRow = touchLocation.y / GameMapLayer::m_iIconHeight;
    int iTouchCol = touchLocation.x / GameMapLayer::m_iIconWidth;
    
    CCLog("===== %d, %d", iTouchRow, iTouchCol);
    
    if (iTouchRow >= GameMapLayer::m_iMapRow || iTouchRow < 0 || iTouchCol < 0 || iTouchCol >= GameMapLayer::m_iMapCol)
    {
        return true;
    }
    
    Icon *pIcon = GameMapLayer::getIconAtRowAndCol(iTouchRow, iTouchCol);
    if (pIcon->getDestroyed())
    {
        return true;
    }
    
    pIcon->changeIconViewWithType(SELECTED);
    if (m_pFirstIcon == NULL || m_pFirstIcon == pIcon)
    {
        m_pFirstIcon = pIcon;
        m_pGameMapLayer->setIconToMaxTop(m_pFirstIcon);
        m_pFirstIcon->playAction();
        SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
        
        return true;
    }
    else if (m_pSecondIcon == NULL)
    {
        m_pSecondIcon = pIcon;
        SimpleAudioEngine::sharedEngine()->playEffect("click.wav");
    }
    
    if (checkSelIcon(m_pFirstIcon, m_pSecondIcon))
    {
        bool bCanMatch = LinkLogic::canFadeAway(m_pFirstIcon, m_pSecondIcon);
        if (bCanMatch)
        {
            m_pFirstIcon->unplayAction();
            m_pFirstIcon->fadeOutAction(1.3f);
            m_pSecondIcon->fadeOutAction(1.3f);
            
            m_pFirstIcon->setDestroyed(true);
            m_pSecondIcon->setDestroyed(true);
            
            SimpleAudioEngine::sharedEngine()->playEffect("dis.wav");
        }
    }
    
    m_pFirstIcon->changeIconViewWithType(UN_SELECTED);
    m_pSecondIcon->changeIconViewWithType(UN_SELECTED);
    m_pFirstIcon->unplayAction();
    SimpleAudioEngine::sharedEngine()->playEffect("err.wav");
    
    initSelIconToNull();
    
    return true;
}

void GameSceneLayer::initSelIconToNull()
{
    m_pFirstIcon = NULL;
    m_pSecondIcon = NULL;
}

bool GameSceneLayer::checkSelIcon(Icon *pIcon1, Icon *pIcon2)
{
    if (pIcon1->getIconType() == pIcon2->getIconType())
    {
        return true;
    }
    
    return false;
}
