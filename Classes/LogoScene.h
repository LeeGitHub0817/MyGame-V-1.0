#ifndef __LOGO_SCENE_H__
#define __LOGO_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "ReadyScene.h"
#include "SimpleAudioEngine.h"

class LogoScene : public cocos2d::Layer
{
private:
	int m_loadNum;
	std::thread *_preLoadAudio;  //��ƵԤ�����߳�
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LogoScene);

	void loadTexture(cocos2d::Texture2D *texture); //Ԥ��������
	void loadAudio(); //Ԥ��������
	void delayCall(float dt); //�ӳ���ת����һ������
	virtual void onExit(); 
};

#endif // __LOGO_SCENE_H__

