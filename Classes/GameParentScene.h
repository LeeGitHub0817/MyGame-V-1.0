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


/*����Ϊ��Ϸ�����ĸ���*/

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

	void update(float delta);//��scheduleUpdate��Ӧ

	void addMonster();//��ӹ���

	void moveBackground(float delta);//�����ƶ�

	void pauseBackMenu(cocos2d::Ref *pSender);//��ͣ��ť���ݴ���

	void pauseMenuJump(cocos2d::Ref *pSender);//��ͣ��ť�ڰ�ť��תʵ�ֵ�����

	void levelFinished();//Ӯ�ùؿ���������������

	void levelFinishedJump(cocos2d::Ref *pSender);//�����ذ�ť������������

};

#endif // __HELLOWORLD_SCENE_H__
