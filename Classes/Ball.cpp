#include "Ball.h"

USING_NS_CC;

Ball * Ball::createWithSpriteFrameName(const char * spriteFrameName)
{
	Ball *ball = new Ball();
	if (ball && ball->initWithSpriteFrameName(spriteFrameName))
	{
		ball->autorelease();
		
		auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0.3f, 1.0f, 0.0f));
		
		//设置相关掩码
		//碰撞掩码与类别掩码共同决定物体之间是否碰撞
		//碰撞掩码
		//body->setCollisionBitmask(0x04);
		//类别掩码
		//body->setCategoryBitmask(0x03);
		//接触掩码
		body->setContactTestBitmask(0x01);
		
		ball->setPhysicsBody(body);

		return ball;
	}

	CC_SAFE_DELETE(ball);
	return nullptr;
}

float Ball::radius()
{
	return this->getContentSize().width / 2;
}

void Ball::setVelocityDir()
{
	velocity.y *= -1;
}

void Ball::move(float delta)
{
	this->setPosition(getPosition() + velocity * delta);
	this->setPosition(getPosition() + velocity * delta);
	//右边
	if (getPosition().x > VisibleRect::right().x - radius())
	{
		setPosition(VisibleRect::right().x - radius(), getPosition().y);
		velocity.x *= -1;
	}
	//左边
	else if (getPosition().x < VisibleRect::left().x + radius())
	{
		setPosition(VisibleRect::left().x + radius(), getPosition().y);
		velocity.x *= -1;
	}
	//顶部
	else if (getPosition().y > VisibleRect::top().y - 60 - radius())
	{
		setPosition(getPosition().x, VisibleRect::top().y - 60 - radius());
		velocity.y *= -1;
	}
}

void Ball::colloideWithPaddle(Paddle * paddle)
{
	auto paddleRect = paddle->getRect();
	paddleRect.origin.x += paddle->getPosition().x;//origin为矩形左下角点
	paddleRect.origin.y += paddle->getPosition().y;

	float lowY = paddleRect.getMinY();//底部坐标
	float midY = paddleRect.getMidY();
	float highY = paddleRect.getMaxY();

	float leftX = paddleRect.getMinX();//左边坐标
	float rightX = paddleRect.getMaxX();//右边坐标

	if (getPosition().x > leftX && getPosition().x < rightX)//球进入矩形范围内
	{
		bool hit = false;
		float angleOffset = 0.0f;//角度偏移值

		if (getPosition().y > midY && getPosition().y <= highY + radius())
		{
			setPosition(getPosition().x, highY + radius());
			hit = true;
			angleOffset = (float)M_PI / 2;
		}

		if (hit)//碰撞后处理
		{
			//getangle()是获取向量（坐标）与X轴的夹角。
			//getLength()是计算点到原点的距离
			float hitAngle = (paddle->getPosition() - getPosition()).getAngle() + angleOffset;
			
			float scalarVelocity = velocity.getLength() * 1.00f; //1.05(原值为1.05，这个值大于1话，速度会越来越快)
			float velocityAngle = -velocity.getAngle() + 0.5f * hitAngle;

			velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
		}
	}
}

