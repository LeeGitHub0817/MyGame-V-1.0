#include "Paddle.h"

USING_NS_CC;

Paddle * Paddle::createWithSpriteFrameName(const char * spriteFrameName)
{
	Paddle *paddle = new Paddle();
	if (paddle && paddle->initWithSpriteFrameName(spriteFrameName))
	{
		paddle->autorelease();

		auto body = PhysicsBody::createBox(paddle->getContentSize(), PhysicsMaterial(0.3f, 1.0f, 0.0f));

		//////设置相关掩码//////
		//碰撞掩码与类别掩码共同决定物体之间是否碰撞
		//碰撞掩码
		body->setCollisionBitmask(0x01);
		//类别掩码
		body->setCategoryBitmask(0x02);
		//接触掩码

		//auto body = PhysicsBody::createEdgeSegment(Vec2(paddle->getPosition().x - paddle->getContentSize().width / 2, paddle->getPosition().y + paddle->getContentSize().height / 2),
		//	Vec2(paddle->getPosition().x + paddle->getContentSize().width / 2, paddle->getPosition().y + paddle->getContentSize().height / 2), 
		//	PhysicsMaterial(0.3f, 1.0f, 0.0f));

		paddle->setPhysicsBody(body);

		return paddle;
	}

	CC_SAFE_DELETE(paddle);
	return nullptr;
}

Rect Paddle::getRect()
{
	Size size = this->getContentSize();
	return Rect(-size.width / 2, -size.height / 2, size.width, size.height);
}

bool Paddle::onTouchBegin(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (_state != paddleStateUngrabbed)
	{
		return false;
	}

	if (containsTouchLoction(touch) == NULL)
	{
		return false;
	}

	_state = paddleStateGrabbed;
	return true;
}

void Paddle::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto touchPoint = touch->getLocation();
	if (touchPoint.x > 0 && touchPoint.x < visibleSize.width)
	{
		setPosition(Vec2(touchPoint.x, getPosition().y));
	}

}

void Paddle::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	_state = paddleStateUngrabbed;
}

bool Paddle::containsTouchLoction(cocos2d::Touch * touch)
{
	auto paddleSize = this->getContentSize();
	auto paddleRect = Rect(-paddleSize.width / 2, -paddleSize.height / 2, paddleSize.width, paddleSize.height);

	return paddleRect.containsPoint(convertTouchToNodeSpaceAR(touch));

}


void Paddle::onEnter()
{
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Paddle::onTouchBegin, this);
	listener->onTouchMoved = CC_CALLBACK_2(Paddle::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Paddle::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
