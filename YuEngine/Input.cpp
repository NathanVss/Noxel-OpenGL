#include "Input.h"
namespace YuEngine {


Input::Input(void){

	this->mouseX = 0;
	this->mouseY = 0;
	this->mouseRelX = 0;
	this->mouseRelY = 0;
	this->SdlEvent = new SDL_Event();

	for(int i = 0; i< SDL_NUM_SCANCODES; i++) {
		this->keys[i] = false;
	}
	for(int i = 0; i < 8; i++){
		this->mouseKeys[i] = false;
	}

}
void Input::update() {

	this->mouseRelX = 0;
	this->mouseRelY = 0;

	while(SDL_PollEvent(this->SdlEvent)) {

		switch(this->SdlEvent->type) {

			case SDL_KEYDOWN:
				this->keys[this->SdlEvent->key.keysym.scancode] = true;
			break;

			case SDL_KEYUP:
				this->keys[this->SdlEvent->key.keysym.scancode] = false;
			break;

			case SDL_MOUSEBUTTONDOWN:
				this->mouseKeys[this->SdlEvent->button.button] = true;
			break;

			case SDL_MOUSEBUTTONUP:
				this->mouseKeys[this->SdlEvent->button.button] = false;
			break;

			case SDL_MOUSEMOTION:
				this->mouseRelX = this->SdlEvent->motion.xrel;
				this->mouseRelY = this->SdlEvent->motion.yrel;
				this->mouseX = this->SdlEvent->motion.x;
				this->mouseY = this->SdlEvent->motion.y;
			break;

			case SDL_WINDOWEVENT:
				if(this->SdlEvent->window.event == SDL_WINDOWEVENT_CLOSE) {

				}
			break;

			default:
			break;

		}

	}

}


Input::~Input(void){

}

}