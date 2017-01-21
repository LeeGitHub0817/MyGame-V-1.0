#ifndef __GAME_SCENE_LEVEL1_H__
#define __GAME_SCENE_LEVEL1_H__

#include "cocos2d.h"
#include "SystemHeader.h"

#include "GameParentScene.h"

/*此类实现关卡2*/

class GameLevel2 : public GameParentScene
{
public:
	static cocos2d::Scene *createScene();
	virtual bool init();
	CREATE_FUNC(GameLevel2);

	void onEnterTransitionDidFinish();
};

#endif // !__GAME_SCENE_LEVEL2_H__

