#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ReadyScene.h"
#include "SimpleAudioEngine.h"

class LogoScene : public cocos2d::Layer
{
private:
	int m_loadNum;
	std::thread *_preLoadAudio;  //音频预加载线程
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LogoScene);

	void loadTexture(cocos2d::Texture2D *texture); //预加载纹理
	void loadAudio(); //预加载音乐
	void delayCall(float dt); //延迟跳转至下一个场景
	virtual void onExit(); 
};

#endif // __LOGO_SCENE_H__

