//
//  GameMapLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#ifndef __SimpleRaiden__GameMapLayer__
#define __SimpleRaiden__GameMapLayer__

#include "cocos2d.h"

class CGameMapLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();

    CREATE_FUNC(CGameMapLayer);
    
public:
    void shake();
    
private:
    
    cocos2d::CCSprite *m_pMap;
    
};

#endif /* defined(__SimpleRaiden__GameMapLayer__) */
