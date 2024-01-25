#include "GameScene.h"

#include "Zombie.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Scene* GameScene::createScene()
{
    return create();
}


bool GameScene::init()
{
    if (!initWithPhysics())
    {
        return false;
    }

    auto background = Sprite::create("assets/backgroundColorGrass.png");
    background->setPosition(Vec2(resolution_.width/2, resolution_.height/2));
    this->addChild(background, 0);

    player = new Player(
        *this,
        Sprite::create("assets/player.png"),
        Vec2(resolution_.width/2, resolution_.height/4)
        );

    this->addChild(player->sprite, 1);


    auto keybordListener = EventListenerKeyboard::create();
    keybordListener->onKeyPressed = [this](auto&& PH1, auto&& PH2)
    {
        keyboardInputCallback(PH1, PH2);
    };
    keybordListener->onKeyReleased = [this](auto&& PH1, auto&& PH2)
    {
        keyboardInputReleaseCallback(PH1, PH2);
    };

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this](auto&& PH1)
    {
        mouseDownCallback(PH1);
    };

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](auto&& PH1)-> bool
    {
        return GameScene::contactCallback(PH1);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keybordListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::update(float delta)
{
    if(player != nullptr)
        player->update(delta);


    for (std::vector<std::unique_ptr<Zombie>>::iterator it = zombies.begin(); it != zombies.end();)
    {
        it->get()->update(delta, player->position);
        ++it;
    }

    spawnTimer += delta;
    if(spawnTimer > 5)
    {
        spawnTimer = 0;
        spawnZombie();
    }
}

void GameScene::keyboardInputCallback(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        spawnZombie();
        return;
    }

    if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        player->move(Player::RIGHT);
    }
    else if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        player->move(Player::LEFT);
    }
}

void GameScene::keyboardInputReleaseCallback(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    player->stopMoving();
}

void GameScene::mouseDownCallback(cocos2d::Event* event)
{
    EventMouse* e = (EventMouse*)event;

    player->shoot(e->getCursorX(), e->getCursorY());
}

bool GameScene::contactCallback(cocos2d::PhysicsContact& contact)
{
    int tagA = contact.getShapeA()->getBody()->getTag();
    int tagB = contact.getShapeB()->getBody()->getTag();

    if((tagA == 1 && tagB == 2) || (tagA == 2 && tagB == 1))
    {
        if(tagA == 2)
        {
            const auto nameA = contact.getShapeA()->getBody()->getOwner()->getName();
            for (std::vector<std::unique_ptr<Zombie>>::iterator it = zombies.begin(); it != zombies.end();)
            {
                const auto name = it->get()->sprite->getName();
                if(name == nameA)
                {
                    it = zombies.erase(it);
                    removeChild(contact.getShapeA()->getBody()->getOwner());
                    continue;
                }
                ++it;
            }
        }
        else
        {
            const auto nameB = contact.getShapeB()->getBody()->getOwner()->getName();
            for (std::vector<std::unique_ptr<Zombie>>::iterator it = zombies.begin(); it != zombies.end();)
            {
                if(it->get()->sprite->getName() == nameB)
                {
                    it = zombies.erase(it);
                    removeChild(contact.getShapeB()->getBody()->getOwner());
                    continue;
                }
                ++it;
            }
        }
    }

    return false;
}

void GameScene::spawnZombie()
{
    const auto random = rand() % static_cast<int>(resolution_.width);
    Vec2 spawnLoc = Vec2(random, resolution_.height + 100);

    Zombie* zombie = new Zombie(
        *this,
        entityId,
        *player,
        spawnLoc
        );

    zombies.emplace_back(zombie);
    entityId++;
}
