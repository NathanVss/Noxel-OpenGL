#pragma once

#include "Object.h"
#include <YuEngine\EventTimer.h>
#include <vector>
#include <string>

class GameConsole : public Object
{
private:
	bool display;
	YuEngine::EventTimer displayTimer;
	YuEngine::EventTimer letterTimer;


	float width;
	float height;
	float x;
	float y;

	std::vector<char> typingContent;
	std::vector<std::string> entries;

public:
	GameConsole(void);
	~GameConsole(void);

	void handleTyping();
	void render();
	void update();


};

