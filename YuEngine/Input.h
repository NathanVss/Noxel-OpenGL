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

	bool getKeyZ() { return this->keys[SDL_SCANCODE_W]; }
	bool getKeyS() { return this->keys[SDL_SCANCODE_S]; }
	bool getKeyA() { return this->keys[SDL_SCANCODE_Q]; }
	bool getKeyQ() { return this->keys[SDL_SCANCODE_A]; }
	bool getKeyD() { return this->keys[SDL_SCANCODE_D]; }
	bool getKeyE() { return this->keys[SDL_SCANCODE_E]; }
	int getMouseX() { return this->mouseX; }
	int getMouseY() { return this->mouseY; }
	int getRelMouseX() { return this->mouseRelX; } 
	int getRelMouseY() { return this->mouseRelY; }

private:
	SDL_Event* SdlEvent;
	bool keys[SDL_NUM_SCANCODES];
	bool mouseKeys[8];

	int mouseX;
	int mouseY;
	int mouseRelX;
	int mouseRelY;
};

}