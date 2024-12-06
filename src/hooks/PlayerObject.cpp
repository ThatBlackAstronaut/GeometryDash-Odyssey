#include <Geode/Geode.hpp>
#include <Geode/modify/PlayerObject.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyPlayerObject, PlayerObject)
{
    struct Fields {
        int cubeID = 1;
        int shipID = 1;
    };
    bool init(int p0, int p1, GJBaseGameLayer* p2, cocos2d::CCLayer* p3, bool p4)
    {
        if (!PlayerObject::init(p0, p1, p2, p3, p4)) return false;

        //log::info("{} {}\n", p0, p1);

        m_fields->cubeID = p0;

        Odyssey::updateIcon(this, p0, IconType::Cube, true);
        //Odyssey::updateIcon(this, GameManager::sharedState()->m_playerShip.value(), IconType::Ship, true);
    
        return true;
    }
    void updatePlayerFrame(int id)
    {
        PlayerObject::updatePlayerFrame(id);

        Odyssey::updateIcon(this, m_fields->cubeID, IconType::Cube, true);
    }

    void updatePlayerRollFrame(int id)
    {
        PlayerObject::updatePlayerRollFrame(id);

        Odyssey::updateIcon(this, id, IconType::Ball, true);
    }

    void updatePlayerSwingFrame(int id)
    {
        PlayerObject::updatePlayerSwingFrame(id);

        Odyssey::updateIcon(this, id, IconType::Swing, true);
    }

    void updatePlayerShipFrame(int id)
    {
        PlayerObject::updatePlayerShipFrame(id);

        Odyssey::updateIcon(this, m_fields->cubeID, IconType::Cube, true);
        m_fields->shipID = id;
        Odyssey::updateIcon(this, id, IconType::Ship, true);
    }

    void updatePlayerDartFrame(int id)
    {
        PlayerObject::updatePlayerDartFrame(id);
        
        Odyssey::updateIcon(this, id, IconType::Wave, true);
    }

    void resetPlayerIcon()
    {
        PlayerObject::resetPlayerIcon();

        Odyssey::updateIcon(this, m_fields->cubeID, IconType::Cube, true);
        Odyssey::updateIcon(this, m_fields->shipID, IconType::Ship, true);

    }

    void updatePlayerJetpackFrame(int id)
    {
        PlayerObject::updatePlayerJetpackFrame(id);
        
        Odyssey::updateIcon(this, id, IconType::Jetpack, true);
        Odyssey::updateIcon(this, m_fields->cubeID, IconType::Cube, true);
    }


};