#include "Utils.hpp"
#include "Dialogs.hpp"

void Odyssey::addCorners(CCLayer *layer, const char *cornerSprite, float offset)
{
    //  Corners
    auto m_cornerBL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBL->setAnchorPoint({0, 0});
    m_cornerBL->setPosition({0 - offset, 0 - offset});
    m_cornerBL->setID("corner-bl"_spr);

    auto m_cornerBR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerBR->setPosition({layer->getContentWidth() + offset, 0 - offset});
    m_cornerBR->setAnchorPoint({1, 0});
    m_cornerBR->setFlipX(true);
    m_cornerBR->setID("corner-br"_spr);

    auto m_cornerTL = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTL->setAnchorPoint({0, 1});
    m_cornerTL->setPosition({0 - offset, layer->getContentHeight() + offset});
    m_cornerTL->setFlipY(true);
    m_cornerTL->setID("corner-tl"_spr);

    auto m_cornerTR = CCSprite::createWithSpriteFrameName(cornerSprite);
    m_cornerTR->setPosition({layer->getContentWidth() + offset, layer->getContentHeight() + offset});
    m_cornerTR->setAnchorPoint({1, 1});
    m_cornerTR->setFlipX(true);
    m_cornerTR->setFlipY(true);
    m_cornerTR->setID("corner-tr"_spr);

    layer->addChild(m_cornerBL);
    layer->addChild(m_cornerBR);
    layer->addChild(m_cornerTL);
    layer->addChild(m_cornerTR);
};

CCNode *Odyssey::createProgressBar(int percentage, bool isPractice)
{
    auto node = CCNode::create();

    int rgbValue = isPractice ? 255 : 0;
    ccColor3B color = {0, 255, (GLubyte)rgbValue};

    auto bgBar = CCSprite::create("GJ_progressBar_001.png");
    bgBar->setColor({0, 0, 0});
    bgBar->setOpacity(100);
    bgBar->setScale(0.9f);
    bgBar->setZOrder(1);

    node->addChild(bgBar);

    auto progressBar = CCSprite::create("GJ_progressBar_001.png");
    auto rectX = (progressBar->getContentWidth() * percentage) / 100;
    progressBar->setTextureRect({0, .5f, rectX, progressBar->getContentHeight()});
    progressBar->setScaleX(0.89f);
    progressBar->setScaleY(0.75f);
    progressBar->setColor(color);
    progressBar->setZOrder(2);

    progressBar->setAnchorPoint({0, 0.5});
    progressBar->setPositionX(-151.3f);

    node->addChild(progressBar);

    std::string progressNumber = std::to_string(percentage);
    auto progressLabel = CCLabelBMFont::create(fmt::format("{}%", progressNumber).c_str(), "bigFont.fnt");
    progressLabel->setPositionY(0.5f);
    progressLabel->setScale(0.325f);
    progressLabel->setZOrder(3);

    node->addChild(progressLabel);

    const char *mode = isPractice ? "Practice Mode" : "Normal Mode";
    auto label = CCLabelBMFont::create(mode, "bigFont.fnt");
    label->setPositionY(18.0f);
    label->setScale(0.45f);
    node->addChild(label);

    return node;
};

CCNode *Odyssey::createDifficultyNode(GJDifficulty diff, int stars)
{
    auto node = CCNode::create();
    node->setContentSize({22.f, 32.5f});

    std::string difficultyName = fmt::format("diffIcon_{:02}_btn_001.png", static_cast<int>(diff));
    auto diffSprite = CCSprite::createWithSpriteFrameName(difficultyName.c_str());
    diffSprite->setPosition({node->getContentWidth() / 2, node->getContentHeight()});
    diffSprite->setScale(1.25f);

    auto starLabel = CCLabelBMFont::create(std::to_string(stars).c_str(), "bigFont.fnt");
    starLabel->limitLabelWidth(25, 0.6f, 0.1f);
    starLabel->setPosition({0, 0});

    auto starSprite = CCSprite::createWithSpriteFrameName("GJ_bigStar_noShadow_001.png");
    starSprite->setPosition({node->getContentWidth(), 0});
    starSprite->setScale(0.5f);

    node->addChild(diffSprite);
    node->addChild(starSprite);
    node->addChild(starLabel);
    return node;
};

