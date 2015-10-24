//
//  BulletSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-15.
//
//

#ifndef __SimpleRaiden__BulletSprite__
#define __SimpleRaiden__BulletSprite__

#include "UnitSprite.h"

enum
{
	BULLET_ORANGE = 0,
	BULLET_BLUE,
    BULLET_MONSTER,
    BULLET_HELPER,
    BULLET_PURPLE,
    BULLET_YELLOW,
    BULLET_SILVER,
    BULLET_GREEN,
};

class CBulletSprite : public CUnitSprite
{
public:
    
    static CBulletSprite* create(int iPlaneType, int iType, int iAllNum, int iCurNum, float x, float y);
    
    bool init(int iPlaneType, int iType, int iAllNum, int iCurNum, float x, float y);
    
    virtual void update(float dt);
    
private:
    
    void resetBulletDatas();
    void setMoveTrack(int iAllNum, int iCurNum);
    void setDelFunc(cocos2d::CCNode *pSender);
    
private:
    std::string m_szFilePath;
    int m_iType;
    int m_iPlaneType;
    int m_iHarm;
};

#endif /* defined(__SimpleRaiden__BulletSprite__) */
