//
//  GameOverLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#ifndef __SimpleRaiden__GameOverLayer__
#define __SimpleRaiden__GameOverLayer__

#include "cocos2d.h"

class CGameOverLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CGameOverLayer);
    
private:
    
    void menuBackCallback(cocos2d::CCObject* pSender);
};

#endif /* defined(__SimpleRaiden__GameOverLayer__) */
