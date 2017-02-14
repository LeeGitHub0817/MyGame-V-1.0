#include "LevelSceneTwo.h"

USING_NS_CC;

Scene *GameLevel2::createScene()
{
	auto scene = Scene::createWithPhysics();

	//��������Ϊ0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//�������֣�����������ڴ��������������
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameLevel2::create();

	scene->addChild(layer);

	return scene;
}

bool GameLevel2::init()
{
	if (Layer::init() == NULL)
	{
		return false;
	}


	return true;
}

void GameLevel2::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void GameLevel2::onExit()
{
	Layer::onExit();
}

void GameLevel2::onEnter()
{
	Layer::onEnter();
}
