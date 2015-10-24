//
//  ItemSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-14.
//
//

#ifndef __SimpleRaiden__ItemSprite__
#define __SimpleRaiden__ItemSprite__

#include "cocos2d.h"
#include "UnitSprite.h"

enum
{
	ITEM_GOLD = 0,
	ITEM_RUBY,
	ITEM_SAPPHIRE,
	ITEM_AMETHYST,
    ITEM_MISSILE,
};

class CItemSprite : public CUnitSprite
{
public:
    
    static CItemSprite* create(int iType, float x, float y);
    
    bool init(int iType, float x, float y);
    
    virtual void update(float dt);
    
private:
    
    void resetItemDatas();
    void reloadAnimation();
    
    void randomMove(float dt);
    void setDelFunc(cocos2d::CCNode *pSender);
    void changeType(float dt);
    
private:
    std::string m_szPathHeader;
    int m_iType;
    int m_iScore;
};

#endif /* defined(__SimpleRaiden__ItemSprite__) */
