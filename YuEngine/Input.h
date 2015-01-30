#pragma once

#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include "Object.h"

namespace YuEngine {

class Input : public Object
{
public:
	Input(void);
	~Input(void);
	void update();

	bool getKeyQ();
	bool getKeyUp();
	bool getKeyDown();
	bool getKeyLeft();
	bool getKeyRight();
	bool getKey0();
	bool getKey1();
	bool getKey2();
	bool getKey3();
	bool getKey4();
	bool getKey5();
	bool getKey6();
	bool getKey7();
	bool getKey8();
	bool getKey9();
	bool getKeyG();
	bool getKeyI();
	bool getKeyEnter();
	bool getKeyBackSpace();
	bool getKeyRightSlash();
	bool getKeyO();
	bool getKeyD();
	bool getKeyT();
	bool getKeyN();
	bool getKeyLeftShift();

	bool getKeyZ() {
		return keyZ;
	}
	bool getKeyS() {
		return keyS;
	}
	bool getKeyA() {
		return keyA;
	}
	bool getKeyE() {
		return keyE;
	}

	bool getLeftClick() { return mouseKeys[SDL_BUTTON_LEFT]; }
	bool getKeySpace() { return this->keys[SDL_SCANCODE_SPACE]; }
	int getMouseX() { return this->mouseX; }
	int getMouseY() { return this->mouseY; }
	int getRelMouseX() { return this->mouseRelX; } 
	int getRelMouseY() { return this->mouseRelY; }

private:
	SDL_Event* SdlEvent;
	bool keys[SDL_NUM_SCANCODES];
	bool mouseKeys[8];

	bool keyRightSlash;
	bool keyLeftShift;
	bool keyZ;
	bool keyS;
	bool keyA;
	bool keyE;

	bool keyT;
	bool keyO;
	bool keyD;
	bool keyN;
	bool keyEnter;
	bool keyBackSpace;
	bool keyQ;
	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;
	bool keyG;
	bool key0;
	bool key1;
	bool key2;
	bool key3;
	bool key4;
	bool key5;
	bool key6;
	bool key7;
	bool key8;
	bool key9;
	bool keyI;

	int mouseX;
	int mouseY;
	int mouseRelX;
	int mouseRelY;
};

}