#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "../layers/OdysseySelectLayer.h"
#include "../utils/OdysseyDialog.hpp"

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
        CCArray *arr = CCArray::create();
        int color = 2;

        auto spanishText = Mod::get()->getSettingValue<bool>("spanish-language");

        if (spanishText)
        {
            auto dialog_01 = DialogObject::create("????", "<s250>ORALE CHAMACO, ALTO.</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "Mis disculpas, <d020><cy>Jugador...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "Tendras que <cr>deshabilitar</c> el mod para acceder al resto del juego.", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Medidas de seguridad, <d020>¿sabes?", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }
        else
        {
            auto dialog_01 = DialogObject::create("????", "<s250>YOU SHALL NOT PASS</s>", 55, 1, false, {255, 255, 255});
            auto dialog_02 = DialogObject::create("????", "I'm sorry,<d010> <cy>Player...</c>", 56, 1, false, {255, 255, 255});
            auto dialog_03 = DialogObject::create("????", "You have to <cr>disable</c> the Mod to have access...", 56, 1, false, {255, 255, 255});
            auto dialog_04 = DialogObject::create("????", "Safety measures,<d020> ya know?", 53, 1, false, {255, 255, 255});

            arr->addObject(dialog_01);
            arr->addObject(dialog_02);
            arr->addObject(dialog_03);
            arr->addObject(dialog_04);
        }

        auto dl = DialogLayer::createDialogLayer(nullptr, arr, color);
        dl->animateInRandomSide();
        dl->setZOrder(2);

        this->addChild(dl, 3);
    }

    void onMoreGames(CCObject *)
    {
        auto dl = OdysseyDialog::create("welcome", false);

        dl->animateInRandomSide();
        dl->setZOrder(2);

        this->addChild(dl, 3);
    }
};