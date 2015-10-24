//
//  BulletManagerLayer.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-20.
//
//

#include "BulletManagerLayer.h"
#include "GameConfig.h"
#include "BulletSprite.h"

using namespace cocos2d;

bool CBulletManagerLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Bullet.plist");
    
    m_pBulletList = CCSpriteBatchNode::create("Image/Bullet.png");
    this->addChild(m_pBulletList);
    
    return true;
}


void CBulletManagerLayer::createBullet(int iPlaneType, int iType, int iNum, float x, float y)
{
    for (int i = 1; i <= iNum; i++)
    {
        CBulletSprite *pBullet = (CBulletSprite *) CBulletSprite::create(iPlaneType, iType, iNum, i, x, y);
        this->addChild(pBullet);
    }
}

