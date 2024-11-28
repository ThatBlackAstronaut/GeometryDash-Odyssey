#include <Geode/Geode.hpp>
#include <Geode/modify/CCSprite.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>

using namespace geode::prelude;

class $modify(CCSprite)
{
	static CCSprite *create(const char *pszFileName)
	{	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_019.png"))
		{
			return CCSprite::create("GDO_DialogIcon_005.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_020.png"))
		{
			return CCSprite::create("GDO_DialogIcon_006.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_021.png"))
		{
			return CCSprite::create("GDO_DialogIcon_007.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_022.png"))
		{
			return CCSprite::create("GDO_DialogIcon_008.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_023.png"))
		{
			return CCSprite::create("GDO_DialogIcon_009.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_024.png"))
		{
			return CCSprite::create("GDO_DialogIcon_010.png"_spr);
		}
	
		if (std::string_view(pszFileName) == std::string_view("dialogIcon_025.png"))
		{
			return CCSprite::create("GDO_DialogIcon_011.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_053.png"))
		{
			return CCSprite::create("GDO_DialogIcon_001.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_054.png"))
		{
			return CCSprite::create("GDO_DialogIcon_002.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_055.png"))
		{
			return CCSprite::create("GDO_DialogIcon_003.png"_spr);
		}

		if (std::string_view(pszFileName) == std::string_view("dialogIcon_056.png"))
		{
			return CCSprite::create("GDO_DialogIcon_004.png"_spr);
		}

		return CCSprite::create(pszFileName);
	}
};

class $modify(GDOMoreOptionsLayer, MoreOptionsLayer)
{
	bool init()
	{
		if (!MoreOptionsLayer::init())
			return false;

		//	Aun en fase de prueba
		MoreOptionsLayer::addToggle("Pizza", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Burger", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Hot Dog", "Pasta", "Ravioli");
		MoreOptionsLayer::addToggle("Soup", "Pasta", "Ravioli");

		return true;
	}

	void goToPage(int p0)
	{
		MoreOptionsLayer::goToPage(p0);

		if (MoreOptionsLayer::m_page == 7)
		{
			MoreOptionsLayer::m_categoryLabel->setString("GD Odyssey Options");
		}
	}
};