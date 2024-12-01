#pragma once
using namespace geode::prelude;

class OdysseyLevelPopup : public geode::Popup<std::string const &>
{
public:
    GJGameLevel* m_level;
    int m_levelID = 0;

protected:

    bool setup(std::string const &value) override
    {
        m_level = GameLevelManager::sharedState()->getMainLevel(m_levelID, false);
        

        setTitle(m_level->m_levelName);

        m_title->limitLabelWidth(200, .85f, .1f);
        m_title->setPositionY(m_title->getPositionY() - 5);

        m_closeBtn->setPosition(m_closeBtn->getPositionX() + 5, m_closeBtn->getPositionY() - 5);
        

        auto lbCorner = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");

        lbCorner->setAnchorPoint({ 0, 0 });
        lbCorner->setPosition({0, 0});

        m_mainLayer->addChild(lbCorner);

        auto ltCorner = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        ltCorner->setFlipY(true);

        ltCorner->setAnchorPoint({ 0, 1 });
        ltCorner->setPosition({0, m_mainLayer->getContentHeight()});

        m_mainLayer->addChild(ltCorner);

        auto rtCorner = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        rtCorner->setFlipX(true);
        rtCorner->setFlipY(true);

        rtCorner->setAnchorPoint({ 1, 1 });
        rtCorner->setPosition({ m_mainLayer->getContentWidth(), m_mainLayer->getContentHeight()});

        m_mainLayer->addChild(rtCorner);

        auto rbCorner = CCSprite::createWithSpriteFrameName("dailyLevelCorner_001.png");
        rbCorner->setFlipX(true);

        rbCorner->setAnchorPoint({ 1, 0 });
        rbCorner->setPosition({m_mainLayer->getContentWidth(), 0});

        m_mainLayer->addChild(rbCorner);


        //std::string difficultyName = fmt::format("diffIcon_{:02}_btn_001.png", static_cast<int>(m_level->m_difficulty));
        auto difficultySprite = GJDifficultySprite::create(static_cast<int>(m_level->m_difficulty), GJDifficultyName::Short); //CCSprite::createWithSpriteFrameName(difficultyName.c_str());

        difficultySprite->setScale(1.2f);
        difficultySprite->setPosition({60, m_mainLayer->getContentHeight() - 80});

        m_mainLayer->addChild(difficultySprite);

        auto starsIcon = CCSprite::createWithSpriteFrameName("GJ_bigStar_001.png");

        starsIcon->setScale(.45f);
        starsIcon->setPosition({65, m_mainLayer->getContentHeight() - 110});

        m_mainLayer->addChild(starsIcon);

        auto starsLabel = CCLabelBMFont::create(std::to_string(m_level->m_stars.value()).c_str(), "bigFont.fnt");

        starsLabel->limitLabelWidth(10, .45f, .1f);
        starsLabel->setPosition({50, m_mainLayer->getContentHeight() - 110});

        m_mainLayer->addChild(starsLabel);

        auto blackBar1 = CCSprite::create("GJ_progressBar_001.png");

        blackBar1->setColor({ 0, 0, 0 });
        blackBar1->setOpacity(125);

        blackBar1->setScaleX(.67f);
        blackBar1->setScaleY(.8f);
        blackBar1->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 45 });

        m_mainLayer->addChild(blackBar1);

        auto normalBar = CCSprite::create("GJ_progressBar_001.png");
        auto rectX = (normalBar->getContentWidth() * m_level->m_normalPercent.value()) / 100;   
     
        normalBar->setTextureRect({ 0, .5f, rectX, normalBar->getContentHeight() });
        normalBar->setColor({ 0, 255, 0 });

        normalBar->setScale(.65f);
        normalBar->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 45 });

        m_mainLayer->addChild(normalBar);

        auto normalLabel = CCLabelBMFont::create(fmt::format("{}%", m_level->m_normalPercent.value()).c_str(), "bigFont.fnt");

        normalLabel->setScale(.45f);
        normalLabel->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 45 });

        m_mainLayer->addChild(normalLabel);

        auto normalModeLabel = CCLabelBMFont::create("Normal Mode", "bigFont.fnt");

        normalModeLabel->setScale(.45f);
        normalModeLabel->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 30 });

        m_mainLayer->addChild(normalModeLabel);

        auto blackBar2 = CCSprite::create("GJ_progressBar_001.png");

        blackBar2->setColor({ 0, 0, 0 });
        blackBar2->setOpacity(125);

        blackBar2->setScaleX(.67f);
        blackBar2->setScaleY(.8f);
        blackBar2->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 85 });

        m_mainLayer->addChild(blackBar2);

        auto practiceBar = CCSprite::create("GJ_progressBar_001.png");
        auto pRectX = (practiceBar->getContentWidth() * m_level->m_practicePercent) / 100;   
     
        practiceBar->setTextureRect({ 0, .5f, rectX, normalBar->getContentHeight() });
        practiceBar->setColor({ 0, 255, 255 });

        practiceBar->setScale(.65f);
        practiceBar->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 85 });

        m_mainLayer->addChild(practiceBar);

        auto practiceLabel = CCLabelBMFont::create(fmt::format("{}%", m_level->m_practicePercent).c_str(), "bigFont.fnt");

        practiceLabel->setScale(.45f);
        practiceLabel->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 85 });

        m_mainLayer->addChild(practiceLabel);

        auto practiceModeLabel = CCLabelBMFont::create("Practice Mode", "bigFont.fnt");

        practiceModeLabel->setScale(.45f);
        practiceModeLabel->setPosition({ m_mainLayer->getContentWidth() / 2, m_mainLayer->getContentHeight() / 2 - 70 });

        m_mainLayer->addChild(practiceModeLabel);

        auto buttonsMenu = CCMenu::create();
        buttonsMenu->setPosition(m_mainLayer->getContentSize() / 2);

        auto playSprite = CCSprite::createWithSpriteFrameName("GJ_playBtn2_001.png");

        auto playButton = CCMenuItemSpriteExtra::create(playSprite, this, nullptr);
        playButton->setPositionY(45);

        buttonsMenu->addChild(playButton);

        auto infoButton = InfoAlertButton::create("Info", m_level->m_levelDesc, 1);

        infoButton->setPosition(m_mainLayer->getContentSize() / 2 - 5);

        buttonsMenu->addChild(infoButton);


        auto optionsSprite = CCSprite::createWithSpriteFrameName("GJ_optionsBtn02_001.png");
        optionsSprite->setScale(.7f);

        auto optionsButton = CCMenuItemSpriteExtra::create(optionsSprite, this, menu_selector(OdysseyLevelPopup::onLevelSettings));

        optionsButton->setPosition({ -m_mainLayer->getContentWidth() / 2 + 5, -m_mainLayer->getContentHeight() / 2 + 5});

        buttonsMenu->addChild(optionsButton);

        auto comicSprite = CCSprite::createWithSpriteFrameName("GDO_comicBtn.png"_spr);
        comicSprite->setScale(.1f); //Es un poco enorme ayuda

        auto comicButton = CCMenuItemSpriteExtra::create(comicSprite, this, nullptr);

        comicButton->setPosition({ m_mainLayer->getContentWidth() / 2 - 5,-m_mainLayer->getContentHeight() / 2 + 5});

        buttonsMenu->addChild(comicButton);

        m_mainLayer->addChild(buttonsMenu);

        return true;
    }

    void onLevelSettings(CCObject*)
    {
        auto layer = GameLevelOptionsLayer::create(m_level);
        layer->show();
    }

public:
    static OdysseyLevelPopup *create(int levelID)
    {
        auto ret = new OdysseyLevelPopup();

        ret->m_levelID = levelID;

        if (ret && ret->initAnchored(300.f, 260.f, " "))
        {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};