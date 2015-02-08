#pragma once

#include "Object.h"
#include <YuEngine\EventTimer.h>
#include <YuEngine\WritingHandler.h>
#include <YuEngine\KeyEvent.h>
#include <vector>
#include <string>

#include "Gui.h"

class GameConsole : public Gui
{
private:
	YuEngine::EventTimer displayTextBarTimer;


	YuEngine::WritingHandler writingHandler;

	float letterSize;
	int displayEntriesNbr;
	bool justOpened;

	std::vector<std::string> entries;

public:
	GameConsole(Container* c);
	~GameConsole(void);

	void handleTyping();
	bool isTyping();
	void newEntry(std::string);
	void submitEntry();
	void render();
	void update();


};

