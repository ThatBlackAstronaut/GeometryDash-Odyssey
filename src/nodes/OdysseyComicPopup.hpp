#pragma once
using namespace geode::prelude;

class OdysseyComicPopup : public geode::Popup<>
{
protected:
    bool setup() override;
    void onComic(CCObject *);

public:
    static OdysseyComicPopup *create();
};