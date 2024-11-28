#pragma once

using namespace geode::prelude;


class OdysseySelectLayer : public cocos2d::CCLayer
{
public:
    BoomScrollLayer* m_scrollLayer;
    cocos2d::CCSprite* m_background;

public:
    bool init() { 
        if (!CCLayer::init()) return false;

        this->setKeyboardEnabled(true);
        this->setKeypadEnabled(true);

        //to do

        
        return true;
    };

    void keyBackClicked()
    {
        cocos2d::CCDirector::sharedDirector()->replaceScene(cocos2d::CCTransitionFade::create(0.5, MenuLayer::scene(false)));
    }

    CREATE_FUNC(OdysseySelectLayer);

};
