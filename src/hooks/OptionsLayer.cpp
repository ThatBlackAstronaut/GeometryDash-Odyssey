#include <Geode/Geode.hpp>
#include <Geode/modify/OptionsLayer.hpp>
#include <Geode/modify/MoreOptionsLayer.hpp>

using namespace geode::prelude;

class $modify(GDO_OptionsLayer, OptionsLayer)
{
	virtual void customSetup()
	{
		OptionsLayer::customSetup();

		if (auto button = this->getChildByIDRecursive("vault-button"))
		{
			button->setVisible(false);
		}
	}

	void onAccount(CCObject *)
	{
		auto spanish = GameManager::sharedState()->getGameVariable("0201");
		auto info = spanish ? "Para evitar riesgos de sobrescribir tus datos por accidente, esta <cr>funcion esta desactivada</c>. Tus datos actuales se restauraran cuando desactives el mod." : "To avoid risks of accidentally overwriting your data, this <cr>feature is disabled</c>. Your actual data will be restored when you disable the mod.";

		auto alert = FLAlertLayer::create("Disabled", info, "OK");
		alert->show();
	}
};

class $modify(GDO_MoreOptionsLayer, MoreOptionsLayer)
{
	bool init()
	{
		if (!MoreOptionsLayer::init())
			return false;

		GameManager::sharedState()->setGameVariable("0201", Mod::get()->getSettingValue<bool>("spanish-language"));
		GameManager::sharedState()->setGameVariable("0202", Mod::get()->getSettingValue<bool>("hide-upcoming"));

		//	Aun en fase de prueba
		MoreOptionsLayer::addToggle("Spanish", "0201", "<cy>ENG</c>: Translates most of the mod's dialogue in Spanish. Due to character limitations, there will be spelling errors.\n\n<cy>ESP</c>: Traduce mayor parte del dialogo del mod en Espanol. Dado a las limitaciones de caracteres en el juego, habran errores ortograficos (como la falta de acentos)");
		//	MoreOptionsLayer::addToggle("Hide upcoming", "0202", "<cy>ENG</c>: Hides icons that are tagged as upcoming (thus impossible to get for now).\n\n<cy>SPA</c>: Oculta los iconos etiquetados como proximos (por tanto, imposibles de conseguir por ahora).");

		return true;
	}

	void goToPage(int p0)
	{
		MoreOptionsLayer::goToPage(p0);

		if (MoreOptionsLayer::m_page == 7)
			MoreOptionsLayer::m_categoryLabel->setString("GD Odyssey Options");
	}

	void onToggle(CCObject *sender)
	{
		MoreOptionsLayer::onToggle(sender);

		auto tag = sender->getTag();
		log::debug("TAG: {}", tag);

		if (sender->getTag() == 201)
			Mod::get()->setSettingValue<bool>("spanish-language", GameManager::sharedState()->getGameVariable("0201"));

		if (sender->getTag() == 202)
			Mod::get()->setSettingValue<bool>("hide-upcoming", GameManager::sharedState()->getGameVariable("0202"));
	}
};