DialogLayer *Odyssey::createDialog(const char *event)
{
    CCArray *arr = CCArray::create();

    auto dialogColor = 2;
    std::vector<std::vector<gd::string>> dialogList;
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");

    //  Puede que esto si o no sirva, pero a este punta ya vale
    if (event == "meetingShopkeeper") dialogList = CarpIntroduction;

    if (event == "meetingWizard") dialogList = WizardIntroduction;

    if (event == "firstIslandClear") dialogList = FirstIslandClear;

    if (event == "end") dialogList = Ending;

    if (event == "meetingHollow"){
        dialogList = HollowIntroduction;
        dialogColor = 5;
    }

    //  Al tener ya una lista de dialogos asignado, se hace este ciclo
    //  Donde cada parte del dialogo es agregado al Array
    for (auto ii = dialogList.begin(); ii != dialogList.end(); ii++)
    {
        auto text = ii->at(2 + spanishText);
        auto dialog = DialogObject::create(ii->at(0), text, std::stoi(ii->at(1)), 1, false, {255, 255, 255});
        arr->addObject(dialog);
    }

    //  Al terminar, crea el Layer del dialogo y lo agrega al a escena
    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, dialogColor);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(10);

    return dialogLayer;
};

DialogLayer *Odyssey::createDialogResponse(const char *event, int times)
{
    //  Esto por arreglar mas tarde
    auto spanishText = GameManager::sharedState()->getGameVariable("0201");
    CCArray *arr = CCArray::create();
    if (event == "playerIsPoor")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "Here's your purcha-<d020> wait a second.", 20, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Sorry,<d030> you don't have enough <cy>coins</c>.", 21, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Are you trying to scam me?", 22, 1, false, {255, 255, 255});
            auto dialog04 = DialogObject::create("Carp", "I might be blind,<d030> but I'm sure you don't have <cy>enough</c> to <cg>buy</c> this.", 25, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                arr->addObject(dialog02);
                break;

            case 1:
                arr->addObject(dialog03);
                break;

            case 2:
                arr->addObject(dialog04);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    if (event == "extraIslandLocked")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "You can buy the key to unlock that in my <cy>Shop</c>.", 25, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Yep,<d030> you still need to <cg>buy</c> it.", 20, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Go grind some stuff to <cg>buy</c> this!", 23, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                break;

            case 1:
                arr->addObject(dialog02);
                break;

            case 2:
                arr->addObject(dialog03);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    if (event == "finalComicLocked")
    {
        if (!spanishText)
        {
            auto dialog01 = DialogObject::create("Carp", "You must <cg>complete</c> the story mode before showing you that.", 19, 1, false, {255, 255, 255});
            auto dialog02 = DialogObject::create("Carp", "Try to <cg>complete</c> the game first.", 21, 1, false, {255, 255, 255});
            auto dialog03 = DialogObject::create("Carp", "Someone's impatient<d010>.<d010>.<d010>.", 22, 1, false, {255, 255, 255});
            auto dialog04 = DialogObject::create("Carp", "Alright man,<d020> you want to <cr>spoil</c> you the story?", 25, 1, false, {255, 255, 255});
            auto dialog05 = DialogObject::create("Carp", "You are getting on my nerves,<d020> <cg>complete the game</c>!", 21, 1, false, {255, 255, 255});
            auto dialog06 = DialogObject::create("Carp", "<s500><cg>COMPLETE THE GAME.</c></s>", 26, 1, false, {255, 255, 255});

            switch (times)
            {
            case 0:
                arr->addObject(dialog01);
                break;

            case 1:
                arr->addObject(dialog02);
                break;

            case 2:
                arr->addObject(dialog03);
                break;

            case 3:
                arr->addObject(dialog04);
                break;

            case 4:
                arr->addObject(dialog05);
                break;

            case 5:
                arr->addObject(dialog06);
                break;
            }
        }
        else
        {
            // To Do
        }
    }

    auto dialogLayer = DialogLayer::createDialogLayer(nullptr, arr, 2);
    dialogLayer->animateInRandomSide();
    dialogLayer->setZOrder(2);
    return dialogLayer;
}

int Odyssey::currentVehicleID()
{
    auto gm = GameManager::get();
    switch (gm->m_playerIconType)
    {
    case IconType::Ship:
        return gm->getPlayerShip();
    case IconType::Ball:
        return gm->getPlayerBall();
    case IconType::Ufo:
        return gm->getPlayerBird();
    case IconType::Wave:
        return gm->getPlayerDart();
    case IconType::Robot:
        return gm->getPlayerRobot();
    case IconType::Spider:
        return gm->getPlayerSpider();
    case IconType::Swing:
        return gm->getPlayerSwing();
    case IconType::Jetpack:
        return gm->getPlayerJetpack();
    default:
        return gm->getPlayerFrame();
    }
}

void Odyssey::insertAssetsToMap(bool isSong, std::vector<int> IDs)
{
    auto map = MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet;

    for (int assetID : IDs)
    {
        if (isSong)
            MusicDownloadManager::sharedState()->m_resourceSongUnorderedSet.insert(assetID);
        else
            MusicDownloadManager::sharedState()->m_resourceSfxUnorderedSet.insert(assetID);
    }
}

bool Odyssey::isIconCustom(int id, IconType type)
{
    if (id > 485 && type == IconType::Cube)
        return true;
    if (id > 169 && type == IconType::Ship)
        return true;
    if (id > 118 && type == IconType::Ball)
        return true;
    if (id > 149 && type == IconType::Ufo)
        return true;
    if (id > 96 && type == IconType::Wave)
        return true;
    if (id > 68 && type == IconType::Robot)
        return true;
    if (id > 69 && type == IconType::Spider)
        return true;
    if (id > 43 && type == IconType::Swing)
        return true;
    if (id > 8 && type == IconType::Jetpack)
        return true;
    if (static_cast<int>(type) >= 900)
        return true;

    return false;
}

bool Odyssey::isIconSecret(int id, IconType type)
{
    if ((id >= 502 && id <= 508) && type == IconType::Cube)
        return true;
    if ((id >= 171 && id <= 172) && type == IconType::Ship)
        return true;
    if ((id >= 120 && id <= 123) && type == IconType::Ball)
        return true;
    if ((id >= 150 && id <= 153) && type == IconType::Ufo)
        return true;
    if ((id >= 98 && id <= 99) && type == IconType::Wave)
        return true;
    if ((id >= 9) && type == IconType::Jetpack)
        return true;

    return false;
}

bool Odyssey::isIconUpcoming(int id, IconType type)
{
    if (id >= 514 && type == IconType::Cube)
        return true;
    /*
    if (id >= 173 && type == IconType::Ship)
        return true;
    if (id >= 124 && type == IconType::Ball)
        return true;
    if (id >= 154 && type == IconType::Ufo)
        return true;
    if (id >= 100 && type == IconType::Wave)
        return true;
    if (id >= 46 && type == IconType::Swing)
        return true;
    */

    return false;
}

std::vector<std::string> Odyssey::getPlayerFrames(int iconID, IconType type)
{
    std::string iconName;
    switch (type)
    {
    case IconType::Ship:
        iconName = "ship";
        break;
    case IconType::Ball:
        iconName = "player_ball";
        break;
    case IconType::Ufo:
        iconName = "bird";
        break;
    case IconType::Wave:
        iconName = "dart";
        break;
    case IconType::Robot:
        iconName = "robot";
        break;
    case IconType::Spider:
        iconName = "spider";
        break;
    case IconType::Swing:
        iconName = "swing";
        break;
    case IconType::Jetpack:
        iconName = "jetpack";
        break;
    default:
        iconName = "player";
        break;
    }

    int typeNumber = static_cast<int>(type);

    switch (typeNumber)
    {
    case 900:
        iconName = "boat";
        break;
    case 901:
        iconName = "drone";
        break;
    case 902:
        iconName = "slider";
        break;
    case 903:
        iconName = "minecart";
        break;
    }

    if (typeNumber >= 900)
        iconID = 1;

    std::string frame1 = fmt::format("{}_{:02}_001.png"_spr, iconName, iconID);
    std::string frame2 = fmt::format("{}_{:02}_2_001.png"_spr, iconName, iconID);
    std::string frameExtra = fmt::format("{}_{:02}_extra_001.png"_spr, iconName, iconID);
    std::string frameGlow = fmt::format("{}_{:02}_glow_001.png"_spr, iconName, iconID);

    return {frame1, frame2, frameExtra, frameGlow};
}

void Odyssey::updateIcon(CCNode *player, int iconID, IconType type, bool isPlayerObject)
{
    if (!isIconCustom(iconID, type))
        return;

    auto frameCache = CCSpriteFrameCache::get();

    auto frames = getPlayerFrames(iconID, type);
    auto frame1Texture = frames[0];
    auto frame2Texture = frames[1];
    auto extraTexture = frames[2];
    auto glowTexture = frames[3];

    CCSprite *firstLayer;
    CCSprite *secondLayer;
    CCSprite *extraLayer;
    CCSprite *glowLayer;
    GJRobotSprite *robotSprite;
    CCSprite *ufoDome;

    if (isPlayerObject)
    {
        auto obj = static_cast<PlayerObject *>(player);

        firstLayer = obj->m_iconSprite;
        secondLayer = obj->m_iconSpriteSecondary;
        extraLayer = obj->m_iconSpriteWhitener;
        glowLayer = obj->m_iconGlow;
        robotSprite = obj->m_robotSprite;

        if (type == IconType::Ship || type == IconType::Jetpack)
        {
            firstLayer = obj->m_vehicleSprite;
            secondLayer = obj->m_vehicleSpriteSecondary;
            extraLayer = obj->m_vehicleSpriteWhitener;
            glowLayer = obj->m_vehicleGlow;
        }

        if (type == IconType::Ufo)
            ufoDome = obj->m_birdVehicle;
    }
    else
    {
        auto obj = static_cast<SimplePlayer *>(player);

        firstLayer = obj->m_firstLayer;
        secondLayer = obj->m_secondLayer;
        extraLayer = obj->m_detailSprite;
        glowLayer = obj->m_outlineSprite;
        robotSprite = obj->m_robotSprite;

        if (type == IconType::Ufo)
            ufoDome = obj->m_birdDome;
    }

    if (type == IconType::Robot || type == IconType::Spider)
    {
        updateRobotSprite(robotSprite, iconID, type);
        return;
    }

    if (auto frame1 = frameCache->spriteFrameByName(frame1Texture.c_str()))
    {
        firstLayer->setDisplayFrame(frame1);
    }

    if (auto frame2 = frameCache->spriteFrameByName(frame2Texture.c_str()))
    {
        secondLayer->setDisplayFrame(frame2);
        secondLayer->setPosition(firstLayer->getContentSize() / 2);
    }

    if (auto extraFrame = frameCache->spriteFrameByName(extraTexture.c_str()))
    {
        extraLayer->setVisible(true);
        extraLayer->setDisplayFrame(extraFrame);
        extraLayer->setPosition(firstLayer->getContentSize() / 2);
    }
    else
        extraLayer->setVisible(false);

    if (auto glowFrame = frameCache->spriteFrameByName(glowTexture.c_str()))
    {
        glowLayer->setDisplayFrame(glowFrame);
        if (!isPlayerObject)
            glowLayer->setPosition(firstLayer->getContentSize() / 2);
    }
}

void Odyssey::updateRobotSprite(GJRobotSprite *sprite, int iconID, IconType type)
{
    if (!sprite)
        return;

    sprite->setBatchNode(nullptr);
    sprite->m_paSprite->setBatchNode(nullptr);

    auto spriteParts = sprite->m_paSprite->m_spriteParts;

    auto frameCache = CCSpriteFrameCache::get();

    const char *iconName = "robot";
    if (type == IconType::Spider)
        iconName = "spider";

    for (int i = 0; i < spriteParts->count(); i++)
    {
        auto spritePart = static_cast<CCSpritePart *>(spriteParts->objectAtIndex(i));
        auto tag = spritePart->getTag();

        std::string frame1Texture = fmt::format("{}_{:02}_{:02}_001.png"_spr, iconName, iconID, tag);
        std::string frame2Texture = fmt::format("{}_{:02}_{:02}_2_001.png"_spr, iconName, iconID, tag);
        std::string extraTexture = fmt::format("{}_{:02}_{:02}_extra_001.png"_spr, iconName, iconID, tag);
        std::string glowTexture = fmt::format("{}_{:02}_{:02}_glow_001.png"_spr, iconName, iconID, tag);

        if (auto frame1 = frameCache->spriteFrameByName(frame1Texture.c_str()))
        {
            spritePart->setBatchNode(nullptr);
            spritePart->setDisplayFrame(frame1);
        }

        if (auto secondSprite = static_cast<CCSprite *>(sprite->m_secondArray->objectAtIndex(i)))
        {
            if (auto frame2 = frameCache->spriteFrameByName(frame2Texture.c_str()))
            {
                secondSprite->setBatchNode(nullptr);
                secondSprite->setDisplayFrame(frame2);
                secondSprite->setPosition(spritePart->getContentSize() / 2);
            }
        }

        if (auto glowChild = static_cast<CCSprite *>(sprite->m_glowSprite->getChildren()->objectAtIndex(i)))
        {
            if (auto frameGlow = frameCache->spriteFrameByName(glowTexture.c_str()))
            {
                glowChild->setBatchNode(nullptr);
                glowChild->setDisplayFrame(frameGlow);
            }
        }

        if (spritePart == sprite->m_headSprite)
        {
            if (auto frameExtra = frameCache->spriteFrameByName(extraTexture.c_str()))
            {
                if (sprite->m_extraSprite)
                {
                    sprite->m_extraSprite->setBatchNode(nullptr);
                    sprite->m_extraSprite->setDisplayFrame(frameExtra);
                }
                else
                {
                    sprite->m_extraSprite = CCSprite::createWithSpriteFrame(frameExtra);
                    sprite->m_headSprite->addChild(sprite->m_extraSprite, 2);
                }

                sprite->m_extraSprite->setPosition(spritePart->getContentSize() / 2);
                sprite->m_extraSprite->setVisible(true);
            }
        }
    }
}

void Odyssey::addCreditsToIcon(std::pair<int, UnlockType> pair, int accountID)
{
    GameStatsManager::sharedState()->m_accountIDForIcon.insert(std::make_pair(pair, accountID));
}

int Odyssey::islandPageForLevelID(int levelID)
{
    if (levelID < 5)
        return 0;

    if (levelID > 200)
        return 2;

    return 1;
};