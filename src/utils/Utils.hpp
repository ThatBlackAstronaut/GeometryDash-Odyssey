#pragma once

using namespace geode::prelude;

namespace Odyssey {
    DialogLayer * createDialog(const char* event);
    DialogLayer * createDialogResponse(const char * event, int times);

    void addCorners(CCLayer *, const char * , float);

    CCNode * createDifficultyNode(GJDifficulty, int);
    CCNode * createProgressBar(int, bool);

    int currentVehicleID();
    void insertAssetsToMap(bool, std::vector<int>);
    bool isCustomIcon(int, IconType);
};