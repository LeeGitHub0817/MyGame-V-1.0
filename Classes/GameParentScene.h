#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define GameSceneBall 200
#define GameSceneMonster 201
#define GameScenePaddle 202

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SystemHeader.h"

#include "Ball.h"
#include "Paddle.h"
#include "Monster.h"
#include "GameOverScene.h"
#include "ReadyScene.h"


/*此类为游戏场景的父类*/

class GameParentScene : public cocos2d::Layer
{
	Ball *ball;
	Paddle *paddle;
	Monster *monster;
	cocos2d::EventListenerPhysicsContact *contactListener;
	int score;
	cocos2d::Menu *menu;
	int monsterNum = 0;

public:
	static cocos2d::Scene *createScene();
    virtual bool init();    
	CREATE_FUNC(GameParentScene);

	virtual void onEnter();
	void onExit();
	virtual void onEnterTransitionDidFinish();

	void update(float delta);//与scheduleUpdate对应

	void addMonster();//添加怪物

	void moveBackground(float delta);//背景移动

	void pauseBackMenu(cocos2d::Ref *pSender);//暂停按钮内容创建

	void pauseMenuJump(cocos2d::Ref *pSender);//暂停按钮内按钮跳转实现的内容

	void levelFinished();//赢得关卡结束跳出的内容

	void levelFinishedJump(cocos2d::Ref *pSender);//点击相关按钮后做出的内容

};

#endif // __HELLOWORLD_SCENE_H__
