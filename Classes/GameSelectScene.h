#ifndef __GAME_SELECT_SCENE_H__
#define __GAME_SELECT_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"

#include "GameScrollScene.h"

/*此类用来调用GameScrollScene*/

class GameSelectScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::Scene *createScene();
	CREATE_FUNC(GameSelectScene);

	void onEnterTransitionDidFinish();
};

#endif // !__GAME_SELECT_SCENE_H__

