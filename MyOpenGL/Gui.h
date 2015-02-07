#pragma once

#include "Object.h"
#include <YuEngine\Input.h>
#include <YuEngine\KeyEvent.h>
#include <YuEngine\Vertex.h>

class Gui : public Object
{


protected:
	float height;
	float width;
	float relX;
	float relY;
	float absX;
	float absY;
	int id;
	bool destroy;
	bool display;
	bool focus;

	float depth;

	YuEngine::KeyName closingKey;
	YuEngine::KeyName displayingKey;
	YuEngine::KeyEvent closingEvent;
	YuEngine::KeyEvent displayingEvent;


	YuEngine::Color color;

public:
	Gui(void);
	Gui(int relX, int relY, YuEngine::KeyName _keyName, YuEngine::KeyName _displayingKey);
	~Gui(void);


	bool hasFocus();
	virtual void render() = 0;

	void baseInit();
	virtual void init() = 0;

	void baseUpdate();
	virtual void update() = 0;
	virtual void switchDisplayState();






	void setDepth(float _depth) {
		depth = _depth;
	}
	float getDepth() {
		return depth;
	}

	void setId(int _id) {
		id = _id;
	}
	int getId() {
		return id;
	}

	bool getDestroy() {
		return destroy;
	}

	bool getDisplay() {
		return display;
	}
	void setDisplay(bool flag) {
		display = flag;
	}

	float getRelX() {
		return relX;
	}
	float getRelY() {
		return relY;
	}
	float getWidth() {
		return width;
	}
	float getHeight() {
		return height;
	}

	bool getFocus() {
		return focus;
	}
	void setFocus(bool flag) {
		focus = flag;
	}

};

