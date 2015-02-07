#pragma once

#include "Object.h"
#include <YuEngine\EventTimer.h>
#include <YuEngine\WritingHandler.h>
#include <YuEngine\KeyEvent.h>
#include <vector>
#include <string>

class GameConsole : public Object
{
private:
	bool display;
	YuEngine::EventTimer displayTimer;
	YuEngine::EventTimer displayTextBarTimer;
	YuEngine::EventTimer justOpenedTimer;


	YuEngine::WritingHandler writingHandler;
	YuEngine::KeyEvent displayingEvent;

	float width;
	float height;
	float x;
	float y;
	float letterSize;
	int displayEntriesNbr;
	bool justOpened;

	std::vector<std::string> entries;

public:
	GameConsole(void);
	~GameConsole(void);
	void init();

	void handleTyping();
	bool isTyping();
	void newEntry(std::string);
	void submitEntry();
	void render();
	void update();


};

