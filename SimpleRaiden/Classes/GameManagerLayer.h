//
//  GameManagerLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-13.
//
//

#ifndef __SimpleRaiden__GameManagerLayer__
#define __SimpleRaiden__GameManagerLayer__

#include "cocos2d.h"
#include "GameMapLayer.h"
#include "ItemManagerLayer.h"
#include "EnemyManagerLayer.h"
#include "BulletManagerLayer.h"
#include "PlayerSprite.h"

#define GAME_MANAGER_LAYER_TAG 99

class CGameManagerLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(CGameManagerLayer);
    
public:
    CGameMapLayer* getGameMap() { return m_pGameMap; }
    CItemManagerLayer* getItemManager() { return m_pItemManager; }
    CBulletManagerLayer* getBulletManager() { return m_pBulletManager; }
    CEnemyManagerLayer* getEnemyManager() { return m_pEnemyManager; }
    CPlayerSprite* getPlayer() { return m_pPlayer; }
    
    void startNextLevelGame();
    
private:
    void menuBackCallback(cocos2d::CCObject* pSender);
    
private:
    
    CGameMapLayer *m_pGameMap;
    CItemManagerLayer *m_pItemManager;
    CBulletManagerLayer *m_pBulletManager;
    CEnemyManagerLayer *m_pEnemyManager;
    CPlayerSprite *m_pPlayer;
};

#endif /* defined(__SimpleRaiden__GameManagerLayer__) */
