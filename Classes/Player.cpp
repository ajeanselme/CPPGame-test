#include "Player.h"

#include "2d/CCActionInterval.h"
#include "2d/CCScene.h"

Player::Player(cocos2d::Scene& scene, cocos2d::Sprite* sprite, const cocos2d::Vec2& position) : scene(scene), sprite(sprite), position(position), isMoving(false), direction()
{
    if(sprite == nullptr)
    {
        cocos2d::log("Couldn't load player sprite");
        return;
    }

    sprite->setPosition(position);
    sprite->setTag(0);
    // sprite->getPhysicsBody()->create();
    // sprite->getPhysicsBody()->setDynamic(false);
    // sprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
}

void Player::move(move_direction to)
{
    isMoving = true;
    direction = to;
}

void Player::stopMoving()
{
    isMoving = false;
}

void Player::shoot(float toX, float toY)
{
    cocos2d::log("shoot %f;%f", toX, toY);

    auto bullet = new Bullet(
        cocos2d::Sprite::create("assets/bullet.png"),
        position,
        cocos2d::Vec2(toX - position.x, toY - position.y)
        );

    scene.addChild(bullet->sprite, 0);
    bullets.emplace_back(bullet);
}

void Player::update(float delta)
{
    for (std::vector<std::unique_ptr<Bullet>>::iterator it = bullets.begin(); it != bullets.end();)
    {
        if(it->get()->position.distance(it->get()->origin) > 300)
        {
            scene.removeChild(it->get()->sprite);
            it = bullets.erase(it);
            continue;
        }

        it->get()->update(delta);
        ++it;
    }

    if(!isMoving) return;

    if(direction == RIGHT)
    {
        position.x += speed * delta;
    }
    else
    {
        position.x -= speed * delta;
    }

    updateSprite();
}

void Player::updateSprite()
{
    sprite->setPosition(position.x, position.y);
}
