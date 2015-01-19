#include "Spritesheet.h"
#include "Texture.h"
#include "Vertex.h"

namespace YuEngine {


Spritesheet::Spritesheet(std::string textureFile, int size){

	this->tTexture = new Texture(textureFile);
	this->tTexture->load();

	this->size = size;
}

GLuint Spritesheet::getTextureId() {

	return this->tTexture->getId();
}

void Spritesheet::setCurSprite(int x, int y) {
	this->curX = x;
	this->curY = y;
}
void Spritesheet::bind() {
	glBindTexture(GL_TEXTURE_2D, this->tTexture->getId());
}
void Spritesheet::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
TexturingRectangle Spritesheet::getCoords() {

	float unit = 1.0f / this->size;

	float bottomLeftX = unit * this->curX;
	float bottomLeftY = unit * this->curY;

	TexturingRectangle texturingRectangle(bottomLeftX, bottomLeftY + unit, bottomLeftX + unit, bottomLeftY + unit, bottomLeftX + unit, bottomLeftY, bottomLeftX, bottomLeftY);

	return texturingRectangle;

}

Spritesheet::~Spritesheet(void){
	delete this->tTexture;
}

}