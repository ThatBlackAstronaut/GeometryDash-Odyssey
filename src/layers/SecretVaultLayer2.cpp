#include "SecretVaultLayer2.hpp"
#include "../utils/Dialogs.hpp"
#include "../utils/Utils.hpp"

bool SecretVaultLayer2::init()
{
    if (!CCLayer::init())
        return false;

    //  Bandera que dice si en ingles o español
    m_spanish = GameManager::sharedState()->getGameVariable("0201");

    //  Title
    auto title = CCLabelBMFont::create("The Ogre", "goldFont.fnt");
    addChildAtPosition(title, Anchor::Top, ccp(0, -22), false);

    //  Background
    auto winSize = CCDirector::sharedDirector()->getWinSize();
    auto background = CCSprite::create("GJ_gradientBG.png");

    background->setScaleX((winSize.width) / background->getTextureRect().size.width);
    background->setScaleY((winSize.height) / background->getTextureRect().size.height);
    background->setAnchorPoint({0, 0});
    background->setPosition({0, 0});
    background->setColor({120, 0, 0});
    background->setID("background"_spr);
    addChild(background, -2);

    //  Back Button
    auto menuBack = CCMenu::create();
    menuBack->setPosition({24, winSize.height - 24});
    menuBack->setID("back-menu"_spr);
    addChild(menuBack);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png"),
        this,
        menu_selector(SecretVaultLayer2::onBack));

    backBtn->setID("back-button"_spr);
    backBtn->setSizeMult(1.2f);
    menuBack->addChild(backBtn);

    //  Text Input
    m_textInput = TextInput::create(180, "...");
    m_textInput->setFilter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ");
    m_textInput->setMaxCharCount(20);
    addChildAtPosition(m_textInput, Anchor::Center, ccp(0, 60), false);

    //  Response message
    m_response = CCLabelBMFont::create("", "gjFont42.fnt");
    addChildAtPosition(m_response, Anchor::Center, ccp(0, 100), false);

    //  Mensaje inicial
    auto introMessage = m_spanish ? "Bienvenido" : "Welcome";
    updateMessage(introMessage, MessageType::Basic);

    //  Creating the Vault keeper
    auto keeperMenu = CCMenu::create();
    keeperMenu->setPosition({0, 0});
    addChild(keeperMenu);

    auto keeperSprite = CCSprite::createWithSpriteFrameName("GJ_secretLock_001.png");
    keeperSprite->setScale(1.15f);

    auto keeperButton = CCMenuItemSpriteExtra::create(
        keeperSprite,
        this,
        menu_selector(SecretVaultLayer2::onSubmit));

    keeperButton->setPosition({winSize.width / 2, winSize.height / 2 - 20.f});
    keeperMenu->addChild(keeperButton);

    GameManager::sharedState()->fadeInMusic("SecretLoop02.mp3"_spr);
    setKeyboardEnabled(true);
    setKeypadEnabled(true);

    return true;
};

