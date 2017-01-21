#ifndef __GAME_LEVEL_SCENE_H__
#define __GAME_LEVEL_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <math.h>

#include "ReadyScene.h"
#include "GameParentScene.h"

/*此类用来实现关卡滑动选择效果，并在GameSelectScene中调用*/

class GameScrollScene : public cocos2d::Layer
{
private:
	cocos2d::extension::ScrollView *m_scrollView;

	//触摸点位置
	cocos2d::Vec2 m_touchPoint;

	//ScrollView的偏移量
	cocos2d::Vec2 m_offsetPoint;

	//当前为第几关
	int m_nCurPage;

	/*cocos2d::Vector<int> tagNum;*/
public:
	virtual bool init();
	CREATE_FUNC(GameScrollScene);

	//触摸事件的相关函数
	bool touchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	//校验关卡位置，使其位于屏幕中央
	void checkScrollView(float offset);

	//跳转到游戏的回调函数
	void menuStartCallback(cocos2d::Ref *pSender);

	void menuBackCallback(cocos2d::Ref *pSender);
};

#endif // !__GAME_LEVEL_SCENE_H__

