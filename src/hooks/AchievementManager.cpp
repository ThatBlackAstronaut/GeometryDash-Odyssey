#include <Geode/Geode.hpp>
#include <Geode/modify/AchievementManager.hpp>

class $modify(OdysseyAchievementManager, AchievementManager)
{
    void addManualAchievements(){
        AchievementManager::addAchievement(
            "geometry.ach.level01a",
            "All hands on deck!",
            "Completed \"The Dangerous Seas\" in practice mode",
            "Complete \"The Dangerous Seas\" in practice mode",
            "icon_487",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level01b",
            "The Dangerous Seas!",
            "Completed \"The Dangerous Seas\" in normal mode",
            "Complete \"The Dangerous Seas\" in normal mode",
            "icon_486",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level02a",
            "Spooky butts...",
            "Completed \"Ghost House\" in practice mode",
            "Complete \"Ghost House\" in practice mode",
            "icon_488",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level02b",
            "Ghost house!",
            "Completed \"Ghost House\" in normal mode",
            "Complete \"Ghost House\" in normal mode",
            "icon_489",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level03a",
            "Under powered",
            "Completed \"Super Ultra\" in practice mode",
            "Complete \"Super Ultra\" in practice mode",
            "icon_490",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level03b",
            "Super Ultra!",
            "Completed \"Super Ultra\" in normal mode",
            "Complete \"Super Ultra\" in normal mode",
            "ball_119",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level04a",
            "Funk you!",
            "Completed \"Criptofunk\" in practice mode",
            "Complete \"Criptofunk\" in practice mode",
            "icon_501",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level04b",
            "Criptofunk!",
            "Completed \"Criptofunk\" in normal mode",
            "Complete \"Criptofunk\" in normal mode",
            "icon_491",
            1
        );

    //Aun sin testear
        AchievementManager::addAchievement(
            "geometry.ach.level201b",
            "Burning Sands!",
            "Completed \"Burning Sands\" in normal mode",
            "Complete \"Burning Sands\" in normal mode",
            "ship_170",
            1
        );

        AchievementManager::addAchievement(
            "geometry.ach.level202b",
            "Conclusive Journey!",
            "Completed \"Conclusive Journey\" in normal mode",
            "Complete \"Conclusive Journey\" in normal mode",
            "icon_493",
            1
        );


        AchievementManager::addAchievement(
            "geometry.ach.demoncoin01",
            "Ultimate Burning Sands",
            "Collected all 3 Secret Coins on \"Burning Sands\"",
            "Collect all 3 Secret Coins on \"Burning Sands\"",
            "icon_494",
            1
        );
    }
};