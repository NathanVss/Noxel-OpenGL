
#include "GameRenderer.h"
#include <iostream>
#include "Renderable.h"
#include "SpriteRect.h"
#include "Object.h"
#include "Container.h"
#include "Shader.h"
#include "Camera2D.h"
#include <algorithm>

namespace YuEngine {


GameRenderer::GameRenderer(void){
	this->vaoId = 0;
	this->vboId = 0;
	sortType = GlyphSorting::BACK_TO_FRONT;
}


GameRenderer::~GameRenderer(void)
{
}


int GameRenderer::getGlyphsNumber() {
	return glyphs.size();

}

void GameRenderer::init() {
	this->createVertexArray();
}

void GameRenderer::end() {
	glyphPointers.resize(glyphs.size());
	for(int i = 0; i < glyphs.size(); i++) {
		glyphPointers[i] = &glyphs[i];
	}
	sortGlyphs();
	this->fillVbo();
}

void GameRenderer::render() {
	if(glyphs.empty()) {
		return;
	}

	
	glUseProgram(this->container->getClassicShader()->getProgramID());
	glUniformMatrix4fv(glGetUniformLocation(container->getClassicShader()->getProgramID(), "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(container->getCamera()->getCameraMatrix()));

	glBindVertexArray(vaoId);

	for(int i = 0; i<renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].textureId);
		glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//for(int i = 0; i < this->glyphs.size(); i++) {
	//	glBindTexture(GL_TEXTURE_2D, this->glyphs[i].textureId);

	//	glDrawArrays(GL_TRIANGLES, i * 6, 6);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	//}

	glBindVertexArray(0);

	glUseProgram(0);
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

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
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
	
	Glyph glyph;


	spritesheet->setCurSprite(u, v);
	TexturingRectangle textureRectangle = spritesheet->getCoords();
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

	glyph.topLeft.setPosition(x, y);
	glyph.topLeft.color = color;
	glyph.topLeft.setUV(textureRectangle.topLeftX, textureRectangle.topLeftY);

	glyph.topRight.setPosition(x + width, y );
	glyph.topRight.color = color;
	glyph.topRight.setUV(textureRectangle.topRightX, textureRectangle.topRightY);
	
	glyph.bottomRight.setPosition(x + width, y - height);
	glyph.bottomRight.color = color;
	glyph.bottomRight.setUV(textureRectangle.bottomRightX, textureRectangle.bottomRightY);

	glyph.bottomLeft.setPosition(x, y -height);
	glyph.bottomLeft.color = color;
	glyph.bottomLeft.setUV(textureRectangle.bottomLeftX, textureRectangle.bottomLeftY);

	//glyph.debug();
	this->glyphs.push_back(glyph);
	return this->glyphs.size() - 1;

}

void GameRenderer::sortGlyphs() {
	switch(sortType) {

		case GlyphSorting::BACK_TO_FRONT :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), compareBackToFront);
			break;

		case GlyphSorting::FRONT_TO_BACK :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), compareFrontToBack);
			break;

		case GlyphSorting::TEXTURE :
			std::stable_sort(glyphPointers.begin(), glyphPointers.end(), compareTexture);
			break;

	}
}


bool GameRenderer::compareBackToFront(Glyph* a, Glyph* b) {
	return ( a->depth > b->depth );
}
bool GameRenderer::compareFrontToBack(Glyph* a, Glyph* b) {
	return ( a->depth < b->depth );
}
bool GameRenderer::compareTexture(Glyph* a, Glyph* b) {
	return ( a->textureId > b->textureId );
}

void GameRenderer::freeObjects() {


}


}