#include "OdysseyDevLayer.hpp"
#include "OdysseyComicLayer.hpp"
#include "../utils/Utils.hpp"

bool OdysseyDevLayer::init()
{
    if (!CCLayer::init())
        return false;

    m_background = CCSprite::create("game_bg_07_001.png");
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto size = m_background->getContentSize();

    m_background->setScale(winSize.width / size.width);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, -75});
    m_background->setColor({0, 0, 60});
    m_background->setID("background"_spr);

    addChild(m_background, -2);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(OdysseyDevLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);

    auto menuBack = CCMenu::create();
    menuBack->addChild(backBtn);
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    auto dialogMenu = CCMenu::create();
    dialogMenu->setID("dialog-menu"_spr);
    dialogMenu->setContentSize({350.0f, 220.0f});
    dialogMenu->setLayout(RowLayout::create()
                              ->setGap(14.0f)
                              ->setAutoScale(false)
                              ->setGrowCrossAxis(true)
                              ->setCrossAxisOverflow(false)
                              ->setCrossAxisLineAlignment(AxisAlignment::Even));

    auto carp01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Shop)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onCarp01));

    auto carp02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Extras)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onCarp02));
    carp02->setTag(0);

    auto carp03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (Comic)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onCarp03));
    carp03->setTag(0);

    auto carp04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Carp (No Coins)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onCarp04));
    carp04->setTag(0);

    auto wizard01 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Introduction)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onWizard01));

    auto wizard02 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Island)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onWizard02));

    auto wizard03 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Finale)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onWizard03));

    auto wizard04 = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Dumbledalf (Access)", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onWizard04));

    auto comic = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Comics", 0.75f),
        this,
        menu_selector(OdysseyDevLayer::onComic));

    dialogMenu->addChild(carp01);
    dialogMenu->addChild(carp02);
    dialogMenu->addChild(carp03);
    dialogMenu->addChild(carp04);
    dialogMenu->addChild(wizard01);
    dialogMenu->addChild(wizard02);
    dialogMenu->addChild(wizard03);
    dialogMenu->addChild(wizard04);
    dialogMenu->addChild(comic);
    dialogMenu->updateLayout();

    addChild(dialogMenu);

    setKeypadEnabled(true);
    return true;
};

void OdysseyDevLayer::onComic(CCObject *)
{
    auto scene = CCScene::create();
    scene->addChild(OdysseyComicLayer::create());

    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
};

void OdysseyDevLayer::onCarp01(CCObject *)
{
    auto dialog = Odyssey::createDialog("shopIntroduction");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp02(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("extraIslandLocked", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);

    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp03(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("finalComicLocked", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
              : (sender->getTag() == 2) ? 3
              : (sender->getTag() == 3) ? 4
              : (sender->getTag() == 4) ? 5
                                        : 0;
    sender->setTag(tag);
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onCarp04(CCObject *sender)
{
    auto dialog = Odyssey::createDialogResponse("playerIsPoor", sender->getTag());

    int tag = (sender->getTag() == 0)   ? 1
              : (sender->getTag() == 1) ? 2
                                        : 0;

    sender->setTag(tag);

    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard01(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardIntroduction");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard02(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardIslandComplete");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard03(CCObject *)
{
    auto dialog = Odyssey::createDialog("wizardEnding");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::onWizard04(CCObject *)
{
    auto dialog = Odyssey::createDialog("blockedAccess");
    this->addChild(dialog, 3);
};

void OdysseyDevLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
};

void OdysseyDevLayer::onBack(CCObject *)
{
    keyBackClicked();
};

OdysseyDevLayer *OdysseyDevLayer::create()
{
    auto ret = new OdysseyDevLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *OdysseyDevLayer::scene()
{
    auto layer = OdysseyDevLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};