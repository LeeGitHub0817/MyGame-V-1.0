#include "ReadyScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* ReadyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ReadyScene::create();

	scene->addChild(layer);

	return scene;
}

bool ReadyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	 
	//获取大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	auto background01 = Sprite::create("texture/home_bg.png");
	background01->setTag(1);
	background01->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background01);
	
	//添加粒子
	auto particleSys = ParticleFireworks::create();
	particleSys->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 200));
	this->addChild(particleSys);

	//添加开始按钮
	auto startItemSpriteNor = Sprite::createWithSpriteFrameName("MainMenu_start_nor.png");
	auto startItemSpriteSel = Sprite::createWithSpriteFrameName("MainMenu_start_sel.png");
	auto startItem = MenuItemSprite::create(startItemSpriteNor,
											startItemSpriteSel,
											CC_CALLBACK_1(ReadyScene::menuItemCallback, this));
	startItem->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	startItem->setTag(10);

	//添加设置按钮
	auto optionItemSpriteNol = Sprite::createWithSpriteFrameName("general_btn_option_nor.png");
	auto optionItemSpriteSel = Sprite::createWithSpriteFrameName("general_btn_option_sel.png");
	auto optionItem = MenuItemSprite::create(optionItemSpriteNol,
		optionItemSpriteSel,
		CC_CALLBACK_1(ReadyScene::optionCallback, this));
	optionItem->setPosition(Vec2(optionItem->getContentSize().width / 2, optionItem->getContentSize().height / 2));

	//添加关闭按钮
	auto closeItemSpriteNor = Sprite::createWithSpriteFrameName("MainMenu_btn_close_nor.png");
	auto closeItemSpriteSel = Sprite::createWithSpriteFrameName("MainMenu_btn_close_sel.png");
	auto closeItem = MenuItemSprite::create(closeItemSpriteNor,
											closeItemSpriteSel,
											CC_CALLBACK_1(ReadyScene::closeItem, this));
	closeItem->setPosition(Point(visibleSize.width - closeItem->getContentSize().width / 2, closeItem->getContentSize().height / 2));
	closeItem->setTag(13);

	//添加关于游戏按钮
	auto aboutItemSpriteNor = Sprite::createWithSpriteFrameName("general_btn_notify_nor.png");
	auto aboutItemSpriteSel = Sprite::createWithSpriteFrameName("general_btn_notify_sel.png");
	auto aboutItem = MenuItemSprite::create(aboutItemSpriteNor,
		aboutItemSpriteSel,
		CC_CALLBACK_1(ReadyScene::menuItemCallback, this));
	aboutItem->setPosition(Vec2(visibleSize.width / 2, aboutItem->getContentSize().height / 2));
	aboutItem->setTag(20);

	auto menu = Menu::create(startItem, optionItem, closeItem, aboutItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//添加小球
	_ballStartingVelocity = Vec2(200.0f, 500.0f);
	_ball = BallTest::ballWithTexture(Director::getInstance()->getTextureCache()->addImage("texture/ball.png"));
	_ball->setPosition(VisibleRect::center());
	_ball->setVelocity(_ballStartingVelocity);
	this->addChild(_ball);

	//计划任务
	this->schedule(CC_SCHEDULE_SELECTOR(ReadyScene::doStep));

	return true;
}

