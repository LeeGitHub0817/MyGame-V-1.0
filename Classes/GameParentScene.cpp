#include "GameParentScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene *GameParentScene::createScene()
{
	auto scene = Scene::createWithPhysics();

	//重力设置为0
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//开启遮罩，这个开启会在创建的物体上描边
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = GameParentScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameParentScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//播放背景音乐
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bg_music2.mp3", true);
	}

	//第一次添加背景
	auto background01 = Sprite::create("texture/game_bg.png");
	background01->setAnchorPoint(Point::ZERO);
	background01->setPosition(Point::ZERO);
	background01->setTag(1);
	this->addChild(background01);

	//第二次添加背景
	auto background02 = Sprite::create("texture/game_bg.png");
	background02->setAnchorPoint(Point::ZERO);
	background02->setPosition(Point::ZERO);
	background02->setPositionY(background01->getPositionY() + 1280);
	background02->setTag(2);
	this->addChild(background02);

	//画一条分界线
	auto draw = DrawNode::create();
	draw->setAnchorPoint(Point::ZERO);
	draw->drawSegment(Point(0, visibleSize.height - 60),
		Point(visibleSize.width, visibleSize.height - 60), 2, Color4F(255, 255, 255, 0.5));//红 绿 蓝 透明度
	this->addChild(draw);

	//添加暂停按钮
	auto pauseItemSpriteNor = Sprite::createWithSpriteFrameName("game_btn_pause_nor.png");
	auto pauseItemSpriteSel = Sprite::createWithSpriteFrameName("game_btn_pause_sel.png");
	auto pauseItem = MenuItemSprite::create(pauseItemSpriteNor, pauseItemSpriteSel, CC_CALLBACK_1(GameParentScene::pauseBackMenu, this));
	pauseItem->setAnchorPoint(Point::ZERO);
	pauseItem->setPosition(Point(visibleSize.width - (pauseItem->getContentSize().width),
		visibleSize.height - (pauseItem->getContentSize().height)));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//添加分数
	score = 0;

	auto labScore = LabelAtlas::create("0", "fonts/num.png", 45, 56, '0');
	labScore->setAnchorPoint(Vec2(0, 0.5));
	labScore->setPosition(Vec2(0, visibleSize.height - pauseItem->getContentSize().height / 2));
	labScore->setTag(20);
	this->addChild(labScore);

    return true;
}

void GameParentScene::update(float delta)
{
	ball->move(delta);
	ball->colloideWithPaddle(paddle);
	if (ball->getPositionY() < VisibleRect::bottom().y - ball->radius())
	{
		//Director::getInstance()->replaceScene(GameOver::createScene(false));
		auto visibleSize = Director::getInstance()->getVisibleSize();

		//播放音乐
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect("sound/game_level_fail.mp3");
		}

		//暂停当前层的内容
		this->pause();

		auto nodes = this->getChildren();
		for (const auto &node : nodes)
		{
			node->pause();
		}

		//文字
		auto label = Label::createWithTTF("You Lose!", "fonts/Marker Felt.ttf", 82);
		label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 80));
		this->addChild(label);

		//重玩本关
		auto restartButtonNor = Sprite::createWithSpriteFrameName("start_end_btn_restart_nor.png");
		auto restartButtonSel = Sprite::createWithSpriteFrameName("start_end_btn_restart_sel.png");

		auto restartButton = MenuItemSprite::create(restartButtonNor,
			restartButtonSel,
			CC_CALLBACK_1(GameParentScene::gameOverJump, this));
		restartButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 80));
		restartButton->setTag(500);

		//返回主菜单
		auto backMainButtonNor = Sprite::createWithSpriteFrameName("general_btn_back_main_nor.png");
		auto backMainButtonSel = Sprite::createWithSpriteFrameName("general_btn_back_main_sel.png");

		auto backMainButton = MenuItemSprite::create(backMainButtonNor,
			backMainButtonSel,
			CC_CALLBACK_1(GameParentScene::gameOverJump, this));
		backMainButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		backMainButton->setTag(600);

		auto menu = Menu::create(restartButton, backMainButton, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

	}
}

