#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>

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
};