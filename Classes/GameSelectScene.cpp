#include "GameSelectScene.h"

USING_NS_CC;

cocos2d::Scene * GameSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameSelectScene::create();
	scene->addChild(layer);
	return scene;
}

void GameSelectScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	GameScrollScene *scroll = GameScrollScene::create();
	this->addChild(scroll);
}


bool GameSelectScene::init()
{
	if (Layer::init() == NULL)
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("texture/gamelevel_select_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	return true;
}

