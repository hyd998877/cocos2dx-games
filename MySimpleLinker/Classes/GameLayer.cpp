//
//  GameLayer.cpp
//  MySimpleLinker
//
//  Created by zhouf369 on 14-8-7.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "CCControlButton.h"
#include "MenuScene.h"

#define START_SPRITE_TAG 100
#define LABEL_CONNER_TAG 501
#define LABEL_NUMBER_TAG 502

#define OFFSET_X -40
#define OFFSET_Y 60

#define SIZE_W 40
#define SIZE_H 40

#define TOTAL_X 10
#define TOTAL_Y 10

#define TOTAL_IMG 16
#define MAX_CLEARED 24

static int imgMap[64] = {
    1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 ,
    5 , 5 , 5 , 5 , 6 , 6 , 0 , 0 ,
    7 , 7 , 7 , 7 , 8 , 8 , 0 , 0 ,
    9 , 9 , 9 , 9 , 10, 10, 10, 10,
    11, 11, 11, 11, 12, 12, 12, 12,
    13, 13, 13, 13, 14, 14, 14, 14,
	15, 15, 16, 16, 0 , 0 , 0 , 0 ,
    0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
};

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

cocos2d::CCScene* GameLayer::scene()
{
    CCScene *pScene = CCScene::create();
    
    GameLayer *pLayer = GameLayer::create();
    pScene->addChild(pLayer);
    
    return pScene;
}

GameLayer::GameLayer()
{
    m_iClearedCount = 0;
    m_iCounter = 0;
    
    m_ptPrePoint = ccp(0, 0);
    m_pArrayMap = NULL;
}

GameLayer::~GameLayer()
{
    if (m_pArrayMap != NULL)
    {
        m_pArrayMap->removeAllObjects();
        m_pArrayMap->release();
        m_pArrayMap = NULL;
    }
}

bool GameLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    this->initSound();
    this->initData();
    this->initView();
    
    return true;
}

void GameLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool GameLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCPoint ptCurPoint = this->pointOfView(touchLocation);
    
    if (!isValiableNode(ptCurPoint))
    {
        return false;
    }
    
    if (isEmptyNode(ptCurPoint))
    {
        return false;
    }
    
    SimpleAudioEngine::sharedEngine()->playEffect("choose.wav");
    
    CCSprite *pCurrentNode = (CCSprite *) this->getChildByTag(START_SPRITE_TAG + indexFromPoint(ptCurPoint));
    CCSprite *pPrevNode = (CCSprite *) this->getChildByTag(START_SPRITE_TAG + indexFromPoint(m_ptPrePoint));
    
    if (isSamePoints(ptCurPoint, m_ptPrePoint))
    {
        if (pPrevNode != NULL)
        {
            pPrevNode->setScale(0.5f);
        }
        m_ptPrePoint = ccp(-1, -1);
        return false;
    }
    
    pCurrentNode->setScale(0.6f);
    
    if (isValiableNode(m_ptPrePoint))
    {
        if (canClearTwo(ptCurPoint, m_ptPrePoint))
        {
            SimpleAudioEngine::sharedEngine()->playEffect("disappear1.wav");
            
            this->clearNode(m_ptPrePoint);
            this->clearNode(ptCurPoint);
            
            pCurrentNode->setVisible(false);
            pPrevNode->setVisible(false);
            
            m_iClearedCount++;
            if (m_iClearedCount >= MAX_CLEARED)
            {
                SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
                SimpleAudioEngine::sharedEngine()->playEffect("win.mp3");
                showWin();
            }
            
            CCLabelTTF *pProgressLabel = (CCLabelTTF *) this->getChildByTag(LABEL_CONNER_TAG);
            CCString *pProgressStr = CCString::createWithFormat("进度:%d%%", (int)(m_iClearedCount * 100 / MAX_CLEARED));
            pProgressLabel->setString(pProgressStr->getCString());
        }
        else
        {
            pPrevNode->setScale(0.5f);
        }
    }
    
    m_ptPrePoint = ptCurPoint;
    return true;
}


void GameLayer::initSound()
{
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3f);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("back2.mp3", true);
}

