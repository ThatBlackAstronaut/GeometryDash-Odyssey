#include "FanmadeGamesLayer.hpp"
#include "FanmadeGamesCell.hpp"
#include "FanmadeGamesCell.hpp"

void FanmadeGamesLayer::customSetup()
{
    m_games = CCArray::create();

    //  Nexitron
    auto game_01 = FanmadeGamesCell::create("Promo_GDNX.png"_spr, this, menu_selector(FanmadeGamesLayer::onNexitron));
    game_01->setTag(0);

    //  Time Reborn
    auto game_02 = FanmadeGamesCell::create("Promo_GDTR.png"_spr, this, nullptr);
    game_02->setTag(1);

    //  Mega World
    auto game_03 = FanmadeGamesCell::create("Promo_GDMW.png"_spr, this, nullptr);
    game_03->setTag(2);

    //  Unnamed GDPS
    auto game_04 = FanmadeGamesCell::create("Promo_UGDPS.png"_spr, this, nullptr);
    game_04->setTag(3);

    //  Lightsync
    auto game_05 = FanmadeGamesCell::create("Promo_LIGHT.png"_spr, this, nullptr);
    game_05->setTag(4);

    //  GDNA
    auto game_06 = FanmadeGamesCell::create("Promo_GDNA.png"_spr, this, nullptr);
    game_06->setTag(5);

    m_games->addObject(game_01);
    m_games->addObject(game_02);
    m_games->addObject(game_03);
    m_games->addObject(game_04);
    m_games->addObject(game_05);
    m_games->addObject(game_06);

    auto *listView = ListView::create(m_games, 118.0f);
    m_listLayer->addChild(listView);
};

void FanmadeGamesLayer::onNexitron(CCObject *sender)
{
    CCApplication::sharedApplication()->openURL("https://gamejolt.com/games/nexitron/797397");
};

FanmadeGamesLayer *FanmadeGamesLayer::create()
{
    auto ret = new FanmadeGamesLayer();

    if (ret->init("Test"))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};