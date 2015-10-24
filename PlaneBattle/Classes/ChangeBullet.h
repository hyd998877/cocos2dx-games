//
//  ChangeBullet.h
//  PlaneBattle
//
//  Created by zhouf369 on 14-8-28.
//
//

#ifndef __PlaneBattle__ChangeBullet__
#define __PlaneBattle__ChangeBullet__

#include "cocos2d.h"

enum _BULLET_TYPE
{
    BULLET_TYPE_BOMB = 4,
    BULLET_TYPE_BULLET = 5,
};

class ChangeBullet : public cocos2d::CCNode
{
public:
    ChangeBullet();
    ~ChangeBullet();
    
    void initWithType(_BULLET_TYPE eType);
    void propAnimation();
    
    cocos2d::CCSprite *getSprite() { return m_pProp; }
    int getBulletType() { return m_eBulletType; }
    
    CREATE_FUNC(ChangeBullet);
    
private:
    
    cocos2d::CCSprite *m_pProp;
    _BULLET_TYPE m_eBulletType;
};

#endif /* defined(__PlaneBattle__ChangeBullet__) */
