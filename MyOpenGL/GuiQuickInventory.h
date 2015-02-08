#pragma once
#include "Gui.h"

class QuickInventory;

class GuiQuickInventory : public Gui
{
public:
	GuiQuickInventory(Container* c);
	GuiQuickInventory();
	~GuiQuickInventory(void);

	virtual void render();
	virtual void update();

	void setQuickInventory(QuickInventory* q) {
		quickInventory = q;
	}

private:
	QuickInventory* quickInventory;
	float slotSize;
	float marginBetweenSlots;

};

