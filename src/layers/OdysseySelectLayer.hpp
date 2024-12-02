#pragma once
using namespace geode::prelude;

class OdysseySelectLayer : public CCLayer
{
public:
    BoomScrollLayer* m_scrollLayer;
    CCSprite* m_background;
    int m_pageAmount = 3;
    int m_currentPage = 0;
    CCSize m_winSize;
    int m_levelAmount = 0;
    CCNode* m_islandNode;
    CCMenu* m_levelMenu;

    virtual bool init(int);
    virtual void keyBackClicked();
    void onBack(CCObject*);

    std::vector<CCPoint> getPositionForButtons();

    void addLevelButtons();

    void switchToPage(int);
    void onNextPage(CCObject*);
    void onBackPage(CCObject*);

    void onLevel(CCObject*);

    void getWizardDialog01();

public:
    static OdysseySelectLayer* create(int);
    static CCScene* scene(int);
};
