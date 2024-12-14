#pragma once
using namespace geode::prelude;

class OdysseyPopup : public geode::Popup<std::string const &, std::string const &>
{
protected:
    bool setup(std::string const &, std::string const &) override;
    bool m_translationWarning = false;
    bool m_savefileWarning = false;

public:
    static OdysseyPopup *create(std::string, std::string);
    void setWarning(bool, bool);

    void onClose(CCObject *) override;
};