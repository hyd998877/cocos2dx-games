//
//  PlayerSprite.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-20.
//
//

#ifndef __SimpleRaiden__PlayerSprite__
#define __SimpleRaiden__PlayerSprite__

#include "RoleSprite.h"

class CGameManagerLayer;

class CPlayerSprite : public CRoleSprite, public cocos2d::CCTouchDelegate
{
public:
    static CPlayerSprite* create(int iType);
    
    virtual bool init(int iType);
    virtual void onEnter();
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
public:

    int getLife(){return m_iLife;}
    
    int getHpMax(){return m_iHpMax;}
    int getHp(){return m_iHp;}
    
    int getMissileNum(){return m_iMissileNum;}
    
    void addScore(int iValue);
    int getScore(){return m_iScore;}
    
    void gainItem(int iType, int iScore);
    
    bool isWin(){return m_bWin;}
    
    void showWinAnim();
    void setWin(bool bValue){m_bWin = bValue;}
    
    void shootMissile();
    
    bool isShield(){return m_bShield;}
    
    void recreatePlayerPlane();
    
private:
    
    virtual void shoot(float dt);
    virtual void destroy(cocos2d::CCNode *pSender);
    
    void winAnimCallback(cocos2d::CCNode *pSender);
    void setShield();
    void clearShield();
    void setShoot();
    void clearShoot();
    void createShoot();
    void createMissile();
    void MissileExplore(cocos2d::CCNode *pSender);
    void MissileDestroy(cocos2d::CCNode *pSender);
    void hurtEnemy();
    
private:
    cocos2d::CCPoint m_PosBack;
    cocos2d::CCSprite *m_pMissile;
    
    int m_iScore;
    int m_iAddLifeScore;
    int m_iMissileNum;
    
    bool m_bMissile;
    bool m_bShield;
    bool m_bWin;
    
    CGameManagerLayer *m_pGameLayer;
};

#endif /* defined(__SimpleRaiden__PlayerSprite__) */
