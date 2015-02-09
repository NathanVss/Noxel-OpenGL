#pragma once

#include "Gui.h"

class HealthBuffer;

class GuiPlayerHealth : public Gui
{
public:
	GuiPlayerHealth(Container* c);
	~GuiPlayerHealth(void);

	virtual void render();
	virtual void update();

	void setHealthBuffer(HealthBuffer* h) {
		healthBuffer = h;
	}

private:
	HealthBuffer* healthBuffer;
};

