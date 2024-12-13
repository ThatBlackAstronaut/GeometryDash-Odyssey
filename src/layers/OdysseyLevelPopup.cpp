#include "OdysseyLevelPopup.hpp"
#include "OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

bool OdysseyLevelPopup::setup(std::string const &title)
{
    //  El Nivel
    m_level = GameLevelManager::get()->getMainLevel(m_levelID, true);
    m_level->m_levelString = LocalLevelManager::get()->getMainLevelString(m_levelID);
    auto contentSize = m_mainLayer->getContentSize();

    //  Titulo
    setTitle(m_level->m_levelName);
    m_title->limitLabelWidth(200, .85f, .1f);
    m_title->setPositionY(m_title->getPositionY() - 5.0f);

    //  Boton de Cerrar
    m_closeBtn->setPosition(m_closeBtn->getPositionX() + 5, m_closeBtn->getPositionY() - 5);

    //  Esquinas del Layer
    Odyssey::addCorners(m_mainLayer, "dailyLevelCorner_001.png", 0);

    //  La cara de Dificultad
    auto difficultyNode = Odyssey::createDifficultyNode(m_level->m_difficulty, m_level->m_stars);
    difficultyNode->setPosition({contentSize.width / 5, contentSize.height / 2 + 25});
    difficultyNode->setAnchorPoint({0.5f, 0.5f});
    difficultyNode->setID("difficulty-node"_spr);
    m_mainLayer->addChild(difficultyNode);

    //  Barra de progreso en Normal
    auto normalProgress = Odyssey::createProgressBar(m_level->m_normalPercent, false);
    normalProgress->setPosition({contentSize.width / 2, contentSize.height / 2 - 55.0f});
    normalProgress->setID("normal-progress-node"_spr);
    m_mainLayer->addChild(normalProgress);

    //  Barra de progreso en Practica
    auto practiceProgress = Odyssey::createProgressBar(m_level->m_practicePercent, true);
    practiceProgress->setPosition({contentSize.width / 2, normalProgress->getPositionY() - 40.0f});
    practiceProgress->setID("practice-progress-node"_spr);
    m_mainLayer->addChild(practiceProgress);

    //  Menu de Botones
    auto buttonsMenu = CCMenu::create();
    buttonsMenu->setContentSize(m_mainLayer->getContentSize());
    buttonsMenu->setID("buttons-menu"_spr);
    buttonsMenu->setPosition({0, 0});
    m_mainLayer->addChild(buttonsMenu);

    //  Play Button
    auto playButton = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png"),
        this,
        menu_selector(OdysseyLevelPopup::onPlay));
    playButton->setPosition({buttonsMenu->getContentWidth() / 2, buttonsMenu->getContentHeight() / 2 + 30.f});
    playButton->setID("play-button"_spr);

    //  Level stats
    std::string levelName = static_cast<gd::string>(m_level->m_levelName);
    std::string levelInfo = "<cy>" + levelName + "</c>" + "\n<cg>Total Attempts</c>: " + std::to_string(m_level->m_attempts) + "\n<cl>Total Jumps</c>: " + std::to_string(m_level->m_jumps) + "\n<cp>Normal</c>: " + std::to_string(m_level->m_normalPercent) + "%" + "\n<co>Practice</c>: " + std::to_string(m_level->m_practicePercent) + "%";

    //  Info Button
    auto infoButton = InfoAlertButton::create("Level Stats", levelInfo, 1);
    infoButton->setPosition({buttonsMenu->getContentWidth() - 20.f, buttonsMenu->getContentHeight() - 20.f});

    //  Options Button
    auto optionsSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
    //  optionsSprite->setScale(.8f);

    auto optionsButton = CCMenuItemSpriteExtra::create(
        optionsSprite,
        this,
        menu_selector(OdysseyLevelPopup::onSettings));
    optionsButton->setPosition({8, 8});

    auto seenComic = GameManager::sharedState()->getUGV(fmt::format("2{}", m_levelID + 11).c_str());
    auto baseColor = seenComic ? CircleBaseColor::Green : CircleBaseColor::Cyan;

    //  Comics Button
    auto comicButton = CCMenuItemSpriteExtra::create(
        CircleButtonSprite::createWithSpriteFrameName("GDO_comicBtn.png"_spr, 1, baseColor, CircleBaseSize::Small),
        this,
        menu_selector(OdysseyLevelPopup::onComic));
    comicButton->setPosition({buttonsMenu->getContentWidth() - 8, 8});

    if (!seenComic)
    {
        comicButton->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(
            CCEaseSineOut::create(CCScaleTo::create(0.5f, 1.5)),
            CCEaseSineIn::create(CCScaleTo::create(0.5f, 1)))));
    }

    //  Adding the buttons
    buttonsMenu->addChild(playButton);
    buttonsMenu->addChild(infoButton);
    buttonsMenu->addChild(comicButton);
    buttonsMenu->addChild(optionsButton);

    if(m_levelID > 5){
        comicButton->setVisible(false);
    }

    //  Coin Array
    auto coinMenu = CCMenu::create();
    coinMenu->setContentSize({80.0f, 25.f});

    auto coinArray = CCArray::create();
    for(int i = 0; i < 3; i++) {
        bool isCollected = GameStatsManager::sharedState()->hasSecretCoin(fmt::format("{}_{}", m_level->m_levelID.value(), i + 1).c_str());

        auto node = CCSprite::createWithSpriteFrameName(isCollected ? "GJ_coinsIcon_001.png" : "GJ_coinsIcon_gray_001.png");

        coinArray->addObject(node);
        coinMenu->addChild(node);
    }

    coinMenu->alignItemsHorizontally();
    coinMenu->setPosition(m_mainLayer->getContentWidth() / 2, 6.f);
    m_mainLayer->addChild(coinMenu);

    return true;
};

void OdysseyLevelPopup::onPlay(CCObject *sender)
{
    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    FMODAudioEngine::sharedEngine()->playEffect("playSound_01.ogg");
    button->setEnabled(false);

    auto GLM = GameLevelManager::sharedState();
    auto playLayer = PlayLayer::scene(m_level, false, false);

    CCScene *scene = CCScene::create();
    scene->addChild(playLayer);

    CCTransitionFade *fade = CCTransitionFade::create(0.5f, scene);
    CCDirector::sharedDirector()->pushScene(fade);
};

void OdysseyLevelPopup::onSettings(CCObject *sender)
{
    auto layer = GameLevelOptionsLayer::create(m_level);
    layer->show();
};

void OdysseyLevelPopup::onComic(CCObject *sender)
{
    auto scene = CCScene::create();
    scene->addChild(OdysseyComicLayer::create(m_levelID + 1, false));

    auto button = static_cast<CCMenuItemSpriteExtra *>(sender);
    button->setSprite(CircleButtonSprite::createWithSpriteFrameName("GDO_comicBtn.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::Small));

    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

OdysseyLevelPopup *OdysseyLevelPopup::create(int levelID)
{
    auto ret = new OdysseyLevelPopup();
    ret->m_levelID = levelID;

    if (ret && ret->initAnchored(360.f, 260.f, ""))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
};