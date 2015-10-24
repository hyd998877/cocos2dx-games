//
//  UnitSprite.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-14.
//
//

#include "UnitSprite.h"

USING_NS_CC;

float CUnitSprite::getDis(float fPosX, float fPosY)
{
    float fDisX = this->getPosition().x - fPosX;
    float fDisY = this->getPosition().y - fPosY;
    
    float fDis = sqrt(fDisX*fDisX + fDisY*fDisY);
    return fDis;
}

float CUnitSprite::getAngle(float fPosX, float fPosY)
{
    float fDisX = this->getPosition().x - fPosX;
    float fDisY = this->getPosition().y - fPosY;
    float fAngle = 0;
    if (fDisY == 0)
    {
        fAngle = 0;
    }
    else
    {
        fAngle = (float) CC_RADIANS_TO_DEGREES(atan(fDisX/fDisY));
        
        if (fDisY < 0)
        {
            fAngle = 180 + fabs(fAngle);
        }
        else
        {
            fAngle = 180 - fabs(fAngle);
        }
    }
    
    return fAngle;
}