//
//  UnitSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-14.
//
//

#ifndef __SimpleRaiden__UnitSprite__
#define __SimpleRaiden__UnitSprite__

#include "cocos2d.h"

class CUnitSprite : public cocos2d::CCSprite
{
public:
    float getDis(float fPosX, float fPosY);
    float getAngle(float fPosX, float fPosY);
};

#endif /* defined(__SimpleRaiden__UnitSprite__) */
