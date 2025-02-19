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

GameConsole::GameConsole(Container* c) : Gui(c, 0, 0, YuEngine::KeyName::none, YuEngine::KeyName::t) {
	
	YuEngine::YuBoudingbox cameraBox = myContainer->getCamera()->getCameraBox();
	width = 600;
	height = 300;
	relX = cameraBox.getWidth() - width;
	relY = 0;

	display = false;
	letterSize = 2;
	displayEntriesNbr = 16;
	justOpened = false;

	displayTextBarTimer = YuEngine::EventTimer(60);
	writingHandler = YuEngine::WritingHandler(myContainer->getInput());
}

GameConsole::~GameConsole(void)
{
}

void GameConsole::update() {


	Gui::update();
	if(justDisplayed) {
		myContainer->getFocusManager()->setGameConsoleFocus();
		justOpened = true;
	}

	handleTyping();
}


void GameConsole::handleTyping() {
	if(!display) {
		return;
	}
	if(display && displayingEvent.isReleased() && justOpened) {
		justOpened = false;
	}
	if(justOpened) {
		return;
	}

	writingHandler.handle();

	auto input = myContainer->getInput();
	if(input->getKeyUp()) {

		if(entries.size() > 0) {
			writingHandler.setTypingContent(entries[entries.size() - 1]);
		}
	}

	if(input->getKeyEnter()) {
		submitEntry();
	}


}

bool GameConsole::isTyping() {
	return writingHandler.getTypingContent().size() > 0;
}
void GameConsole::newEntry(std::string newEntry) {
	entries.push_back(newEntry);
}

void GameConsole::submitEntry() {
	std::string typingContent = writingHandler.getTypingContent();
	if(typingContent != "") {

		newEntry(typingContent);

		myContainer->getCommander()->checkCommand(typingContent);
		writingHandler.empty();

	}

	myContainer->getFocusManager()->setPlayerFocus();
	display = false;
}

void GameConsole::render() {
	float opacity;

	float backgroundDepth = 10;
	float lettersDepth = 10.1;

	if(display) {
		opacity = 1;
		std::string typingContent = writingHandler.getTypingContent();


		myContainer->getGameRenderer()->addGlyph(absX,absY+height, width, height, backgroundDepth, 1.0f, 1.0f, 1.0f, 0.8f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);

		displayTextBarTimer.update();
		myContainer->getFontRenderer()->renderText(typingContent, absX, absY+ YuEngine::FontRenderer::letterHeight * letterSize, lettersDepth, letterSize, 1.0f, 1.0f, 1.0f, 1.0f);

		if(displayTextBarTimer.isOver(30)) {
			myContainer->getGameRenderer()->addGlyph(absX + typingContent.size() * YuEngine::FontRenderer::letterHeight * letterSize, absY+ YuEngine::FontRenderer::letterHeight * letterSize, YuEngine::FontRenderer::letterHeight * letterSize, YuEngine::FontRenderer::letterHeight * letterSize, lettersDepth, 1.0f,1.0f,1.0f,1.0f, myContainer->getSpritesheetsManager()->getFontSpritesheet(), 12,2);

			if(displayTextBarTimer.isOver()) {
				displayTextBarTimer.reset();
			}
		}
	} else {
		opacity = 0.5;
		myContainer->getGameRenderer()->addGlyph(absX,absY+height, width, height, backgroundDepth, 1.0f, 1.0f, 1.0f, 0.2f, myContainer->getSpritesheetsManager()->getMiscSpritesheet(), 0,0);

	}

	if(entries.size() > 0) {
		int j = entries.size() - displayEntriesNbr;
		if(j < 0) {
			j = 0;
		}
		int k = 1;
		for(int i = entries.size()-1; i >= j; i--) {
			k++;
			myContainer->getFontRenderer()->renderText(entries[i], absX, absY + YuEngine::FontRenderer::letterHeight * letterSize*k, lettersDepth,  letterSize, 1.0f, 1.0f, 1.0f, opacity);

		}
	}
}