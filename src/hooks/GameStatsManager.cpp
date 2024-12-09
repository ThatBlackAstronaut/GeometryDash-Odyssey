#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyGameStatsManager, GameStatsManager)
{
    void checkCoinAchievement(GJGameLevel *level)
    {
        auto GM = GameManager::sharedState();
        int coinPercent = (getCollectedCoinsForLevel(level) / 3.f) * 100.f;

        auto achievementID = fmt::format("geometry.ach.level{:02}c", level->m_levelID.value());
        log::info("coinPercent: {}, achID: {}", coinPercent, achievementID);

        if (level->m_levelType == GJLevelType::Local)
        {
            GM->reportAchievementWithID(achievementID.c_str(), coinPercent, false);
        }
    }

    bool isItemUnlocked(UnlockType type, int ID)
    {
        //  Practice Music Unlocker
        if (type == UnlockType::GJItem && ID == 17)
            return true;

        return GameStatsManager::isItemUnlocked(type, ID);
    }

    int getItemUnlockState(int p0, UnlockType p1)
    {
        //  El icono no es custom
        if (!Odyssey::isIconCustom(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 4;

        //  No tiene achievement
        if (!AchievementManager::sharedState()->achievementForUnlock(p0, p1).empty())
            return 1;

        //  Icono aun no ha salido
        if (Odyssey::isIconUpcoming(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 6;

        //  Icono de tienda
        return 5;
    }

    void createStoreItems()
    {
        auto newShop = static_cast<ShopType>(6);
        if (!m_allStoreItems)
        {
            m_allStoreItems = CCDictionary::create();
            m_allStoreItems->retain();

            m_storeItems = CCDictionary::create();
            m_storeItems->retain();

            m_storeItemArray = CCArray::create();
            m_storeItemArray->retain();

            //  REFERENCIA
            //  - Indice en la tienda
            //  - ID
            //  - UnlockType
            //  - Precio
            //  - Tienda

            addStoreItem(0, 495, 1, 100, newShop);
            addStoreItem(1, 496, 1, 100, newShop);
            addStoreItem(2, 497, 1, 100, newShop);
            addStoreItem(3, 498, 1, 100, newShop);
            addStoreItem(4, 1, 12, 250, newShop);
            addStoreItem(5, 2, 12, 250, newShop);
            addStoreItem(6, 3, 12, 1, newShop);
            addStoreItem(7, 5, 12, 1, newShop);
            addStoreItem(8, 45, 13, 100, newShop);
            addStoreItem(9, 499, 1, 100, newShop);
            addStoreItem(10, 500, 1, 100, newShop);
            addStoreItem(11, 501, 1, 100, newShop);
            addStoreItem(11, 501, 1, 100, newShop);
        }
    }
};