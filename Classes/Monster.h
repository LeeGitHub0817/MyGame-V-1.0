#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "cocos2d.h"

enum MonsterType
{
	MonsterRed = 0,
	MonsterGreen,
	MonsterBlue,
	MonsterYellow
};

class Monster : public cocos2d::Sprite
{
public:
	static Monster *createWithSpriteFrameName(const char *spriteFrameName);

};


#endif // !__MONSTER_H__

