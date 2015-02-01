#pragma once

#include <string>


class FocusManager
{
public:
	FocusManager(void);
	~FocusManager(void);

	void setPlayerFocus() {
		curFocus = std::string("player");
	}
	void setGameConsoleFocus() {
		curFocus = std::string("gameConsole");
	}

	bool getPlayerFocus() {
		return curFocus == "player";
	}
	bool getGameConsoleFocus() {
		return curFocus == "gameConsole";
	}

private:
	std::string curFocus;
};

