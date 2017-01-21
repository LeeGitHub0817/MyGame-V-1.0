#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "VisibleRect.h"
#include "SystemHeader.h"

#include "GameParentScene.h"
#include "ReadyScene.h"


class GameOver : public cocos2d::Layer
{
public:
	bool initEndScene(bool win);
	static cocos2d::Scene* createScene(bool isWin);
	void menuCallback(Ref* pSender);
};