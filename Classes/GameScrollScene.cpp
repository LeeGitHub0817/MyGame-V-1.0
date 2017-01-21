#include "GameScrollScene.h"

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

		//����ScrollViewΪ������Ļ��С
		ScrollView *scrollView = ScrollView::create(Size(winSize.width, winSize.height));

		//////����ScrollViewһЩ��ز���//////
		//���÷���Ч��
		scrollView->setBounceable(true);

		//��ê����Ϊ����
		scrollView->ignoreAnchorPointForPosition(false);
		scrollView->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

		//���û�������
		scrollView->setDirection(ScrollView::Direction::HORIZONTAL);

		//����һ��Layer����������ӵ�Layer�У�Ȼ�����layer��ӵ�scrollview��
		Layer *layer = Layer::create();
		for (int i = 1; i < 6; ++i)
		{
			//��ӱ���
			Sprite *sprite = Sprite::createWithSpriteFrameName("general_back11.png");
			sprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2) + Vec2(winSize.width * (i - 1), 0));
			//sprite->setContentSize(Size(400.0f, 400.0f));
			layer->addChild(sprite);

			//��ӵڼ���
			auto levelBoard = Sprite::createWithSpriteFrameName("general_level_title_bg.png");
			levelBoard->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y + sprite->getContentSize().height / 2));
			layer->addChild(levelBoard);

			__String *levelNum = __String::createWithFormat("Level %d", i);
			auto level = Label::createWithTTF(levelNum->getCString(), "fonts/Marker Felt.ttf", 28);
			level->setPosition(levelBoard->getPosition());
			layer->addChild(level);

			//��ӿ�ʼ��ť
			Sprite *menuItemStartNor = Sprite::createWithSpriteFrameName("start_end_btn_start_nor.png");
			Sprite *menuItemStartSel = Sprite::createWithSpriteFrameName("start_end_btn_start_sel.png");
			MenuItemSprite *menuItemStart = MenuItemSprite::create(menuItemStartNor, menuItemStartSel,
				CC_CALLBACK_1(GameScrollScene::menuStartCallback, this));
			menuItemStart->setPosition(Vec2(sprite->getPosition().x, sprite->getPosition().y - sprite->getContentSize().height / 2));
			menuItemStart->setTag(i);

			Menu *menu = Menu::create(menuItemStart, NULL);
			menu->setPosition(Vec2::ZERO);
			layer->addChild(menu);
		}

		//���ذ�ť
		auto backItemSpriteNor = Sprite::createWithSpriteFrameName("map_btn_back_nor.png");
		auto backItemSpriteSel = Sprite::createWithSpriteFrameName("map_btn_back_sel.png");
		auto backItem = MenuItemSprite::create(backItemSpriteNor,
			backItemSpriteSel,
			CC_CALLBACK_1(GameScrollScene::menuBackCallback, this));

		backItem->setPosition(Vec2(winSize.width - backItem->getContentSize().width / 2, backItem->getContentSize().height / 2));

		auto menu = Menu::create(backItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

		//����scrollView�������,�������������������ô�С
		scrollView->setContainer(layer);
		scrollView->setContentSize(Size(winSize.width * 5, winSize.height));

		//����scrollView��ǰ��Ĵ���
		scrollView->setTouchEnabled(false);

		//����scrollView�������ݵ�ƫ����
		scrollView->setContentOffset(Vec2(0.0f, 0.0f));
		this->addChild(scrollView);
		////Ҫ��ֵ����ΪscrollView�Ǿֲ��������������ִ�к���ͷš�
		this->m_scrollView = scrollView; 
		this->m_nCurPage = 0;

		bRet = true;

		//������Ӧ�Ĵ����¼�
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
	���µ���һ���ر�Ҫע�⣬��ҿ�����ע�͵����µ���
	�仰Ȼ�����г��򣬻ᷢ������������Ǻܿ�
	��ʱ�򲻻���ʲô���⣬��������������еĺܿ죬��
	����λ��ƫ�ƵľͲ�����ȷ�����µĴ������ǽ��������⵽
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
	//���ùؿ�����ָ�����ƶ�
	auto point = touch->getLocation();
	auto direction = point - this->m_touchPoint;

	//���ó�ֻ��X�᷽��ƫ��
	Vec2 spriteDirection = Vec2(direction.x + this->m_offsetPoint.x, 0);
	this->m_scrollView->setContentOffset(spriteDirection);
}

void GameScrollScene::touchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	//����������ʱ��ʹ�ؿ���ʾ����Ļ���м�
	auto endPoint = touch->getLocation();
	auto distance = endPoint.x - this->m_touchPoint.x;

	//��ָ�ƶ�����С��20�� ��ƫ������Ϊ0����
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
	//�����ؿ�������λ��
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//��ָ����ʱ��offset����0��ҳ���С����������
	if (offset < 0)
	{
		m_nCurPage++;
	}
	else if (offset > 0)
	{
		m_nCurPage--;
	}

	//�����������һҳ�����ұ�һҳ
	if (m_nCurPage < 0)
	{
		m_nCurPage = 0;
	}
	else if (m_nCurPage > 4)
	{
		m_nCurPage = 4;
	}
	auto adjustPoint = Vec2(-visibleSize.width * m_nCurPage, 0);

	//�ڶ�����������ʱ�䣬�ö೤ʱ�����ı�ƫ������
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
	default:
		break;
	}
}

void GameScrollScene::menuBackCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(ReadyScene::createScene());
}
