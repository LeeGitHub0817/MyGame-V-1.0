#include "Monster.h"

USING_NS_CC;


Monster * Monster::createWithSpriteFrameName(const char * spriteFrameName)
{
	Monster *monster = new Monster();

	if (monster && monster->initWithSpriteFrameName(spriteFrameName))
	{
		monster->autorelease();

		//auto body = PhysicsBody::createBox(monster->getContentSize() - Size(2, 2), PhysicsMaterial(0.3f, 1.0f, 0.0f));
		auto body = PhysicsBody::createCircle(monster->getContentSize().width / 2, PhysicsMaterial(0.3f, 1.0f, 0.0f));

		//////设置相关掩码//////
		//碰撞掩码与类别掩码共同决定物体之间是否碰撞
		//碰撞掩码
		//body->setCollisionBitmask(0x01);
		//类别掩码
		//body->setCategoryBitmask(0x03);
		//接触掩码
		body->setContactTestBitmask(0x01);

		monster->setPhysicsBody(body);

		return monster;
	}

	CC_SAFE_DELETE(monster);
	return nullptr;
}
