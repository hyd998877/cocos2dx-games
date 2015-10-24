//
//  GameLayer.h
//  MySimpleLinker
//
//  Created by zhouf369 on 14-8-7.
//
//

#ifndef __MySimpleLinker__GameLayer__
#define __MySimpleLinker__GameLayer__

#include "cocos2d.h"

int compare(const void *a, const void *b);

class MapNode : public cocos2d::CCObject
{
public:
    int order;
    int imgid;
};

class GameLayer : public cocos2d::CCLayer
{
public:
    GameLayer();
    ~GameLayer();
    
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    CREATE_FUNC(GameLayer);
    
private:
    
    void initSound();
    void initData();
    void initView();
    cocos2d::CCString* imageFilename(int index);
    
    void exitGame(CCObject *pSender);
    cocos2d::CCPoint pointOfView(cocos2d::CCPoint point);
    void showWin();
    void clearNode(cocos2d::CCPoint point);
    int indexFromPoint(cocos2d::CCPoint point);
    bool isSamePoints(cocos2d::CCPoint p1, cocos2d::CCPoint p2);
    bool isValiableNode(cocos2d::CCPoint point);
    bool isEmptyNode(cocos2d::CCPoint point);
    bool canClearTwo(cocos2d::CCPoint point1, cocos2d::CCPoint point2);
    bool match_direct(cocos2d::CCPoint a, cocos2d::CCPoint b);
    bool match_one_corner(cocos2d::CCPoint a, cocos2d::CCPoint b);
    bool match_two_corner(cocos2d::CCPoint a, cocos2d::CCPoint b);
    bool match(cocos2d::CCPoint a, cocos2d::CCPoint b);
    
private:
    
    int m_iClearedCount;
    int m_iCounter;
    
    cocos2d::CCPoint m_ptPrePoint;
    cocos2d::CCArray *m_pArrayMap;
};

#endif /* defined(__MySimpleLinker__GameLayer__) */
