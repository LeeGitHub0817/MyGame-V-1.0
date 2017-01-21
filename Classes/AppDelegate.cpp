#include "AppDelegate.h"

USING_NS_CC;
using namespace CocosDenshion;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
static cocos2d::Size mineResolutionSize = cocos2d::Size(720, 1280);
static cocos2d::Size myResolutionSize = cocos2d::Size(360, 640);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {

	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("MyGame", Rect(0, 0, myResolutionSize.width, myResolutionSize.height));
#else
		glview = GLViewImpl::create("MyGame");
#endif
		director->setOpenGLView(glview);
	}               

	glview->setDesignResolutionSize(mineResolutionSize.width, mineResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
	Size frameSize = glview->getFrameSize();

	//director->setDisplayStats(true);

	//director->setAnimationInterval(1.0f / 60.0f);

	FileUtils::getInstance()->addSearchPath("res");

    auto scene = LogoScene::createScene();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
