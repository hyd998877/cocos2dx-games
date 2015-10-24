//
//  LinkLogic.h
//  MyLinker
//
//  Created by zhouf369 on 14-8-18.
//
//

#ifndef __MyLinker__LinkLogic__
#define __MyLinker__LinkLogic__

#include "cocos2d.h"

class Icon;

class LinkLogic
{
public:
    
    static bool canFadeAway(Icon *first, Icon *second);
    
private:
    
    static bool checkLine(Icon *first, Icon *second);
    static bool checkOneCorner(Icon *first, Icon *second);
    static bool checkTwoCorner(Icon *first, Icon *second);
    
};

#endif /* defined(__MyLinker__LinkLogic__) */
