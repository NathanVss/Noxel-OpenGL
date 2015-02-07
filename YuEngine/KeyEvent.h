#pragma once

#include <string>
#include "Input.h"
#include <iostream>

namespace YuEngine {


class KeyEvent
{
public:
	KeyEvent(void) {

	}
	KeyEvent(KeyName _keyName, Input* _input) {
		input = _input;
		keyName = _keyName;
		lastCheck = false;
		curCheck = false;
		checkFlag = false;
	}
	~KeyEvent(void) {

	}

	bool getEvent() {

		// IF CHECKFLAG = TRUE
		// Cur = last
		// last = cur


		// Si on est en checkFlag == true
		// Alors on est pass� dans if(!checkFlag) ( car apr�s on inverse checkFlag
		// Donc le lastCheck est en fait l'actuel ( update la plus r�cente )
		// Le but �tant d'avoir "cur" == true && last == false
		// On se d�brouille avec ces conditions :
		if(checkFlag) {
			return (!curCheck && lastCheck) && input->getKey(keyName);
		}
		return (!lastCheck && curCheck) && input->getKey(keyName); 

	}

	bool isReleased() {
		return (input->getKey(keyName) == false);
	}

	void update() {
		if(!checkFlag) {
			lastCheck = input->getKey(keyName);
			checkFlag = true;
		} else {
			
			curCheck = input->getKey(keyName);
			checkFlag = false;
		}
	}

private:
	KeyName keyName;
	Input* input;

	bool lastCheck;
	bool curCheck;
	bool checkFlag;
};


}

