#include "OdysseyComicLayer.hpp"
#include "OdysseySelectLayer.hpp"
#include "SecretVaultLayer.hpp"
#include "../utils/Utils.hpp"

bool OdysseyComicLayer::init(int issueNumber, bool redirectToMap)
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("GJ_gradientBG.png");
    m_winSize = CCDirector::sharedDirector()->getWinSize();
    m_comicNumber = issueNumber;
    m_RedirectToMap = redirectToMap;

    auto size = m_background->getContentSize();

    m_background->setScaleX((m_winSize.width) / size.width);
    m_background->setScaleY((m_winSize.height) / size.height);
    m_background->setAnchorPoint({0, 0});

    m_background->setColor({120, 120, 120});
    m_background->setID("background"_spr);
    addChild(m_background, -2);

    auto arr = CCArray::create();
    auto dotMenu = CCMenu::create();

    createComic(arr, issueNumber);

    m_scrollLayer = BoomScrollLayer::create(arr, 0, false, nullptr, static_cast<DynamicScrollDelegate *>(this));
    m_scrollLayer->m_extendedLayer->m_delegate = static_cast<BoomScrollLayerDelegate *>(this);
    m_scrollLayer->m_looped = true;

    m_scrollLayer->instantMoveToPage(m_currentPage);
    addChild(m_scrollLayer);

    static_cast<CCSpriteBatchNode *>(m_scrollLayer->getChildren()->objectAtIndex(1))->setPositionY(-45);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyComicLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, m_winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    if (issueNumber == 4)
    {
        auto hollowSprite = CCSprite::createWithSpriteFrameName("HollowSkull_001.png"_spr);
        hollowSprite->setColor({50, 50, 50});
        hollowSprite->setOpacity(50);

        auto hollowBtn = CCMenuItemSpriteExtra::create(
            hollowSprite,
            this,
            menu_selector(OdysseyComicLayer::onHollow));

        hollowBtn->setPosition({m_winSize.width - 20, m_winSize.height - 20});
        hollowBtn->setTag(0);

        auto secretMenu = CCMenu::create();
        secretMenu->addChild(hollowBtn);
        secretMenu->setPosition({0, 0});
        addChild(secretMenu);
    };

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

    //  Mod::get()->setSettingValue<bool>("watched-comic-0" + std::to_string(m_comicNumber), true);
    GameManager::sharedState()->setUGV(fmt::format("2{}", m_comicNumber + 10).c_str(), true);

    //  Llama a la funcion para el logro secreto
    verifySecretAchievement();
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void OdysseyComicLayer::createComic(CCArray *arr, int issueNumber)
{
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");

    std::vector<ccColor3B> colors = {
        {33, 33, 33},
        {63, 6, 155},
        {0, 32, 59},
        {29, 24, 51},
        {173, 41, 66},
        {120, 0, 0}};

    m_background->setColor(colors[issueNumber - 1]);

    m_totalPages = (issueNumber == 1)   ? 9
                   : (issueNumber == 2) ? 5
                   : (issueNumber == 3) ? 4
                   : (issueNumber == 4) ? 4
                   : (issueNumber == 5) ? 9
                   : (issueNumber == 6) ? 6
                                        : 1;

    m_backgroundMusic = (issueNumber == 1)   ? "comic_01.mp3"_spr
                        : (issueNumber == 2) ? "comic_02.mp3"_spr
                        : (issueNumber == 3) ? "comic_03.mp3"_spr
                        : (issueNumber == 4) ? "comic_04.mp3"_spr
                        : (issueNumber == 5) ? "comic_05.mp3"_spr
                        : (issueNumber == 6) ? "comic_06.mp3"_spr
                                             : "shop5.mp3";

    for (int ii = 0; ii < m_totalPages; ii++)
    {
        auto pages = getPage(issueNumber, ii + 1);
        auto pageSprite = spanishText ? pages.second : pages.first;

        arr->addObject(createComicPage(pageSprite));
    };

    if (issueNumber < 1 || issueNumber > 6)
    {
        m_totalPages = 2;
        auto test = CCNode::create();
        auto menu = CCMenu::create();

        auto button = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("chest_02_02_001.png"),
            this,
            menu_selector(OdysseyComicLayer::onSecret));

        menu->addChild(button);
        test->addChild(menu);
        arr->addObject(test);
    };

    GameManager::sharedState()->fadeInMusic(m_backgroundMusic);
};