void GameParentScene::addMonster()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int j = 0; j < 6; j++)
	{
		//const float pitch = 2.8f;//间距
		const float pitch = 12.6f;
		float setX = 34.0f;
		float setY = 60.0f;
		for (int i = 0; i < 10; i++)
		{
			Vector<SpriteFrame *> frameArray;
			int randomNum = random(0, 3);
			switch (randomNum)
			{
			case 0:
				monster = Monster::createWithSpriteFrameName("Blue_Horiz0.png");
				for (int m = 0; m < 9; ++m)
				{
					__String *frameName = __String::createWithFormat("Blue_Horiz%d.png", m);
					SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
					frameArray.pushBack(spriteFrame);
				}
				break;

			case 1:
				monster = Monster::createWithSpriteFrameName("Green_Horiz0.png");
				for (int m = 0; m < 9; ++m)
				{
					__String *frameName = __String::createWithFormat("Green_Horiz%d.png", m);
					SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
					frameArray.pushBack(spriteFrame);
				}
				break;

			case 2:
				monster = Monster::createWithSpriteFrameName("Pink_Horiz0.png");
				for (int m = 0; m < 9; ++m)
				{
					__String *frameName = __String::createWithFormat("Pink_Horiz%d.png", m);
					SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
					frameArray.pushBack(spriteFrame);
				}
				break;

			case 3:
				monster = Monster::createWithSpriteFrameName("Yellow_Horiz0.png");
				for (int m = 0; m < 9; ++m)
				{
					__String *frameName = __String::createWithFormat("Yellow_Horiz%d.png", m);
					SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
					frameArray.pushBack(spriteFrame);
				}
				break;

			default:
				break;
			}

			monster->setPosition(Vec2(setX, VisibleRect::top().y - 65 - (j * setY + monster->getContentSize().height / 2)));
			this->addChild(monster, 1, GameSceneMonster);
			Animation *animation = Animation::create();
			for (int m = 0; m < 9; ++m)
			{
				animation->addSpriteFrame(frameArray.at(m));
			}

			animation->setDelayPerUnit(0.1f);
			animation->setRestoreOriginalFrame(true);

			monster->runAction(RepeatForever::create(Animate::create(animation)));

			setX += (pitch + monster->getContentSize().width);
		}
	}
}

void GameParentScene::moveBackground(float delta)
{
	auto bg1 = this->getChildByTag(1);
	auto bg2 = this->getChildByTag(2);

	bg1->setPositionY(bg1->getPositionY() - 1);
	if (bg1->getPositionY() < -1280)
	{
		bg1->setPositionY(0);
	}
	bg2->setPositionY(bg1->getPositionY() + 1280);
}

void GameParentScene::pauseBackMenu(cocos2d::Ref * pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	this->pause();

	for (const auto &node : this->getChildren())
	{
		node->pause();
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//继续游戏
	auto continueButtonNor = Sprite::createWithSpriteFrameName("game_btn_continue_game_nor.png");
	auto continueButtonSel = Sprite::createWithSpriteFrameName("game_btn_continue_game_sel.png");

	auto continueButton = MenuItemSprite::create(continueButtonNor,
		continueButtonSel,
		CC_CALLBACK_1(GameParentScene::pauseMenuJump, this));
	continueButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 80));
	continueButton->setTag(100);

	//回到主菜单
	auto backMainButtonNor = Sprite::createWithSpriteFrameName("general_btn_back_main_nor.png");
	auto backMainButtonSel = Sprite::createWithSpriteFrameName("general_btn_back_main_sel.png");

	auto backMainButton = MenuItemSprite::create(backMainButtonNor,
		backMainButtonSel,
		CC_CALLBACK_1(GameParentScene::pauseMenuJump, this));
	backMainButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backMainButton->setTag(200);

	//重玩本关
	auto restartButtonNor = Sprite::createWithSpriteFrameName("start_end_btn_restart_nor.png");
	auto restartButtonSel = Sprite::createWithSpriteFrameName("start_end_btn_restart_sel.png");

	auto restartButton = MenuItemSprite::create(restartButtonNor,
		restartButtonSel,
		CC_CALLBACK_1(GameParentScene::pauseMenuJump, this));
	restartButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 80));
	restartButton->setTag(300);

	menu = Menu::create(continueButton, backMainButton, restartButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

}

void GameParentScene::pauseMenuJump(cocos2d::Ref * pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	auto target = (MenuItem *)pSender;

	switch (target->getTag())
	{
	case 100:
		this->resume();

		for (const auto &node : this->getChildren())
		{
			node->resume();
		}

		this->removeChild(menu);
		break;

	case 200:
		Director::getInstance()->replaceScene(ReadyScene::createScene());
		break;

	case 300:
		Director::getInstance()->replaceScene(GameParentScene::createScene());
		break;

	default:
		break;
	}

}