void GameLayer::initData()
{
    m_ptPrePoint = CCPointMake(-1, -1);
    m_iClearedCount = 0;
    m_iCounter = 0;
    CCArray *pArray = CCArray::create();
    
    srandom((unsigned int) time(NULL));
    
    for (int i = 0; i < (TOTAL_X - 2) * (TOTAL_Y - 2); i++)
    {
        MapNode *pNewNode = new MapNode();
        pNewNode->autorelease();
        pNewNode->order = (int) (CCRANDOM_0_1() * INT_MAX) % (int) (CCRANDOM_0_1() * INT_MAX);
        pNewNode->imgid = imgMap[i];
        pArray->addObject(pNewNode);
    }
    
    // 所有的方块有一个随机order，根据这个随机order进行降序排序
    qsort(pArray->data->arr, pArray->data->num, sizeof(MapNode*), compare);
    
    m_pArrayMap = CCArray::create();
    m_pArrayMap->retain();
    for (int x = 0; x < TOTAL_X; x++)
    {
        for (int y = 0; y < TOTAL_Y; y++)
        {
            if (x == 0 || x == (TOTAL_X - 1) || y == 0 || y == (TOTAL_Y - 1))
            {
                // 添加最外面一圈空的
                MapNode *pNewNode = new MapNode();
                pNewNode->autorelease();
                pNewNode->order = 0;
                pNewNode->imgid = 0;
                m_pArrayMap->addObject(pNewNode);
            }
            else
            {
                int i = (y - 1) * (TOTAL_Y - 2) + x - 1;
                m_pArrayMap->addObject(pArray->objectAtIndex(i));
            }
        }
    }
}

void GameLayer::initView()
{
    this->setTouchEnabled(true);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *pBg = CCSprite::create("bg.png");
    pBg->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pBg);
    
    // Show all block sprite.
    for (int y = 0; y < TOTAL_Y; y++)
    {
        for (int x = 0; x < TOTAL_X; x++)
        {
            int index = y * TOTAL_X + x;
            if (imageFilename(index) != NULL)
            {
                CCSprite *pBlockImg = CCSprite::create(imageFilename(index)->getCString());
                pBlockImg->setScale(0.5f);
                pBlockImg->setPosition(ccp(OFFSET_X + (SIZE_W / 2) + SIZE_W * x,
                                           OFFSET_Y + (SIZE_H / 2) + SIZE_H * y));
                this->addChild(pBlockImg, 0, START_SPRITE_TAG+index);
            }
        }
    }
    
    CCLabelTTF *pEmpty = CCLabelTTF::create("", "Arial", 10);
    CCScale9Sprite *pBtnBg = CCScale9Sprite::create("close_btn_nor.png");
    CCControlButton *pBackBtn = CCControlButton::create(pEmpty, pBtnBg);
    pBackBtn->setPreferredSize(CCSizeMake(94, 94));
    pBackBtn->setPosition(ccp(winSize.width - 55, 25));
    pBackBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::exitGame), CCControlEventTouchDown);
    pBackBtn->setTouchPriority(kCCMenuHandlerPriority - 1);
    this->addChild(pBackBtn);
    
    CCLabelTTF *pProgressLabel = CCLabelTTF::create("进度:0%%", "Arial", 20.0f);
    pProgressLabel->setPosition(ccp(50, 15));
    this->addChild(pProgressLabel, 0, LABEL_CONNER_TAG);
    
    CCLabelTTF *pNumLabel1 = CCLabelTTF::create("3", "Marker Felt", 64);
    pNumLabel1->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pNumLabel1);
    
    CCLabelTTF *pNumLabel2 = CCLabelTTF::create("2", "Marker Felt", 64);
    pNumLabel2->setPosition(ccp(winSize.width/2, winSize.height/2));
    pNumLabel2->setVisible(false);
    this->addChild(pNumLabel2);
    
    CCLabelTTF *pNumLabel3 = CCLabelTTF::create("1", "Marker Felt", 64);
    pNumLabel3->setPosition(ccp(winSize.width/2, winSize.height/2));
    pNumLabel3->setVisible(false);
    this->addChild(pNumLabel3);
    
    CCLabelTTF *pNumLabel4 = CCLabelTTF::create("Go", "Marker Felt", 64);
    pNumLabel4->setPosition(ccp(winSize.width/2, winSize.height/2));
    pNumLabel4->setVisible(false);
    this->addChild(pNumLabel4);
    
    CCSequence *pAnim1 = CCSequence::create(CCDelayTime::create(0.5f), CCShow::create(), CCScaleBy::create(0.5, 2.0f), CCHide::create(), NULL);
    pNumLabel1->runAction(pAnim1);
    
    CCSequence *pAnim2 = CCSequence::create(CCDelayTime::create(1.0f), CCShow::create(), CCScaleBy::create(0.5, 2.0f), CCHide::create(), NULL);
    pNumLabel2->runAction(pAnim2);
    
    CCSequence *pAnim3 = CCSequence::create(CCDelayTime::create(1.5f), CCShow::create(), CCScaleBy::create(0.5, 2.0f), CCHide::create(), NULL);
    pNumLabel3->runAction(pAnim3);
    
    CCSequence *pAnim4 = CCSequence::create(CCDelayTime::create(2.0f), CCShow::create(), CCScaleBy::create(0.5, 2.0f), CCHide::create(), NULL);
    pNumLabel4->runAction(pAnim4);
}

