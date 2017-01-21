#include "LevelSceneTwo.h"

USING_NS_CC;

Scene *GameLevel2::createScene()
{
	auto scene = Scene::createWithPhysics();

	//重力设置为0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//开启遮罩，这个开启会在创建的物体上描边
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameLevel2::create();

	scene->addChild(layer);

	return scene;
}

bool GameLevel2::init()
{
	if (GameParentScene::init() == NULL)
	{
		return false;
	}
	

	return true;
}

void GameLevel2::onEnterTransitionDidFinish()
{
	GameParentScene::onEnterTransitionDidFinish();
}
