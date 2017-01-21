#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "cocos2d.h"

enum PaddleState
{
	paddleStateGrabbed,
	paddleStateUngrabbed
};

class Paddle : public cocos2d::Sprite
{
private:
	PaddleState _state = paddleStateUngrabbed;

public:
	static Paddle *createWithSpriteFrameName(const char *spriteFrameName);

	bool onTouchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	//检测触摸点是否在板子上
	bool containsTouchLoction(cocos2d::Touch *touch);

	//获取板子大小
	cocos2d::Rect getRect();

	virtual void onEnter();
};

#endif // !__PADDLE_H__

