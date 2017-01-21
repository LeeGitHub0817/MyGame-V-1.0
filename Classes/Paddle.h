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

	//��ⴥ�����Ƿ��ڰ�����
	bool containsTouchLoction(cocos2d::Touch *touch);

	//��ȡ���Ӵ�С
	cocos2d::Rect getRect();

	virtual void onEnter();
};

#endif // !__PADDLE_H__

