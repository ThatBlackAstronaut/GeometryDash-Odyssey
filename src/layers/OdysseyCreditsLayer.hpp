#pragma once
using namespace geode::prelude;

#include "../nodes/OdysseyCreditNode.hpp"

class OdysseyCreditsLayer : public geode::Popup<>
{
public:
    // virtual void keyDown(cocos2d::enumKeyCodes key);
    CCMenuItemSpriteExtra *m_fowardTabBtn = nullptr;
    CCMenuItemSpriteExtra *m_backTabBtn = nullptr;

    cocos2d::CCMenu *m_fowardTabMenu = nullptr;
    cocos2d::CCMenu *m_backTabMenu = nullptr;

    cocos2d::CCLayer *m_creditsmoddevLayer = nullptr;
    cocos2d::CCLayer *m_creditsrobLayer = nullptr;
    cocos2d::CCLayer *m_creditsOrgLayer = nullptr;
    cocos2d::CCLayer *m_creditsCreatorsLayer = nullptr;
    cocos2d::CCLayer *m_creditsArtLayer = nullptr;
    cocos2d::CCLayer *m_creditsPlayTestLayer = nullptr;

    cocos2d::extension::CCScale9Sprite *m_bgSprite02 = nullptr;
    cocos2d::extension::CCScale9Sprite *bgLayer = nullptr;
    CCLabelBMFont *creditsLabel = nullptr;

    int m_tab = 0;
    int m_lastTab = 5;

protected:
    bool setup()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();
        auto bg_LayerSprite02 = CCLayer::create();

        m_bgSprite02 = cocos2d::extension::CCScale9Sprite::create("GJ_square06.png", {0, 0, 80, 80});
        m_bgSprite02->setContentSize({430.0f, 270.0f});
        m_bgSprite02->setPosition(winSize.width / 2, winSize.height / 2);

        creditsLabel = CCLabelBMFont::create("Credits", "bigFont.fnt");
        creditsLabel->setPosition(ccp(winSize.width / 2, m_bgSprite02->getPositionY() + 112));

        auto lineDeco = CCSprite::createWithSpriteFrameName("floorLine_001.png");
        lineDeco->setScale(0.65f);
        lineDeco->setPosition({m_bgSprite02->getPositionX(), creditsLabel->getPositionY() - 20});

