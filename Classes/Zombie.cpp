#include "Zombie.h"

Zombie::Zombie(cocos2d::Scene& scene, int id, Player& player, cocos2d::Vec2& position): scene(scene), player(player), id(id), position(position)
{
    setSprite("assets/zombie_falling.png");
}

void Zombie::update(float delta, cocos2d::Vec2& targetPos)
{
    if(targetPos.y < position.y)
    {
        position += cocos2d::Vec2(0, -1) * 80 * delta;
    } else
    {
        if(isFalling)
        {
            setSprite("assets/zombie.png");
            isFalling = false;
        }
        cocos2d::Vec2 direction = cocos2d::Vec2(targetPos.x - position.x, targetPos.y - position.y).getNormalized();
        position += direction * 20 * delta;
    }

    sprite->setPosition(position);
}

void Zombie::setSprite(std::string path)
{
    if(sprite != nullptr)
    {
        sprite->removeFromParentAndCleanup(true);
    }

    sprite = cocos2d::Sprite::create(path);
    if(sprite == nullptr)
    {
        cocos2d::log("Couldn't load sprite");
        return;
    }
    sprite->setName(cocos2d::StringUtils::toString(id));
    sprite->setPosition(position);
    scene.addChild(sprite);

    auto hitbox = cocos2d::PhysicsBody::createBox(cocos2d::Size(10.f, 20.f), cocos2d::PhysicsMaterial(0,0,0));
    hitbox->setDynamic(false);
    hitbox->setContactTestBitmask(0xFFFFFFFF);
    hitbox->setTag(2);
    sprite->setPhysicsBody(hitbox);
}
