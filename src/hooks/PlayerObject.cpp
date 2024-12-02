#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(OdysseyPlayerObject, PlayerObject)
{
    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4)
    {
        if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;

        updatePlayerFrame(p0);

        return true;
    }
    void updatePlayerFrame(int id)
    {
        PlayerObject::updatePlayerFrame(id);

        log::info("{}\n", id);
        id = GameManager::get()->m_playerFrame.value();
        log::info("{}\n", id);
        if (id > 485)
        {
            std::string frame1 = fmt::format("player_{:02}_001.png"_spr, id);
            std::string frame2 = fmt::format("player_{:02}_2_001.png"_spr, id);
            std::string frameExtra = fmt::format("player_{:02}_extra_001.png"_spr, id);
            std::string frameGlow = fmt::format("player_{:02}_glow_001.png"_spr, id);

            auto frameCache = CCSpriteFrameCache::get();

            if (auto layer1 = frameCache->spriteFrameByName(frame1.c_str()))
            {
                m_iconSprite->setDisplayFrame(layer1);
            }

            if (auto layer2 = frameCache->spriteFrameByName(frame2.c_str()))
            {
                m_iconSpriteSecondary->setDisplayFrame(layer2);
                m_iconSpriteSecondary->setPosition(m_iconSprite->getContentSize() / 2);
                m_iconSpriteSecondary->setAnchorPoint({ .5f, .5f });
            }

            if (auto layerExtra = frameCache->spriteFrameByName(frameExtra.c_str()))
            {
                m_iconSpriteWhitener->setVisible(true);
                m_iconSpriteWhitener->setAnchorPoint({ .5f, .5f });
                m_iconSpriteWhitener->setDisplayFrame(layerExtra);
                m_iconSpriteWhitener->setPosition(m_iconSprite->getContentSize() / 2);
            }

            if (auto glowLayer = frameCache->spriteFrameByName(frameGlow.c_str()))
            {
                m_iconGlow->setDisplayFrame(glowLayer);
                //m_iconGlow->setAnchorPoint({ .5f, .5f });
                //m_iconGlow->setPosition(m_iconSprite->getContentSize() / 2);
            }
        }
    }
};