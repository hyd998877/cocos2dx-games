//
//  ItemManagerLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#ifndef __SimpleRaiden__ItemManagerLayer__
#define __SimpleRaiden__ItemManagerLayer__

#include "cocos2d.h"

class CItemManagerLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
//    virtual void update(float dt);
    
    CREATE_FUNC(CItemManagerLayer);
    
public:
    void createItem(int iType, float x, float y);
    
private:
    
//    int m_iItemCount;
    cocos2d::CCSpriteBatchNode *m_pItemList;
};

#endif /* defined(__SimpleRaiden__ItemManagerLayer__) */
