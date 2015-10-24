//
//  MenuScene.h
//  MySimpleLinker
//
//  Created by zhouf369 on 14-8-7.
//
//

#ifndef __MySimpleLinker__MenuScene__
#define __MySimpleLinker__MenuScene__

#include "cocos2d.h"

class Menu : public cocos2d::CCLayer
{
public:
    
    Menu();
    ~Menu();
    
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    CREATE_FUNC(Menu);
    
private:
    void btnPlayCallback(CCObject *pSender);
    void btnCloseCallback(CCObject *pSender);
    
private:
};

#endif /* defined(__MySimpleLinker__MenuScene__) */
