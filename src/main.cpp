#include <Geode/Geode.hpp>
using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>

#include "OdysseySelectLayer.h"

class $modify(MenuLayer)
{
	bool init()
	{
		if (!MenuLayer::init())
		{
			return false;
		}

		auto gameTitle = static_cast<CCSprite*>(this->getChildByID("main-title"));
		if (gameTitle)
		{
			auto odysseyTitle = CCSprite::createWithSpriteFrameName("GDODYSSEY_logo_001.png"_spr);
			gameTitle->setDisplayFrame(odysseyTitle->displayFrame());

			gameTitle->setPositionY(gameTitle->getPositionY() - 20);
		}
		
		auto mainMenu = static_cast<CCMenu*>(this->getChildByID("main-menu"));

		auto creatorButton = static_cast<CCMenuItemSpriteExtra*>(mainMenu->getChildByID("editor-button"));
		if (creatorButton)
		{
			auto mgSprite = CCSprite::createWithSpriteFrameName("GJ_moreGamesBtn_001.png");
			static_cast<CCSprite*>(creatorButton->getChildren()->objectAtIndex(0))->setDisplayFrame(mgSprite->displayFrame());
		}


		auto mgButton = static_cast<CCMenuItemSpriteExtra*>(this->getChildByID("more-games-menu")->getChildByID("more-games-button"));
		if (mgButton)
		{
			auto creditsSpr = CCSprite::createWithSpriteFrameName("GJL_creditsBtn_001.png"_spr);
			static_cast<CCSprite*>(mgButton->getChildren()->objectAtIndex(0))->setDisplayFrame(creditsSpr->displayFrame());
		}


		return true;
	}

	void onPlay(CCObject *)
	{
		auto scene = CCScene::create();
		scene->addChild(OdysseySelectLayer::create());

		CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
	}
};