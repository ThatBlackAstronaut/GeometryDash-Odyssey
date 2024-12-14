#include "SecretVaultLayer.hpp"
#include "../utils/Utils.hpp"

bool SecretVaultLayer::init()
{
    if (!CCLayer::init())
        return false;

    //  Title
    m_title = CCLabelBMFont::create("The Hollow", "goldFont.fnt");
    addChildAtPosition(m_title, Anchor::Top, ccp(0, -22), false);
    m_title->setColor({180, 0, 0});

    //  Data
    m_achievementName = "";
    m_spanish = GameManager::sharedState()->getGameVariable("0201");

    //  Background
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    m_background = CCSprite::createWithSpriteFrameName("HollowBG_001.png"_spr);
    m_bg_2 = CCSprite::createWithSpriteFrameName("HollowBG_2_001.png"_spr);
    m_bg_3 = CCSprite::createWithSpriteFrameName("HollowBG_3_001.png"_spr);

    m_background->setScaleX((winSize.width) / m_background->getTextureRect().size.width);
    m_background->setScaleY((winSize.height) / m_background->getTextureRect().size.height);
    m_background->setAnchorPoint({0, 0});
    m_background->setPosition({0, 0});
    m_background->setColor({120, 0, 0});
    m_background->setID("background"_spr);
    addChild(m_background, -4);

    m_bg_2->setScaleX((winSize.width) / m_bg_2->getTextureRect().size.width);
    m_bg_2->setScaleY((winSize.height) / m_bg_2->getTextureRect().size.height);
    m_bg_2->setID("background-layer-2"_spr);
    m_bg_2->setAnchorPoint({0, 0});
    m_bg_2->setPosition({0, 0});
    m_bg_2->setColor({0, 0, 0});
    m_bg_2->setOpacity(90);
    addChild(m_bg_2, -3);

    m_bg_3->setScaleX((winSize.width) / m_bg_3->getTextureRect().size.width);
    m_bg_3->setScaleY((winSize.height) / m_bg_3->getTextureRect().size.height);
    m_bg_3->setID("background-layer-3"_spr);
    m_bg_3->setAnchorPoint({0, 0});
    m_bg_3->setPosition({0, 0});
    m_bg_3->setColor({0, 0, 0});
    addChild(m_bg_3, -2);

    //  Back Button
    auto menuBack = CCMenu::create();
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(SecretVaultLayer::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);
    menuBack->addChild(backBtn);

    //  Text Input
    m_textInput = TextInput::create(180, "...");
    m_textInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    m_textInput->setMaxCharCount(20);
    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 65), false);

    //  Creating the Vault keeper
    auto keeperMenu = CCMenu::create();
    keeperMenu->setPosition({0, 0});
    addChild(keeperMenu, 3);

    m_keeperSprite = CCSprite::create();
    m_keeperSprite->setContentSize({60, 60});

    keeperSprite = CCSprite::createWithSpriteFrameName("HollowKeeper_001.png"_spr);
    keeperSprite->setScale(1.15f);

    keeperEyes = CCSprite::createWithSpriteFrameName("HollowKeeper_eyes_001.png"_spr);
    keeperEyes->setScale(1.15f);
    keeperEyes->setOpacity(0);

    m_keeperSprite->addChildAtPosition(keeperSprite, Anchor::Center);
    m_keeperSprite->addChildAtPosition(keeperEyes, Anchor::Center);

    m_keeperBtn = CCMenuItemSpriteExtra::create(
        m_keeperSprite,
        this,
        menu_selector(SecretVaultLayer::onSubmit));

    m_keeperBtn->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    m_keeperBtn->m_colorEnabled = false;
    m_keeperBtn->m_colorDip = 100.0f;
    keeperMenu->addChild(m_keeperBtn);

    //  Response message
    m_response = CCLabelBMFont::create("", "gjFont41.fnt");
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 100), false);

    //  Mensaje inicial
    auto introMessage = m_spanish ? "Bienvenido..." : "Welcome...";
    updateMessage(introMessage, MessageType::Basic);

    bg_particle_01 = GameToolbox::particleFromString("50a-1a2a0.5a15a90a0a50a25a400a0a0a0a0a0a0a0a15a7a0a0a0a0a0a0a0a0a1a0a0a0a0a0a0a0a0a0a0a0a1a0a0.5a0.2a0.5a0.2a0a0a0a0a0a0a0a2a0a0a0a0a25a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    bg_particle_01->setPositionX(winSize.width / 2);
    addChild(bg_particle_01);

    bg_particle_02 = GameToolbox::particleFromString("10a-1a4a2a1a90a0a15a10a400a100a0a0a0a0a0a0a100a50a0a0a0a0a0a0a0a0a0.5a0.25a0a0a0a0a0a0a0a0a0a0a0.5a0.25a1a0a1a0a0a0a0a0a0a0a0a2a0a0a0a0a40a0a0a0a0a0a0a1a0a0a0a0a0a0a0", NULL, false);
    bg_particle_02->setPosition(winSize / 2);
    addChild(bg_particle_02);

    keeper_auraParticles = GameToolbox::particleFromString("20a-1a2a1a6a90a180a29a0a11a0a0a0a0a0a0a0a6a4a0a0a0a0a0a0a0a0a1a0a0a0a0a0a0a0a0a0a0a0a1a0a0.5a0a0.5a0a25a20a30a15a0a0a1a2a0a0a0a0a2a0a0a0a0a0a0a1a1a0a0a0a0a0a0", NULL, false);
    keeper_auraParticles->setPosition(m_keeperBtn->getPosition());
    addChild(keeper_auraParticles, 1);

    GameManager::sharedState()->fadeInMusic("SecretLoop01.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void SecretVaultLayer::onSubmit(CCObject *)
{
    std::string response = getMessage();
    std::string language = m_spanish ? "SPA" : "ENG";
    std::vector<gd::string> messages;
    std::vector<gd::string> voiceFiles;
    std::string lower;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    for (auto elem : m_textInput->getString())
        lower += std::tolower(elem);

    m_textInput->setString("");
    m_achievementName = "";

    /*
    if (lower == "gargan")
    {
        if (m_garganIDX > 3)
        {
            messages = {
                "Stop.",
                "Don't provoke him.",
                "Get out while you can.",
                "..."};

            m_title->setString(messages[m_garganIDX % 3].c_str());
        }

        m_garganIDX++;
        return;
    }

    m_title->setString("The Hollow");
    m_garganIDX = 0;
    */

    //  List of codes
    if (lower == "color" && !AM->isAchievementEarned("geometry.ach.odyssey.secret10"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_004.mp3"_spr, language));
        response = m_spanish ? "Esto es monocromatico, cierto?" : "This isn't monochromatic, is it?";

        updateMessage(response, MessageType::CorrectAnswer);
        m_achievementName = "geometry.ach.odyssey.secret10";
        return;
    };

    if (lower == "fracture")
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_010.mp3"_spr, language));
        response = m_spanish ? "Abraza el caos" : "Embrace the chaos...";

        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "explorers" && !AM->isAchievementEarned("geometry.ach.odyssey.secret11"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_014.mp3"_spr, language));
        response = m_spanish ? "Tal vez en la proxima actualizacion" : "Maybe in the next update...";

        m_achievementName = "geometry.ach.odyssey.secret11";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "player" && !AM->isAchievementEarned("geometry.ach.odyssey.secret12"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_018.mp3"_spr, language));
        response = m_spanish ? "Fuistes tu?" : "...was it you?",

        m_achievementName = "geometry.ach.odyssey.secret12";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "mono" && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_022.mp3"_spr, language));
        response = m_spanish ? "Algo en ella se siente extrano..." : "Something about her feels off...",

        m_achievementName = "geometry.ach.odyssey.secret13";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "nock em" && !AM->isAchievementEarned("geometry.ach.odyssey.secret14"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_025.mp3"_spr, language));
        response = m_spanish ? "Enemigo derrotado... nah" : "Enemy defeated... not";

        m_achievementName = "geometry.ach.odyssey.secret14";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "machina" && !AM->isAchievementEarned("geometry.ach.odyssey.secret15"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_028.mp3"_spr, language));
        response = m_spanish ? "Que casualidad..." : "How sudden...";

        m_achievementName = "geometry.ach.odyssey.secret15";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "the seven seas" && !AM->isAchievementEarned("geometry.ach.odyssey.secret16"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_031.mp3"_spr, language));
        response = m_spanish ? "Guianos, capitan." : "Guide us, captain.";

        m_achievementName = "geometry.ach.odyssey.secret16";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "smooth jazz" && !AM->isAchievementEarned("geometry.ach.odyssey.secret17"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_034.mp3"_spr, language));
        response = "Blergh";

        m_achievementName = "geometry.ach.odyssey.secret17";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    if (lower == "angel" && !AM->isAchievementEarned("geometry.ach.odyssey.secret18"))
    {
        FMODAudioEngine::sharedEngine()->playEffect(fmt::format("hollow_{}_037.mp3"_spr, language));
        response = m_spanish ? "Los sagrados..." : "The holy...";

        m_achievementName = "geometry.ach.odyssey.secret18";
        updateMessage(response, MessageType::CorrectAnswer);
        return;
    };

    /*
    if (lower == "gargan")
    {
        FMODAudioEngine::sharedEngine()->fadeOutMusic(5.f, 0);

        m_textInput->runAction(CCSequence::create(
            CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::disableKeeper)),
            nullptr));

        keeperSprite->runAction(CCSequence::create(
            CCTintTo::create(2.f, 40, 0, 0),
            CCEaseSineInOut::create(CCScaleTo::create(3.f, 5)),
            nullptr));

        m_background->runAction(CCSequence::create(
            CCTintTo::create(3.f, 0, 0, 0),
            nullptr));

        return;
    };

    if (lower == "gargan")
    {
        response = "What do you mean...?",
        updateMessage(response, MessageType::CorrectAnswer);

        keeper_angerParticles_01 = GameToolbox::particleFromString("50a-1a2a0a25a90a30a29a0a20a20a0a100a0a0a0a0a30a20a0a0a0a0a0a0a0a0a1a0a20a10a0a0a0a0a0a0a0a0a1a0a0.1a0a0.25a0a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
        keeper_angerParticles_01->setPosition(m_keeperBtn->getPosition());
        addChild(keeper_angerParticles_01, 1);

        keeper_angerParticles_02 = GameToolbox::particleFromString("30a-1a1a0.3a23a90a5a83a20a0a0a0a0a0a0a0a0a20a0a0a0a1a0a0a0a0a0a1a0a5a5a0a0a1a0a0a0a0a0a1a0a0a0a0.2a0.1a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
        keeper_angerParticles_02->setPosition(m_keeperBtn->getPosition());
        keeperSprite->addChild(keeper_angerParticles_02, 4);

        keeper_angerParticles_03 = GameToolbox::particleFromString("30a-1a1a0.3a23a90a5a83a20a0a0a0a0a0a0a0a0a20a0a0a0a1a0a0a0a0a0a1a0a5a5a0a0a1a0a0a0a0a0a1a0a0a0a0.2a0.1a0a0a0a0a0a0a0a2a0a0a0a0a2a0a0a0a0a0a0a0a0a0a0a0a0a0a0", NULL, false);
        keeper_angerParticles_03->setPosition(m_keeperBtn->getPosition());
        keeperSprite->addChild(keeper_angerParticles_03, 4);

        return;
    };
    */

    //  Wrong Answers
    if (lower != "")
    {
        messages = {
            "Well then...",
            "You really are a fool...",
            "Enough is enough",
            "Come back when you're a little... smarter",
            "Arrgh... you pest...",
            "Cough, cough cough...",
            "Don't waste my time",
            "Your requests mean nothing",
            "Feel ashamed of yourself...",
            "A lasting impression...",
        };

        voiceFiles = {
            "hollow_ENG_043.mp3"_spr,
            "hollow_ENG_044.mp3"_spr,
            "hollow_ENG_045.mp3"_spr,
            "hollow_ENG_046.mp3"_spr,
            "hollow_ENG_047.mp3"_spr,
            "hollow_ENG_048.mp3"_spr,
            "hollow_ENG_049.mp3"_spr,
            "hollow_ENG_050.mp3"_spr,
            "hollow_ENG_051.mp3"_spr,
            "hollow_ENG_052.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Muy bien...",
                "Eres realmente un tonto...",
                "Ya es suficiente",
                "Vuelve cuando seas un poco... mas inteligente",
                "Arrgh... eres una molestia...",
                "Cough, cough cough...",
                "No me hagas perder el tiempo",
                "Tus peticiones no significan nada",
                "Siente vergüenza de ti mismo...",
                "Una impresión duradera...",
            };

            voiceFiles = {
                "hollow_SPA_043.mp3"_spr,
                "hollow_SPA_044.mp3"_spr,
                "hollow_SPA_045.mp3"_spr,
                "hollow_SPA_046.mp3"_spr,
                "hollow_SPA_047.mp3"_spr,
                "hollow_SPA_048.mp3"_spr,
                "hollow_SPA_049.mp3"_spr,
                "hollow_SPA_050.mp3"_spr,
                "hollow_SPA_051.mp3"_spr,
                "hollow_SPA_052.mp3"_spr,
            };
        }

        int rand = (std::rand() % messages.size());
        response = messages[rand];
        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[rand]);
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    //  Gets the type color
    MessageType type = (m_messageID > 10) ? MessageType::Special : MessageType::Basic;
    updateMessage(response, type);
};

std::string SecretVaultLayer::getMessage()
{
    int rand = std::rand() % 30 + 1;

    if (m_messageID == 0)
    {
        m_messageID = rand;
        m_messageIDX = 0;

        std::string message = getThreadMessage(m_messageID, m_messageIDX);

        if (message == "")
            message = getBasicMessage();
        m_messageIDX++;

        return message;
    }
    else
    {
        auto ret = getThreadMessage(m_messageID, m_messageIDX++);
        if (ret == "")
            ret = getBasicMessage();
        return ret;
    }
};

std::string SecretVaultLayer::getThreadMessage(int ID, int index)
{
    log::debug("ID: {} - IDX: {}", ID, index);
    std::vector<std::string> messages;
    std::vector<gd::string> voiceFiles;

    //  auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    //  Color
    if (ID == 11 && !AM->isAchievementEarned("geometry.ach.odyssey.secret10"))
    {
        messages = {
            "I am the language of light",
            "I give life to all you see",
            "Without me, the world would be gray...",
        };

        voiceFiles = {
            "hollow_ENG_001.mp3"_spr,
            "hollow_ENG_002.mp3"_spr,
            "hollow_ENG_003.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Soy el lenguaje de la luz,",
                "Doy vida a todo lo que ves.",
                "Sin mí, el mundo sería gris...",
            };

            voiceFiles = {
                "hollow_SPA_001.mp3"_spr,
                "hollow_SPA_002.mp3"_spr,
                "hollow_SPA_003.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Fracture
    if (ID == 12)
    {
        messages = {
            "Sometimes, breaking isn't the end, but the start...",
            "Dive into the glitchy abyss I have for you",
            "It's called Fracture",
            "Hold on tight",
            "The beats here might just split reality",
        };

        voiceFiles = {
            "hollow_ENG_005.mp3"_spr,
            "hollow_ENG_006.mp3"_spr,
            "hollow_ENG_007.mp3"_spr,
            "hollow_ENG_008.mp3"_spr,
            "hollow_ENG_009.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "A veces, romper no es el final, sino el comienzo...",
                "Sumérgete en esta prueba que tengo para ti",
                "Se llama Fracture",
                "Aguanta fuerte",
                "Los ritmos aquí podrían partir la realidad",
            };

            voiceFiles = {
                "hollow_SPA_005.mp3"_spr,
                "hollow_SPA_006.mp3"_spr,
                "hollow_SPA_007.mp3"_spr,
                "hollow_SPA_008.mp3"_spr,
                "hollow_SPA_009.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Explorers
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret11"))
    {
        messages = {
            "That failed promise...",
            "That guardian of the forest temple...",
            "Delayed until the end of time...",
        };

        voiceFiles = {
            "hollow_ENG_011.mp3"_spr,
            "hollow_ENG_012.mp3"_spr,
            "hollow_ENG_013.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "La promesa fallida",
                "Aquel guardian del templo del bosque",
                "Retrasado hasta el fin de los tiempos...",
            };

            voiceFiles = {
                "hollow_SPA_011.mp3"_spr,
                "hollow_SPA_012.mp3"_spr,
                "hollow_SPA_013.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Player
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret12"))
    {
        messages = {
            "They have doomed this world...",
            "They who let the Darkness out...",
            "Who could it be? Perhaps, is it in front of me?",
        };

        voiceFiles = {
            "hollow_ENG_015.mp3"_spr,
            "hollow_ENG_016.mp3"_spr,
            "hollow_ENG_017.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Han condenado a este mundo...",
                "Aquellos que liberaron a The Darkness...",
                "Quien pudo ser? Acaso, esta frente a mi?",
            };

            voiceFiles = {
                "hollow_SPA_015.mp3"_spr,
                "hollow_SPA_016.mp3"_spr,
                "hollow_SPA_017.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Mono
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        messages = {
            "Her cross-shaped ribbon and blank eyes...",
            "A traveller with pale, greyscale skin...",
            "Her pure black hair flows like a waterfall...",
        };

        voiceFiles = {
            "hollow_ENG_019.mp3"_spr,
            "hollow_ENG_020.mp3"_spr,
            "hollow_ENG_021.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Su cinta en forma de cruz",
                "Una viajera con piel palida y en escala de grises",
                "Su cabello negro fluye como cascada",
            };

            voiceFiles = {
                "hollow_SPA_019.mp3"_spr,
                "hollow_SPA_020.mp3"_spr,
                "hollow_SPA_021.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Nock em
    if (ID == 16 && !AM->isAchievementEarned("geometry.ach.odyssey.secret14"))
    {
        messages = {
            "A bossfight approaches...",
            "Predator or prey...",
        };

        voiceFiles = {
            "hollow_ENG_023.mp3"_spr,
            "hollow_ENG_024.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Pagina numero dos...",
                "Bajo Zero...",
            };

            voiceFiles = {
                "hollow_SPA_023.mp3"_spr,
                "hollow_SPA_024.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Machina
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret15"))
    {
        messages = {
            "Silhouette harmony...",
            "Deus ex...",
        };

        voiceFiles = {
            "hollow_ENG_026.mp3"_spr,
            "hollow_ENG_027.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Casualidades, existen varias",
                "Mi favorita es el Deus Ex...",
            };

            voiceFiles = {
                "hollow_SPA_026.mp3"_spr,
                "hollow_SPA_027.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  The seven seas
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret16"))
    {
        messages = {
            "Sail forth if you dare...",
            "There used to be seven, now they are dangerous...",
        };

        voiceFiles = {
            "hollow_ENG_029.mp3"_spr,
            "hollow_ENG_030.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Navega si te atreves...",
                "Antes eran siete, y ahora son peligrosos...",
            };

            voiceFiles = {
                "hollow_SPA_029.mp3"_spr,
                "hollow_SPA_030.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Smooth Jazz
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret17"))
    {
        messages = {
            "The Warrior of Wubstep's worst enemy...",
            "I am tired of hearing that saxophone...",
        };

        voiceFiles = {
            "hollow_ENG_032.mp3"_spr,
            "hollow_ENG_033.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "El peor enemigo del Guerrero del Wubstep...",
                "Estoy cansado de oír ese saxofon...",
            };

            voiceFiles = {
                "hollow_SPA_032.mp3"_spr,
                "hollow_SPA_033.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    //  Angel
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret18"))
    {
        messages = {
            "Those against the demons...",
            "Their voice echoes across heaven...",
        };

        voiceFiles = {
            "hollow_ENG_035.mp3"_spr,
            "hollow_ENG_036.mp3"_spr,
        };

        if (m_spanish)
        {
            messages = {
                "Aquellos contra los demonios...",
                "Su voz resuena en el cielo...",
            };

            voiceFiles = {
                "hollow_SPA_035.mp3"_spr,
                "hollow_SPA_036.mp3"_spr,
            };
        }

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        FMODAudioEngine::sharedEngine()->playEffect(voiceFiles[index]);
        return messages[index];
    }

    m_messageID = 0;
    m_messageIDX = 0;
    return "";
};

std::string SecretVaultLayer::getBasicMessage()
{
    std::vector<std::string> messages = {
        "What brings you here?",
        "I've been rotting for years...",
        "Do I look sane to you?",
        "Welcome to the shadow realm",
        "The shadow government fears me",
        "Greheheheheh...",
        "How long you'll stay here...",
        "This will be fun...",
        "Join me... become one with the darkness",
        "Amuse me... mortal",
        "He locked me in here...",
        "It's been a while since I've seen someone here...",
    };

    int rand = (std::rand() % messages.size());
    return (messages[rand]);
};

void SecretVaultLayer::updateMessage(std::string message, MessageType type)
{
    auto flag_2 = false;
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.6f);
    log::debug("TYPE {}", (int)type);

    switch (type)
    {
    case MessageType::Basic:
        m_response->setColor({255, 255, 255});
        flag_2 = true;
        break;

    case MessageType::Special:
        m_response->setColor({255, 102, 102});
        break;

    case MessageType::WrongAnswer:
        m_response->setColor({102, 102, 102});
        m_messageID = 99;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({150, 102, 255});
        m_messageID = 99;
        m_messageIDX = 0;
        break;
    }

    auto flag = (message == "Welcome..." || message == "Bienvenido...");
    log::debug("Test: {}", flag);
    fadeInLabel(flag, flag_2);
};

void SecretVaultLayer::fadeInLabel(bool firstTime, bool skipAnimation)
{
    if (skipAnimation && !firstTime)
    {
        for (int ii = 0; ii < strlen(m_response->getString()); ii++)
        {
            auto child = static_cast<CCSprite *>(m_response->getChildren()->objectAtIndex(ii));
            child->setOpacity(0);
        }
        return;
    }

    for (int ii = 0; ii < strlen(m_response->getString()); ii++)
    {
        auto child = static_cast<CCSprite *>(m_response->getChildren()->objectAtIndex(ii));
        child->setOpacity(0);

        m_textInput->runAction(CCSequence::create(
            CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::disableKeeper)),
            CCDelayTime::create((strlen(m_response->getString()) * .175f) + 0.5),
            CCCallFunc::create(this, callfunc_selector(SecretVaultLayer::enableKeeper)),
            nullptr));

        if (ii == 0 && !firstTime)
        {
            keeperSprite->runAction(CCSequence::create(
                CCTintTo::create(1.f, 80, 0, 0),
                CCDelayTime::create((strlen(m_response->getString()) * .175f) - 1),
                CCTintTo::create(1.f, 255, 255, 255),
                nullptr));

            keeperEyes->runAction(CCSequence::create(
                CCFadeTo::create(1.f, 255),
                CCDelayTime::create((strlen(m_response->getString()) * .175f) - 1),
                CCFadeTo::create(1.f, 0),
                nullptr));
        }

        auto fadeInDelay = CCDelayTime::create(.05f * ii);
        auto fadeIn = CCFadeTo::create(.2f, 255);
        auto fadeOutDelay = CCDelayTime::create(.1f * strlen(m_response->getString()));
        auto fadeOut = CCFadeTo::create(.2f, 0);

        child->runAction(CCSequence::create(fadeInDelay, fadeIn, fadeOutDelay, fadeOut, nullptr));
    }
};

void SecretVaultLayer::enableKeeper()
{
    log::debug("Keeper enabled");

    if (m_achievementName != "")
    {
        auto GM = GameManager::sharedState();
        GM->reportAchievementWithID(m_achievementName.c_str(), 100, false);
    };

    m_textInput->setEnabled(true);
    m_keeperBtn->setEnabled(true);
};

void SecretVaultLayer::disableKeeper()
{
    log::debug("Keeper Disabled");
    m_textInput->setEnabled(false);
    m_keeperBtn->setEnabled(false);
};

void SecretVaultLayer::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->fadeInMusic("comic_04.mp3"_spr);
    FMODAudioEngine::sharedEngine()->stopAllEffects();
};

void SecretVaultLayer::onBack(CCObject *)
{
    keyBackClicked();
};

SecretVaultLayer *SecretVaultLayer::create()
{
    auto ret = new SecretVaultLayer();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *SecretVaultLayer::scene()
{
    auto layer = SecretVaultLayer::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};
