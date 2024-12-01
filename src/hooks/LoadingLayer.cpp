#include <Geode/Geode.hpp>
#include <Geode/modify/LoadingLayer.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyLoadingLayer, LoadingLayer)
{
    bool init(bool reload)
    {
        if (!LoadingLayer::init(reload))
            return false;

        auto SFC = CCSpriteFrameCache::get();
        auto searchPathRoot = dirs::getModRuntimeDir() / Mod::get()->getID() / "resources";
        CCFileUtils::sharedFileUtils()->addSearchPath(searchPathRoot.string().c_str()); 
        SFC->addSpriteFramesWithFile("GJO_GameSheet01.plist"_spr);

        auto mainTitle = static_cast<CCSprite *>(this->getChildByID("gd-logo"));
        if (mainTitle)
        {
            auto odysseyTitle = CCSprite::createWithSpriteFrameName("GDO_MainLogo_001.png"_spr);
            mainTitle->setDisplayFrame(odysseyTitle->displayFrame());
        }

        auto robtopLogo = static_cast<CCSprite *>(this->getChildByID("robtop-logo"));
        if (robtopLogo)
        {
            auto teamLogo = CCSprite::createWithSpriteFrameName("GDO_TeamLogo_001.png"_spr);
            robtopLogo->setDisplayFrame(teamLogo->displayFrame());
        };

        return true;
    }
};