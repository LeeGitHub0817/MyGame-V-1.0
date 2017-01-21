#include "GameOverScene.h"

USING_NS_CC;
using namespace CocosDenshion;

bool GameOver::initEndScene(bool isWin)
{
	if (!Layer::create())
	{
		return false;
	}
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playEffect("sound/game_level_fail.mp3");
	}
	

	//添加背景
	auto background = Sprite::create("texture/gameover_bg.png");
	background->setPosition(VisibleRect::center());
	background->setOpacity(75);
	this->addChild(background);

	//添加结果文字
	char words[64];
	if (isWin)
	{
		sprintf(words, "You Win!");
	}
	else
	{
		sprintf(words, "You Lose!");
	}

	Label* label = Label::createWithTTF(words, "fonts/Marker Felt.ttf", 82);
	label->setPosition(VisibleRect::center().x, VisibleRect::center().y + 62);
	this->addChild(label);
	
	MenuItemFont::setFontSize(52);
	MenuItemFont::setFontName("Tregger");

	//添加重试按钮
	MenuItemFont* menuTry = MenuItemFont::create("Play Again", CC_CALLBACK_1(GameOver::menuCallback, this));	
	menuTry->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - 60));
	menuTry->setTag(10);

	//添加回到主菜单按钮
	MenuItemFont* menuBack = MenuItemFont::create("Back Menu", CC_CALLBACK_1(GameOver::menuCallback, this));
	menuBack->setPosition(Vec2(VisibleRect::center().x, VisibleRect::center().y - 180));
	menuBack->setTag(11);

	Menu* menu = Menu::create(menuTry, menuBack, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	
	return true;
}

Scene* GameOver::createScene(bool isWin)
{
	Scene* scene = Scene::create();
	GameOver* gamese = new GameOver();
	if (gamese)
	{
		gamese->autorelease();

		gamese->initEndScene(isWin);
		scene->addChild(gamese);
		return scene;
	}

	CC_SAFE_DELETE(gamese);
	return nullptr;
	
}

void GameOver::menuCallback(Ref * pSender)
{
	auto target = (MenuItem*)pSender;
	switch (target->getTag())
	{
	case 10:
		Director::getInstance()->replaceScene(GameParentScene::createScene());
		break;
	case 11:
		Director::getInstance()->replaceScene(ReadyScene::createScene());
		break;
	default:
		break;
	}
}
	
