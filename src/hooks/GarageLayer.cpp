#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include "../utils/Utils.hpp"

class $modify(GDOGarageLayer, GJGarageLayer)
{
    bool init()
    {
        if (!GJGarageLayer::init())
            return false;

        auto gm = GameManager::get();

        log::info("{}\n", m_iconID);

        m_playerObject->updatePlayerFrame(Odyssey::currentVehicleID(), gm->m_playerIconType);

        auto menu = getChildByID("shards-menu");

        if (auto shards = menu->getChildByID("shards-button"))
            shards->setVisible(false);

        if (auto shopButton = getChildByID("top-left-menu")->getChildByID("shop-button"))
            shopButton->setVisible(false);


        return true;
    }

};