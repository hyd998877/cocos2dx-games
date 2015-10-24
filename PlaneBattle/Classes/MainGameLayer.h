//
//  MainGameLayer.h
//  PlaneBattle
//
//  Created by zhouf369 on 14-8-28.
//
//

#ifndef __PlaneBattle__MainGameLayer__
#define __PlaneBattle__MainGameLayer__

#include "cocos2d.h"
#include "ChangeBullet.h"

class FeoPlane;

class MainGameLayer : public cocos2d::CCLayer
{
public:
    MainGameLayer();
    ~MainGameLayer();
    
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void update(float dt);
    
    CREATE_FUNC(MainGameLayer);
    
private:
    // Play sounds
    void playFireSound();
    void smallPlaneDownSound();
    void mediumPlaneDownSound();
    void bigPlaneDownSound();
    void bigPlaneOutSound();
    
    // Button clicked functions
    void btnGamePauseCallback(cocos2d::CCObject *pSender);
    void btnGameStartCallback(cocos2d::CCObject *pSender);
    void btnGameRestartCallback(cocos2d::CCObject *pSender);
    
    // Init func
    void initDatas();
    void loadBackground();
    void loadPlayerPlane();
    void madeBullets();
    void resetBullets();
    
    void addFeoPlane();
    FeoPlane *makeSmallFoePlane();
    FeoPlane *makeMediumFoePlane();
    FeoPlane *makeBigFoePlane();
    void moveFoePlane();
    void firingBullest();
    void scrollBackground();
    void bulletLastTime();
    void addBulletTypeTip();
    void setPlayerPlanePos(cocos2d::CCPoint ptAddPos);
    void collisionDetection();
    
    void gameOver();
    
    // Anim func
    void blowupEnd(cocos2d::CCNode *pSender);
    void hitAnimationToFoePlane(FeoPlane *pFoePlane);
    void playerBlowupAnimation();
    void foePlaneBlowupAnimation(FeoPlane *pFoePlane);
    
private:
    // Datas
    bool m_bIsGameOver;
    
    // Background
    cocos2d::CCSprite *m_pBg1;
    cocos2d::CCSprite *m_pBg2;
    int m_iAdjustmentBg;
    
    // Scroe
    cocos2d::CCLabelTTF *m_pScoreLabel;
    int m_iScores;
    
    // Menu
    cocos2d::CCMenu *m_pRestartMenu;
    cocos2d::CCMenu *m_pPauseMenu;
    
    cocos2d::CCSprite *m_pPlayerPlane;
    
    cocos2d::CCSprite *m_pBullet;
    int m_iBulletSpeed;
    
    cocos2d::CCArray *m_pFoePlanesList;
    int m_iSmallPlaneTime;
    int m_iMediumPlaneTime;
    int m_iBigPlaneTime;
    
    int m_iPropTime;
    ChangeBullet *m_pProp;
    bool m_bIsPropVisible;
    
    bool m_bIsBigBullet;
    bool m_bIsChangeBullet;
    int m_iBulletLastTime;
    
    cocos2d::CCPoint m_ptPreTouch;
};

#endif /* defined(__PlaneBattle__MainGameLayer__) */
