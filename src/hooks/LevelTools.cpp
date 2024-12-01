#include <Geode/Geode.hpp>
#include <Geode/modify/LevelTools.hpp>

using namespace geode::prelude;

class $modify(OdysseyLevelTools, LevelTools)
{
	static gd::string getAudioTitle(int levelID)
	{
		switch (levelID)
		{
		case 100:
			return "The Dangereous Seas";
		case 101:
			return "Ghost House";
		case 102:
			return "Super Ultra";
		case 103:
			return "Cryptofunk";
		default:
			return LevelTools::getAudioTitle(levelID);
		}
	}

	static GJGameLevel *getLevel(int levelID, bool loaded)
	{
		auto level = GJGameLevel::create();

		level->m_levelName = getAudioTitle(99 + levelID);
		level->m_audioTrack = 99 + levelID;
		level->m_coins = 3;


		switch (levelID)
		{
		case 1:
			level->m_stars = 5;
			level->m_difficulty = GJDifficulty::Hard;
			break;
		case 2:
			level->m_stars = 7;
			level->m_difficulty = GJDifficulty::Harder;
			break;
		case 3:
			level->m_stars = 8;
			level->m_difficulty = GJDifficulty::Insane;
			break;
		case 4:
			level->m_stars = 9;
			level->m_difficulty = GJDifficulty::Insane;
			break;
		}

		level->m_levelID = levelID;
		level->m_levelType = GJLevelType::Local;

		return level;
	}

	static bool verifyLevelIntegrity(std::string verifyString, int levelID)
	{
		return true;
	}
};