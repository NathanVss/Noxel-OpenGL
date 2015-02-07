#include "WritingHandler.h"

namespace YuEngine {

WritingHandler::WritingHandler(void){
}

WritingHandler::WritingHandler(Input* _input) {
	input = _input;
	letterTimer = EventTimer(10);
	lastLetter = '£';
}

WritingHandler::~WritingHandler(void){
}

void WritingHandler::empty() {
	typingContent.clear();
}

void WritingHandler::setTypingContent(std::string _new) {
	std::vector<char>  _newVec;
	for(int i = 0; i < _new.size(); i++) {
		_newVec.push_back(_new[i]);
	}
	typingContent = _newVec;
}


void WritingHandler::handle() {

	letterTimer.update();
	char curLetter;
	bool typed = false;
	bool backSpacing = false;

	if(input->getKeyRightSlash()) { typed = true; curLetter = '/'; }
	if(input->getKeyA()) { typed = true; curLetter = 'a'; }
	if(input->getKeyB()) { typed = true; curLetter = 'b'; }
	if(input->getKeyC()) { typed = true; curLetter = 'c'; }
	if(input->getKeyD()) { typed = true; curLetter = 'd'; }
	if(input->getKeyE()) { typed = true; curLetter = 'e'; }
	if(input->getKeyF()) { typed = true; curLetter = 'f'; }
	if(input->getKeyG()) { typed = true; curLetter = 'g'; }
	if(input->getKeyH()) { typed = true; curLetter = 'h'; }
	if(input->getKeyI()) { typed = true; curLetter = 'i'; }
	if(input->getKeyJ()) { typed = true; curLetter = 'j'; }
	if(input->getKeyK()) { typed = true; curLetter = 'k'; }
	if(input->getKeyL()) { typed = true; curLetter = 'l'; }
	if(input->getKeyM()) { typed = true; curLetter = 'm'; }
	if(input->getKeyN()) { typed = true; curLetter = 'n'; }
	if(input->getKeyO()) { typed = true; curLetter = 'o'; }
	if(input->getKeyP()) { typed = true; curLetter = 'p'; }
	if(input->getKeyQ()) { typed = true; curLetter = 'q'; }
	if(input->getKeyR()) { typed = true; curLetter = 'r'; }
	if(input->getKeyS()) { typed = true; curLetter = 's'; }
	if(input->getKeyT()) { typed = true; curLetter = 't'; }
	if(input->getKeyU()) { typed = true; curLetter = 'u'; }
	if(input->getKeyV()) { typed = true; curLetter = 'v'; }
	if(input->getKeyW()) { typed = true; curLetter = 'w'; }
	if(input->getKeyX()) { typed = true; curLetter = 'x'; }
	if(input->getKeyY()) { typed = true; curLetter = 'y'; }
	if(input->getKeyZ()) { typed = true; curLetter = 'z'; }
	if(input->getKeySpace()) { typed = true; curLetter = ' '; }
	if(input->getKey0()) { typed = true; curLetter = '0'; }
	if(input->getKey1()) { typed = true; curLetter = '1'; }
	if(input->getKey2()) { typed = true; curLetter = '2'; }
	if(input->getKey3()) { typed = true; curLetter = '3'; }
	if(input->getKey4()) { typed = true; curLetter = '4'; }
	if(input->getKey5()) { typed = true; curLetter = '5'; }
	if(input->getKey6()) { typed = true; curLetter = '6'; }
	if(input->getKey7()) { typed = true; curLetter = '7'; }
	if(input->getKey8()) { typed = true; curLetter = '8'; }
	if(input->getKey9()) { typed = true; curLetter = '9'; }
	if(input->getKeyDot()) { typed = true; curLetter = '.'; }

	if(input->getKeyBackSpace()) {
		backSpacing = true;
	}
	if(!typed && !backSpacing) {
		letterTimer.setOver();
	}

	// Le principe est de :
	// Soit l'utilisateur appuie sur la même touche entre deux frame est dans ce cas là on ré affiche la même
	// Lettre ssi isOver()
	// Soit l'utilisateur appuie sur une lettre différente entre deux frame et on ne tiens pas compte du temps
	// .reset dans les deux cas car il peut se passer qu'on apppuie sur la même lettre entre deux frames et passer dans ces
	// deux frames dans cette condition
	if((typed && curLetter != lastLetter) || (letterTimer.isOver() && typed)) {
		typingContent.push_back(curLetter);
		lastLetter = curLetter;
		letterTimer.reset();
	} else if(backSpacing && letterTimer.isOver()) {

		typingContent.pop_back();
		letterTimer.reset();
	}


}



std::string WritingHandler::getTypingContent() {
	std::string content("");
	for(int i = 0; i < typingContent.size(); i++) {
		content = content + typingContent[i];
	}
	return content;
}



}