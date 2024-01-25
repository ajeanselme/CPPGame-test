#pragma once
#include "Bullet.h"
#include "2d/CCSprite.h"

class Player
{
public:
    enum move_direction
    {
        RIGHT,
        LEFT
    };

    cocos2d::Sprite* sprite;

    Player(cocos2d::Scene& scene, cocos2d::Sprite* sprite, const cocos2d::Vec2& position);

    void move(move_direction direction);
    void stopMoving();

    void shoot(float toX, float toY);

    void update(float delta);

    cocos2d::Vec2 position;

private:
    cocos2d::Scene& scene;

    bool isMoving;
    move_direction direction;
    float speed = 40.f;

    std::vector<std::unique_ptr<Bullet>> bullets;

    void updateSprite();
};