cocos2d::CCString* GameLayer::imageFilename(int index)
{
    CCObject *pMapNode = m_pArrayMap->objectAtIndex(index);
    int iImgId = ((MapNode *) pMapNode)->imgid;
    if (iImgId >= 1 && iImgId <= TOTAL_IMG)
    {
        return CCString::createWithFormat("%d.png", iImgId);
    }
    
    return NULL;
}

void GameLayer::exitGame(CCObject *pSender)
{
    CCScene *pMenuScene = Menu::scene();
    CCTransitionFade *pFadeScene = CCTransitionFade::create(1.0f, pMenuScene, ccWHITE);
    CCDirector::sharedDirector()->replaceScene(pFadeScene);
}

cocos2d::CCPoint GameLayer::pointOfView(cocos2d::CCPoint point)
{
    int x = -1;
    int y = -1;
    
    if (point.x > OFFSET_X && point.x < OFFSET_X + TOTAL_X * SIZE_W)
    {
        x = (point.x - OFFSET_X) / SIZE_W;
    }
    if (point.y > OFFSET_Y && point.y < OFFSET_Y + TOTAL_Y * SIZE_H)
    {
        y = (point.y - OFFSET_Y) / SIZE_H;
    }
    
    return CCPointMake(x, y);
}

void GameLayer::showWin()
{
    CCLabelTTF *pWinText = CCLabelTTF::create("过关了~", "Arial", 36.0f);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pWinText->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(pWinText);
    
    this->scheduleOnce(schedule_selector(GameLayer::exitGame), 2.0f);
}

int GameLayer::indexFromPoint(cocos2d::CCPoint point)
{
    return point.x + point.y * TOTAL_X;
}

bool GameLayer::isSamePoints(cocos2d::CCPoint p1, cocos2d::CCPoint p2)
{
    return (p1.x == p2.x && p1.y == p2.y);
}

bool GameLayer::isValiableNode(cocos2d::CCPoint point)
{
    return (point.x >= 0 && point.x < TOTAL_X && point.y >= 0 && point.y < TOTAL_Y);
}

bool GameLayer::isEmptyNode(cocos2d::CCPoint point)
{
    int index = indexFromPoint(point);
    MapNode *pMapNode = (MapNode *) m_pArrayMap->objectAtIndex(index);
    return pMapNode->imgid == 0;
}


void GameLayer::clearNode(cocos2d::CCPoint point)
{
    int index = indexFromPoint(point);
    MapNode *pMapNode = (MapNode *) m_pArrayMap->objectAtIndex(index);
    pMapNode->imgid = 0;
}

