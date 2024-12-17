#pragma once
using namespace geode::prelude;

class FanmadeGamesLayer : public GJDropDownLayer
{
private:
    cocos2d::CCArray *m_games;

    void onNexitron(CCObject *);
    void onTimeReborn(CCObject *);
    void onMegaWorld(CCObject *);
    void onUnnamed(CCObject *);
    void onLight(CCObject *);
    void onAdventure(CCObject *);
public:
    static FanmadeGamesLayer *create();
    void customSetup() override;
};