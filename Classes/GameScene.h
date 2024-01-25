#pragma once

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include <unordered_set>

#include "cocos2d.h"
#include "Player.h"
#include "Zombie.h"

class GameScene : public cocos2d::Scene
{
public:
    static Scene* createScene();
    bool init() override;
    void update(float delta) override;

private:
    const cocos2d::Size& resolution_ = cocos2d::Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

    Player* player;

    void keyboardInputCallback(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void keyboardInputReleaseCallback(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void mouseDownCallback(cocos2d::Event* event);
    bool contactCallback(cocos2d::PhysicsContact& contact);

    void spawnZombie();

    std::vector<std::unique_ptr<Zombie>> zombies;
    int entityId = 0;
    float spawnTimer = 0;


public:
    CREATE_FUNC(GameScene)

};


#endif