#pragma once

#include "cocos2d.h"
#include "Player.h"

class Zombie
{
public:
    Zombie(cocos2d::Scene& scene, int id, Player& player, cocos2d::Vec2& position);

    void update(float delta, cocos2d::Vec2& targetPos);

    void setSprite(std::string path);

    cocos2d::Scene& scene;
    Player& player;
    cocos2d::Sprite* sprite = nullptr;

    int id = 0;
    cocos2d::Vec2 position;
    bool isFalling = true;
};
