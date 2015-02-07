
#include "GameRenderer.h"
#include <iostream>
#include "Renderable.h"
#include "SpriteRect.h"
#include "Object.h"
#include "Container.h"
#include "Shader.h"
#include "Camera2D.h"
#include <algorithm>
#include <math.h>
#include "Utils.h"

namespace YuEngine {


GameRenderer::GameRenderer(void){
	this->vaoId = 0;
	this->vboId = 0;
	totalGlyphsNumber = 0;
	sortType = GlyphSorting::FRONT_TO_BACK;
}


GameRenderer::~GameRenderer(void)
{
}


int GameRenderer::getGlyphsNumber() {
	return glyphs.size();

}

void GameRenderer::init() {
	createVertexArray();
}

void GameRenderer::end() {
	glyphPointers.resize(glyphs.size());
	for(int i = 0; i < glyphs.size(); i++) {
		glyphPointers[i] = &glyphs[i];
	}
	sortGlyphs();
	fillVbo();
}

void GameRenderer::render(int programId) {
	if(glyphs.empty()) {
		return;
	}



	glBindVertexArray(vaoId);

	for(int i = 0; i<renderBatches.size(); i++) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].textureId);
		
		glUniform1i(glGetUniformLocation(programId, "spriteTexture"), 1);


		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	glBindVertexArray(0);

	return;

}

void GameRenderer::createVertexArray() {
	if(vaoId == 0) {
		glGenVertexArrays(1, &vaoId);
	}

	glBindVertexArray(vaoId);


		if(vboId == 0) {
			glGenBuffers(1, &vboId);
		}
		glBindBuffer(GL_ARRAY_BUFFER, vboId);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}


