#include <Geode/Geode.hpp>
#include <Geode/modify/ProfilePage.hpp>

using namespace geode::prelude;

class $modify(GDOProfilePage, ProfilePage)
{
    void loadPageFromUserInfo(GJUserScore* p0)
    {
        ProfilePage::loadPageFromUserInfo(p0);

        if (auto myLevelsHint = m_mainLayer->getChildByID("my-levels-hint"))
        {
            myLevelsHint->setVisible(false);
        }

        
        if (auto myListsHint = m_mainLayer->getChildByID("my-lists-hint"))
        {
            myListsHint->setVisible(false);
        }

        if (auto menu = m_mainLayer->getChildByID("main-menu"))
        {
            if (auto levelsButton = menu->getChildByID("my-levels-button")) levelsButton->setVisible(false);
            if (auto listsButton = menu->getChildByID("my-lists-button")) listsButton->setVisible(false);
        }
    }
};