        bgLayer = cocos2d::extension::CCScale9Sprite::create("square02c_001.png", {0, 0, 80, 80});
        bgLayer->setContentSize({375, 200});
        bgLayer->setOpacity(75);
        bgLayer->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 15));

        m_creditsmoddevLayer = CCLayer::create();
        m_creditsmoddevLayer->setID("creditsModDev-tab"_spr);

        m_creditsrobLayer = CCLayer::create();
        m_creditsrobLayer->setID("creditsRobTop-tab"_spr);

        m_creditsOrgLayer = CCLayer::create();
        m_creditsOrgLayer->setID("creditsOrg-tab"_spr);

        m_creditsCreatorsLayer = CCLayer::create();
        m_creditsCreatorsLayer->setID("creditsCreators-tab"_spr);

        m_creditsArtLayer = CCLayer::create();
        m_creditsArtLayer->setID("creditsArtists-tab"_spr);

        m_creditsPlayTestLayer = CCLayer::create();
        m_creditsPlayTestLayer->setID("creditsPlayTesters-tab"_spr);

        setupCreditsOrgTab();
        setupCreditsModDeveloperTab();
        setupCreditsCreatorsTab();
        setupCreditsArtistsTab();
        setupCreditsTestersTab();
        setupCreditsSpecialThanksTab();

        bg_LayerSprite02->addChild(m_bgSprite02);
        bg_LayerSprite02->addChild(bgLayer, 2);
        bg_LayerSprite02->addChild(lineDeco, 3);
        bg_LayerSprite02->addChild(creditsLabel, 2);

        m_mainLayer->addChild(bg_LayerSprite02, 1);
        bg_LayerSprite02->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsmoddevLayer, 1);
        m_creditsmoddevLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsrobLayer, 1);
        m_creditsrobLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsOrgLayer, 1);
        m_creditsOrgLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsCreatorsLayer, 1);
        m_creditsCreatorsLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsArtLayer, 1);
        m_creditsArtLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        m_mainLayer->addChild(m_creditsPlayTestLayer, 1);
        m_creditsPlayTestLayer->setPosition(m_mainLayer->convertToNodeSpace(ccp(0, 0)));

        auto fowardTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        fowardTabSpr->setFlipX(true);
        m_fowardTabBtn = CCMenuItemSpriteExtra::create(fowardTabSpr, this, menu_selector(OdysseyCreditsLayer::onNext));

        m_fowardTabMenu = CCMenu::create();
        m_fowardTabMenu->addChild(m_fowardTabBtn);
        m_fowardTabMenu->setPosition({director->getScreenRight() - 35, winSize.height / 2});

        auto backTabSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        m_backTabBtn = CCMenuItemSpriteExtra::create(backTabSpr, this, menu_selector(OdysseyCreditsLayer::onPrev));

        m_backTabMenu = CCMenu::create();
        m_backTabMenu->addChild(m_backTabBtn);
        m_backTabMenu->setPosition({director->getScreenLeft() + 35, winSize.height / 2});

        bg_LayerSprite02->addChild(m_fowardTabMenu, 5);
        bg_LayerSprite02->addChild(m_backTabMenu, 5);

        changeTab();

        return true;
    }

    void setupCreditsOrgTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto SwitchStepUser = OdysseyCreditNode::create("SwitchStepGDYT", 106, 18, 12, 9, true, 10158911);
        auto ZapManiacUser = OdysseyCreditNode::create("ZapManiac", 80, 6, 0, 8, true, 1605650);
        auto MathisCreatorUser = OdysseyCreditNode::create("MathisCreator", 263, 8, 11, 3, true, 9250716);
        auto SearUser = OdysseyCreditNode::create("Sear15", 51, 7, 12, 3, true, 28639090);

        CCArray *row1CreditArray = CCArray::create();

        row1CreditArray->addObject(SwitchStepUser);
        row1CreditArray->addObject(ZapManiacUser);
        row1CreditArray->addObject(MathisCreatorUser);
        row1CreditArray->addObject(SearUser);

        auto creditsReason = CCLabelBMFont::create("Management and Organization", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        m_creditsOrgLayer->addChild(SwitchStepUser, 4);
        m_creditsOrgLayer->addChild(ZapManiacUser, 4);
        m_creditsOrgLayer->addChild(MathisCreatorUser, 4);
        m_creditsOrgLayer->addChild(SearUser, 4);
        m_creditsOrgLayer->addChild(bgLayer, 3);
        m_creditsOrgLayer->addChild(creditsReason, 4);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 84.f, ccp(winSize.width / 2, winSize.height / 2), false);
    }

    void setupCreditsCreatorsTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto MathisCreatorUser = OdysseyCreditNode::create("MathisCreator", 263, 8, 11, 3, true, 9250716);
        MathisCreatorUser->setScale(0.85);

        auto SwitchStepUser = OdysseyCreditNode::create("SwitchStepGDYT", 106, 18, 12, 9, true, 10158911);
        SwitchStepUser->setScale(0.85);

        auto ZapManiacUser = OdysseyCreditNode::create("ZapManiac", 80, 6, 0, 8, true, 1605650);
        ZapManiacUser->setScale(0.85);

        auto JintaUser = OdysseyCreditNode::create("Jinta22", 231, 18, 9, 3, true, 4257871);
        JintaUser->setScale(0.85);

        auto KoromiGDUser = OdysseyCreditNode::create("KoromiGD", 98, 17, 2, 44, true, 1683840);
        KoromiGDUser->setScale(0.85);

        auto DankyUser = OdysseyCreditNode::create("Danky99", 88, 9, 11, 3, true, 14178231);
        DankyUser->setScale(0.85);

        auto MasterTheCubeUser = OdysseyCreditNode::create("MasterTheCube5", 107, 8, 10, 11, true, 13319860);
        MasterTheCubeUser->setScale(0.85);

        auto GenaUser = OdysseyCreditNode::create("GenaMorphosis", 467, 6, 83, 40, true, 10026833);
        GenaUser->setScale(0.85);

        auto NKUser = OdysseyCreditNode::create("NotKaizer", 135, 41, 11, 12, true, 10075800);
        NKUser->setScale(0.85);

        auto DogneRUser = OdysseyCreditNode::create("DogneR", 12, 33, 2, 2, true, 22859812);
        DogneRUser->setScale(0.85);

        auto JoshuaUser = OdysseyCreditNode::create("JoshuaGD23", 459, 12, 12, 12, true, 14831460);
        JoshuaUser->setScale(0.85);

        auto BonntuUser = OdysseyCreditNode::create("Bonntu", 35, 12, 17, 70, true, 23438222);
        BonntuUser->setScale(0.85);

        auto SearUser = OdysseyCreditNode::create("Sear15", 51, 7, 12, 3, true, 28639090);
        SearUser->setScale(0.85);

        auto BreadUser = OdysseyCreditNode::create("TheBreadCat24", 1, 0, 3, 3, true, 14604196);
        BreadUser->setScale(0.85);

        auto BenUser = OdysseyCreditNode::create("ReyBenGDYT", 1, 86, 0, 0, true, 13492478);
        BenUser->setScale(0.85);

        CCArray *row1CreditArray = CCArray::create();
        CCArray *row2CreditArray = CCArray::create();
        CCArray *row3CreditArray = CCArray::create();

        row1CreditArray->addObject(MathisCreatorUser);
        row1CreditArray->addObject(SwitchStepUser);
        row1CreditArray->addObject(ZapManiacUser);
        row1CreditArray->addObject(JintaUser);
        row1CreditArray->addObject(KoromiGDUser);

        row2CreditArray->addObject(DankyUser);
        row2CreditArray->addObject(MasterTheCubeUser);
        row2CreditArray->addObject(GenaUser);
        row2CreditArray->addObject(NKUser);
        row2CreditArray->addObject(DogneRUser);

        row3CreditArray->addObject(JoshuaUser);
        row3CreditArray->addObject(BonntuUser);
        row3CreditArray->addObject(SearUser);
        row3CreditArray->addObject(BreadUser);
        row3CreditArray->addObject(BenUser);

        auto creditsReason = CCLabelBMFont::create("Level Creators", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        m_creditsCreatorsLayer->addChild(SwitchStepUser, 4);
        m_creditsCreatorsLayer->addChild(ZapManiacUser, 4);
        m_creditsCreatorsLayer->addChild(MathisCreatorUser, 4);
        m_creditsCreatorsLayer->addChild(JintaUser, 4);

        m_creditsCreatorsLayer->addChild(KoromiGDUser, 4);
        m_creditsCreatorsLayer->addChild(DankyUser, 4);
        m_creditsCreatorsLayer->addChild(MasterTheCubeUser, 4);
        m_creditsCreatorsLayer->addChild(GenaUser, 4);

        m_creditsCreatorsLayer->addChild(NKUser, 4);
        m_creditsCreatorsLayer->addChild(DogneRUser, 4);
        m_creditsCreatorsLayer->addChild(JoshuaUser, 4);
        m_creditsCreatorsLayer->addChild(BonntuUser, 4);

        m_creditsCreatorsLayer->addChild(SearUser, 4);
        m_creditsCreatorsLayer->addChild(BreadUser, 4);
        m_creditsCreatorsLayer->addChild(BenUser, 4);

        m_creditsCreatorsLayer->addChild(bgLayer, 3);
        m_creditsCreatorsLayer->addChild(creditsReason, 4);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 74.f, ccp(winSize.width / 2, winSize.height / 2 + 35), false);
        GameToolbox::alignItemsHorisontally(row2CreditArray, 74.f, ccp(winSize.width / 2, winSize.height / 2 - 17), false);
        GameToolbox::alignItemsHorisontally(row3CreditArray, 74.f, ccp(winSize.width / 2, winSize.height / 2 - 70), false);
    }

    void setupCreditsArtistsTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto DankyUser = OdysseyCreditNode::create("Danky99", 88, 9, 11, 3, true, 14178231);
        DankyUser->setScale(0.85);

        auto BenUser = OdysseyCreditNode::create("ReyBenGDYT", 1, 86, 0, 0, true, 13492478);
        BenUser->setScale(0.85);

        auto _3lipngUser = OdysseyCreditNode::create("3lipng", 465, 12, 17, 17, true, 29170137);
        _3lipngUser->setScale(0.85);

        auto VaughnersUser = OdysseyCreditNode::create("Vaughners", 350, 87, 3, 40, true, 2180460);
        VaughnersUser->setScale(0.85);

        auto MinoX29User = OdysseyCreditNode::create("MinoX28", 283, 94, 12, 12, true, 13284787);
        MinoX29User->setScale(0.85);

        auto ML5User = OdysseyCreditNode::create("ML500", 296, 22, 106, 106, true, 2102);
        ML5User->setScale(0.85);

        auto cyanflowerUser = OdysseyCreditNode::create("cyanflower", 2, 12, 3, 3, true, 21113321);
        cyanflowerUser->setScale(0.85);

        auto AngelozDDUser = OdysseyCreditNode::create("AngelozDD", 431, 0, 3, 12, true, 18718615);
        AngelozDDUser->setScale(0.85);

        auto MasterTheCubeUser = OdysseyCreditNode::create("MasterTheCube5", 107, 8, 10, 11, true, 13319860);
        MasterTheCubeUser->setScale(0.85);

        auto SweeSwagUser = OdysseyCreditNode::create("SweeSwag", 102, 12, 8, 8, true, 21644186);
        SweeSwagUser->setScale(0.85);

        CCArray *row1CreditArray = CCArray::create();
        CCArray *row2CreditArray = CCArray::create();

        row1CreditArray->addObject(DankyUser);
        row1CreditArray->addObject(BenUser);
        row1CreditArray->addObject(_3lipngUser);
        row1CreditArray->addObject(VaughnersUser);
        row1CreditArray->addObject(MinoX29User);

        row2CreditArray->addObject(ML5User);
        row2CreditArray->addObject(cyanflowerUser);
        row2CreditArray->addObject(AngelozDDUser);
        row2CreditArray->addObject(MasterTheCubeUser);
        row2CreditArray->addObject(SweeSwagUser);

        auto creditsReason = CCLabelBMFont::create("Artists", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        m_creditsArtLayer->addChild(DankyUser, 4);
        m_creditsArtLayer->addChild(BenUser, 4);
        m_creditsArtLayer->addChild(_3lipngUser, 4);
        m_creditsArtLayer->addChild(VaughnersUser, 4);
        m_creditsArtLayer->addChild(MinoX29User, 4);

        m_creditsArtLayer->addChild(ML5User, 4);
        m_creditsArtLayer->addChild(cyanflowerUser, 4);
        m_creditsArtLayer->addChild(AngelozDDUser, 4);
        m_creditsArtLayer->addChild(MasterTheCubeUser, 4);
        m_creditsArtLayer->addChild(SweeSwagUser, 4);

        m_creditsArtLayer->addChild(bgLayer, 3);
        m_creditsArtLayer->addChild(creditsReason, 4);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 71.f, ccp(winSize.width / 2, winSize.height / 2 + 25), false);
        GameToolbox::alignItemsHorisontally(row2CreditArray, 71.f, ccp(winSize.width / 2, winSize.height / 2 - 50), false);
    }

    void setupCreditsTestersTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto DAPixelheroUser = OdysseyCreditNode::create("DAPixelhero", 72, 5, 9, 12, true, 1826718);
        DAPixelheroUser->setScale(0.85);

        auto AndrexelUser = OdysseyCreditNode::create("Andrexel", 114, 8, 11, 11, true, 8327873);
        AndrexelUser->setScale(0.85);

        auto cyanflowerUser = OdysseyCreditNode::create("cyanflower", 2, 12, 3, 3, true, 21113321);
        cyanflowerUser->setScale(0.85);

        auto ZerkGMDUser = OdysseyCreditNode::create("ZerkGMD", 37, 12, 15, 12, true, 27986840);
        ZerkGMDUser->setScale(0.85);

        auto ObsidianAJUser = OdysseyCreditNode::create("ObsidianAJ", 48, 6, 3, 44, true, 11368602);
        ObsidianAJUser->setScale(0.85);

        auto Emmmanuel2014User = OdysseyCreditNode::create("Emmmanuel2014", 42, 15, 3, 3, true, 5911554);
        Emmmanuel2014User->setScale(0.85);

        auto DolphinOFFICIALUser = OdysseyCreditNode::create("DolphinOFFICIAL", 371, 4, 14, 14, true, 16564836);
        DolphinOFFICIALUser->setScale(0.85);

        auto TochyGMDUser = OdysseyCreditNode::create("TochyGMD", 98, 12, 12, 3, true, 26108122);
        TochyGMDUser->setScale(0.85);

        auto MichTopGDMTUser = OdysseyCreditNode::create("MichTopGDMT", 22, 3, 12, 3, true, 8983710);
        MichTopGDMTUser->setScale(0.85);

        auto dreenUser = OdysseyCreditNode::create("dreen", 1, 0, 3, 3, true, 15960627);
        dreenUser->setScale(0.85);

        CCArray *row1CreditArray = CCArray::create();
        CCArray *row2CreditArray = CCArray::create();

        row1CreditArray->addObject(DAPixelheroUser);
        row1CreditArray->addObject(AndrexelUser);
        row1CreditArray->addObject(cyanflowerUser);
        row1CreditArray->addObject(ZerkGMDUser);
        row1CreditArray->addObject(ObsidianAJUser);

        row2CreditArray->addObject(Emmmanuel2014User);
        row2CreditArray->addObject(DolphinOFFICIALUser);
        row2CreditArray->addObject(TochyGMDUser);
        row2CreditArray->addObject(MichTopGDMTUser);
        row2CreditArray->addObject(dreenUser);

        auto creditsReason = CCLabelBMFont::create("Playtesters", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        m_creditsPlayTestLayer->addChild(DAPixelheroUser, 4);
        m_creditsPlayTestLayer->addChild(AndrexelUser, 4);
        m_creditsPlayTestLayer->addChild(cyanflowerUser, 4);
        m_creditsPlayTestLayer->addChild(ZerkGMDUser, 4);
        m_creditsPlayTestLayer->addChild(ObsidianAJUser, 4);

        m_creditsPlayTestLayer->addChild(Emmmanuel2014User, 4);
        m_creditsPlayTestLayer->addChild(DolphinOFFICIALUser, 4);
        m_creditsPlayTestLayer->addChild(TochyGMDUser, 4);
        m_creditsPlayTestLayer->addChild(MichTopGDMTUser, 4);
        m_creditsPlayTestLayer->addChild(dreenUser, 4);

        m_creditsPlayTestLayer->addChild(bgLayer, 3);
        m_creditsPlayTestLayer->addChild(creditsReason, 4);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 71.f, ccp(winSize.width / 2, winSize.height / 2 + 25), false);
        GameToolbox::alignItemsHorisontally(row2CreditArray, 71.f, ccp(winSize.width / 2, winSize.height / 2 - 50), false);
    }

    void setupCreditsModDeveloperTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto ML5User = OdysseyCreditNode::create("ML500", 296, 22, 106, 106, true, 2102);
        auto SumiUser = OdysseyCreditNode::create("Chumiu", 457, 94, 52, 52, true, 25521533);
        auto CypherUser = OdysseyCreditNode::create("Cypher", 31, 9, 1, 1, true, 6332919);

        CCArray *row1CreditArray = CCArray::create();

        row1CreditArray->addObject(ML5User);
        row1CreditArray->addObject(SumiUser);
        row1CreditArray->addObject(CypherUser);

        auto creditsReason = CCLabelBMFont::create("Mod Developers", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        m_creditsmoddevLayer->addChild(ML5User, 4);
        m_creditsmoddevLayer->addChild(SumiUser, 4);
        m_creditsmoddevLayer->addChild(CypherUser, 4);
        m_creditsmoddevLayer->addChild(bgLayer, 3);
        m_creditsmoddevLayer->addChild(creditsReason, 4);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 100.f, ccp(winSize.width / 2, winSize.height / 2), false);
    }

    void setupCreditsSpecialThanksTab()
    {
        auto director = CCDirector::sharedDirector();
        auto winSize = director->getWinSize();

        auto RobTopUser = OdysseyCreditNode::create("RobTop", 275, 6, 3, 1, true, 71);
        RobTopUser->setScale(0.85);

        auto EVWUser = OdysseyCreditNode::create("EVW", 28, 12, 9, 9, true, 710192);
        EVWUser->setScale(0.85);

        auto ImFernandoUser = OdysseyCreditNode::create("im fernando", 56, 35, 3, 3, true, 5398449);
        ImFernandoUser->setScale(0.85);

        auto StivenelXDUser = OdysseyCreditNode::create("StivenelXD", 50, 12, 3, 3, true, 167848);
        StivenelXDUser->setScale(0.85);

        auto CapelingUser = OdysseyCreditNode::create("Capeling", 70, 41, 12, 12, true, 18226543);
        CapelingUser->setScale(0.85);

        auto LimeGradientUser = OdysseyCreditNode::create("LimeGradient", 46, 98, 12, 43, true, 7214334);
        LimeGradientUser->setScale(0.85);

        auto MXSTOUser = OdysseyCreditNode::create("Mxst0", 296, 89, 2, 44, true, 24326682);
        MXSTOUser->setScale(0.85);

        auto BlueSpaceUser = OdysseyCreditNode::create("Bluespace", 37, 3, 6, 6, true, 10206148);
        BlueSpaceUser->setScale(0.85);

        CCArray *row1CreditArray = CCArray::create();
        CCArray *row2CreditArray = CCArray::create();
        CCArray *row3CreditArray = CCArray::create();

        row1CreditArray->addObject(RobTopUser);

        row2CreditArray->addObject(EVWUser);
        row2CreditArray->addObject(ImFernandoUser);
        row2CreditArray->addObject(StivenelXDUser);

        row3CreditArray->addObject(CapelingUser);
        row3CreditArray->addObject(LimeGradientUser);
        row3CreditArray->addObject(MXSTOUser);
        row3CreditArray->addObject(BlueSpaceUser);

        auto creditsReason = CCLabelBMFont::create("Special Thanks", "goldFont.fnt");
        creditsReason->setScale(0.7f);
        creditsReason->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        creditsReason->setAnchorPoint({0.5f, 1.0f});
        creditsReason->limitLabelWidth(180.0f, 0.6f, 0.f);
        creditsReason->setPosition(ccp(winSize.width / 2, creditsLabel->getPositionY() - 32));

        auto deeperspaceLabel = CCLabelBMFont::create("(Deeper Space nos la pela)", "bigFont.fnt");
        deeperspaceLabel->setScale(0.7f);
        deeperspaceLabel->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
        deeperspaceLabel->setAnchorPoint({0.5f, 1.0f});
        deeperspaceLabel->limitLabelWidth(180.0f, 0.6f, 0.f);
        deeperspaceLabel->setColor({255, 58, 58});
        deeperspaceLabel->setPosition(ccp(winSize.width / 2, m_bgSprite->getContentHeight() - 225));

        m_creditsrobLayer->addChild(RobTopUser, 4);
        m_creditsrobLayer->addChild(EVWUser, 4);
        m_creditsrobLayer->addChild(ImFernandoUser, 4);
        m_creditsrobLayer->addChild(StivenelXDUser, 4);
        m_creditsrobLayer->addChild(CapelingUser, 4);
        m_creditsrobLayer->addChild(LimeGradientUser, 4);
        m_creditsrobLayer->addChild(MXSTOUser, 4);
        m_creditsrobLayer->addChild(BlueSpaceUser, 4);

        m_creditsrobLayer->addChild(deeperspaceLabel, 4);
        m_creditsrobLayer->addChild(creditsReason, 4);
        m_creditsrobLayer->addChild(bgLayer, 3);

        GameToolbox::alignItemsHorisontally(row1CreditArray, 90.f, ccp(winSize.width / 2, winSize.height / 2 + 35), false);
        GameToolbox::alignItemsHorisontally(row2CreditArray, 90.f, ccp(winSize.width / 2, winSize.height / 2 - 17), false);
        GameToolbox::alignItemsHorisontally(row3CreditArray, 90.f, ccp(winSize.width / 2, winSize.height / 2 - 70), false);
    }

    void onNext(CCObject *)
    {
        m_tab++;
        changeTab();
    }

    void onPrev(CCObject *)
    {
        m_tab--;
        changeTab();
    }

    void changeTab()
    {
        m_creditsmoddevLayer->setVisible(false);
        m_creditsrobLayer->setVisible(false);
        m_creditsOrgLayer->setVisible(false);
        m_creditsCreatorsLayer->setVisible(false);
        m_creditsArtLayer->setVisible(false);
        m_creditsPlayTestLayer->setVisible(false);

        m_fowardTabBtn->setVisible(m_tab < m_lastTab);
        m_backTabBtn->setVisible(m_tab > 0);

        if (m_tab > m_lastTab)
            m_tab = m_lastTab;

        if (m_tab < 0)
            m_tab = 0;

        switch (m_tab)
        {
        case 0:
            m_bgSprite02->setColor({0, 0, 255});
            bgLayer->setColor({0, 10, 255});
            m_creditsOrgLayer->setVisible(true);
            break;

        case 1:
            m_bgSprite02->setColor({0, 125, 255});
            bgLayer->setColor({0, 135, 255});
            m_creditsmoddevLayer->setVisible(true);
            break;

        case 2:
            m_bgSprite02->setColor({0, 255, 0});
            bgLayer->setColor({0, 255, 10});
            m_creditsCreatorsLayer->setVisible(true);
            break;

        case 3:
            m_bgSprite02->setColor({255, 0, 125});
            bgLayer->setColor({255, 0, 135});
            m_creditsArtLayer->setVisible(true);
            break;

        case 4:
            m_bgSprite02->setColor({175, 175, 175});
            bgLayer->setColor({175, 185, 175});
            m_creditsPlayTestLayer->setVisible(true);
            break;

        case 5:
            m_bgSprite02->setColor({100, 0, 150});
            bgLayer->setColor({100, 10, 150});
            m_creditsrobLayer->setVisible(true);
            break;
        }
    }

public:
    static OdysseyCreditsLayer *create()
    {
        auto ref = new OdysseyCreditsLayer();
        if (ref && ref->initAnchored(430.0f, 270.0f, "GJ_square07.png"))
        {
            ref->autorelease();
            return ref;
        }
        CC_SAFE_DELETE(ref);
        return nullptr;
    }
};
