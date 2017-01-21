#ifndef __READY_SCENE_H__
#define __READY_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

#include "AboutScene.h"
#include "GameSelectScene.h"

class BallTest;//前向声明
class ReadyScene : public cocos2d::Layer
{
private:
	//设置牌中的相关按钮等
	cocos2d::Menu *menu;
	cocos2d::Sprite *boardSprite;
	cocos2d::Menu *toggleMenu;

public:
	cocos2d::Vec2 _ballStartingVelocity;
	BallTest* _ball;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ReadyScene);

	void onEnter();

	void menuItemCallback(cocos2d::Ref* pSender); //开始游戏
	void closeItem(cocos2d::Ref* pSender);//关闭按钮,无法写在menuCloseCallback中，不然scene没初始化，执行会出错
	
	void doStep(float delta);//执行小球运动

	void optionCallback(cocos2d::Ref *pSender);//设置按钮调用函数
	void onEnterTransitionDidFinish();

	void menuResumeCallback(cocos2d::Ref *pSender);
	void menuSoundToggleCallback(cocos2d::Ref *pSender);
	void menuMusicToggleCallback(cocos2d::Ref *pSender);

};

class BallTest : public cocos2d::Sprite
{
private:
	cocos2d::Vec2 _velocity;
public:
	BallTest(void);
	virtual ~BallTest(void);
	float radius();
	void move(float delta);
	static BallTest* ballWithTexture(cocos2d::Texture2D* aTexture);
public:
	void setVelocity(cocos2d::Vec2 velocity) { _velocity = velocity; }
	cocos2d::Vec2 getVelocity() { return _velocity; }
};

#endif // __READY_SCENE_H__