#ifndef __READY_SCENE_H__
#define __READY_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "VisibleRect.h"
#include "SimpleAudioEngine.h"

#include "AboutScene.h"
#include "GameSelectScene.h"

class BallTest;//ǰ������
class ReadyScene : public cocos2d::Layer
{
private:
	//�������е���ذ�ť��
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

	void menuItemCallback(cocos2d::Ref* pSender); //��ʼ��Ϸ
	void closeItem(cocos2d::Ref* pSender);//�رհ�ť,�޷�д��menuCloseCallback�У���Ȼsceneû��ʼ����ִ�л����
	
	void doStep(float delta);//ִ��С���˶�

	void optionCallback(cocos2d::Ref *pSender);//���ð�ť���ú���
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