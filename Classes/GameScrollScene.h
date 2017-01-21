#ifndef __GAME_LEVEL_SCENE_H__
#define __GAME_LEVEL_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <math.h>

#include "ReadyScene.h"
#include "GameParentScene.h"

/*��������ʵ�ֹؿ�����ѡ��Ч��������GameSelectScene�е���*/

class GameScrollScene : public cocos2d::Layer
{
private:
	cocos2d::extension::ScrollView *m_scrollView;

	//������λ��
	cocos2d::Vec2 m_touchPoint;

	//ScrollView��ƫ����
	cocos2d::Vec2 m_offsetPoint;

	//��ǰΪ�ڼ���
	int m_nCurPage;

	/*cocos2d::Vector<int> tagNum;*/
public:
	virtual bool init();
	CREATE_FUNC(GameScrollScene);

	//�����¼�����غ���
	bool touchBegin(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void touchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);

	//У��ؿ�λ�ã�ʹ��λ����Ļ����
	void checkScrollView(float offset);

	//��ת����Ϸ�Ļص�����
	void menuStartCallback(cocos2d::Ref *pSender);

	void menuBackCallback(cocos2d::Ref *pSender);
};

#endif // !__GAME_LEVEL_SCENE_H__

