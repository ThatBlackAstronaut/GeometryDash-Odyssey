#include <Geode/Geode.hpp>
#include <Geode/modify/SimplePlayer.hpp>

using namespace geode::prelude;

class $modify(CustomSimplePlayer, SimplePlayer)
{
    void updatePlayerFrame(int iconID, IconType type)
    {
        SimplePlayer::updatePlayerFrame(iconID, type);

        std::string iconString;

        if (type == IconType::Cube && iconID > 485)
        {
            iconString = "player";
        }
        else if (type == IconType::Ship && iconID > 169)
        {
            iconString = "ship";
        }
        else if (type == IconType::Ball && iconID > 118)
        {
            iconString = "player_ball";
        }
        else if (type == IconType::Wave && iconID > 96)
        {
            iconString = "dart";
        }
        else return;

        std::string frame1 = fmt::format("{}_{:02}_001.png"_spr, iconString, iconID);
        std::string frame2 = fmt::format("{}_{:02}_2_001.png"_spr, iconString, iconID);
        std::string frameExtra = fmt::format("{}_{:02}_extra_001.png"_spr, iconString, iconID);
        std::string frameGlow = fmt::format("{}_{:02}_glow_001.png"_spr, iconString, iconID);


        auto frameCache = CCSpriteFrameCache::get();

        if (auto layer1 = frameCache->spriteFrameByName(frame1.c_str()))
        {
            m_firstLayer->setDisplayFrame(layer1);
        }

        if (auto layer2 = frameCache->spriteFrameByName(frame2.c_str()))
        {
            m_secondLayer->setDisplayFrame(layer2);
            m_secondLayer->setPosition(m_firstLayer->getContentSize() / 2);
        }

        if (auto layerExtra = frameCache->spriteFrameByName(frameExtra.c_str()))
        {
            m_detailSprite->setVisible(true);
            m_detailSprite->setDisplayFrame(layerExtra);
            m_detailSprite->setPosition(m_firstLayer->getContentSize() / 2);
        }

        if (auto glowLayer = frameCache->spriteFrameByName(frameGlow.c_str()))
        {
            m_outlineSprite->setDisplayFrame(glowLayer);
            m_outlineSprite->setPosition(m_firstLayer->getContentSize() / 2);
        }
    }
};