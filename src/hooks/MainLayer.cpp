#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseySelectLayer.h"
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
        }

        //  Reemplazar el boton para acceder al Menu Online
        auto mainMenu = static_cast<CCMenu *>(this->getChildByID("main-menu"));
        auto creatorButton = static_cast<CCMenuItemSpriteExtra *>(mainMenu->getChildByID("editor-button"));
        if (creatorButton)
        {
            auto mgSprite = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");

            //  Esto cambiara mas tarde
            //  static_cast<CCSprite *>(creatorButton->getChildren()->objectAtIndex(0))->setDisplayFrame(mgSprite->displayFrame());
        }

        auto moreGamesMenu = static_cast<CCMenu *>(this->getChildByID("more-games-menu"));
        auto moreGamesButton = static_cast<CCMenuItemSpriteExtra *>(moreGamesMenu->getChildByID("more-games-button"));
        if (moreGamesButton)
        {
            auto creditsSprite = CCSprite::createWithSpriteFrameName("GDO_CreditsBtn_001.png"_spr);
            creditsSprite->setScale(0.9f);

            //  Esto cambiara mas tarde
            static_cast<CCSprite *>(moreGamesButton->getChildren()->objectAtIndex(0))->setDisplayFrame(creditsSprite->displayFrame());
        }

        return true;
    }

    void onPlay(CCObject *)
    {
        auto scene = CCScene::create();
        scene->addChild(OdysseySelectLayer::create());

        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }

    void onCreator(CCObject *)
    {
        auto dialog = Odyssey::createDialog("on_creator");
        this->addChild(dialog, 3);
    }

    void onMoreGames(CCObject *)
    {
        auto credits = FLAlertLayer::create("Si", "Si", "ok");
        credits->show();
    }
};