void OdysseyComicLayer::onHollow(CCObject *)
{
    if (!GameManager::sharedState()->getUGV("205"))
    {
        auto dialog = Odyssey::createDialog("meetingHollow");
        GameManager::sharedState()->setUGV("205", true);
        this->addChild(dialog, 3);
    }
    else
    {
        auto scene = CCScene::create();
        scene->addChild(SecretVaultLayer::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
};

std::pair<const char *, const char *> OdysseyComicLayer::getPage(int issueNumber, int page)
{
    std::pair<const char *, const char *> names;

    if (issueNumber == 1)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_01_01.png", "Comic_SPA_01_01.png"};
            break;

        case 2:
            return {"Comic_ENG_01_02.png", "Comic_SPA_01_02.png"};
            break;

        case 3:
            return {"Comic_ENG_01_03.png", "Comic_SPA_01_03.png"};
            break;

        case 4:
            return {"Comic_ENG_01_04.png", "Comic_SPA_01_04.png"};
            break;

        case 5:
            return {"Comic_ENG_01_05.png", "Comic_SPA_01_05.png"};
            break;

        case 6:
            return {"Comic_ENG_01_06.png", "Comic_SPA_01_06.png"};
            break;

        case 7:
            return {"Comic_ENG_01_07.png", "Comic_SPA_01_07.png"};
            break;

        case 8:
            return {"Comic_ENG_01_08.png", "Comic_SPA_01_08.png"};
            break;

        case 9:
            return {"Comic_ENG_01_09.png", "Comic_SPA_01_09.png"};
            break;
        }
    }

    if (issueNumber == 2)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_02_01.png", "Comic_SPA_02_01.png"};
            break;

        case 2:
            return {"Comic_ENG_02_02.png", "Comic_SPA_02_02.png"};
            break;

        case 3:
            return {"Comic_ENG_02_03.png", "Comic_SPA_02_03.png"};
            break;

        case 4:
            return {"Comic_ENG_02_04.png", "Comic_SPA_02_04.png"};
            break;

        case 5:
            return {"Comic_ENG_02_05.png", "Comic_SPA_02_05.png"};
            break;
        }
    }

    if (issueNumber == 3)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_03_01.png", "Comic_SPA_03_01.png"};
            break;

        case 2:
            return {"Comic_ENG_03_02.png", "Comic_SPA_03_02.png"};
            break;

        case 3:
            return {"Comic_ENG_03_03.png", "Comic_SPA_03_03.png"};
            break;

        case 4:
            return {"Comic_ENG_03_04.png", "Comic_SPA_03_04.png"};
            break;
        }
    }

    if (issueNumber == 4)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_04_01.png", "Comic_SPA_04_01.png"};
            break;

        case 2:
            return {"Comic_ENG_04_02.png", "Comic_SPA_04_02.png"};
            break;

        case 3:
            return {"Comic_ENG_04_03.png", "Comic_SPA_04_03.png"};
            break;

        case 4:
            return {"Comic_ENG_04_04.png", "Comic_SPA_04_04.png"};
            break;
        }
    }

    if (issueNumber == 5)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_05_01.png", "Comic_SPA_05_01.png"};
            break;

        case 2:
            return {"Comic_ENG_05_02.png", "Comic_SPA_05_02.png"};
            break;

        case 3:
            return {"Comic_ENG_05_03.png", "Comic_SPA_05_03.png"};
            break;

        case 4:
            return {"Comic_ENG_05_04.png", "Comic_SPA_05_04.png"};
            break;

        case 5:
            return {"Comic_ENG_05_05.png", "Comic_SPA_05_05.png"};
            break;

        case 6:
            return {"Comic_ENG_05_06.png", "Comic_SPA_05_06.png"};
            break;

        case 7:
            return {"Comic_ENG_05_07.png", "Comic_SPA_05_07.png"};
            break;

        case 8:
            return {"Comic_ENG_05_08.png", "Comic_SPA_05_08.png"};
            break;

        case 9:
            return {"Comic_ENG_05_09.png", "Comic_SPA_05_09.png"};
            break;
        }
    }

    if (issueNumber == 6)
    {
        switch (page)
        {
        case 1:
            return {"Comic_ENG_06_01.png", "Comic_SPA_06_01.png"};
            break;

        case 2:
            return {"Comic_ENG_06_02.png", "Comic_SPA_06_02.png"};
            break;

        case 3:
            return {"Comic_ENG_06_03.png", "Comic_SPA_06_03.png"};
            break;

        case 4:
            return {"Comic_ENG_06_04.png", "Comic_SPA_06_04.png"};
            break;

        case 5:
            return {"Comic_ENG_06_05.png", "Comic_SPA_06_05.png"};
            break;

        case 6:
            return {"Comic_ENG_06_06.png", "Comic_SPA_06_06.png"};
            break;
        }
    }

    return {"Comic_Error.png", "Comic_Error.png"};
};

