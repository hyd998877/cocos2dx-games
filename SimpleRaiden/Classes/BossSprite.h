//
//  BossSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-17.
//
//

#ifndef __SimpleRaiden__BossSprite__
#define __SimpleRaiden__BossSprite__

#include "RoleSprite.h"

enum
{
    BOSS_TYPE_ONE = 0,
    BOSS_TYPE_TWO,
    BOSS_TYPE_THREE,
};

class CGameManagerLayer;

class CBossSprite : public CRoleSprite
{
public:
    static CBossSprite* create(int iType);
    
    virtual bool init(int iType);
    virtual void onEnter();
    
    virtual void update(float dt);
    
protected:
    
    virtual void shoot(float dt);
    void shoot2(float dt);
    virtual void destroy(cocos2d::CCNode *pSender);
    
    void setBossDatas();
    void setBossMoveAction(float dt);
    
private:
    int m_iScore;
    int m_iMoveType;
    
    int m_iBullet2Num;
    int m_iBullet2Type;
    float m_fShoot2Space;
    bool m_bHpChange1;
    bool m_bHpChange2;
    
    CGameManagerLayer *m_pGameLayer;
};

#endif /* defined(__SimpleRaiden__BossSprite__) */
