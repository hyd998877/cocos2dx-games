//
//  MainScene.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-15.
//
//

#ifndef __MyParkour__MainScene__
#define __MyParkour__MainScene__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(MainScene);
    
private:
    
    void preloadMusic();
    void onBtnPlay();
};

#endif /* defined(__MyParkour__MainScene__) */
