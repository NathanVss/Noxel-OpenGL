#pragma once

#include "Input.h"
#include "EventTimer.h"
#include <vector>
#include <string>

namespace YuEngine {

class WritingHandler
{
public:
	WritingHandler(void);
	WritingHandler(Input* input);
	~WritingHandler(void);

	void handle();
	void empty();
	void setTypingContent(std::string _new);

	std::string getTypingContent();

private:
	Input* input;
	char lastLetter;
	EventTimer letterTimer;
	std::vector<char> typingContent;
};

}