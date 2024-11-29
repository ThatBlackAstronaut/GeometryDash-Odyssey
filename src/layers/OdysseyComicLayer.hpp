#pragma once
using namespace geode::prelude;

class OdysseyComicLayer : public cocos2d::CCLayer, public BoomScrollLayerDelegate, public DynamicScrollDelegate {
    public:
        BoomScrollLayer * m_scrollLayer = nullptr;
        CCSprite * m_background = nullptr;
        CCSprite * m_cornerBL = nullptr;
        CCSprite * m_cornerBR = nullptr;
        CCSize m_winSize;

        int m_currentPage = 0;
        int m_pageAmount = 9;

        virtual bool init();
        virtual void keyBackClicked();

        CCNode * createPage(int);

        void scrollLayerMoved(CCPoint);
        void onBack(CCObject *);

    public:
        static OdysseyComicLayer * create();
        CCScene * scene();
};