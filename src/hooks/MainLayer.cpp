#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseyCreditsLayer.hpp"
#include "../nodes/OdysseyCreditNode.hpp"
#include "../layers/OdysseySelectLayer.hpp"
#include "../layers/OdysseyDevLayer.hpp"
#include "../layers/FanmadeGamesLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

        //  Reemplaza el titulo
        auto gameTitle = static_cast<CCSprite *>(this->getChildByID("main-title"));
        if (gameTitle)
        {
            auto odysseyTitle = CCSprite::createWithSpriteFrameName("GDO_MainLogo_001.png"_spr);
            gameTitle->setDisplayFrame(odysseyTitle->displayFrame());
            gameTitle->setPositionY(gameTitle->getPositionY() - 15);
        }

        //  Reemplazar el boton para acceder al Menu Online
        auto mainMenu = static_cast<CCMenu *>(this->getChildByID("main-menu"));
        auto creatorButton = static_cast<CCMenuItemSpriteExtra *>(mainMenu->getChildByID("editor-button"));
        if (creatorButton)
        {
            auto mgSprite = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");

            //  Esto cambiara mas tarde
            creatorButton->setNormalImage(mgSprite);
        }

        //  Boton para acceder a los comics mas facil
        auto bottomMenu = static_cast<CCMenu *>(this->getChildByID("bottom-menu"));
        auto seenComic = Mod::get()->getSettingValue<bool>("watched-comic-01");

        auto geodeButton = bottomMenu->getChildByID("geode.loader/geode-button");
        geodeButton->removeFromParentAndCleanup(false);

        if (seenComic)
        {
            auto comicButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_comicBtn.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                nullptr);

            bottomMenu->addChild(comicButton);
        }

        auto devButton = CCMenuItemSpriteExtra::create(
            CircleButtonSprite::createWithSpriteFrameName("geode.loader/settings.png", 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
            this,
            menu_selector(OdysseyMenuLayer::onDev));

        bottomMenu->addChild(devButton);
        bottomMenu->addChild(geodeButton);
        bottomMenu->updateLayout();

        //  Boton de more games es reemplazado por Creditos
        auto moreGamesMenu = static_cast<CCMenu *>(this->getChildByID("more-games-menu"));
        auto moreGamesButton = static_cast<CCMenuItemSpriteExtra *>(moreGamesMenu->getChildByID("more-games-button"));
        if (moreGamesButton)
        {
            auto creditsSprite = CCSprite::createWithSpriteFrameName("GDO_CreditsBtn_001.png"_spr);
            creditsSprite->setScale(0.9f);
            moreGamesButton->setTag(1);

            //  Esto cambiara mas tarde
            moreGamesButton->setNormalImage(creditsSprite);
        }

        if (auto levelEditorHint = static_cast<CCSprite *>(this->getChildByID("level-editor-hint")))
            levelEditorHint->setVisible(false);

        return true;
    }

    void onDev(CCObject *)
    {
        auto scene = CCScene::create();
        scene->addChild(OdysseyDevLayer::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }

    void onPlay(CCObject *)
    {
        auto levelscene = OdysseySelectLayer::scene(0);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, levelscene));
    }

    void onCreator(CCObject *sender)
    {
        auto showFanmades = Mod::get()->getSettingValue<bool>("show-more-games");

        if (showFanmades)
        {
            auto *layer = FanmadeGamesLayer::create();
            addChild(layer, 100);

            layer->showLayer(false);
            return;
        }

        MenuLayer::onCreator(sender);
    }

    void onMoreGames(CCObject *)
    {
        // auto credits = FLAlertLayer::create("Si", "Si", "ok");
        // credits->show();
        /*
        auto shop = GJShopLayer::scene(static_cast<ShopType>(6));

        CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInT::create(.63f, shop));
        */

        auto credits = OdysseyCreditsLayer::create();
        credits->show();
    }
};