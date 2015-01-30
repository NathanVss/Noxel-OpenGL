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

	keyQ = false;
	keyUp = false;
	keyDown = false;
	keyLeft = false;
	keyRight = false;
	keyG = false;
	key0 = false;
	key1 = false;
	key2 = false;
	key3 = false;
	key4 = false;
	key5 = false;
	key6 = false;
	key7 = false;
	key8 = false;
	key9 = false;
	keyI = false;
	keyEnter = false;
	keyBackSpace = false;
	keyRightSlash = false;
	keyA = false;
	keyZ = false;
	keyE = false;
	keyS = false;

	keyG = false;
	keyO = false;
	keyD = false;
	keyT = false;
	keyN = false;
	keyLeftShift = false;

}
void Input::update() {

	this->mouseRelX = 0;
	this->mouseRelY = 0;

	while(SDL_PollEvent(this->SdlEvent)) {

		switch(SdlEvent->type) {

			case SDL_KEYDOWN:
				if(SdlEvent->key.keysym.sym == SDLK_UP) {
					keyUp = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_DOWN) {
					keyDown = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_LEFT) {
					keyLeft = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_RIGHT) {
					keyRight = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_g) {
					keyG = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_0) {
					key0 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_1) {
					key1 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_2) {
					key2 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_3) {
					key3 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_4) {
					key4 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_5) {
					key5 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_6) {
					key6 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_7) {
					key7 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_8) {
					key8 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_9) {
					key9 = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_i) {
					keyI = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_RETURN) {
					keyEnter = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_BACKSPACE) {
					keyBackSpace = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_o) {
					keyO = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_d) {
					keyD = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_PERIOD && keyLeftShift) {
					keyRightSlash = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_LSHIFT) {
					keyLeftShift = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_t) {
					keyT = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_n) {
					keyN = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_z) {
					keyZ = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_s) {
					keyS = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_a) {
					keyA = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_e) {
					keyE = true;
				}				
				if(SdlEvent->key.keysym.sym == SDLK_q) {
					keyQ = true;
				}
			break;

			case SDL_KEYUP:
				if(SdlEvent->key.keysym.sym == SDLK_UP) {
					keyUp = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_DOWN) {
					keyDown = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_LEFT) {
					keyLeft = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_RIGHT) {
					keyRight = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_g) {
					keyG = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_0) {
					key0 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_1) {
					key1 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_2) {
					key2 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_3) {
					key3 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_4) {
					key4 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_5) {
					key5 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_6) {
					key6 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_7) {
					key7 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_8) {
					key8 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_9) {
					key9 = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_i) {
					keyI = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_RETURN) {
					keyEnter = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_BACKSPACE) {
					keyBackSpace = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_o) {
					keyO = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_d) {
					keyD = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_PERIOD) {
					keyRightSlash = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_LSHIFT) {
					keyLeftShift = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_t) {
					keyT = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_n) {
					keyN = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_z) {
					keyZ = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_s) {
					keyS = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_a) {
					keyA = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_e) {
					keyE = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_q) {
					keyQ = false;
				}
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

bool Input::getKeyN() {
	return this->keyN;
}
bool Input::getKeyT() {
	return this->keyT;
}

bool Input::getKeyLeftShift() {
	return this->keyLeftShift;
}

bool Input::getKeyRightSlash() {
	return this->keyRightSlash;
}
bool Input::getKeyO() {
	return this->keyO;
}
bool Input::getKeyD() {
	return this->keyD;
}

bool Input::getKeyBackSpace() {
	return this->keyBackSpace;
}

bool Input::getKeyEnter() {
	return this->keyEnter;
}

bool Input::getKeyI() {
	return this->keyI;
}

bool Input::getKey0() {
	return this->key0;
}
bool Input::getKey1() {
	return this->key1;
}
bool Input::getKey2() {
	return this->key2;
}
bool Input::getKey3() {
	return this->key3;
}
bool Input::getKey4() {
	return this->key4;
}

bool Input::getKey5() {
	return this->key5;
}
bool Input::getKey6() {
	return this->key6;
}
bool Input::getKey7() {
	return this->key7;
}
bool Input::getKey8() {
	return this->key8;
}
bool Input::getKey9() {
	return this->key9;
}

bool Input::getKeyG() {
	return this->keyG;
}

bool Input::getKeyQ() {
	return this->keyQ;
}

bool Input::getKeyUp() {
	return this->keyUp;
}

bool Input::getKeyDown() {
	return this->keyDown;
}

bool Input::getKeyLeft() {
	return this->keyLeft;
}

bool Input::getKeyRight() {
	return this->keyRight;
}


}