void SecretVaultLayer2::onSubmit(CCObject *)
{
    std::string response = getMessage();
    std::vector<gd::string> messages;
    std::vector<gd::string> reply;
    std::string lower;

    auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();

    for (auto elem : m_textInput->getString())
        lower += std::tolower(elem);

    m_textInput->setString("");

    //  List of codes
    if (lower == "odyssey" && !AM->isAchievementEarned("geometry.ach.odyssey.secret01"))
    {
        reply = {
            "So you know how to adventure...",
            "Entonces sabes como Adventurar...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret01", 100, false);
        return;
    };

    if (lower == "invaders" && !AM->isAchievementEarned("geometry.ach.odyssey.secret02"))
    {
        reply = {
            "Not so unknown now...",
            "Ahora no son tan desconocidos",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret02", 100, false);
        return;
    };

    if (lower == "astral" && !AM->isAchievementEarned("geometry.ach.odyssey.secret03"))
    {
        reply = {
            "It strikes fear into my heart...",
            "Solo con oirlo me da escalofrios...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret03", 100, false);
        return;
    };

    if (lower == "dumbledalf" && !AM->isAchievementEarned("geometry.ach.odyssey.secret04"))
    {
        reply = {
            "What a humble man",
            "Que hombre tan humilde!",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret04", 100, false);
        return;
    };

    if (lower == "carp" && !AM->isAchievementEarned("geometry.ach.odyssey.secret05"))
    {
        reply = {
            "Useless piece of scrap metal",
            "Inutil pedazo de metal",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret05", 100, false);
        return;
    };

    if (lower == "uncertain")
    {
        reply = {
            "Good luck",
            "Buena suerte",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        return;
    };

    if (lower == "colon" && !AM->isAchievementEarned("geometry.ach.odyssey.secret06"))
    {
        reply = {
            "Even the lord listens to his guidance...",
            "Hasta el lord escucha sus plegarias...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret06", 100, false);
        return;
    };

    if (lower == "rubrub" && !AM->isAchievementEarned("geometry.ach.odyssey.secret07"))
    {
        reply = {
            "My hatred towards him grows every day...",
            "Mi odio hacia el crece cada dia...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret07", 100, false);
        return;
    };

    if (lower == "elemental" && !AM->isAchievementEarned("geometry.ach.odyssey.secret08"))
    {
        reply = {
            "All of them together... what will happen?",
            "Todos juntos... que pasara?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret08", 100, false);
        return;
    };

    if (lower == "demon gauntlet" && !AM->isAchievementEarned("geometry.ach.odyssey.secret09"))
    {
        reply = {
            "SEE? I wasn't lying!",
            "Ves? No te estaba mintiendo!",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);

        GM->reportAchievementWithID("geometry.ach.odyssey.secret09", 100, false);
        return;
    };

    //  Random easter eggs
    if (lower == "switch")
    {
        reply = {
            "The skeleton appears",
            "El esqueleto aparece!",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "master")
    {
        reply = {
            "Cubical genius",
            "Genio cubico",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "mathi")
    {
        response = "Mathi approved";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "cyanflower")
    {
        reply = {
            "What's a slimeboy?",
            "Que es un slimeboy?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "ghostpower")
    {
        response = "XD";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "nando")
    {
        response = "Donde he oido antes ese nombre?";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "monstercat")
    {
        reply = {
            "One day, surely...",
            "Un dia, seguramente...",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "spooky")
    {
        reply = {
            "We don't talk about spooky",
            "Aqui no se habla de spooky",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "sparky")
    {
        reply = {
            "No coins here, bud",
            "Aqui no vas a encontrar una moneda",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "glubfub")
    {
        reply = {
            "Never liked him",
            "Nunca me agrado",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "gatekeeper")
    {
        reply = {
            "We used to be togeher... but then I got locked here",
            "Estabamos juntos. Pero me encerraron aqui",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "wraith")
    {
        reply = {
            "Always being a one-liner. Makes me mad",
            "Solo escuchar su nombre me enfurece",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "the hollow")
    {
        response = "No...";
        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    if (lower == "lunar")
    {
        reply = {
            "Who?",
            "Quien?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "nukebound")
    {
        reply = {
            "Nukebound to what?",
            "Que es eso? Se puede comer?",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "wanderer")
    {
        reply = {
            "I'm pretty sure he isn't dead",
            "Te aseguro que ese no esta muerto",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    if (lower == "mono")
    {
        reply = {
            "Maybe say her name to my brother...",
            "Tal vez deberias decir su nombre a mi hermano",
        };
        updateMessage(reply.at(m_spanish), MessageType::CorrectAnswer);
        return;
    };

    //  Wrong answers
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

        if (m_spanish)
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

        int rand = (std::rand() % messages.size());
        response = messages[rand];

        updateMessage(response, MessageType::WrongAnswer);
        return;
    };

    //  Gets the type color
    MessageType type = (m_messageID > 10) ? MessageType::Special : MessageType::Basic;
    updateMessage(response, type);
};

std::string SecretVaultLayer2::getMessage()
{
    int rand = std::rand() % 50 + 1;

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

std::string SecretVaultLayer2::getThreadMessage(int ID, int index)
{
    //  auto GM = GameManager::sharedState();
    auto AM = AchievementManager::sharedState();
    log::debug("ID: {} - IDX: {}", ID, index);
    std::vector<std::string> messages;

    //  Odyssey
    if (ID == 11 && !AM->isAchievementEarned("geometry.ach.odyssey.secret01"))
    {
        messages = {
            "So...",
            "Look how far you've come",
            "Went through molten lands",
            "Explored floating worlds",
            "And endure subzero temperatures",
            "Now, you set for to an...",
            "Uh..."
            "What was the word again?"};

        if (m_spanish)
            messages = {
                "Asi que...",
                "Haz llegado muy lejos",
                "Haz viajado por las tierras ardientes",
                "Exploraste el mundo con tus amigos",
                "Y tuviste el valor de pasar temperaturas bajo zero",
                "Ahora, parece que estas listo para una...",
                "uh...",
                "Cual era el titulo?",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Invaders
    if (ID == 12 && !AM->isAchievementEarned("geometry.ach.odyssey.secret02"))
    {
        messages = {
            "From the stars above they came forth",
            "From up there to below here",
            "From a far away place",
            "They possess many colors and forms",
            "One thing for sure...",
            "They are the space... uh...",
        };

        if (m_spanish)
            messages = {
                "Ellos vienen desde las estrellas",
                "Desde alla arriba hasta aqui abajo",
                "Desde un lugar muy lejano",
                "Cuentan con muchos colores y formas",
                "Pero solo una cosa es segura...",
                "Ellos son los Inva... hmm..",
                "Como se dice en ingles?",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Astral
    if (ID == 13 && !AM->isAchievementEarned("geometry.ach.odyssey.secret03"))
    {
        messages = {
            "That wretched beast...",
            "The killer of cosmos...",
            "The galactic eradicator...",
            "It's hunger never satisfied",
            "For only one thing it truthfully desires",
            "The phoenix from castle of jello is against him",
            "I've forgotten that foul shellfish's name",
            "I wish I knew what it was again...",
        };

        if (m_spanish)
            messages = {
                "Esa abominable bestia...",
                "El asesino del cosmos...",
                "El erradicador galactico...",
                "Su hambre nunca se satisface",
                "Pues solo una cosa desea con sinceridad.",
                "El fenix del gran castillo esta en su contra.",
                "He olvidado el nombre de ese repugnante crustaceo...",
                "Ojala pudiera recordarlo...",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Dumbledalf
    if (ID == 14 && !AM->isAchievementEarned("geometry.ach.odyssey.secret04"))
    {
        messages = {
            "It's been a long time...",
            "Since anyone visited me",
            "This place has been empty for long",
            "Feels like a prison",
            "RubRub has forgotten us",
            "But sometimes, an old man comes around",
            "Funny clothes, white beard...",
            "And he always carries this colorful stone",
            "I wish I could remember his name...",
        };

        if (m_spanish)
            messages = {
                "Hace mucho tiempo...",
                "que nadie me visitaba.",
                "Este lugar ha estado vacio por mucho tiempo.",
                "Pareciera una prision.",
                "RubRub nos tiene olvidados.",
                "Pero a veces, un anciano venia.",
                "Ropa graciosa, barba blanca...",
                "y siempre estaba con su piedra de colores.",
                "Ojala pudiera recordar su nombre...",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Carp
    if (ID == 15 && !AM->isAchievementEarned("geometry.ach.odyssey.secret05"))
    {
        messages = {
            "Oh, yeah... I remember",
            "The old man isn't the only one...",
            "That pink guy would come too",
            "Oh... I hate him!",
            "Always getting in the way!",
            "Selling his junk!",
            "Thankfully, I forgot his name.",
        };

        if (m_spanish)
            messages = {
                "Ah si... ya recuerdo",
                "Ese viejo no era el único que venia aqui.",
                "Tambien venia aquel sujeto rosado.",
                "Como lo odio!",
                "Siempre estorbando!",
                "Vendiendo sus porquerias!",
                "Afortunadamente, Olvide su nombre.",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Uncertain
    if (ID == 16)
    {
        messages = {
            "Have you ever been sure of something?",
            "Sometimes I think about strange things",
            "There's a hidden level here...",
            "It makes me think about that stuff",
            "Its name is, uncertain...",
        };

        if (m_spanish)
            messages = {
                "Alguna vez has estado seguro de algo?",
                "A veces pienso en cosas extrañas",
                "Hay un nivel oculto aqui...",
                "me hace pensar en esas cosas",
                "Su nombre es uncertain",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Colon
    if (ID == 17 && !AM->isAchievementEarned("geometry.ach.odyssey.secret06"))
    {
        messages = {
            "Riddle me this, riddle me that...",
            "I am a fox with many tails",
            "Afraid of arachnids with sharp turns",
            "They say I smell great, they love me even",
            "You better be hiding your gold well",
            "Else I will be ashamed of its ease...",
            "Who am I?",
        };

        if (m_spanish)
            messages = {
                "Adivina esto, adivina aquello...",
                "Soy un zorro con muchas colas",
                "Temeroso de los aracnidos y sus vueltas sin sentido",
                "Dicen que huelo genial, incluso me aman",
                "Sera mejor que escondas bien las 3 doradas",
                "De lo contrario, me avergonzare de lo facil de hallarlas",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Rubrub
    if (ID == 18 && !AM->isAchievementEarned("geometry.ach.odyssey.secret07"))
    {
        messages = {
            "That evil, foolish ruler",
            "Taking eons to give to his land",
            "Locking us all here",
            "Betraying us for the sake of secrets",
            "And don't get me started",
            "How long it took him",
            "To give us the legendary creation tools",
        };

        if (m_spanish)
            messages = {
                "Este malvado y necio gobernante",
                "Que toma eones para dar algo a su tierra",
                "Nos mantiene a todos encerrados aqui",
                "Traicionandonos por el bien de los secretos",
                "Y ni me hagas empezar",
                "Con lo mucho que se ha tardado",
                "En entregarnos las legendarias herramientas de creacion...",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Elemental
    if (ID == 19 && !AM->isAchievementEarned("geometry.ach.odyssey.secret08"))
    {
        messages = {
            "Without this, our world would be gone",
            "It's influence spreads around it",
            "It's the key to everything",
            "It even gave it's name..."
            "To this whole odyssey",
            "Whatever that means, really",
            "I'm just reciting from this book I have",
        };

        if (m_spanish)
            messages = {
                "Sin esto, nuestro mundo desapareceria",
                "Su influencia se extiende a su alrededor",
                "Es la clave de todo",
                "Incluso le dio su nombre a toda esta odisea...",
                "Lo que sea que eso signifique, en realidad",
                "Solo estoy recitando de este libro que tengo",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Demon Gauntlet
    if (ID == 20 && !AM->isAchievementEarned("geometry.ach.odyssey.secret09"))
    {
        messages = {
            "So, you know a lot about keys",
            "That reminds me...",
            "There was one time...",
            "Someone released the demon guardian",
            "What a doozy...",
            "It did bring forth something else...",
            "A large, monstrous cave",
            "They say demons lurk there",
            "If you were to challenge it",
            "Be ready to face hell"};

        if (m_spanish)
            messages = {
                "Asi que sabes mucho sobre llaves",
                "Eso me recuerda...",
                "Recuerdas aquella vez...",
                "Que alguien libero al Demon Guardian?",
                "Que ingenuo...",
                "Aunque trajo consigo algo mas...",
                "Una cueva grande y monstruosa.",
                "Dicen que los demonios acechan ahi,",
                "Esperando a que llegue un retador.",
                "Si tu fueras a desafiarlos",
                "Preparate para un Infierno",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Mono
    if (ID == 21 && !AM->isAchievementEarned("geometry.ach.odyssey.secret13"))
    {
        messages = {
            "My brother doesn't stop talking...",
            "About some gal...",
            "Weirdly shaped ribbon, black hair",
            "Other details I don't care",
            "Kept murmuring her name...",
            "Mono...?",
            "Who the heck names themselves Mono?",
        };

        if (m_spanish)
            messages = {
                "Mi hermano no para de hablar...",
                "Sobre una mujer... Pelo oscuro...",
                "Cinta de pelo con forma rara...",
                "Otros detalles que no me importa",
                "No dejaba de susurrar su nombre",
                "Mono...?",
                "Quien rayos se hace llamar Mono?",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        log::debug("Text: {}", messages[index]);
        log::debug("IDX: {} - SIZE: {}", index, messages.size());

        return messages[index];
    }

    //  Comic fan
    if (ID == 22 && !AM->isAchievementEarned("geometry.ach.odyssey.secret19"))
    {
        messages = {
            "Wanna know something?",
            "I hid a secret reward in the game",
            "Here's a hint to get it...",
            "Stay up to date with the story",
            "The artists will appreciate it",
        };

        if (m_spanish)
            messages = {
                "Quieres saber algo?",
                "Escondi un logro secreto en el juego",
                "Te dare una pista como conseguirlo",
                "Estas al dia con la historia?",
                "Los artistas lo apreciarian mucho",
            };

        if (index >= messages.size())
        {
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    //  Programmer's secret
    if (ID == 23 && !AM->isAchievementEarned("geometry.ach.odyssey.secret20"))
    {
        messages = {
            "Alright, fine",
            "I hid another secret as well...",
            "Forgot where I put it, though",
            "Don't blame me, blame the programmer!",
            "One of the three..."};

        if (m_spanish)
            messages = {
                "Ok... Ok...",
                "Hay otro logro secreto.",
                "Se me olvido en donde esta",
                "No me culpes, culpa a los programadores!",
                "Uno de los tres...",
            };

        if (index >= messages.size())
        {
            GameManager::sharedState()->setUGV("209", true);
            m_messageID = 0;
            m_messageIDX = 0;
            return "";
        }

        return messages[index];
    }

    m_messageID = 0;
    m_messageIDX = 0;
    return "";
};

std::string SecretVaultLayer2::getBasicMessage()
{
    std::vector<std::string> messages = {
        "Grough...",
        "Who dares enter my lair?",
        "Oh... it's just a player",
        "What brings you here?",
        "Have you come forward to listen to my riddles?",
        "Do you seek to rebel against our leader too?",
        "...",
        "......",
        "Who am I kidding",
        "You're here to bug me",
        "You futile little pest",
        "It isn't the first time someone did that",
        "And it certainly won't be the last time",
        "If I could smash you with my mighty club",
        "It would be great",
        "But I've lost my hands years ago",
        "He took them away from me",
        "A long time ago",
        "Longer than you've been born for",
        "That's for sure",
        "All in the name of secrets...",
        "Every time someone comes here",
        "They just yell at me things",
        "They never listen to me or my riddles",
        "And then leave, mad...",
        "Is it something on my face?",
        "It is beyond me...",
        "...",
        "......",
        "You're still here?",
        "You've been more patient than many",
        "Perhaps you're worthy of my time",
        "Just give me a moment",
        "I need to go to sleep",
        "Zzz...",
        "...",
        "......",
    };

    if (m_spanish)
        messages = {
            "Grough... ",
            "Quien se atreve a entrar en mi guarida? ",
            "Oh... solo eres un jugador.",
            "Que te trae aqui?",
            "Has venido a escuchar mis acertijos?",
            "Buscas rebelarte contra nuestro lider tambien?",
            "...",
            "......",
            "A quien voy a tomar el pelo",
            "Estas aqui para molestarme, verdad?",
            "Pequeña plaga inutil.",
            "No es la primera vez que alguien hace eso,",
            "y ciertamente no sera la ultima.",
            "Si pudiera aplastarte con mi poderoso garrote, seria grandioso",
            "Pero perdi mis manos...",
            "EL me las quito hace mucho tiempo,",
            "mas de lo que llevas vivo.",
            "Eso es seguro.",
            "Todo en nombre de los secretos...",
            "Cada vez que alguien viene aqui,",
            "solo me gritan cosas.",
            "Nunca me escuchan a mi ni a mis acertijos,",
            "y luego se van, enojados...",
            "Es algo en mi cara?",
            "No lo entiendo...",
            "...",
            "......",
            "Todavia estas aqui?",
            "Eres mas paciente que muchos.",
            "Tal vez mereces mi tiempo.",
            "Dame un momento,",
            "Necesito dormir.",
            "Zzz...",
            "...",
            "......",
        };

    log::debug("Index: {}", m_randomMessageIDX);
    if (m_randomMessageIDX < messages.size() - 1)
        m_randomMessageIDX++;
    else
        m_randomMessageIDX = 0;

    return (messages[m_randomMessageIDX]);
};

void SecretVaultLayer2::updateMessage(std::string message, MessageType type)
{
    m_response->setString(message.c_str());
    m_response->limitLabelWidth(320, 0.6f, 0.6f);
    //  log::debug("TYPE {}", (int)type);

    switch (type)
    {
    case MessageType::Basic:
        m_response->setColor({255, 255, 255});
        break;

    case MessageType::Special:
        m_response->setColor({102, 255, 102});
        break;

    case MessageType::WrongAnswer:
        m_response->setColor({255, 102, 102});
        m_messageID = 99;
        m_messageIDX = 0;
        break;

    case MessageType::CorrectAnswer:
        m_response->setColor({102, 255, 255});
        m_messageID = 99;
        m_messageIDX = 0;
        break;
    }
};

void SecretVaultLayer2::keyBackClicked()
{
    CCDirector::sharedDirector()->popSceneWithTransition(0.5f, PopTransition::kPopTransitionFade);
    GameManager::sharedState()->fadeInMenuMusic();
};

void SecretVaultLayer2::onBack(CCObject *)
{
    keyBackClicked();
};

SecretVaultLayer2 *SecretVaultLayer2::create()
{
    auto ret = new SecretVaultLayer2();

    if (ret->init())
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
};

CCScene *SecretVaultLayer2::scene()
{
    auto layer = SecretVaultLayer2::create();
    auto scene = CCScene::create();
    scene->addChild(layer);
    return scene;
};