// 连连看核心算法
// 1. 看两个点ab能不能直接连接
// 2. 看两个点ab，能不能和他们之间的角落点c能否直接连接
// 3. 遍历点a相连的所有空节点（x，y两个方向），看这些点是否能于b之间的角落点c连接。
bool GameLayer::match_direct(cocos2d::CCPoint a, cocos2d::CCPoint b)
{
    if (a.x != b.x && a.y != b.y)
    {
        return false;
    }
    
    bool bMatchX = false;
    if (a.x == b.x)
    {
        int iMinY = 0;
        int iMaxY = 0;
        if (a.y > b.y)
        {
            iMaxY = a.y;
            iMinY = b.y;
        }
        else if (a.y < b.y)
        {
            iMaxY = b.y;
            iMinY = a.y;
        }
        else
        {
            return false;
        }
        
        bMatchX = true;
        for (int i = iMinY+1; i < iMaxY; i++)
        {
            CCPoint ptCurPoint = ccp(a.x, i);
            if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
            {
                bMatchX = false;
                break;
            }
        }
    }
    
    bool bMatchY = false;
    if (a.y == b.y)
    {
        int iMinX = 0;
        int iMaxX = 0;
        if (a.x > b.x)
        {
            iMaxX = a.x;
            iMinX = b.x;
        }
        else if (a.x < b.x)
        {
            iMaxX = b.x;
            iMinX = a.x;
        }
        else
        {
            return false;
        }
        
        bMatchY = true;
        for (int i = iMinX+1; i < iMaxX; i++)
        {
            CCPoint ptCurPoint = ccp(i, a.y);
            if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
            {
                bMatchY = false;
                break;
            }
        }
    }
    
    return (bMatchX || bMatchY);
}

bool GameLayer::match_one_corner(cocos2d::CCPoint a, cocos2d::CCPoint b)
{
    CCPoint ptCorner1 = ccp(a.x, b.y);
    if (isValiableNode(ptCorner1) && isEmptyNode(ptCorner1) && match_direct(a, ptCorner1) && match_direct(b, ptCorner1))
    {
        return true;
    }
    
    CCPoint ptCorner2 = ccp(b.x, a.y);
    if (isValiableNode(ptCorner2) && isEmptyNode(ptCorner2) && match_direct(a, ptCorner2) && match_direct(b, ptCorner2))
    {
        return true;
    }
    
    return false;
}

bool GameLayer::match_two_corner(cocos2d::CCPoint a, cocos2d::CCPoint b)
{
    // Search in x direction.
    for (int i = a.x - 1; i >= 0; i--)
    {
        CCPoint ptCurPoint = ccp(i, a.y);
        if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
        {
            break;
        }
        else
        {
            if (match_one_corner(ptCurPoint, b))
            {
                return true;
            }
        }
    }
    
    for (int i = a.x + 1; i < TOTAL_X; i++)
    {
        CCPoint ptCurPoint = ccp(i, a.y);
        if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
        {
            break;
        }
        else
        {
            if (match_one_corner(ptCurPoint, b))
            {
                return true;
            }
        }
    }
    
    // Search in y direction.
    for (int i = a.y - 1; i >= 0; i--)
    {
        CCPoint ptCurPoint = ccp(a.x, i);
        if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
        {
            break;
        }
        else
        {
            if (match_one_corner(ptCurPoint, b))
            {
                return true;
            }
        }
    }
    
    for (int i = a.y + 1; i < TOTAL_Y; i++)
    {
        CCPoint ptCurPoint = ccp(a.x, i);
        if (!isValiableNode(ptCurPoint) || !isEmptyNode(ptCurPoint))
        {
            break;
        }
        else
        {
            if (match_one_corner(ptCurPoint, b))
            {
                return true;
            }
        }
    }
    
    return false;
}

bool GameLayer::match(cocos2d::CCPoint a, cocos2d::CCPoint b)
{
    if (match_direct(a, b))
    {
        return true;
    }
    if (match_one_corner(a, b))
    {
        return true;
    }
    if (match_two_corner(a, b))
    {
        return true;
    }
    
    return false;
}

bool GameLayer::canClearTwo(cocos2d::CCPoint point1, cocos2d::CCPoint point2)
{
    int index1 = indexFromPoint(point1);
    int index2 = indexFromPoint(point2);
    
    int img1 = ((MapNode *) m_pArrayMap->objectAtIndex(index1))->imgid;
    int img2 = ((MapNode *) m_pArrayMap->objectAtIndex(index2))->imgid;
    
    if (img1 == img2 && match(point1, point2))
    {
        return true;
    }
    
    return false;
}

int compare(const void *a, const void *b)
{
    MapNode *pSelf = (MapNode *) a;
    MapNode *pOther = (MapNode *) b;
    
    if (pSelf->order > pOther->order)
    {
        return 1;
    }
    else if (pSelf->order == pOther->order)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}