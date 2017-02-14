#include "GameScrollScene.h"
#include "LevelSceneTwo.h"

USING_NS_CC_EXT;
USING_NS_CC;

bool GameScrollScene::init()
{
	if (Layer::init() == NULL)
	{
		return false;
	}

	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());
		auto winSize = Director::getInstance()->getVisibleSize();

		//设置ScrollView为整个屏幕大小
		ScrollView *scrollView = ScrollView::create(Size(winSize.width, winSize.height));

		//////设置ScrollView一些相关参数//////
		//设置反弹效果
		scrollView->setBounceable(true);

		//将锚点设为中心
		scrollView->ignoreAnchorPointForPosition(false);
		scrollView->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

		//设置滑动方向
		scrollView->setDirection(ScrollView::Direction::HORIZONTAL);

		//创建一个Layer，将内容添加到Layer中，然后将这个layer添加到scrollview中
		Layer *layer = Layer::create();
		for (int i = 1; i < 6; ++i)
		{
			//添加背景
			Sprite *sprite = Sprite::createWithSpriteFrameName("general_back11.png");
			sprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2) + Vec2(winSize.width * (i - 1), 0));
			//sprite->setContentSize(Size(400.0f, 400.0f));
			layer->addChild(sprite);

			//添加第几关
			auto levelBoard = Sprite::createWithSpriteFrameName("general_level_title_bg.png");
			levelBoard->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y + sprite->getContentSize().height / 2));
			layer->addChild(levelBoard);

			__String *levelNum = __String::createWithFormat("Level %d", i);
			auto level = Label::createWithTTF(levelNum->getCString(), "fonts/Marker Felt.ttf", 28);
			level->setPosition(levelBoard->getPosition());
			layer->addChild(level);

			//添加开始按钮
			Sprite *menuItemStartNor = Sprite::createWithSpriteFrameName("start_end_btn_start_nor.png");
			Sprite *menuItemStartSel = Sprite::createWithSpriteFrameName("start_end_btn_start_sel.png");
			MenuItemSprite *menuItemStart = MenuItemSprite::create(menuItemStartNor, menuItemStartSel,
				CC_CALLBACK_1(GameScrollScene::menuStartCallback, this));
			menuItemStart->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y - sprite->getContentSize().height / 2));
			menuItemStart->setTag(i);

			Menu *menu = Menu::create(menuItemStart, NULL);
			menu->setPosition(Vec2::ZERO);
			layer->addChild(menu);

			//添加精灵动画1
			auto spriteAni1 = Sprite::createWithSpriteFrameName("Blue_Horiz0.png");
			spriteAni1->setPosition(Vec2(sprite->getPosition().x - 100, sprite->getPosition().y));
			layer->addChild(spriteAni1);

			auto animation1 = Animation::create();
			for (int i = 0; i < 9; ++i)
			{
				__String *frameName = __String::createWithFormat("Blue_Horiz%d.png", i);
				SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation1->addSpriteFrame(spriteFrame);
			}
			animation1->setDelayPerUnit(0.05f);
			animation1->setRestoreOriginalFrame(true);

			spriteAni1->runAction(RepeatForever::create(Animate::create(animation1)));


			//添加精灵动画2
			auto spriteAni2 = Sprite::createWithSpriteFrameName("Green_Horiz0.png");
			spriteAni2->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y));
			layer->addChild(spriteAni2);

			auto animation2 = Animation::create();
			for (int i = 0; i < 9; ++i)
			{
				__String *frameName = __String::createWithFormat("Green_Horiz%d.png", i);
				SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation2->addSpriteFrame(spriteFrame);
			}
			animation2->setDelayPerUnit(0.05f);
			animation2->setRestoreOriginalFrame(true);

			spriteAni2->runAction(RepeatForever::create(Animate::create(animation2)));

			//添加精灵动画3
			auto spriteAni3 = Sprite::createWithSpriteFrameName("Pink_Horiz0.png");
			spriteAni3->setPosition(Vec2(sprite->getPosition().x + 100, sprite->getPosition().y));
			layer->addChild(spriteAni3);

			auto animation3 = Animation::create();
			for (int i = 0; i < 9; ++i)
			{
				__String *frameName = __String::createWithFormat("Pink_Horiz%d.png", i);
				SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
				animation3->addSpriteFrame(spriteFrame);
			}
			animation3->setDelayPerUnit(0.05f);
			animation3->setRestoreOriginalFrame(true);

			spriteAni3->runAction(RepeatForever::create(Animate::create(animation3)));
		}

		//返回按钮
		auto backItemSpriteNor = Sprite::createWithSpriteFrameName("map_btn_back_nor.png");
		auto backItemSpriteSel = Sprite::createWithSpriteFrameName("map_btn_back_sel.png");
		auto backItem = MenuItemSprite::create(backItemSpriteNor,
			backItemSpriteSel,
			CC_CALLBACK_1(GameScrollScene::menuBackCallback, this));

		backItem->setPosition(Vec2(winSize.width - backItem->getContentSize().width / 2, backItem->getContentSize().height / 2));

		auto menu = Menu::create(backItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

		//设置scrollView里的内容,必须先设置内容再设置大小
		scrollView->setContainer(layer);
		scrollView->setContentSize(Size(winSize.width * 5, winSize.height));

		//屏蔽scrollView当前层的触摸
		scrollView->setTouchEnabled(false);

		//设置scrollView当中内容的偏移量
		scrollView->setContentOffset(Vec2(0.0f, 0.0f));
		this->addChild(scrollView);
		////要赋值是因为scrollView是局部变量，这个函数执行后会释放。
		this->m_scrollView = scrollView; 
		this->m_nCurPage = 0;

		bRet = true;

		//定义响应的触摸事件
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(GameScrollScene::touchBegin, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(GameScrollScene::touchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(GameScrollScene::touchEnded, this);
		touchListener->onTouchCancelled = CC_CALLBACK_2(GameScrollScene::touchCancelled, this);
		touchListener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	} while (0);

	return bRet;
}

bool GameScrollScene::touchBegin(cocos2d::Touch * touch, cocos2d::Event * event)
{
	this->m_touchPoint = touch->getLocation();
	this->m_offsetPoint = this->m_scrollView->getContentOffset();

	/**********************	
	以下的这一点特别要注意，大家可以先注释掉以下的这
	句话然后运行程序，会发现如果触摸不是很快
	的时候不会有什么问题，但是如果触摸进行的很快，关
	卡的位置偏移的就不会正确，以下的代码正是解决这个问题到
	************************/
	auto visibleWidth = (int)Director::getInstance()->getVisibleSize().width;
	auto temp = (int)this->m_offsetPoint.x;
	if ((temp % visibleWidth) == 0)
	{
		return true;
	}

	return false;
}

void GameScrollScene::touchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	//设置关卡随手指方向移动
	auto point = touch->getLocation();
	auto direction = point - this->m_touchPoint;

	//设置成只在X轴方向偏移
	Vec2 spriteDirection = Vec2(direction.x + this->m_offsetPoint.x, 0);
	this->m_scrollView->setContentOffset(spriteDirection);
}

