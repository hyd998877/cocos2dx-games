//
//  GameLevelLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#ifndef __SimpleRaiden__GameLevelLayer__
#define __SimpleRaiden__GameLevelLayer__

#include "cocos2d.h"

class CGameLevelLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CGameLevelLayer);
    
private:
    
    void menuBackCallback(cocos2d::CCObject* pSender);
    
    void menuSetLevelModeCallback(cocos2d::CCObject* pSender);
    void menuSetLevelStartCallback(cocos2d::CCObject* pSender);
    
private:
    cocos2d::CCParticleSun *m_pSun;
};

#endif /* defined(__SimpleRaiden__GameLevelLayer__) */
