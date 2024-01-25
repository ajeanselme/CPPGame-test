#include "Bullet.h"

Bullet::Bullet(cocos2d::Sprite* sprite, const cocos2d::Vec2& position, const cocos2d::Vec2& direction):
    position(position), origin(position), sprite(sprite), direction(direction.getNormalized())
{
    if(sprite == nullptr)
    {
        cocos2d::log("Couldn't load bullet sprite");
        return;
    }

    sprite->setPosition(position);

    auto hitbox = cocos2d::PhysicsBody::createCircle(10, cocos2d::PhysicsMaterial(0,0,0));
    hitbox->setDynamic(false);
    hitbox->setContactTestBitmask(0xFFFFFFFF);
    hitbox->setTag(1);

    sprite->setPhysicsBody(hitbox);
}

void Bullet::update(float delta)
{
    position += direction * 80 * delta;
    sprite->setPosition(position);
}
