//
//  InfosLayer.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-27.
//
//

#ifndef __MyParkour__InfosLayer__
#define __MyParkour__InfosLayer__

#include "cocos2d.h"

class InfosLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    
    CREATE_FUNC(InfosLayer);
    
public:
    
    void addCoin(int num);
    void updateMeter(float posX);
    
private:
    cocos2d::CCLabelTTF* mScore;
    
    cocos2d::CCLabelTTF* mMeters;
    
    int mCoins;
};

#endif /* defined(__MyParkour__InfosLayer__) */
