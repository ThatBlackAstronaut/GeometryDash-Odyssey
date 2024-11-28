#pragma once

using namespace geode::prelude;

class OdysseySelectLayer : public cocos2d::CCLayer
{
public:
    BoomScrollLayer *m_scrollLayer;
    CCSprite *m_background;
    int m_pageAmount = 3;
    int m_currentPage = 0;

public:
    bool init()
    {
        if (!CCLayer::init())
            return false;

        setKeyboardEnabled(true);
        setKeypadEnabled(true);

        auto size = CCDirector::sharedDirector()->getWinSize();

        m_background = CCSprite::create(GameManager::sharedState()->getBGTexture(52));
        m_background->setID("background"_spr);

        m_background->setScale(size.width / m_background->getContentWidth());
        m_background->setColor(colorForPage(0));

        m_background->setAnchorPoint({0, 0});
        m_background->setPositionY(-100);

        addChild(m_background, -1);

        auto backMenu = CCMenu::create();
        backMenu->setPosition(24, size.height - 24);

        addChild(backMenu);

        auto backSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        auto backButton = CCMenuItemSpriteExtra::create(backSpr, this, menu_selector(OdysseySelectLayer::onBack));

        backMenu->addChild(backButton);

        return true;
    };

    void keyBackClicked()
    {
        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, MenuLayer::scene(false)));
    }

    void onBack(CCObject *)
    {
        keyBackClicked();
    }

    ccColor3B colorForPage(int page)
    {
        std::vector<ccColor3B> arr = {
            {32, 39, 46},
            {26, 12, 43},
            {53, 7, 0}
        };
        return arr[page];
    }

    CREATE_FUNC(OdysseySelectLayer);
};
