//
//  BulletManagerLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-20.
//
//

#ifndef __SimpleRaiden__BulletManagerLayer__
#define __SimpleRaiden__BulletManagerLayer__

#include "cocos2d.h"

class CBulletManagerLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    CREATE_FUNC(CBulletManagerLayer);
    
public:
    void createBullet(int iPlaneType, int iType, int iNum, float x, float y);
    
private:
    
    cocos2d::CCSpriteBatchNode *m_pBulletList;
};

#endif /* defined(__SimpleRaiden__BulletManagerLayer__) */
