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
	YuEngine::EventTimer displayTextBarTimer;
	YuEngine::EventTimer justOpenedTimer;

	YuEngine::EventTimer letterTimer;


	float width;
	float height;
	float x;
	float y;
	float letterSize;
	int displayEntriesNbr;
	char lastLetter;
	bool justOpened;


	std::vector<char> typingContent;
	std::vector<std::string> entries;

public:
	GameConsole(void);
	~GameConsole(void);

	void handleTyping();
	bool isTyping();
	std::string getTypingContent();
	void newEntry(std::string);
	void submitEntry();
	void render();
	void update();


};

