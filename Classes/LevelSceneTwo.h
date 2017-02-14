#ifndef __LEVEL_SCENE_TWO_H__
#define __LEVEL_SCENE_TWO_H__

#include "cocos2d.h"
#include "SystemHeader.h"

/*����ʵ�ֹؿ�2*/

class GameLevel2 : public cocos2d::Layer
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameLevel2);

	void onEnterTransitionDidFinish();
	void onExit();
	void onEnter();
};

#endif // !__LEVEL_SCENE_TWO_H__

