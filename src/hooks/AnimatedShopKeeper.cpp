#include <Geode/Geode.hpp>
#include <Geode/modify/AnimatedShopKeeper.hpp>
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(OdysseyShopKeeper, AnimatedShopKeeper)
{
    struct Fields
    {
        CCSpritePart* m_shopKeeperJaw;
    };
    

    void startAnimating()
    {
        AnimatedShopKeeper::startAnimating();

        auto animSprite = static_cast<CCPartAnimSprite*>(getChildren()->objectAtIndex(0));

        auto children = animSprite->getChildren();

        auto body = static_cast<CCSpritePart*>(children->objectAtIndex(0));
        body->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopKeeper_torso_01_001.png"_spr)->displayFrame());

        auto mouth = static_cast<CCSpritePart*>(children->objectAtIndex(1));
        mouth->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopKeeper_mouth_01_001.png"_spr)->displayFrame());

        auto head = static_cast<CCSpritePart*>(children->objectAtIndex(3));
        head->setDisplayFrame(CCSprite::createWithSpriteFrameName("shopKeeper_head_01_001.png"_spr)->displayFrame());

        //ojo izquierdo
        static_cast<CCSpritePart*>(children->objectAtIndex(4))->setOpacity(0);

        //ojo derecho
        static_cast<CCSpritePart*>(children->objectAtIndex(5))->setOpacity(0);

        //pupila izquierda
        static_cast<CCSpritePart*>(children->objectAtIndex(6))->setOpacity(0);

        //pupila derecha
        static_cast<CCSpritePart*>(children->objectAtIndex(7))->setOpacity(0);
       

        auto hand = CCSprite::createWithSpriteFrameName("shopKeeper_hand_01_001.png"_spr)->displayFrame(); 
        
        //mano izquierda
        static_cast<CCSpritePart*>(children->objectAtIndex(9))->setDisplayFrame(hand);

        //mano derecha
        static_cast<CCSpritePart*>(children->objectAtIndex(10))->setDisplayFrame(hand);
    }

};