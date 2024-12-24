#include <Geode/Geode.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

class $modify(GDO_GameLevelManager, GameLevelManager){
    public:
        $override
        GJGameLevel * getMainLevel(int levelID, bool loaded){
            auto level = GameLevelManager::getMainLevel(levelID, loaded);

            switch(levelID){
                default:
                    level->m_creatorName = "SwitchstepGDYT";
                    level->m_accountID = 10158911;
                    break;
            }

            return level;
        }
};