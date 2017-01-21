#include "LogoScene.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	scene->addChild(layer);
	return scene;
}

bool LogoScene::init()
{
	if (Layer::init() == false)
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading.plist");
	
	//��һ����ӱ���
	auto background = Sprite::create("texture/loading_bg.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setTag(1);
	this->addChild(background);

	//////���Ÿ�Ц����//////
	auto ani = Sprite::create("image/mybk1.png");
	ani->setPosition(Point(visibleSize.width / 2, visibleSize.height - 100));
	this->addChild(ani);

	//��������֡����
	auto animation = Animation::create();
	for (int i = 1; i < 62; i++)//ͼƬ���Ƹ���
	{
		char szName[100] = { 0 };
		sprintf(szName, "image/mybk%d.png", i);
		animation->addSpriteFrameWithFile(szName);//��������֡����
	}

	animation->setDelayPerUnit(0.1f);//������֮֡��ļ��
	animation->setLoops(-1);//ѭ����-1����ѭ����
	animation->setRestoreOriginalFrame(true);//���ò�������Ƿ�ص���һ֡

	auto action = Animate::create(animation);//������������
	ani->runAction(Sequence::create(action, action->reverse(), NULL));//ִ��

	//////���ż��ض���//////
	auto sprite = Sprite::createWithSpriteFrameName("loading_0.png");
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	this->addChild(sprite);

	//��������
	Animation *animation_load = Animation::create();
	for (int i = 0; i < 6; ++i)
	{
		__String *frameName = __String::createWithFormat("loading_%d.png", i);
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation_load->addSpriteFrame(spriteFrame);
	}
	animation_load->setDelayPerUnit(0.2f);
	animation_load->setRestoreOriginalFrame(true);

	Animate *action_load = Animate::create(animation_load);
	sprite->runAction(RepeatForever::create(action_load));

	//////Ԥ��������//////
	m_loadNum = 0;
	Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
		CC_CALLBACK_1(LogoScene::loadTexture, this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/gamelevel_select_texture.png",
		CC_CALLBACK_1(LogoScene::loadTexture, this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/game_texture.png",
		CC_CALLBACK_1(LogoScene::loadTexture, this));


	//////Ԥ������Ƶ//////
	_preLoadAudio = new std::thread(&LogoScene::loadAudio, this);

	return true;
}

void LogoScene::loadTexture(cocos2d::Texture2D * texture)
{
	switch (m_loadNum++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist", texture);
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gamelevel_select_texture.plist", texture);
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/game_texture.plist", texture);
		this->schedule(schedule_selector(LogoScene::delayCall), 1, 1, 4);
		break;
	}
}

void LogoScene::loadAudio()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bg_music1.mp3");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bg_music2.mp3");
}

void LogoScene::delayCall(float dt)
{
	auto scene = ReadyScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void LogoScene::onExit()
{
	Layer::onExit();
	_preLoadAudio->join();
	CC_SAFE_DELETE(_preLoadAudio);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading.plist");
	Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading.png");
	this->unschedule(schedule_selector(LogoScene::delayCall));
}



