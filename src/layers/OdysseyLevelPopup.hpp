#pragma once
using namespace geode::prelude;

class OdysseyLevelPopup : public geode::Popup<std::string const &>
{
public:
    GJGameLevel *m_level;
    int m_levelID = 0;

protected:

    bool setup(std::string const &value) override
    {
        m_level = GameLevelManager::sharedState()->getMainLevel(m_levelID, false);
        
        setTitle(m_level->m_levelName);

        m_title->limitLabelWidth(200, .85f, .1f);
        m_title->setPositionY(m_title->getPositionY() - 5);

        m_closeBtn->setPosition(m_closeBtn->getPositionX() + 5, m_closeBtn->getPositionY() - 5);

        return true;
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