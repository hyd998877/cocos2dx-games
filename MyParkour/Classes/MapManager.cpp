//
//  MapManager.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-25.
//
//

#include "MapManager.h"
#include "resources.h"

USING_NS_CC;

MapManager::MapManager()
{
    m_iMapCount = 2;
    m_iCurMap = 0;
    m_fMapWidth = 0;
    
    m_pParentLayer = NULL;
    m_pWorld = NULL;
    
    m_pMap0 = NULL;
    m_pMap1 = NULL;
    
    m_pGround0 = NULL;
    m_pGround1 = NULL;
}

MapManager::~MapManager()
{
    
}

MapManager* MapManager::create(cocos2d::CCLayer *pLayer, b2World *pWorld)
{
    MapManager *pMapMgr = new MapManager();
    
    if (pMapMgr && pMapMgr->init(pLayer, pWorld))
    {
        pMapMgr->autorelease();
    }
    else
    {
        delete pMapMgr;
        pMapMgr = NULL;
    }
    
    return pMapMgr;
}

bool MapManager::init(cocos2d::CCLayer *pLayer, b2World *pWorld)
{
    if (!CCNode::init())
    {
        return false;
    }
    
    m_pParentLayer = pLayer;
    m_pWorld = pWorld;
    
    m_pMap0 = CCSprite::create(map0);
    m_pMap1 = CCSprite::create(map1);
    
    m_pGround0 = CCSprite::create(ground0);
    m_pGround1 = CCSprite::create(ground1);
    
    m_pMap0->setAnchorPoint(ccp(0, 0));
    m_pMap0->setPosition(ccp(0, 0));
    m_pParentLayer->addChild(m_pMap0);
    
    m_pGround0->setAnchorPoint(ccp(0, 0));
    m_pGround0->setPosition(ccp(0, GROUND_HEIGHT - m_pGround0->getContentSize().height));
    m_pParentLayer->addChild(m_pGround0);
    
    m_fMapWidth = m_pMap0->getContentSize().width;
    
    m_pMap1->setAnchorPoint(ccp(0, 0));
    m_pMap1->setPosition(ccp(m_fMapWidth, 0));
    m_pParentLayer->addChild(m_pMap1);
    
    m_pGround1->setAnchorPoint(ccp(0, 0));
    m_pGround1->setPosition(ccp(m_fMapWidth, GROUND_HEIGHT - m_pGround1->getContentSize().height));
    m_pParentLayer->addChild(m_pGround1);
    
    return true;
}

bool MapManager::checkReloadMap(float fEyeX)
{
    int iNewCurMap = fEyeX / m_fMapWidth;
    if (iNewCurMap == m_iCurMap)
    {
        return false;
    }
    
    CCSprite *pReloadMap = NULL;
    CCSprite *pReloadGround = NULL;
    
    if (iNewCurMap % 2 == 1)
    {
        pReloadMap = m_pMap0;
        pReloadGround = m_pGround0;
    }
    else
    {
        pReloadMap = m_pMap1;
        pReloadGround = m_pGround1;
    }
    
    m_iCurMap++;
    
    pReloadMap->setPosition(ccp(pReloadMap->getPosition().x + 2*m_fMapWidth, pReloadMap->getPosition().y));
    pReloadGround->setPosition(ccp(pReloadGround->getPosition().x + 2*m_fMapWidth, pReloadGround->getPosition().y));
    
    return true;
}



