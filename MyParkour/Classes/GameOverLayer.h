//
//  GameOverLayer.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-27.
//
//

#ifndef __MyParkour__GameOverLayer__
#define __MyParkour__GameOverLayer__

#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer : public CCLayerColor
{
public:
    virtual bool init();
    
    void onRestart(CCObject* pSender);
    
    CREATE_FUNC(GameOverLayer);
};

#endif /* defined(__MyParkour__GameOverLayer__) */
