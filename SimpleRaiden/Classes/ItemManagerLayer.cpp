//
//  ItemManagerLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#include "ItemManagerLayer.h"
#include "ItemSprite.h"

using namespace cocos2d;

bool CItemManagerLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Item.plist");
    
//    m_iItemCount = 0;
    m_pItemList = CCSpriteBatchNode::create("Image/Item.png");
    this->addChild(m_pItemList);
    
//    this->scheduleUpdate();
    
    return true;
}

//void CItemManagerLayer::update(float dt)
//{
//    for (int i = 0; i < m_iItemCount; i++)
//    {
//        CCSprite *pItem = (CCSprite *) m_pItemList->getChildByTag(i);
//        if (pItem != NULL && pItem->isVisible() == false)
//        {
//            pItem->removeFromParentAndCleanup(true);
//        }
//    }
//}

void CItemManagerLayer::createItem(int iType, float x, float y)
{
//    int iTag = -1;
    CItemSprite *pItem = (CItemSprite *) CItemSprite::create(iType, x, y);
//    for (int i = 0; i < m_iItemCount; i++)
//    {
//        CCSprite *pSprite = (CCSprite *) m_pItemList->getChildByTag(i);
//        if (pSprite == NULL)
//        {
//            iTag = i;
//            break;
//        }
//    }
//    
//    if (iTag == -1)
//    {
//        iTag = m_iItemCount;
//        m_iItemCount++;
//    }
//    
//    m_pItemList->addChild(pItem, 1, iTag);
    
    m_pItemList->addChild(pItem);
}