void GameRenderer::fillVbo() {

	std::vector<Vertex> vertices;
	vertices.resize(glyphPointers.size() * 6);

	if(glyphPointers.empty()) {

		return;
	}
	int cv = 0;
	int offset = 0;

	renderBatches.emplace_back(offset, 6, glyphPointers[0]->textureId);
	vertices[cv++] = glyphPointers[0]->topLeft; 
	vertices[cv++] = glyphPointers[0]->topRight; 
	vertices[cv++] = glyphPointers[0]->bottomLeft; 

	vertices[cv++] = glyphPointers[0]->bottomLeft; 
	vertices[cv++] = glyphPointers[0]->topRight;
	vertices[cv++] = glyphPointers[0]->bottomRight;
	offset += 6;

	for(int i=1;i<glyphPointers.size();i++) {

		if(glyphPointers[i]->textureId != glyphPointers[i-1]->textureId) {
		
			renderBatches.emplace_back(offset, 6, glyphPointers[i]->textureId);
		} else {

			renderBatches.back().numVertices += 6;

		}

		vertices[cv++] = glyphPointers[i]->topLeft; 
		vertices[cv++] = glyphPointers[i]->topRight; 
		vertices[cv++] = glyphPointers[i]->bottomLeft; 

		vertices[cv++] = glyphPointers[i]->bottomLeft; 
		vertices[cv++] = glyphPointers[i]->topRight;
		vertices[cv++] = glyphPointers[i]->bottomRight;

		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void GameRenderer::begin() {
	glyphPointers.clear();
	glyphs.clear();
	renderBatches.clear();
}


void GameRenderer::updateGlyph(int vertex, float x, float y) {
	glBindBuffer(GL_ARRAY_BUFFER, vboId);


	void *vboAdress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if(vboAdress == NULL) {
		return;
	}
	Glyph glyph = this->glyphs[vertex];

	glyph.topLeft.setPosition(x, y);
	glyph.topRight.setPosition(x + glyph.width, y );
	glyph.bottomRight.setPosition(x + glyph.width, y - glyph.height);
	glyph.bottomLeft.setPosition(x, y - glyph.height);


	std::vector<Vertex> vertices;
	vertices.resize(6);
	vertices[0] = glyph.topLeft;
	vertices[1] = glyph.topRight;
	vertices[2] = glyph.bottomLeft;

	vertices[3] = glyph.bottomLeft;
	vertices[4] = glyph.topRight;
	vertices[5] = glyph.bottomRight;

	memcpy((char*)vboAdress + sizeof(Vertex)*vertex, vertices.data(), sizeof(Vertex)*6);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	vboAdress = 0;


	glBindBuffer(GL_ARRAY_BUFFER, 0);
};


int GameRenderer::addGlyph(float x, float y, float width, float height, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, int u, int v) {
	
	spritesheet->setCurSprite(u, v);
	TexturingRectangle texturingRectangle = spritesheet->getCoords();
	return addGlyph(x, y, width, height, 0, 0, 0, depth, r, g, b, a, spritesheet, texturingRectangle);
}
int GameRenderer::addGlyph(float x, float y, float width, float height, float pointToRotateArroundX, float pointToRotateArroundY, float angle, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, int u, int v) {

	spritesheet->setCurSprite(u, v);
	TexturingRectangle texturingRectangle = spritesheet->getCoords();
	return addGlyph(x, y, width, height, pointToRotateArroundX, pointToRotateArroundY, angle, depth, r, g, b, a, spritesheet, texturingRectangle);
}



int GameRenderer::addGlyph(float x, float y, float width, float height, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, int u1, int v1, int u2, int v2) {
	
	spritesheet->setCurArea(u1, v1, u2, v2);
	TexturingRectangle texturingRectangle = spritesheet->getCoords();
	//texturingRectangle.debug();
	return addGlyph(x, y, width, height, 0, 0, 0, depth, r, g, b, a, spritesheet, texturingRectangle);
}

int GameRenderer::addGlyph(float x, float y, float width, float height, float pointToRotateArroundX, float pointToRotateArroundY, float angle, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, TexturingRectangle &texturingRectangle) {
	
	Glyph glyph;

	Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	glyph.depth = depth;
	float halfW = width / 2.0f;
	float halfH = height / 2.0f;
	glyph.width = width;
	glyph.height = height;
	glyph.textureId = spritesheet->getTextureId();

	if(angle == 0) {
		glyph.topLeft.setPosition(x, y);
		glyph.topRight.setPosition(x + width, y );
		glyph.bottomRight.setPosition(x + width, y - height);
		glyph.bottomLeft.setPosition(x, y -height);
	} else {
		angle = 3.141592 * (angle) / 180.0f;
		Position newTopLeft = Utils::rotatePoint(Position(x, y), Position(pointToRotateArroundX, pointToRotateArroundY), angle);
		Position newTopRight = Utils::rotatePoint(Position(x + width, y), Position(pointToRotateArroundX, pointToRotateArroundY), angle);
		Position newBottomRight = Utils::rotatePoint(Position(x + width, y - height), Position(pointToRotateArroundX, pointToRotateArroundY), angle);
		Position newBottomLeft = Utils::rotatePoint(Position(x, y - height), Position(pointToRotateArroundX, pointToRotateArroundY), angle);

		glyph.topLeft.setPosition(newTopLeft.x, newTopLeft.y);
		glyph.topRight.setPosition(newTopRight.x, newTopRight.y );
		glyph.bottomRight.setPosition(newBottomRight.x, newBottomRight.y);
		glyph.bottomLeft.setPosition(newBottomLeft.x, newBottomLeft.y);
	}
	glyph.topLeft.color = color;
	glyph.topLeft.setUV(texturingRectangle.topLeftX, texturingRectangle.topLeftY);

	glyph.topRight.color = color;
	glyph.topRight.setUV(texturingRectangle.topRightX, texturingRectangle.topRightY);
	
	glyph.bottomRight.color = color;
	glyph.bottomRight.setUV(texturingRectangle.bottomRightX, texturingRectangle.bottomRightY);


	glyph.bottomLeft.color = color;
	glyph.bottomLeft.setUV(texturingRectangle.bottomLeftX, texturingRectangle.bottomLeftY);

	//glyph.debug();
	this->glyphs.push_back(glyph);
	totalGlyphsNumber++;
	return this->glyphs.size() - 1;

}


void GameRenderer::sortGlyphs() {
	switch(sortType) {

		case GlyphSorting::BACK_TO_FRONT :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), YuEngine::RenderingUtils::compareBackToFront);
			break;

		case GlyphSorting::FRONT_TO_BACK :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), YuEngine::RenderingUtils::compareFrontToBack);
			break;

		case GlyphSorting::TEXTURE :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), YuEngine::RenderingUtils::compareTexture);
			break;

	}
}


}