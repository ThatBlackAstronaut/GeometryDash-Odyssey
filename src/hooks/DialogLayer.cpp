#include <Geode/Geode.hpp>
#include <Geode/modify/DialogLayer.hpp>
#include "../layers/OdysseyComicLayer.hpp"

using namespace geode::prelude;

class $modify(OdysseyDialogLayer, DialogLayer)
{
    void onClose()
    {
        if(GameManager::sharedState()->getUGV("203") && !GameManager::sharedState()->getUGV("211"))
        {
            auto layer = OdysseyComicLayer::create(1, true);
            auto scene = CCScene::create();
            scene->addChild(layer);

            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        };

        if(GameManager::sharedState()->getUGV("207") && !GameManager::sharedState()->getUGV("216"))
        {
            auto layer = OdysseyComicLayer::create(6, true);
            auto scene = CCScene::create();
            scene->addChild(layer);

            CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, scene));
        };

        DialogLayer::onClose();
    };
};