
#include "FontRenderer.h"
#include "Container.h"
#include "SpritesheetsManager.h"
#include "Spritesheet.h"
#include "SpriteRect.h"
#include "GameRenderer.h"
#include <iostream>
namespace YuEngine {

	float FontRenderer::letterHeight = 8;

FontRenderer::FontRenderer(void) {
}


FontRenderer::~FontRenderer(void) {
}

void FontRenderer::renderText(std::string text, float x, float y, float depth, float size, float r, float g, float b, float a) {

	const char* cText = text.c_str();
	int length = strlen(cText);
	int letterWidth = 8*size;
	Spritesheet* FontSpritesheet = this->container->getSpritesheetsManager()->getFontSpritesheet();



	for(int i=0; i<length; i++) {

		int curX, curY;
		if(cText[i] == 'A') {
			FontSpritesheet->setCurSprite(0, 7);
		} else if(cText[i] == 'B') {
			FontSpritesheet->setCurSprite(1, 7);
		} else if(cText[i] == 'C') {
			FontSpritesheet->setCurSprite(2, 7);
		} else if(cText[i] == 'D') {
			FontSpritesheet->setCurSprite(3, 7);
		} else if(cText[i] == 'E') {
			FontSpritesheet->setCurSprite(4, 7);
		} else if(cText[i] == 'F') {
			FontSpritesheet->setCurSprite(5, 7);
		} else if(cText[i] == 'G') {
			FontSpritesheet->setCurSprite(6, 7);
		} else if(cText[i] == 'H') {
			FontSpritesheet->setCurSprite(7, 7);
		} else if(cText[i] == ' ') {
			FontSpritesheet->setCurSprite(0, 6);
		} else if(cText[i] == 'I') {
			FontSpritesheet->setCurSprite(1, 6);
		} else if(cText[i] == 'J') {
			FontSpritesheet->setCurSprite(2, 6);
		} else if(cText[i] == 'K') {
			FontSpritesheet->setCurSprite(3, 6);
		} else if(cText[i] == 'L') {
			FontSpritesheet->setCurSprite(4, 6);
		} else if(cText[i] == 'M') {
			FontSpritesheet->setCurSprite(5, 6);
		} else if(cText[i] == 'N') {
			FontSpritesheet->setCurSprite(6, 6);
		} else if(cText[i] == 'O') {
			FontSpritesheet->setCurSprite(7, 6);
		} else if(cText[i] == 'P') {
			FontSpritesheet->setCurSprite(0, 5);
		} else if(cText[i] == 'Q') {
			FontSpritesheet->setCurSprite(1, 5);
		} else if(cText[i] == 'R') {
			FontSpritesheet->setCurSprite(2, 5);
		} else if(cText[i] == 'S') {
			FontSpritesheet->setCurSprite(3, 5);
		} else if(cText[i] == 'T') {
			FontSpritesheet->setCurSprite(4, 5);
		} else if(cText[i] == 'U') {
			FontSpritesheet->setCurSprite(5, 5);
		} else if(cText[i] == 'V') {
			FontSpritesheet->setCurSprite(6, 5);
		} else if(cText[i] == 'X') {
			FontSpritesheet->setCurSprite(7, 5);
		} else if(cText[i] == 'Y') {
			FontSpritesheet->setCurSprite(0, 4);
		} else if(cText[i] == 'Z') {
			FontSpritesheet->setCurSprite(1, 4);
		} else if(cText[i] == 'a') {
			FontSpritesheet->setCurSprite(2, 4);
		} else if(cText[i] == 'b') {
			FontSpritesheet->setCurSprite(3, 4);
		} else if(cText[i] == 'c') {
			FontSpritesheet->setCurSprite(4, 4);
		} else if(cText[i] == 'd') {
			FontSpritesheet->setCurSprite(5, 4);
		} else if(cText[i] == 'e') {
			FontSpritesheet->setCurSprite(6, 4);
		} else if(cText[i] == 'f') {
			FontSpritesheet->setCurSprite(7, 4);
		} else if(cText[i] == 'g') {
			FontSpritesheet->setCurSprite(0, 3);
		} else if(cText[i] == 'h') {
			FontSpritesheet->setCurSprite(1, 3);
		} else if(cText[i] == 'i') {
			FontSpritesheet->setCurSprite(2, 3);
		} else if(cText[i] == 'j') {
			FontSpritesheet->setCurSprite(3, 3);
		} else if(cText[i] == 'k') {
			FontSpritesheet->setCurSprite(4, 3);
		} else if(cText[i] == 'l') {
			FontSpritesheet->setCurSprite(5, 3);
		} else if(cText[i] == 'm') {
			FontSpritesheet->setCurSprite(6, 3);
		} else if(cText[i] == 'n') {
			FontSpritesheet->setCurSprite(7, 3);
		} else if(cText[i] == 'o') {
			FontSpritesheet->setCurSprite(0, 2);
		} else if(cText[i] == 'p') {
			FontSpritesheet->setCurSprite(1, 2);
		} else if(cText[i] == 'q') {
			FontSpritesheet->setCurSprite(2, 2);
		} else if(cText[i] == 'r') {
			FontSpritesheet->setCurSprite(3, 2);
		} else if(cText[i] == 's') {
			FontSpritesheet->setCurSprite(4, 2);
		} else if(cText[i] == 't') {
			FontSpritesheet->setCurSprite(5, 2);
		} else if(cText[i] == 'u') {
			FontSpritesheet->setCurSprite(6, 2);
		} else if(cText[i] == 'v') {
			FontSpritesheet->setCurSprite(7, 2);
		} else if(cText[i] == 'w') {
			FontSpritesheet->setCurSprite(0, 1);
		} else if(cText[i] == 'x') {
			FontSpritesheet->setCurSprite(1, 1);
		} else if(cText[i] == 'y') {
			FontSpritesheet->setCurSprite(2, 1);
		} else if(cText[i] == 'z') {
			FontSpritesheet->setCurSprite(3, 1);
		} else if(cText[i] == '0') {
			FontSpritesheet->setCurSprite(4, 1);
		} else if(cText[i] == '1') {
			FontSpritesheet->setCurSprite(5, 1);
		} else if(cText[i] == '2') {
			FontSpritesheet->setCurSprite(6, 1);
		} else if(cText[i] == '3') {
			FontSpritesheet->setCurSprite(7, 1);
		} else if(cText[i] == '4') {
			FontSpritesheet->setCurSprite(0, 0);
		} else if(cText[i] == '5') {
			FontSpritesheet->setCurSprite(1, 0);
		} else if(cText[i] == '6') {
			FontSpritesheet->setCurSprite(2, 0);
		} else if(cText[i] == '7') {
			FontSpritesheet->setCurSprite(3, 0);
		} else if(cText[i] == '8') {
			FontSpritesheet->setCurSprite(4, 0);
		} else if(cText[i] == '9') {
			FontSpritesheet->setCurSprite(5, 0);
		} else if(cText[i] == '-') {
			FontSpritesheet->setCurSprite(6, 0);
		} else if(cText[i] == ':') {
			FontSpritesheet->setCurSprite(7, 0);
		} else if(cText[i] == ';') {
			FontSpritesheet->setCurSprite(8, 0);
		} else if(cText[i] == 'W') {
			FontSpritesheet->setCurSprite(8, 5);
		} else if(cText[i] == '[') {
			FontSpritesheet->setCurSprite(9, 0);
		} else if(cText[i] == ']') {
			FontSpritesheet->setCurSprite(10, 0);
		} else if(cText[i] == '_') {
			FontSpritesheet->setCurSprite(11, 0);
		} else if(cText[i] == '(') {
			FontSpritesheet->setCurSprite(12, 0);
		} else if(cText[i] == ')') {
			FontSpritesheet->setCurSprite(13, 0);
		} else if(cText[i] == '\'') {
			FontSpritesheet->setCurSprite(14, 0);
		} else if(cText[i] == '"') {
			FontSpritesheet->setCurSprite(15, 0);
		} else if(cText[i] == '+') {
			FontSpritesheet->setCurSprite(8, 1);
		} else if(cText[i] == '#') {
			FontSpritesheet->setCurSprite(9, 1);
		} else if(cText[i] == '\\') {
			FontSpritesheet->setCurSprite(10, 1);
		} else if(cText[i] == '/') {
			FontSpritesheet->setCurSprite(11, 1);
		} else if(cText[i] == '.') {
			FontSpritesheet->setCurSprite(12, 1);
		} else if(cText[i] == '?') {
			FontSpritesheet->setCurSprite(13, 1);
		} else if(cText[i] == '!') {
			FontSpritesheet->setCurSprite(14, 1);
		} else if(cText[i] == ',') {
			FontSpritesheet->setCurSprite(15, 1);
		} else if(cText[i] == '=') {
			FontSpritesheet->setCurSprite(8, 2);
		} else if(cText[i] == '*') {
			FontSpritesheet->setCurSprite(9, 2);
		} else if(cText[i] == '$') {
			FontSpritesheet->setCurSprite(10, 2);
		} else if(cText[i] == '£') {
			FontSpritesheet->setCurSprite(11, 2);
		} else if(cText[i] == 'é') {
			FontSpritesheet->setCurSprite(8, 4);
		} else if(cText[i] == 'è') {
			FontSpritesheet->setCurSprite(9, 4);
		} else if(cText[i] == 'ù') {
			FontSpritesheet->setCurSprite(10, 4);
		} else if(cText[i] == 'à') {
			FontSpritesheet->setCurSprite(11, 4);
		} else if(cText[i] == 'ç') {
			FontSpritesheet->setCurSprite(12, 4);
		} else if(text[i] == '&') {
			FontSpritesheet->setCurSprite(13, 4);
		}
		curX = FontSpritesheet->getCurX();
		curY = FontSpritesheet->getCurY();
		
		this->container->getGameRenderer()->addGlyph(x+i*letterWidth, y, letterWidth, letterWidth, depth, r, g, b, a, FontSpritesheet, curX, curY);

	}
	//delete cText;
}

}