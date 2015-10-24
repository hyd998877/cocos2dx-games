//
//  BaseObject.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-27.
//
//

#ifndef MyParkour_BaseObject_h
#define MyParkour_BaseObject_h

#include "cocos2d.h"

class BaseObject : public cocos2d::CCNode
{
public:
    
    virtual cocos2d::extension::CCPhysicsSprite* getObjSprite() = 0;
    
    virtual void destroy() = 0;
    
    virtual void setObjVisible(bool visible) = 0;
};

#endif
