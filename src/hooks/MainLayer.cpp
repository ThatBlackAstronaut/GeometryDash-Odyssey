#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseyCreditsLayer.hpp"
#include "../layers/OdysseySelectLayer.hpp"
#include "../layers/OdysseyDevLayer.hpp"
#include "../layers/FanmadeGamesLayer.hpp"
#include "../nodes/OdysseyCreditNode.hpp"
#include "../nodes/OdysseyPopup.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyMenuLayer, MenuLayer)
{
    bool init()
    {
        if (!MenuLayer::init())
            return false;

        if (Mod::get()->getSettingValue<bool>("reset-variables"))
            OdysseyMenuLayer::Restart();

        if (!GameManager::sharedState()->getUGV("201"))
        {
            auto popup = OdysseyPopup::create("Savefile Notice", "<cr>Odyssey</c> stores the data in\na separate <cy>savefile</c>. Your data\nwill be <cg>restored</c> when you\n<cb>turn off</c> the Mod.");
            popup->setWarning(true, false);
            popup->m_scene = this;
            popup->show();
        };

        if (!GameManager::sharedState()->getUGV("202") && GameManager::sharedState()->getGameVariable("0201"))
        {
            auto popup = OdysseyPopup::create("Language Notice", "Dado a limitaciones de\ncaracteres en el juego, habran\n<cr>errores ortograficos</c>\n(como la falta de acentos)");
            popup->setWarning(false, true);
            popup->setZOrder(104);
            popup->m_scene = this;
            popup->show();
        };

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

        /*
        auto seenComic = GameManager::sharedState()->getUGV("222");
        if (seenComic)
        {
            auto comicButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("GDO_ComicIcon_001.png"_spr, 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                nullptr);

            bottomMenu->addChild(comicButton);
        }
        */

        if (Mod::get()->getSettingValue<bool>("dev-mode"))
        {
            auto devButton = CCMenuItemSpriteExtra::create(
                CircleButtonSprite::createWithSpriteFrameName("geode.loader/settings.png", 1, CircleBaseColor::Green, CircleBaseSize::MediumAlt),
                this,
                menu_selector(OdysseyMenuLayer::onDev));

            bottomMenu->addChild(devButton);
            bottomMenu->updateLayout();
        }

        //  Boton de more games es reemplazado por Creditos
        auto moreGamesMenu = static_cast<CCMenu *>(this->getChildByID("more-games-menu"));
        auto moreGamesButton = static_cast<CCMenuItemSpriteExtra *>(moreGamesMenu->getChildByID("more-games-button"));
        if (moreGamesButton)
        {
            auto creditsSprite = CrossButtonSprite::createWithSpriteFrameName("GDO_CreditsIcon_001.png"_spr, 1.5f);
            creditsSprite->setScale(0.9f);
            moreGamesButton->setTag(1);

            //  Esto cambiara mas tarde
            moreGamesButton->setNormalImage(creditsSprite);
        }

        if (auto levelEditorHint = static_cast<CCSprite *>(this->getChildByID("level-editor-hint")))
            levelEditorHint->setVisible(false);

        auto rightMenu = static_cast<CCMenu *>(this->getChildByID("right-side-menu"));

        auto dailyCButton = static_cast<CCMenuItemSpriteExtra *>(rightMenu->getChildByID("daily-chest-button"));
        if (dailyCButton)
            dailyCButton->setVisible(false);

        auto dict = GameManager::sharedState()->m_valueKeeper;
        auto keys = dict->allKeys();

        for (int i = 0; i < keys->count(); ++i)
        {
            CCString *key = (CCString *)keys->objectAtIndex(i);
            CCString *value = (CCString *)dict->objectForKey(key->getCString());

            log::info("Key: {} Value: {} \n", key->getCString(), value->getCString());
        };

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

        if (!showFanmades)
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
        GameManager::sharedState();

        auto credits = OdysseyCreditsLayer::create();
        credits->show();
    }

    void Restart()
    {
        Mod::get()->setSettingValue<bool>("reset-variables", false);

        for (auto ii = 1; ii <= 60; ii++)
        {
            auto variable = (ii < 10) ? fmt::format("20{}", ii) : fmt::format("2{}", ii);
            GameManager::sharedState()->setUGV(variable.c_str(), false);
            log::info("Restarting UGV = {}", variable);
        };

        /*  REINICIA TODO PARA EL JUGADOR, SOLAMENTE EN DEV
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7001, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7002, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7003, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7004, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7005, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7006, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7007, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7008, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7009, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7501, true));
        GameStatsManager::sharedState()->uncompleteLevel(GameLevelManager::sharedState()->getMainLevel(7502, true));
        */

        log::info("Variables succesfully restarted");
    }
};