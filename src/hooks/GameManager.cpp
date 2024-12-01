#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

class $modify(OdysseyGameManager, GameManager)
{
    int countForType(IconType icon)
    {
        if (icon == IconType::Cube)
            return 490;
        if (icon == IconType::Ball)
            return 119;

        return GameManager::countForType(icon);
    }
};