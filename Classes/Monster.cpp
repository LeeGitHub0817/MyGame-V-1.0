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

		//////�����������//////
		//��ײ������������빲ͬ��������֮���Ƿ���ײ
		//��ײ����
		//body->setCollisionBitmask(0x01);
		//�������
		//body->setCategoryBitmask(0x03);
		//�Ӵ�����
		body->setContactTestBitmask(0x01);

		monster->setPhysicsBody(body);

		return monster;
	}

	CC_SAFE_DELETE(monster);
	return nullptr;
}
