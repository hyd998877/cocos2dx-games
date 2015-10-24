//
//  GameMenuLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#ifndef __SimpleRaiden__GameMenuLayer__
#define __SimpleRaiden__GameMenuLayer__

#include "cocos2d.h"

class CGameMenuLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CGameMenuLayer);
    
private:
    
    void menuStartCallback(cocos2d::CCObject* pSender);
    void menuOptionCallback(cocos2d::CCObject* pSender);
    void menuExitCallback(cocos2d::CCObject* pSender);
    
    void move(float dt);
    
private:
    cocos2d::CCParticleSun *m_pMeteorolite;
};

#endif /* defined(__SimpleRaiden__GameMenuLayer__) */
