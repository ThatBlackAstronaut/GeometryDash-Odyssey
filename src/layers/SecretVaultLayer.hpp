#pragma once
using namespace geode::prelude;

enum class MessageType
{
    Basic = 0,
    Special = 1,
    WrongAnswer = 2,
    CorrectAnswer = 3
};

class SecretVaultLayer : public CCLayer
{
protected:
    CCMenuItemSpriteExtra *m_keeperBtn = nullptr;
    CCLabelBMFont *m_response = nullptr;
    TextInput *m_textInput = nullptr;

    CCSprite * m_keeperSprite = nullptr;
    CCSprite * keeperSprite = nullptr;
    CCSprite * keeperEyes = nullptr;

    CCParticleSystemQuad * bg_particle_01 = nullptr;
    CCParticleSystemQuad * bg_particle_02 = nullptr;
    CCParticleSystemQuad * keeper_auraParticles = nullptr;
    CCParticleSystemQuad * keeper_angerParticles_01 = nullptr;
    CCParticleSystemQuad * keeper_angerParticles_02 = nullptr;
    CCParticleSystemQuad * keeper_angerParticles_03 = nullptr;

    gd::string m_achievementName;

    int m_messageID;
    int m_messageIDX;
    int m_garganIDX = 0;

    virtual bool init();
    virtual void keyBackClicked();

    void enableKeeper();
    void disableKeeper();
    void onSubmit(CCObject *);
    void onBack(CCObject *);

public:
    static SecretVaultLayer *create();
    CCScene *scene();

    void updateMessage(std::string, MessageType);
    std::string getBasicMessage();
    std::string getMessage();
    std::string getThreadMessage(int, int);

    void fadeInLabel(bool);
};