//
//  LinkAssetsManager.cpp
//  MyLinker
//
//  Created by zhouf369 on 14-8-15.
//
//

#include "LinkAssetsManager.h"

using namespace cocos2d;

LinkAssetsManager::LinkAssetsManager()
{
    
}

LinkAssetsManager::~LinkAssetsManager()
{
    
}

void LinkAssetsManager::initAssets()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("point.plist");
}