#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
#include "ReadyScene.h"
#include "SystemHeader.h"
#include "SimpleAudioEngine.h"

class AboutScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutScene);

	void menuBackCallback(Ref* pSender);
	void moveBackground(float);//±³¾°ÒÆ¶¯
	void onEnterTransitionDidFinish();
};

#endif // __ABOUT_SCENE_H__
