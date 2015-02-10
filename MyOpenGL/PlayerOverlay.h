#pragma once

class GuiPlayerHealth;
class GuiQuickInventory;

class PlayerOverlay
{
private:
	GuiPlayerHealth* guiPlayerHealth;
	GuiQuickInventory* guiQuickInventory;

public:
	PlayerOverlay(void) {

	}
	~PlayerOverlay(void) {

	}

	void setGuiPlayerHealth(GuiPlayerHealth* g) {
		guiPlayerHealth = g;
	}
	void setGuiQuickInventory(GuiQuickInventory* g) {
		guiQuickInventory = g;
	}
	GuiPlayerHealth* getGuiPlayerHealth() {
		return guiPlayerHealth;
	}
	GuiQuickInventory* getGuiQuickInventory() {
		return guiQuickInventory;
	}
};