void GameParentScene::onExit()
{
	Layer::onExit();

	this->unscheduleUpdate();
	this->unschedule(schedule_selector(GameParentScene::moveBackground));

	Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);

	auto nodes = this->getChildren();
	for (const auto &node : nodes)
	{
		this->removeChild(node);
	}
}

void GameParentScene::onEnter()
{
	Layer::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//创建小球
	ball = Ball::createWithSpriteFrameName("ball2.png");
	ball->setVelocity(Vec2(200.0f, 400.0f));
	ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(ball, 1, GameSceneBall);

	//创建板子
	paddle = Paddle::createWithSpriteFrameName("paddle.png");
	paddle->setPosition(Vec2(visibleSize.width / 2, paddle->getContentSize().height / 2 + 60));
	this->addChild(paddle, 1, GameScenePaddle);

	//创建怪物及其动画
	this->addMonster();

	//注册碰撞监听器
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact &contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeB()->getBody()->getNode();

		//////检测 球与怪物的碰撞//////
		Node *monster = nullptr;

		if (spriteA->getTag() == GameSceneBall && spriteB->getTag() == GameSceneMonster)
		{
			monster = spriteB;
		}
		if (spriteA->getTag() == GameSceneMonster && spriteB->getTag() == GameSceneBall)
		{
			monster = spriteA;
		}
		if (monster != nullptr)
		{
			log("Execute Successful");

			//改变球的运动方向
			ball->setVelocityDir();

			//添加骷髅头
			auto skull = Sprite::createWithSpriteFrameName("skull.png");
			skull->setPosition(monster->getPosition());
			this->addChild(skull, 0);

			//播放音效
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
			{
				SimpleAudioEngine::getInstance()->playEffect("sound/effect.wav");
			}

			//加分
			auto labScore = (LabelAtlas*)this->getChildByTag(20);
			score += 200;
			labScore->setString(String::createWithFormat("%d", score)->_string);

			//移除碰撞怪物
			if (monster != nullptr)
			{
				this->removeChild(monster);
				monsterNum++;
				log("%d", monsterNum);
			}

			//判断怪物是否打完
			if (monsterNum >= 54)
			{
				this->levelFinished();
			}

			return false;
		}

		return false;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(contactListener, 1);

}

void GameParentScene::levelFinished()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/bg_music2.mp3");
		SimpleAudioEngine::getInstance()->playEffect("sound/game_level_win.mp3");
	}

	//暂停场景中内容
	this->pause();
	auto nodes = this->getChildren();
	for (const auto &node : nodes)
	{
		node->pause();
	}

	//////添加相关内容//////
	//文字
	auto label = Label::createWithTTF("You Win!", "fonts/Marker Felt.ttf", 82);
	label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 80));
	this->addChild(label);

	//重玩本关
	auto restartButtonNor = Sprite::createWithSpriteFrameName("start_end_btn_restart_nor.png");
	auto restartButtonSel = Sprite::createWithSpriteFrameName("start_end_btn_restart_sel.png");

	auto restartButton = MenuItemSprite::create(restartButtonNor,
		restartButtonSel,
		CC_CALLBACK_1(GameParentScene::levelFinishedJump, this));
	restartButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 80));
	restartButton->setTag(50);

	//下一关
	auto nextButtonNor = Sprite::createWithSpriteFrameName("start_end_btn_next_nor.png");
	auto nextButtonSel = Sprite::createWithSpriteFrameName("start_end_btn_next_sel.png");

	auto nextButton = MenuItemSprite::create(nextButtonNor,
		nextButtonSel,
		CC_CALLBACK_1(GameParentScene::levelFinishedJump, this));
	nextButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 160));
	nextButton->setTag(60);

	auto menu = Menu::create(restartButton, nextButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void GameParentScene::levelFinishedJump(Ref *pSender)
{
	auto target = (MenuItem *)pSender;
	switch (target->getTag())
	{
	case 50:
		Director::getInstance()->replaceScene(GameParentScene::createScene());
		break;

	case 60:

		break;

	default:
		break;
	}
}

void GameParentScene::gameOverJump(cocos2d::Ref * pSender)
{
	auto target = (MenuItem *)pSender;
	switch (target->getTag())
	{
	case 500:
		Director::getInstance()->replaceScene(GameParentScene::createScene());
		break;
	case 600:
		Director::getInstance()->replaceScene(ReadyScene::createScene());
		break;
	default:
		break;
	}
}

void GameParentScene::onEnterTransitionDidFinish()
{
	//调用update函数
	this->scheduleUpdate();

	//背景移动
	this->schedule(schedule_selector(GameParentScene::moveBackground));
}