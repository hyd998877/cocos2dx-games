//
//  LoadLogo.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#ifndef __SimpleRaiden__LoadLogo__
#define __SimpleRaiden__LoadLogo__

#include "cocos2d.h"

class CLoadLogoLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CLoadLogoLayer);
    
private:
    void transitionLayerCallback(float dt);
};

#endif /* defined(__SimpleRaiden__LoadLogo__) */
