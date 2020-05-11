#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
//#include "audio/include/SimpleAudioEngine.h"

#include "Core.h"
#include "Specification.h"

//using namespace CocosDenshion;


class GameSettingsMenu : public cocos2d::Layer {
private:
	Core* _core = Core::sharedCore();
	//SimpleAudioEngine* _audioEngine = SimpleAudioEngine::getInstance();
	cocos2d::ui::Slider* _sliderSound = nullptr;
	cocos2d::ui::Slider* _sliderMusic = nullptr;
	int _musicID = 0;
	float _soundVolume = 0.0f;
	float _musicVolume = 0.0f;

public:
	static cocos2d::Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(GameSettingsMenu);
};
