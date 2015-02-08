#include "Input.h"
#include <iostream>
namespace YuEngine {


Input::Input(void){

	this->mouseX = 0;
	this->mouseY = 0;
	this->mouseRelX = 0;
	this->mouseRelY = 0;
	this->SdlEvent = new SDL_Event();

	for(int i = 0; i < 8; i++){
		this->mouseKeys[i] = false;
	}

	mouseScrollY = 0;

	keyMap[KeyName::mouseLeft] = false;
	keyMap[KeyName::mouseRight] = false;
	keyMap[KeyName::up] = false;
	keyMap[KeyName::down] = false;
	keyMap[KeyName::left] = false;
	keyMap[KeyName::right] = false;
	keyMap[KeyName::top0] = false;
	keyMap[KeyName::top1] = false;
	keyMap[KeyName::top2] = false;
	keyMap[KeyName::top3] = false;
	keyMap[KeyName::top4] = false;
	keyMap[KeyName::top5] = false;
	keyMap[KeyName::top6] = false;
	keyMap[KeyName::top7] = false;
	keyMap[KeyName::top8] = false;
	keyMap[KeyName::top9] = false;
	keyMap[KeyName::enter] = false;
	keyMap[KeyName::backspace] = false;
	keyMap[KeyName::rightSlash] = false;
	keyMap[KeyName::leftShift] = false;
	keyMap[KeyName::space] = false;
	keyMap[KeyName::dot] = false;
	keyMap[KeyName::a] = false;
	keyMap[KeyName::b] = false;
	keyMap[KeyName::c] = false;
	keyMap[KeyName::d] = false;
	keyMap[KeyName::e] = false;
	keyMap[KeyName::f] = false;
	keyMap[KeyName::g] = false;
	keyMap[KeyName::h] = false;
	keyMap[KeyName::i] = false;
	keyMap[KeyName::j] = false;
	keyMap[KeyName::k] = false;
	keyMap[KeyName::l] = false;
	keyMap[KeyName::m] = false;
	keyMap[KeyName::n] = false;
	keyMap[KeyName::o] = false;
	keyMap[KeyName::p] = false;
	keyMap[KeyName::q] = false;
	keyMap[KeyName::r] = false;
	keyMap[KeyName::s] = false;
	keyMap[KeyName::t] = false;
	keyMap[KeyName::u] = false;
	keyMap[KeyName::v] = false;
	keyMap[KeyName::w] = false;
	keyMap[KeyName::x] = false;
	keyMap[KeyName::y] = false;
	keyMap[KeyName::z] = false;

	keyUp = false;
	keyDown = false;
	keyLeft = false;
	keyRight = false;
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
	keyEnter = false;
	keyBackSpace = false;
	keyRightSlash = false;
	keyLeftShift = false;
	keySpace = false;
	keyEscape = false;

	keyA = false;
	keyB = false;
	keyC = false;
	keyD = false;
	keyE = false;
	keyF = false;
	keyG = false;
	keyH = false;
	keyI = false;
	keyJ = false;
	keyK = false;
	keyL = false;
	keyM = false;
	keyN = false;
	keyO = false;
	keyP = false;
	keyQ = false;
	keyR = false;
	keyS = false;
	keyT = false;
	keyU = false;
	keyV = false;
	keyW = false;
	keyX = false;
	keyY = false;
	keyZ = false;


	keyDot = false;

}
void Input::update() {

	this->mouseRelX = 0;
	this->mouseRelY = 0;
	bool hasMouseWhelled = false;

	while(SDL_PollEvent(this->SdlEvent)) {

		switch(SdlEvent->type) {

			case SDL_KEYDOWN:
				if(SdlEvent->key.keysym.sym == SDLK_UP) {
					keyUp = true;
					keyMap[KeyName::up] = true;
				}
				if(SdlEvent->key.keysym.sym == SDLK_DOWN) {
					keyDown = true;
					keyMap[KeyName::down] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_LEFT) {
					keyLeft = true;
					keyMap[KeyName::left] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_RIGHT) {
					keyRight = true;
					keyMap[KeyName::right] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_0) {
					key0 = true;
					keyMap[KeyName::up] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_1) {
					key1 = true;
					keyMap[KeyName::top1] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_2) {
					key2 = true;
					keyMap[KeyName::top2] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_3) {
					key3 = true;
					keyMap[KeyName::top3] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_4) {
					key4 = true;
					keyMap[KeyName::top4] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_5) {
					key5 = true;
					keyMap[KeyName::top5] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_6) {
					key6 = true;
					keyMap[KeyName::top6] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_7) {
					key7 = true;
					keyMap[KeyName::top7] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_8) {
					key8 = true;
					keyMap[KeyName::top8] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_9) {
					key9 = true;
					keyMap[KeyName::top9] = true;

				}

				if(SdlEvent->key.keysym.sym == SDLK_RETURN) {
					keyEnter = true;
					keyMap[KeyName::enter] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_BACKSPACE) {
					keyBackSpace = true;
					keyMap[KeyName::backspace] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_SPACE) {
					keySpace = true;
					keyMap[KeyName::space] = true;

				}

				if(SdlEvent->key.keysym.sym == SDLK_LSHIFT) {
					keyLeftShift = true;
					keyMap[KeyName::leftShift] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_COLON && keyLeftShift) {

					keyRightSlash = true;
					keyMap[KeyName::rightSlash] = true;

				}


				if(SdlEvent->key.keysym.sym == SDLK_a) {
					keyA = true;
					keyMap[KeyName::a] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_b) {
					keyB = true;
					keyMap[KeyName::b] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_c) {
					keyC = true;
					keyMap[KeyName::c] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_d) {
					keyD = true;
					keyMap[KeyName::d] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_e) {
					keyE = true;
					keyMap[KeyName::e] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_f) {
					keyF = true;
					keyMap[KeyName::f] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_g) {
					keyG = true;
					keyMap[KeyName::g] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_h) {
					keyH = true;
					keyMap[KeyName::h] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_i) {
					keyI = true;
					keyMap[KeyName::i] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_j) {
					keyJ = true;
					keyMap[KeyName::j] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_k) {
					keyK = true;
					keyMap[KeyName::k] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_l) {
					keyL = true;
					keyMap[KeyName::l] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_m) {
					keyM = true;
					keyMap[KeyName::m] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_n) {

					keyN = true;
					keyMap[KeyName::n] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_o) {
					keyO = true;
					keyMap[KeyName::o] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_p) {
					keyP = true;
					keyMap[KeyName::p] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_q) {
					keyQ = true;
					keyMap[KeyName::q] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_r) {
					keyR = true;
					keyMap[KeyName::r] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_s) {
					keyS = true;
					keyMap[KeyName::s] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_t) {
					keyT = true;
					keyMap[KeyName::t] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_u) {
					keyU = true;
					keyMap[KeyName::u] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_v) {
					keyV = true;
					keyMap[KeyName::v] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_w) {
					keyW = true;
					keyMap[KeyName::w] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_x) {
					keyX = true;
					keyMap[KeyName::x] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_y) {
					keyY = true;
					keyMap[KeyName::y] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_z) {
					keyZ = true;
					keyMap[KeyName::z] = true;

				}

				if(SdlEvent->key.keysym.sym == SDLK_SEMICOLON && keyLeftShift) {
					keyDot = true;
					keyMap[KeyName::dot] = true;

				}
				if(SdlEvent->key.keysym.sym == SDLK_ESCAPE) {
					keyEscape = true;
					keyMap[KeyName::escape] = true;

				}

			break;

			case SDL_KEYUP:
				if(SdlEvent->key.keysym.sym == SDLK_UP) {
					keyUp = false;
					keyMap[KeyName::up] = false;
				}
				if(SdlEvent->key.keysym.sym == SDLK_DOWN) {
					keyDown = false;
					keyMap[KeyName::down] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_LEFT) {
					keyLeft = false;
					keyMap[KeyName::left] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_RIGHT) {
					keyRight = false;
					keyMap[KeyName::right] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_0) {
					key0 = false;
					keyMap[KeyName::up] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_1) {
					key1 = false;
					keyMap[KeyName::top1] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_2) {
					key2 = false;
					keyMap[KeyName::top2] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_3) {
					key3 = false;
					keyMap[KeyName::top3] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_4) {
					key4 = false;
					keyMap[KeyName::top4] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_5) {
					key5 = false;
					keyMap[KeyName::top5] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_6) {
					key6 = false;
					keyMap[KeyName::top6] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_7) {
					key7 = false;
					keyMap[KeyName::top7] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_8) {
					key8 = false;
					keyMap[KeyName::top8] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_9) {
					key9 = false;
					keyMap[KeyName::top9] = false;

				}

				if(SdlEvent->key.keysym.sym == SDLK_RETURN) {
					keyEnter = false;
					keyMap[KeyName::enter] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_BACKSPACE) {
					keyBackSpace = false;
					keyMap[KeyName::backspace] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_SPACE) {
					keySpace = false;
					keyMap[KeyName::space] = false;

				}

				if(SdlEvent->key.keysym.sym == SDLK_LSHIFT) {
					keyLeftShift = false;
					keyMap[KeyName::leftShift] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_COLON) {

					keyRightSlash = false;
					keyMap[KeyName::rightSlash] = false;

				}


				if(SdlEvent->key.keysym.sym == SDLK_a) {
					keyA = false;
					keyMap[KeyName::a] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_b) {
					keyB = false;
					keyMap[KeyName::b] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_c) {
					keyC = false;
					keyMap[KeyName::c] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_d) {
					keyD = false;
					keyMap[KeyName::d] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_e) {
					keyE = false;
					keyMap[KeyName::e] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_f) {
					keyF = false;
					keyMap[KeyName::f] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_g) {
					keyG = false;
					keyMap[KeyName::g] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_h) {
					keyH = false;
					keyMap[KeyName::h] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_i) {
					keyI = false;
					keyMap[KeyName::i] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_j) {
					keyJ = false;
					keyMap[KeyName::j] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_k) {
					keyK = false;
					keyMap[KeyName::k] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_l) {
					keyL = false;
					keyMap[KeyName::l] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_m) {
					keyM = false;
					keyMap[KeyName::m] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_n) {

					keyN = false;
					keyMap[KeyName::n] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_o) {
					keyO = false;
					keyMap[KeyName::o] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_p) {
					keyP = false;
					keyMap[KeyName::p] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_q) {
					keyQ = false;
					keyMap[KeyName::q] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_r) {
					keyR = false;
					keyMap[KeyName::r] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_s) {
					keyS = false;
					keyMap[KeyName::s] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_t) {
					keyT = false;
					keyMap[KeyName::t] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_u) {
					keyU = false;
					keyMap[KeyName::u] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_v) {
					keyV = false;
					keyMap[KeyName::v] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_w) {
					keyW = false;
					keyMap[KeyName::w] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_x) {
					keyX = false;
					keyMap[KeyName::x] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_y) {
					keyY = false;
					keyMap[KeyName::y] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_z) {
					keyZ = false;
					keyMap[KeyName::z] = false;

				}

				if(SdlEvent->key.keysym.sym == SDLK_SEMICOLON) {
					keyDot = false;
					keyMap[KeyName::dot] = false;

				}
				if(SdlEvent->key.keysym.sym == SDLK_ESCAPE) {
					keyEscape = false;
					keyMap[KeyName::escape] = false;

				}

			
			break;

			case SDL_MOUSEBUTTONDOWN:
				this->mouseKeys[this->SdlEvent->button.button] = true;
				if(this->SdlEvent->button.button == SDL_BUTTON_LEFT) {
					keyMap[KeyName::mouseLeft] = true;
				}
				if(this->SdlEvent->button.button == SDL_BUTTON_RIGHT) {
					keyMap[KeyName::mouseRight] = true;
				}
			break;

			case SDL_MOUSEBUTTONUP:
				this->mouseKeys[this->SdlEvent->button.button] = false;
				if(this->SdlEvent->button.button == SDL_BUTTON_LEFT) {
					//std::cout << "NO LEFT CLICK" << std::endl;
					keyMap[KeyName::mouseLeft] = false;
				}
				if(this->SdlEvent->button.button == SDL_BUTTON_RIGHT) {
					keyMap[KeyName::mouseRight] = false;
				}
			break;

			case SDL_MOUSEWHEEL:
				hasMouseWhelled = true;
				mouseScrollY = SdlEvent->wheel.y;

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
	if(!hasMouseWhelled) {
		mouseScrollY = 0;
		
	}

}


Input::~Input(void){

}


bool Input::getKeyLeftShift() {
	return this->keyLeftShift;
}

bool Input::getKeyRightSlash() {
	return this->keyRightSlash;
}

bool Input::getKeyBackSpace() {
	return this->keyBackSpace;
}

bool Input::getKeyEnter() {
	return this->keyEnter;
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