#include "OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

bool OdysseyComicLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("GJ_gradientBG.png");
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    m_background->setScaleX((m_winSize.width) / size.width);
    m_background->setScaleY((m_winSize.height) / size.height);
    m_background->setAnchorPoint({0, 0});

    m_background->setColor({120, 120, 120});
    m_background->setID("background"_spr);
    addChild(m_background, -2);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyComicLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto arr = CCArray::create();
    auto dotMenu = CCMenu::create();

    for (int ii = 0; ii < m_pageAmount; ii++)
    {
        arr->addObject(createPage(ii));
    };

    m_scrollLayer = BoomScrollLayer::create(arr, 0, false, nullptr, static_cast<DynamicScrollDelegate *>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate *>(this);
    m_scrollLayer->m_looped = true;

    m_scrollLayer->instantMoveToPage(m_currentPage);

    addChild(m_scrollLayer);

    static_cast<CCSpriteBatchNode *>(m_scrollLayer->getChildren()->objectAtIndex(1))->setPositionY(-45);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, m_winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    m_cornerBL = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBL->setPosition({-1, -1});
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setID("corner-bl"_spr);
    addChild(m_cornerBL, 2);

    m_cornerBR = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    m_cornerBR->setPosition({m_winSize.width + 1, -1});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);
    addChild(m_cornerBR, 2);

    setKeyboardEnabled(true);
    setKeypadEnabled(true);
    return true;
};

CCNode *OdysseyComicLayer::createPage(int page)
{
    auto node = CCNode::create();
    auto spriteName = (page == 0)   ? "Comic_01_01_001.png"_spr
                      : (page == 1) ? "Comic_01_02_001.png"_spr
                      : (page == 2) ? "Comic_01_03_001.png"_spr
                      : (page == 3) ? "Comic_01_04_001.png"_spr
                      : (page == 4) ? "Comic_01_05_001.png"_spr
                      : (page == 5) ? "Comic_01_06_001.png"_spr
                      : (page == 6) ? "Comic_01_07_001.png"_spr
                      : (page == 7) ? "Comic_01_08_001.png"_spr
                                    : "Comic_01_09_001.png"_spr;

    auto comicSprite = CCSprite::createWithSpriteFrameName(spriteName);
    comicSprite->setPosition(m_winSize / 2);
    comicSprite->setScale(0.95f);
    node->addChild(comicSprite);

    return node;
}

void OdysseyComicLayer::scrollLayerMoved(CCPoint point)
{
    float transitionPoint = -point.x / CCDirector::sharedDirector()->getWinSize().width;

    int offset = std::floor(transitionPoint);

    // float transitionOffset = transitionPoint - offset;

    if (transitionPoint == offset)
    {
        m_currentPage = offset % m_pageAmount;
        //  updateBackground();
    }
};

void OdysseyComicLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void OdysseyComicLayer::onBack(CCObject *)
{
    keyBackClicked();
};

OdysseyComicLayer *OdysseyComicLayer::create()
{
    auto ret = new OdysseyComicLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *OdysseyComicLayer::scene()
{
    auto layer = OdysseyComicLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};