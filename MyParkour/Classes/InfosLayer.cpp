//
//  InfosLayer.cpp
//  MyParkour
//
//  Created by zhouf fang on 14-7-27.
//
//

#include "InfosLayer.h"
#include "resources.h"

USING_NS_CC;

bool InfosLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setTag(INFOS_LAYER_TAG);
    mScore = CCLabelTTF::create("Coins: 0", "Helvetica", 20);
    mScore->setColor(ccc3(255, 193, 37));
    mScore->setPosition(ccp(70, 300));
    addChild(mScore);
    
    mMeters = CCLabelTTF::create("0 M", "Helvetica", 25);
    mMeters->setPosition(ccp(300, 300));
    addChild(mMeters);
    return true;
}


void InfosLayer::addCoin(int num)
{
    mCoins += num;
    char coins[30] = {0};
    sprintf(coins, "Coins: %d",mCoins);
    mScore->setString(coins);
}

void InfosLayer::updateMeter(float posX)
{
    char meter[100] = {0};
	sprintf(meter, "%d M", int(posX / 10));
    mMeters->setString(meter);
}

