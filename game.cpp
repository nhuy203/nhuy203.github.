bool HelloWorld::init()
{

    ...

    // Add label "PLAY" with callback HelloWorld::play
    auto play = MenuItemLabel::create(Label::createWithTTF("PLAY", "fonts/Marker Felt.ttf", 40),
                                      CC_CALLBACK_1(HelloWorld::play, this));
    // Assert that play is not null
    CCASSERT(play != nullptr, "problem loading fonts/Marker Felt.ttf");

    // Position PLAY in the middle of screen
    play->setPosition((Vec2(visibleSize) - origin) / 2);

    // Add PLAY to menu
    menu->addChild(play);
    return true;
}

void HelloWorld::play(Ref *pSender) {
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(
        TransitionFade::create(0.5, gameScene, Color3B(0, 255, 255)));
}

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public Scene
{
public:

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);
};

