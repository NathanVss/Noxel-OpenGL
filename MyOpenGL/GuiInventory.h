#pragma once

#include "Gui.h"

#include <YuEngine\EventTimer.h>

class GuiInventory : public Gui
{
public:
	GuiInventory(float relX, float relY);
	~GuiInventory(void);

	virtual void render();
	virtual void update();
	virtual void init();

private:
	YuEngine::EventTimer displayTimer;
};

