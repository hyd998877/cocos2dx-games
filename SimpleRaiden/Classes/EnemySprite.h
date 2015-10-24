//
//  EnemySprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-16.
//
//

#ifndef __SimpleRaiden__EnemySprite__
#define __SimpleRaiden__EnemySprite__

#include "RoleSprite.h"

enum
{
    ENEMY_TYPE_ONE = 1,
    ENEMY_TYPE_TWO,
    ENEMY_TYPE_THREE,
};

class CGameManagerLayer;

class CEnemySprite : public CRoleSprite
{
public:
    static CEnemySprite* create(int iType);
    
    virtual bool init(int iType);
    virtual void onEnter();
    
    virtual void update(float dt);
    
protected:
    
    virtual void shoot(float dt);
    virtual void destroy(cocos2d::CCNode *pSender);
    
    void setEnemyDatas();
    void setEnemyMoveAction(float dt);
    void setDelFunc(cocos2d::CCNode *pSender);
    
protected:
    int m_iScore;
    int m_iMoveType;
    
    CGameManagerLayer *m_pGameLayer;
};

#endif /* defined(__SimpleRaiden__EnemySprite__) */
