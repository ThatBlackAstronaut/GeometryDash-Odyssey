#pragma once
using namespace geode::prelude;

class FanmadeGamesLayer : public GJDropDownLayer {
    private:
        cocos2d::CCArray * m_games;
        void onNexitron(CCObject *);
        void onGDPS(CCObject *);

    public:
        static FanmadeGamesLayer * create();
        void customSetup() override;
};