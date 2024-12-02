#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementManager.hpp>

class $modify(OdysseyAchievementManager, AchievementManager)
{
    void addManualAchievements(){
        AchievementManager::addAchievement(
            "geometry.ach.level01a",
            "All hands on deck!",
            "Completed \"The Dangerous Seas\" in practice mode.",
            "Complete \"The Dangerous Seas\" in practice mode.",
            "icon_487",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level01b",
            "The Dangerous Seas!",
            "Completed \"The Dangerous Seas\" in normal mode.",
            "Complete \"The Dangerous Seas\" in normal mode.",
            "icon_486",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level02a",
            "Spooky butts...",
            "Completed \"Ghost House\" in practice mode.",
            "Complete \"Ghost House\" in practice mode.",
            "icon_488",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level02b",
            "Ghost house!",
            "Completed \"Ghost House\" in normal mode.",
            "Complete \"Ghost House\" in normal mode.",
            "icon_489",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level03a",
            "Under powered",
            "Completed \"Super Ultra\" in practice mode.",
            "Complete \"Super Ultra\" in practice mode.",
            "icon_490",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level03b",
            "Super Ultra!",
            "Completed \"Super Ultra\" in normal mode.",
            "Complete \"Super Ultra\" in normal mode.",
            "ball_119",
            1
        );
    }
};