void ReadyScene::onEnter()
{
	Layer::onEnter();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	//////播放动画//////
	auto sprite1 = Sprite::createWithSpriteFrameName("Yellow_Horiz0.png");
	sprite1->setPosition(Vec2(VisibleRect::left().x + 100, VisibleRect::bottom().y + sprite1->getContentSize().height / 2));
	this->addChild(sprite1);

	//创建动画
	Animation *animation_load = Animation::create();
	for (int i = 0; i < 6; ++i)
	{
		__String *frameName = __String::createWithFormat("Yellow_Horiz%d.png", i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation_load->addSpriteFrame(spriteFrame);
	}
	animation_load->setDelayPerUnit(0.05f);
	animation_load->setRestoreOriginalFrame(true);

	Animate *action_load = Animate::create(animation_load);
	sprite1->runAction(RepeatForever::create(action_load));

	//组合动作动画
	FiniteTimeAction *ac1 = (FiniteTimeAction *)JumpBy::create(2,
		Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150), 40.0f, 3);

	FiniteTimeAction *ac2 = ((FiniteTimeAction *)ac1)->reverse();//反顺序动作，XXXTo一般都不支持

	FiniteTimeAction *ac3 = (FiniteTimeAction *)RotateBy::create(3, 350.0f);

	FiniteTimeAction *ac4 = ((FiniteTimeAction *)ac3)->reverse();

	ActionInterval *as1 = Sequence::create(ac1, ac2, ac3, ac4, NULL);
	sprite1->runAction(RepeatForever::create(EaseSineOut::create(as1)));

	//第二个动画
	auto sprite2 = Sprite::createWithSpriteFrameName("Pink_Horiz0.png");
	sprite2->setPosition(Vec2(VisibleRect::right().x - 100, VisibleRect::bottom().y + sprite2->getContentSize().height / 2));
	this->addChild(sprite2);

	//创建动画
	Animation *animation_load2 = Animation::create();
	for (int i = 0; i < 6; ++i)
	{
		__String *frameName = __String::createWithFormat("Pink_Horiz%d.png", i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation_load2->addSpriteFrame(spriteFrame);
	}
	animation_load2->setDelayPerUnit(0.05f);
	animation_load2->setRestoreOriginalFrame(true);

	Animate *action_load2 = Animate::create(animation_load2);
	sprite2->runAction(RepeatForever::create(action_load2));

	//组合动作动画
	FiniteTimeAction *ac5 = (FiniteTimeAction *)JumpBy::create(2,
		Vec2(-visibleSize.width / 2, visibleSize.height / 2 - 150), 40.0f, 3);

	FiniteTimeAction *ac6 = ((FiniteTimeAction *)ac5)->reverse();//反顺序动作，XXXTo一般都不支持

	FiniteTimeAction *ac7 = (FiniteTimeAction *)RotateBy::create(3, 350.0f);

	FiniteTimeAction *ac8 = ((FiniteTimeAction *)ac7)->reverse();

	ActionInterval *as2 = Sequence::create(ac5, ac6, ac7, ac8, NULL);
	sprite2->runAction(RepeatForever::create(EaseSineOut::create(as2)));

}

void ReadyScene::menuItemCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	auto target = (MenuItem*)pSender;
	Scene* scene = nullptr;
	switch (target->getTag())
	{
	case 10:
		scene = GameSelectScene::createScene();
		break;
	case 20:
		scene = AboutScene::createScene();
		break;
	default:
		break;
	}
	auto scene01 = TransitionCrossFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(scene01);
}

void ReadyScene::closeItem(Ref* pSender)//关闭按钮
{
	Director::getInstance()->end();	
}

