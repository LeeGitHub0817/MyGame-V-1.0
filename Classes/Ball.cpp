#include "Ball.h"

USING_NS_CC;

Ball * Ball::createWithSpriteFrameName(const char * spriteFrameName)
{
	Ball *ball = new Ball();
	if (ball && ball->initWithSpriteFrameName(spriteFrameName))
	{
		ball->autorelease();
		
		auto body = PhysicsBody::createCircle(ball->getContentSize().width / 2, PhysicsMaterial(0.3f, 1.0f, 0.0f));
		
		//�����������
		//��ײ������������빲ͬ��������֮���Ƿ���ײ
		//��ײ����
		//body->setCollisionBitmask(0x04);
		//�������
		//body->setCategoryBitmask(0x03);
		//�Ӵ�����
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
	//�ұ�
	if (getPosition().x > VisibleRect::right().x - radius())
	{
		setPosition(VisibleRect::right().x - radius(), getPosition().y);
		velocity.x *= -1;
	}
	//���
	else if (getPosition().x < VisibleRect::left().x + radius())
	{
		setPosition(VisibleRect::left().x + radius(), getPosition().y);
		velocity.x *= -1;
	}
	//����
	else if (getPosition().y > VisibleRect::top().y - 60 - radius())
	{
		setPosition(getPosition().x, VisibleRect::top().y - 60 - radius());
		velocity.y *= -1;
	}
}

void Ball::colloideWithPaddle(Paddle * paddle)
{
	auto paddleRect = paddle->getRect();
	paddleRect.origin.x += paddle->getPosition().x;//originΪ�������½ǵ�
	paddleRect.origin.y += paddle->getPosition().y;

	float lowY = paddleRect.getMinY();//�ײ�����
	float midY = paddleRect.getMidY();
	float highY = paddleRect.getMaxY();

	float leftX = paddleRect.getMinX();//�������
	float rightX = paddleRect.getMaxX();//�ұ�����

	if (getPosition().x > leftX && getPosition().x < rightX)//�������η�Χ��
	{
		bool hit = false;
		float angleOffset = 0.0f;//�Ƕ�ƫ��ֵ

		if (getPosition().y > midY && getPosition().y <= highY + radius())
		{
			setPosition(getPosition().x, highY + radius());
			hit = true;
			angleOffset = (float)M_PI / 2;
		}

		if (hit)//��ײ����
		{
			//getangle()�ǻ�ȡ���������꣩��X��ļнǡ�
			//getLength()�Ǽ���㵽ԭ��ľ���
			float hitAngle = (paddle->getPosition() - getPosition()).getAngle() + angleOffset;
			
			float scalarVelocity = velocity.getLength() * 1.00f; //1.05(ԭֵΪ1.05�����ֵ����1�����ٶȻ�Խ��Խ��)
			float velocityAngle = -velocity.getAngle() + 0.5f * hitAngle;

			velocity = Vec2::forAngle(velocityAngle) * scalarVelocity;
		}
	}
}

