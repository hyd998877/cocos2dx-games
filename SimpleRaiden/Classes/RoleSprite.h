//
//  RoleSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#ifndef __SimpleRaiden__RoleSprite__
#define __SimpleRaiden__RoleSprite__

#include "UnitSprite.h"

enum
{
	LEFT = 0,
	STRAIGHT,
	RIGHT,
};
enum
{
	PLAYER = 0,
	ENEMY,
};

class CRoleSprite : public CUnitSprite
{
public:
    void hurt(int iHarm);
    
protected:
    void setFlyAnimation(int iDirection);
    void setDelFunc(cocos2d::CCNode *pSender);
    void explosion();
    void finishExplosionAnim();
    void changeFlyAnimation(float dt);
    int getDirection();
    
    virtual void shoot(float dt) = 0;
    virtual void destroy(cocos2d::CCNode *pSender) = 0;
    
protected:
    
    int m_iHpMax;
    int m_iHp;
    int m_iType;
    float m_fShootSpace;
    
    int m_iFlyStraightNum;
    int m_iFlyLeftNum;
    int m_iLife;
    int m_iDirection;
    
    int m_iBulletType;
    int m_iBulletNum;
    
    cocos2d::CCPoint m_ptLastPos;
    cocos2d::CCSprite *m_pExplosion;
};

#endif /* defined(__SimpleRaiden__RoleSprite__) */
