#pragma once

#include "AudioEngine.h"
#include <iostream>

using namespace std;
USING_NS_CC;
class AudioManager
{
private:
	AudioManager();
	~AudioManager();

public:
	static AudioManager* getInstance();
	int index;
	int thunder;
	int set_Effect(string a);	
};

