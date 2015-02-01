#include "GameConsole.h"
#include "Container.h"
#include "Commander.h"
#include "FocusManager.h"
#include <YuEngine\Input.h>
#include <YuEngine\YuBoudingbox.h>
#include <YuEngine\Camera2D.h>
#include <YuEngine\GameRenderer.h>
#include <YuEngine\SpritesheetsManager.h>
#include <YuEngine\Spritesheet.h>
#include <YuEngine\FontRenderer.h>

GameConsole::GameConsole(void){
	displayTimer = YuEngine::EventTimer(1);
	letterTimer = YuEngine::EventTimer(10);
	displayTextBarTimer = YuEngine::EventTimer(60);
	justOpenedTimer = YuEngine::EventTimer(30);
	width = 600;
	height =300;
	display = false;
	letterSize = 2;
	displayEntriesNbr = 16;
	justOpened = false;
}


GameConsole::~GameConsole(void)
{
}

void GameConsole::update() {
	displayTimer.update();


	if(display) {
		letterTimer.update();
	}
	if(displayTimer.isOver()) {
		if(myContainer->getInput()->getKeyT()) {
			if(!display) {
				myContainer->getFocusManager()->setGameConsoleFocus();
				lastLetter = 't';
				display = true;
				justOpened = true;
			}
		}

		displayTimer.reset();
	}
	YuEngine::YuBoudingbox cameraBox = myContainer->getCamera()->getCameraBox();

	x = cameraBox.getX1() + cameraBox.getWidth() - width;
	y = cameraBox.getY1() - cameraBox.getHeight() + height;

	handleTyping();
}


void GameConsole::handleTyping() {
	if(!display) {
		return;
	}

	justOpenedTimer.update();
	if(justOpenedTimer.isOver() && justOpened) {
		justOpened = false;

		justOpenedTimer.reset();

	}


	auto input = myContainer->getInput();

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
	if(input->getKeyT() && !justOpened) { typed = true; curLetter = 't'; }
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
	if(input->getKeyUp()) {

		if(entries.size() > 0) {

			std::string lastEntry = entries[entries.size() - 1];
			std::vector<char> newTypingContent;
			for(int i = 0; i < lastEntry.size(); i++) {
				newTypingContent.push_back(lastEntry[i]);
			}
			typingContent = newTypingContent;
		}
	}

	if(input->getKeyEnter()) {
		submitEntry();
	}

	// Le principe est de :
	// Soit l'utilisateur appuie sur la même touche entre deux frame est dans ce cas là on ré affiche la même
	// Lettre ssi isOver()
	// Soit l'utilisateur appuie sur une lettre différente entre deux frame et on ne tiens pas compte du temps
	// .reset dans les deux cas car il peut se passer qu'on apppuie sur la même lettre entre deux frames et passer dans ces
	// deux frames dans cette condition
	if(!typed && !backSpacing) {
		letterTimer.setOver();
	}
	if((typed && curLetter != lastLetter) || (letterTimer.isOver() && typed)) {
		typingContent.push_back(curLetter);
		lastLetter = curLetter;
		letterTimer.reset();
	} else if(backSpacing && letterTimer.isOver()) {
		typingContent.pop_back();
		letterTimer.reset();
	}

}

bool GameConsole::isTyping() {
	return typingContent.size() > 0;
}

std::string GameConsole::getTypingContent() {

	std::string content("");
	for(int i = 0; i < typingContent.size(); i++) {
		content = content + typingContent[i];
	}


	return content;

}

void GameConsole::newEntry(std::string newEntry) {
	entries.push_back(newEntry);
}

void GameConsole::submitEntry() {
	std::string typingContent = getTypingContent();
	if(typingContent != "") {

		newEntry(typingContent);

		myContainer->getCommander()->checkCommand(typingContent);

		this->typingContent.clear();

	}


	letterTimer.reset();
	justOpenedTimer.reset();
	myContainer->getFocusManager()->setPlayerFocus();
	display = false;
}

void GameConsole::render() {
	float opacity;

	float backgroundDepth = 10;
	float lettersDepth = 10.1;

	if(display) {
		opacity = 1;
		std::string typingContent = getTypingContent();


		myContainer->getGameRenderer()->addGlyph(x,y, width, height, backgroundDepth, 1.0f, 1.0f, 1.0f, 0.8f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);

		displayTextBarTimer.update();
		myContainer->getFontRenderer()->renderText(typingContent, x, y - height + YuEngine::FontRenderer::letterHeight * letterSize, lettersDepth, letterSize, 1.0f, 1.0f, 1.0f, 1.0f);

		if(displayTextBarTimer.isOver(30)) {
			myContainer->getGameRenderer()->addGlyph(x + typingContent.size() * YuEngine::FontRenderer::letterHeight * letterSize, y - height + YuEngine::FontRenderer::letterHeight * letterSize, YuEngine::FontRenderer::letterHeight * letterSize, YuEngine::FontRenderer::letterHeight * letterSize, lettersDepth, 1.0f,1.0f,1.0f,1.0f, myContainer->getSpritesheetsManager()->getFontSpritesheet(), 12,2);

			if(displayTextBarTimer.isOver()) {
				displayTextBarTimer.reset();
			}
		}
	} else {
		opacity = 0.5;
		myContainer->getGameRenderer()->addGlyph(x,y, width, height, backgroundDepth, 1.0f, 1.0f, 1.0f, 0.2f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);

	}

	if(entries.size() > 0) {
		int j = entries.size() - displayEntriesNbr;
		if(j < 0) {
			j = 0;
		}
		int k = 1;
		for(int i = entries.size()-1; i >= j; i--) {
			k++;
			myContainer->getFontRenderer()->renderText(entries[i], x, y - height + YuEngine::FontRenderer::letterHeight * letterSize*k, lettersDepth,  letterSize, 1.0f, 1.0f, 1.0f, opacity);

		}
	}
}