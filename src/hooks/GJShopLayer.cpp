#include <Geode/Geode.hpp>
#include <Geode/modify/GJShopLayer.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyShopLayer, GJShopLayer)
{
	bool init(ShopType p0)
	{
		if (!GJShopLayer::init(ShopType{6}))
			return false;

		FMODAudioEngine::sharedEngine()->playMusic("Shop.mp3"_spr, true, 0.1f, 0);

		auto children = getChildren();

		auto background = static_cast<CCSprite*>(children->objectAtIndex(0));
		background->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopBG_001.png"_spr)->displayFrame());

		auto shopSign = static_cast<CCSprite*>(children->objectAtIndex(1));
		shopSign->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopSign_001.png"_spr)->displayFrame());

		auto desk = static_cast<CCSprite*>(children->objectAtIndex(3));
		desk->setDisplayFrame(CCSprite::createWithSpriteFrameName("storeDesk_001.png"_spr)->displayFrame());

		auto particle = static_cast<CCParticleSystemQuad*>(children->objectAtIndex(7));
		particle->setStartColor({ 193, 122, 5, 255 });
		particle->setEndColor({ 255, 122, 0, 0 });

		auto currency = static_cast<CCSprite*>(children->objectAtIndex(6));

		if (!GameManager::sharedState()->getUGV("204"))
		{
			this->runAction(CCSequence::create(
				CCDelayTime::create(0.5f),
				CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::getCarpDialog)),
				0));
		};

		return true;
	}

	void getCarpDialog()
	{
		auto dialog = Odyssey::createDialog("shopIntroduction");
		GameManager::sharedState()->setUGV("204", true);
		this->addChild(dialog, 200);
	}

	void onBack(CCObject *)
	{
		auto director = CCDirector::sharedDirector();
		auto winSize = director->getWinSize();

		this->retain();
		this->removeFromParentAndCleanup(false);

		auto garage = GJGarageLayer::scene();
		director->replaceScene(garage);
		garage->addChild(this, 1000);

		this->release();

		auto moveTo = CCMoveTo::create(0.3f, ccp(0, winSize.height));
		auto easeIn = CCEaseIn::create(moveTo, 2.0f);
		auto callFunc = CCCallFunc::create(this, callfunc_selector(OdysseyShopLayer::removeFromParent));

		auto ccSeq = CCSequence::create(easeIn, callFunc, 0);
		this->runAction(ccSeq);
		GameManager::sharedState()->fadeInMenuMusic();

		setKeyboardEnabled(false);
		setKeypadEnabled(false);
	}
};