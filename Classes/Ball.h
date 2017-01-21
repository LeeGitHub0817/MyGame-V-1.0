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

	void move(float delta); //球的运动

	void colloideWithPaddle(Paddle *paddle); //与底板碰撞处理函数

	float radius(); //返回球的半径

	void setVelocityDir();//设置球碰撞后的方向

};

#endif // !__BALL_H__

