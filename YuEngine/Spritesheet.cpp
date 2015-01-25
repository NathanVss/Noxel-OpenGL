#include "Spritesheet.h"
#include "Texture.h"
#include "Vertex.h"

namespace YuEngine {


Spritesheet::Spritesheet(std::string textureFile, int size){

	this->tTexture = new Texture(textureFile);
	this->tTexture->load();

	areaMode = false;
	textureId = 0;
	this->size = size;
}

Spritesheet::Spritesheet(int _textureId, int _size) : textureId(_textureId), size(_size), tTexture(nullptr) {

}

GLuint Spritesheet::getTextureId() {
	if(textureId != 0) {

		return textureId;
	}

	return this->tTexture->getId();
}

void Spritesheet::setCurArea(int x1, int y1, int x2, int y2) {
	curAreaX1 = x1;
	curAreaY1 = y1;
	curAreaX2 = x2;
	curAreaY2 = y2;
	areaMode = true;
}


void Spritesheet::setCurSprite(int x, int y) {
	areaMode = false;
	this->curX = x;
	this->curY = y;
}
void Spritesheet::bind() {
	if(textureId != 0) {

		glBindTexture(GL_TEXTURE_2D, textureId);
		return;
	}

	glBindTexture(GL_TEXTURE_2D, this->tTexture->getId());
}
void Spritesheet::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
TexturingRectangle Spritesheet::getCoords() {

	float unit = 1.0f / this->size;

	
	float topLeftX;
	float topLeftY;

	float topRightX;
	float topRightY;

	float bottomRightX;
	float bottomRightY;

	float bottomLeftX;
	float bottomLeftY;

	if(areaMode) {
		topLeftX = curAreaX1 * unit;
		topLeftY = curAreaY2 * unit;

		topRightX = curAreaX2 * unit;
		topRightY = topLeftY;

		bottomRightX = topRightX;
		bottomRightY = curAreaY1 * unit;

		bottomLeftX = topLeftX;
		bottomLeftY = bottomRightY;
	} else {

		bottomLeftX = unit * curX;
		bottomLeftY = unit * curY;

		topLeftX = bottomLeftX;
		topLeftY = bottomLeftY + unit;

		topRightX = bottomLeftX + unit;
		topRightY = bottomLeftY + unit;

		bottomRightX = bottomLeftX + unit;
		bottomRightY = bottomLeftY;

	}

	//TexturingRectangle texturingRectangle(bottomLeftX, bottomLeftY + unit, bottomLeftX + unit, bottomLeftY + unit, bottomLeftX + unit, bottomLeftY, bottomLeftX, bottomLeftY);
	TexturingRectangle texturingRectangle(topLeftX, topLeftY, topRightX, topRightY, bottomRightX, bottomRightY, bottomLeftX, bottomLeftY);

	return texturingRectangle;

}

Spritesheet::~Spritesheet(void){
	if(tTexture)
		delete this->tTexture;
}

}