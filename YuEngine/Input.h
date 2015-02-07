#pragma once

#include <Dependecies\SDL2-2.0.3\include\SDL.h>
#include "Object.h"
#include <map>

namespace YuEngine {


enum class KeyName {
	none,
	mouseLeft,
	up,
	down,
	left,
	right,
	top0,
	top1,
	top2,
	top3,
	top4,
	top5,
	top6,
	top7,
	top8,
	top9,
	enter,
	backspace,
	rightSlash,
	leftShift,
	space,
	dot,
	escape,
	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z

};

class Input : public Object
{
public:
	Input(void);
	~Input(void);
	void update();

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

	bool getKeyEnter();
	bool getKeyBackSpace();
	bool getKeyRightSlash();
	bool getKeyLeftShift();

	bool getKeySpace() {
		return keySpace;
	}

	bool getKey(KeyName keyName) {
		return keyMap[keyName];
	}

	bool getKeyA() {
		return keyA;
	}
	bool getKeyB() {
		return keyB;
	}
	bool getKeyC() {
		return keyC;
	}
	bool getKeyD() {
		return keyD;
	}
	bool getKeyE() {
		return keyE;
	}
	bool getKeyF() {
		return keyF;
	}
	bool getKeyG() {
		return keyG;
	}
	bool getKeyH() {
		return keyH;
	}
	bool getKeyI() {
		return keyI;
	}
	bool getKeyJ() {
		return keyJ;
	}
	bool getKeyK() {
		return keyK;
	}
	bool getKeyL() {
		return keyL;
	}
	bool getKeyM() {
		return keyM;
	}
	bool getKeyN() {
		return keyN;
	}
	bool getKeyO() {
		return keyO;
	}
	bool getKeyP() {
		return keyP;
	}
	bool getKeyQ() {
		return keyQ;
	}
	bool getKeyR() {
		return keyR;
	}
	bool getKeyS() {
		return keyS;
	}
	bool getKeyT() {
		return keyT;
	}
	bool getKeyU() {
		return keyU;
	}
	bool getKeyV() {
		return keyV;
	}
	bool getKeyW() {
		return keyW;
	}
	bool getKeyX() {
		return keyX;
	}
	bool getKeyY() {
		return keyY;
	}
	bool getKeyZ() {
		return keyZ;
	}

	bool getKeyDot() {
		return keyDot;
	}

	bool getKeyEscape() {
		return keyEscape;
	}

	bool getLeftClick() { return mouseKeys[SDL_BUTTON_LEFT]; }
	bool getRightClick() { return mouseKeys[SDL_BUTTON_RIGHT]; }
	int getMouseX() { return this->mouseX; }
	int getMouseY() { return this->mouseY; }
	int getRelMouseX() { return this->mouseRelX; } 
	int getRelMouseY() { return this->mouseRelY; }

private:
	std::map<KeyName, bool> keyMap;
	SDL_Event* SdlEvent;
	bool mouseKeys[8];

	bool keyRightSlash;
	bool keyLeftShift;
	bool keySpace;

	bool keyDot;

	bool keyEscape;

	bool keyA;
	bool keyB;
	bool keyC;
	bool keyD;
	bool keyE; /* Done */
	bool keyF;
	bool keyG; //
	bool keyH;
	bool keyI;
	bool keyJ;
	bool keyK;
	bool keyL;
	bool keyM;
	bool keyN; //
	bool keyO; //
	bool keyP;
	bool keyQ; //
	bool keyR;
	bool keyS; //
	bool keyT;
	bool keyU;
	bool keyV;
	bool keyW;
	bool keyX;
	bool keyY;
	bool keyZ;

	bool keyEnter;
	bool keyBackSpace;
	bool keyUp;
	bool keyDown;
	bool keyLeft;
	bool keyRight;
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

	int mouseX;
	int mouseY;
	int mouseRelX;
	int mouseRelY;
};

}