void ReadyScene::optionCallback(Ref *pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	//暂停当前层中相关节点
	this->pause();
	for (const auto &node : this->getChildren())
	{
		node->pause();
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//添加背景牌
	boardSprite = Sprite::createWithSpriteFrameName("general_back5.png");
	boardSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(boardSprite, 1);

	//////添加相关按钮//////
	//关闭按钮
	auto resumeButtonSpriteNor = Sprite::createWithSpriteFrameName("general_btn_close_nor.png");
	auto resumeButtonSpriteSel = Sprite::createWithSpriteFrameName("general_btn_close_sel.png");
	auto resumeButton = MenuItemSprite::create(resumeButtonSpriteNor,
		resumeButtonSpriteSel,
		CC_CALLBACK_1(ReadyScene::menuResumeCallback, this));
	resumeButton->setPosition(Vec2(visibleSize.width / 2 + boardSprite->getContentSize().width / 2 - resumeButton->getContentSize().width / 2, 
		visibleSize.height / 2 + boardSprite->getContentSize().height / 2 - resumeButton->getContentSize().height/ 2));
	menu = Menu::create(resumeButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);

	//是否关闭音乐按钮
	auto musicButtonSpriteNor = Sprite::createWithSpriteFrameName("general_btn_music_nor.png");
	auto musicButtonSpriteSel = Sprite::createWithSpriteFrameName("general_btn_music_sel.png");
	auto musicButtonNor = MenuItemSprite::create(musicButtonSpriteNor, NULL);
	auto musicButtonSel = MenuItemSprite::create(musicButtonSpriteSel, NULL);
	auto musicButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ReadyScene::menuMusicToggleCallback, this),
		musicButtonNor,
		musicButtonSel, NULL);
	musicButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 40));

	//是否关闭音效按钮
	auto soundButtonSpriteNor = Sprite::createWithSpriteFrameName("general_btn_sound_nor.png");
	auto soundButtonSpriteSel = Sprite::createWithSpriteFrameName("general_btn_sound_sel.png");
	auto soundButtonNor = MenuItemSprite::create(soundButtonSpriteNor, NULL);
	auto soundButtonSel = MenuItemSprite::create(soundButtonSpriteSel, NULL);
	auto soundButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ReadyScene::menuSoundToggleCallback, this),
		soundButtonNor,
		soundButtonSel, NULL);
	soundButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 40));

	toggleMenu = Menu::create(musicButton, soundButton, NULL);
	toggleMenu->setPosition(Vec2::ZERO);
	this->addChild(toggleMenu, 2);

	//////设置音效和音乐选中状态//////
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		musicButton->setSelectedIndex(0);
	}
	else {
		musicButton->setSelectedIndex(1);
	}
	if (defaults->getBoolForKey(SOUND_KEY)) {
		soundButton->setSelectedIndex(0);
	}
	else {
		soundButton->setSelectedIndex(1);
	}

}

void ReadyScene::menuResumeCallback(Ref *pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	this->resume();

	for (const auto &node : this->getChildren())
	{
		node->resume();
	}
	this->removeChild(menu);
	this->removeChild(boardSprite);
	this->removeChild(toggleMenu);
}

void ReadyScene::menuMusicToggleCallback(Ref *pSender)
{
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		defaults->setBoolForKey(MUSIC_KEY, false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else {
		defaults->setBoolForKey(MUSIC_KEY, true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bg_music1.mp3", true);
	}
}

void ReadyScene::menuSoundToggleCallback(Ref *pSender)
{
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(SOUND_KEY)) {
		defaults->setBoolForKey(SOUND_KEY, false);
	}
	else {
		defaults->setBoolForKey(SOUND_KEY, true);
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}
}

void ReadyScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	UserDefault *def = UserDefault::getInstance();
	if (def->getBoolForKey(MUSIC_KEY))
	{
		//播放背景音乐
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bg_music1.mp3", true);
	}
}



void ReadyScene::doStep(float delta)
{
	_ball->move(delta);
}

BallTest::BallTest(void)
{
}

BallTest::~BallTest(void)
{
}

BallTest *BallTest::ballWithTexture(Texture2D* aTexture)
{
	BallTest* pBall = new (std::nothrow) BallTest();
	pBall->initWithTexture(aTexture);
	pBall->autorelease();
	return pBall;
}

void BallTest::move(float delta)//球的移动，碰到边界反弹
{
	this->setPosition(getPosition() + _velocity * delta);

	if (getPosition().x > VisibleRect::right().x - radius())
	{
		setPosition(VisibleRect::right().x - radius(), getPosition().y);
		_velocity.x *= -1;
	}
	else if (getPosition().x < VisibleRect::left().x + radius())
	{
		setPosition(VisibleRect::left().x + radius(), getPosition().y);
		_velocity.x *= -1;
	}
	else if (getPosition().y > VisibleRect::top().y - radius())
	{
		setPosition(getPosition().x, VisibleRect::top().y - radius());
		_velocity.y *= -1;
	}
	else if (getPosition().y < VisibleRect::bottom().y + radius())
	{
		setPosition(getPosition().x, VisibleRect::bottom().y + radius());
		_velocity.y *= -1;
	}
}

float BallTest::radius()
{
	return getTexture()->getContentSize().width / 2;
}

