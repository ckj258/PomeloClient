#include "ChatScene.h"
#include "ChatDialog.hpp"
USING_NS_CC;


Scene* ChatScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = ChatScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ChatScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto size = Director::getInstance()->getVisibleSize();
	auto chat = ChatDialog::create();
	chat->setPosition(Point::ZERO);
	addChild(chat);
	

    return true;
}

