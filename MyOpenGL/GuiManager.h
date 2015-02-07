#pragma once
#include "Object.h"
#include <vector>

class Gui;

class GuiManager : public Object
{
public:
	GuiManager(void);
	~GuiManager(void);


	void handleGui(Gui* g, bool display);
	void update();
	void render();

private:
	std::vector<Gui*> guis;
	int idsCounter;
};

