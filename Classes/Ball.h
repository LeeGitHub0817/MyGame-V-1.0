#ifndef __BALL_H__
#define __BALL_H__

#include "cocos2d.h"
#include "Paddle.h"
#include "VisibleRect.h"

class Ball : public cocos2d::Sprite
{
private:
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);

public:
	static Ball *createWithSpriteFrameName(const char *spriteFrameName);

	void move(float delta); //����˶�

	void colloideWithPaddle(Paddle *paddle); //��װ���ײ������

	float radius(); //������İ뾶

	void setVelocityDir();//��������ײ��ķ���

};

#endif // !__BALL_H__