CCNode *OdysseyComicLayer::createComicPage(const char *spriteName)
{
    auto node = CCNode::create();
    auto comicSprite = CCSprite::create(spriteName);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    comicSprite->setPosition(winSize / 2);
    comicSprite->setScale(1.9f);
    node->addChild(comicSprite);
    return node;
};

void OdysseyComicLayer::onSecret(CCObject *sender)
{
    AchievementNotifier::sharedState()->notifyAchievement("Programmer's secret", "Unlocked achievement!", "gk-icon", false);
    GJRewardObject *diamonds = GJRewardObject::create(SpecialRewardItem::Diamonds, 100, 0);

    CCArray *rewards = CCArray::create();
    rewards->addObject(diamonds);

    GJRewardItem *item = GJRewardItem::createWithObjects(GJRewardType::Large, rewards);
    RewardUnlockLayer *layer = RewardUnlockLayer::create(2, nullptr);
    layer->m_chestType = 2;

    // Put layer in scene
    cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer);
    layer->showCollectReward(item);

    auto btn = static_cast<CCMenuItemSpriteExtra *>(sender);
    btn->setVisible(false);
};

void OdysseyComicLayer::verifySecretAchievement(){
    int comicProgress = 0;
    for(auto ii = 1; ii <= 6; ii++){
        comicProgress += GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str());
        log::debug("Comic {}, UGV {}, Value {}", ii, fmt::format("2{}", ii + 10).c_str(), GameManager::sharedState()->getUGV(fmt::format("2{}", ii + 10).c_str()));
    };
    log::debug("Comic progress: {}", comicProgress);

    auto percent = (comicProgress * 100) / 6;
    log::info("Secret Comic Achievement progress: {}", percent);
    GameManager::sharedState()->reportAchievementWithID("geometry.ach.odyssey.secret19", percent, false);
};

void OdysseyComicLayer::scrollLayerMoved(CCPoint point)
{
    float transitionPoint = -point.x / CCDirector::sharedDirector()->getWinSize().width;
    int offset = std::floor(transitionPoint);

    if (transitionPoint == offset)
    {
        m_currentPage = offset % m_totalPages;
    }
};

void OdysseyComicLayer::keyBackClicked()
{
    if(m_RedirectToMap){
        auto layer = OdysseySelectLayer::create(0);
        auto scene = CCScene::create();
        scene->addChild(layer);

        CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        return;
    }

    GameManager::sharedState()->fadeInMusic("TheMap.mp3"_spr);
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void OdysseyComicLayer::onBack(CCObject *)
{
    keyBackClicked();
};

OdysseyComicLayer *OdysseyComicLayer::create(int issueNumber, bool redirectToMap)
{
    auto ret = new OdysseyComicLayer();

    if (ret->init(issueNumber, redirectToMap))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *OdysseyComicLayer::scene(int issueNumber, bool redirectToMap)
{
    auto layer = OdysseyComicLayer::create(issueNumber, redirectToMap);
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};