//
//  FeoPlane.h
//  PlaneBattle
//
//  Created by zhouf369 on 14-8-28.
//
//

#ifndef __PlaneBattle__FeoPlane__
#define __PlaneBattle__FeoPlane__

#include "cocos2d.h"

enum _PLANE_TYPE
{
    PLANE_TYPE_SMALL = 1,
    PLANE_TYPE_LARGE,
    PLANE_TYPE_MIDDLE,
};

class FeoPlane : public cocos2d::CCSprite
{
public:
    
    FeoPlane();
    ~FeoPlane();
    
    int getPlaneType() { return m_iPlaneType; }
    void setPlaneType(int iType) { m_iPlaneType = iType; }
    
    int getHp() { return m_iHp; }
    void setHp(int iHp) { m_iHp = iHp; }
    
    int getSpeed() { return m_iSpeed; }
    void setSpeed(int iSpeed) { m_iSpeed = iSpeed; }
    
    CREATE_FUNC(FeoPlane);
    
private:
    
    int m_iPlaneType;
    int m_iHp;
    int m_iSpeed;
};

#endif /* defined(__PlaneBattle__FeoPlane__) */
