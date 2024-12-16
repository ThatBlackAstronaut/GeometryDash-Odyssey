#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include "../layers/OdysseySelectLayer.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyShopLayer, GJShopLayer)
{
	bool init(ShopType p0)
	{
		if (!GJShopLayer::init(ShopType{6}))
			return false;

		FMODAudioEngine::sharedEngine()->playMusic("Shop.mp3"_spr, true, 0.1f, 0);

		/*
		auto children = getChildren();

		auto background = static_cast<CCSprite*>(children->objectAtIndex(0));
		background->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopBG_001.png"_spr)->displayFrame());

		auto shopSign = static_cast<CCSprite*>(children->objectAtIndex(1));
		shopSign->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopSign_001.png"_spr)->displayFrame());

		auto desk = static_cast<CCSprite*>(children->objectAtIndex(3));
		desk->setDisplayFrame(CCSprite::createWithSpriteFrameName("storeDesk_001.png"_spr)->displayFrame());
		desk->setPositionY(93);

		auto currency = static_cast<CCSprite*>(children->objectAtIndex(6));
		*/
		auto extraMenu = CCMenu::create();
		extraMenu->setPosition({0, 0});
		
		auto spriteTV = CCSprite::createWithSpriteFrameName("gj_videoRewardBtn_001.png");
		spriteTV->setScale(0.9f);

		auto buttonTV = CCMenuItemSpriteExtra::create(
			spriteTV,
			this,
			menu_selector(OdysseyShopLayer::onPlayVideo)
		);

		buttonTV->setPosition({250, 222});
		buttonTV->m_scaleMultiplier = 1;
		buttonTV->m_colorEnabled = true;
		buttonTV->m_colorDip = 100;

		extraMenu->addChild(buttonTV);
		this->addChild(extraMenu);
	
		auto particle = static_cast<CCParticleSystemQuad*>(getChildren()->objectAtIndex(7));
		particle->setStartColor({ 193, 122, 5, 255 });
		particle->setEndColor({ 255, 122, 0, 0 });

		auto winSize = CCDirector::sharedDirector()->getWinSize();
		int rand = (std::rand() % 3) + 1;

		auto wantedPoster = CCSprite::createWithSpriteFrameName(fmt::format("GDO_Wanted0{}_001.png"_spr, rand).c_str());
		wantedPoster->setPosition({(winSize.width / 4) + (std::rand() % 3 * 40), winSize.height / 2 + 65.f});
		wantedPoster->setScale(0.8f);
		wantedPoster->setZOrder(-1);

		this->addChild(wantedPoster);

		auto GSM = GameStatsManager::sharedState();

		if (!GameManager::sharedState()->getUGV("204"))
		{
			this->runAction(CCSequence::create(
				CCDelayTime::create(0.5f),
				CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::getCarpDialog)),
				0));
		};

		return true;
	}

	void onPlayVideo(CCObject *){
		std::vector<gd::string>  videoLinks = {
			"https://youtu.be/34ajXNmtI4U?si=cLptfnth-uhYDq9E",
			"https://youtu.be/aRdpABVEKho?si=2huyHafEWQFz1R58",
			"https://youtu.be/uvN5OGo_fcY?si=piU_ncFAZvQJCUUD",
			"https://youtu.be/abB1-zyyHSI?si=1XBhha5sC1ho9MqU"
		};

		CCApplication::sharedApplication()->openURL(videoLinks.at(rand() % videoLinks.size()).c_str());
	}

	void getCarpDialog()
	{
		auto dialog = Odyssey::createDialog("meetingShopkeeper");
		GameManager::sharedState()->setUGV("204", true);
		this->addChild(dialog, 200);
	}

	void onBack(CCObject *)
	{
		auto director = CCDirector::sharedDirector();
		auto winSize = director->getWinSize();

		this->retain();
		this->removeFromParentAndCleanup(false);

		auto selectLayer = OdysseySelectLayer::scene(GameManager::sharedState()->getIntGameVariable("1001") - 1);
		director->replaceScene(selectLayer);
		selectLayer->addChild(this, 1000);

		this->release();

		auto moveTo = CCMoveTo::create(0.3f, ccp(0, winSize.height));
		auto easeIn = CCEaseIn::create(moveTo, 2.0f);
		auto callFunc = CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::removeFromParent));

		auto ccSeq = CCSequence::create(easeIn, callFunc, 0);
		this->runAction(ccSeq);

		setKeyboardEnabled(false);
		setKeypadEnabled(false);
	}
};