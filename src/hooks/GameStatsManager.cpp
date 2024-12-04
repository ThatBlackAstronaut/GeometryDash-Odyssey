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
        auto achievementID = fmt::format("geometry.ach.odyssey.levelcoin{:02}", level->m_levelID.value());

        log::info("coinPercent: {}, achID: {}", coinPercent, achievementID);

        if (level->m_levelType == GJLevelType::Local)
        {
            GM->reportAchievementWithID(achievementID.c_str(), coinPercent, false);
        }
    }

    int getItemUnlockState(int p0, UnlockType p1)
    {
        
        if (!Odyssey::isCustomIcon(p0, GameManager::sharedState()->unlockTypeToIconType(static_cast<int>(p1))))
            return 4;

        if (!AchievementManager::sharedState()->achievementForUnlock(p0, p1).empty())
            return 1;
            
        return 5;
    }
};