void GameScrollScene::touchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	//结束触摸的时候，使关卡显示在屏幕的中间
	auto endPoint = touch->getLocation();
	auto distance = endPoint.x - this->m_touchPoint.x;

	//手指移动距离小于20， 将偏移量作为0处理
	if (fabs(distance) < 20)
	{
		this->checkScrollView(0);
	}
	else
	{
		this->checkScrollView(distance);
	}
}

void GameScrollScene::touchCancelled(cocos2d::Touch * touch, cocos2d::Event * event)
{

}

void GameScrollScene::checkScrollView(float offset)
{
	//调整关卡的最终位置
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//手指往左滑时，offset大于0，页面减小，往右增大
	if (offset < 0)
	{
		m_nCurPage++;
	}
	else if (offset > 0)
	{
		m_nCurPage--;
	}

	//不超出最左边一页和最右边一页
	if (m_nCurPage < 0)
	{
		m_nCurPage = 0;
	}
	else if (m_nCurPage > 4)
	{
		m_nCurPage = 4;
	}
	auto adjustPoint = Vec2(-visibleSize.width * m_nCurPage, 0);

	//第二个参数设置时间，用多长时间来改变偏移量。
	this->m_scrollView->setContentOffsetInDuration(adjustPoint, 0.3f);
}

void GameScrollScene::menuStartCallback(cocos2d::Ref * pSender)
{
	auto menuItem = (MenuItem *)pSender;
	switch (menuItem->getTag())
	{
	case 1:
		Director::getInstance()->replaceScene(GameParentScene::createScene());
		break;
	case 2:
		Director::getInstance()->replaceScene(GameLevel2::createScene());
		break;
	default:
		break;
	}
}

void GameScrollScene::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(ReadyScene::createScene());
}
