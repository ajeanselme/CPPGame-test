#pragma once
#include "cocos2d.h"

class Bullet
{
public:
    explicit Bullet(cocos2d::Sprite* sprite, const cocos2d::Vec2& position, const cocos2d::Vec2& direction);

    void update(float delta);

    cocos2d::Vec2 position;
    cocos2d::Vec2 origin;
    cocos2d::Sprite* sprite;
    cocos2d::Vec2 direction;
};
