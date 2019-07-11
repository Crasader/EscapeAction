#include "AudioManager.h"
#include "GameManager.h"
static AudioManager* Audio_M = NULL;

AudioManager::AudioManager()
{
	experimental::AudioEngine::play2d("sound/background_rain.mp3", true);
	index = -1;
}

AudioManager::~AudioManager()
{
}

AudioManager * AudioManager::getInstance()
{
	if (Audio_M == NULL) {
		Audio_M = new AudioManager;
	}
	return Audio_M;
}

int AudioManager::set_Effect(string effect_name)
{
	if (effect_name == "sound/thunder.mp3")
	{
		thunder = experimental::AudioEngine::play2d(effect_name, false);
	}	
	else {
		experimental::AudioEngine::stop(index);
		index = experimental::AudioEngine::play2d(effect_name, true);
	}
	return index;
}
