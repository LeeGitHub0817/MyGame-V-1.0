#include "AboutScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* AboutScene::createScene()
{

	auto scene = Scene::create();

	auto layer = AboutScene::create();

	scene->addChild(layer);

	return scene;
}

bool AboutScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//添加背景
	auto background01 = Sprite::create("texture/about_bg.png");
	background01->setAnchorPoint(Point::ZERO);
	background01->setPosition(Point::ZERO);
	background01->setTag(1);
	this->addChild(background01);
	//第二次添加背景
	auto background02 = Sprite::create("texture/about_bg.png");
	background02->setAnchorPoint(Point::ZERO);
	background02->setPosition(Point::ZERO);
	background02->setPositionY(background01->getPositionY() + 1280);
	background02->setTag(2);
	this->addChild(background02);

	//返回按钮
	auto backItemSpriteNor = Sprite::createWithSpriteFrameName("general_btn_back_nor.png");
	auto backItemSpriteSel = Sprite::createWithSpriteFrameName("general_btn_back_sel.png");
	auto backItem = MenuItemSprite::create(backItemSpriteNor,
		backItemSpriteSel,
		CC_CALLBACK_1(AboutScene::menuBackCallback, this));
	backItem->setPosition(Vec2(visibleSize.width - backItem->getContentSize().width / 2, backItem->getContentSize().height / 2));

	auto menu = Menu::create(backItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);



	return true;
}

void AboutScene::menuBackCallback(Ref* pSender)
{
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	}

	Director::getInstance()->replaceScene(ReadyScene::createScene());
}

void AboutScene::moveBackground(float)
{
	auto background01 = this->getChildByTag(1);
	auto background02 = this->getChildByTag(2);
	background01->setPositionY(background01->getPositionY() + 1);
	if (background01->getPositionY() > 1280)
	{
		background01->setPositionY(0);
	}
	background02->setPositionY(background01->getPositionY() - 1280);
}

void AboutScene::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

	//计划任务之背景滚动
	this->schedule(schedule_selector(AboutScene::moveBackground));
}

