//
//  EnemyManagerLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-17.
//
//

#ifndef __SimpleRaiden__EnemyManagerLayer__
#define __SimpleRaiden__EnemyManagerLayer__

#include "cocos2d.h"

class CBossSprite;

class CEnemyManagerLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    CREATE_FUNC(CEnemyManagerLayer);
    
public:
    cocos2d::CCSpriteBatchNode* getEnemyList() { return m_pEnemyList; }
    CBossSprite* getBoss();
    
    void createEnemy(float dt);
    void createBoss(float dt);
    
private:
    
    cocos2d::CCSpriteBatchNode *m_pEnemyList;
};

#endif /* defined(__SimpleRaiden__EnemyManagerLayer__) */
