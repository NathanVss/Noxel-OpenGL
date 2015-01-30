#pragma once

#include <vector>

#include "Renderable.h"
#include "SpriteRect.h"
#include "Object.h"
#include "Vertex.h"
#include "Glyph.h"
#include "Spritesheet.h"
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
namespace YuEngine {

enum class GlyphSorting {

	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE

};

class RenderBatch {

public:
	GLuint offset;
	GLuint numVertices;
	GLuint textureId;
	RenderBatch(GLuint _offset, GLuint _numVertices, GLuint _textureId) : offset(_offset), numVertices(_numVertices),
		textureId(_textureId) {

	}

};

class GameRenderer : public Object
{
public:
	GameRenderer(void);
	~GameRenderer(void);
	int addGlyph(float x, float y, float width, float height, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, TexturingRectangle &texturingRectangle);
	int addGlyph(float x, float y, float width, float height, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, int u, int v);
	int addGlyph(float x, float y, float width, float height, float depth, float r, float g, float b, float a, Spritesheet* spritesheet, int u1, int v1, int u2, int v2);
	int addGlyph(float x, float y, float width, float height, float r, float g, float b, float a);
	void updateGlyph(int vertex, float x, float y);
	void init();
	void begin();
	void end();
	void render(int programId);

	void freeObjects();
	int getGlyphsNumber();

	void sortGlyphs();
	static bool compareFrontToBack(Glyph* a, Glyph* b);
	static bool compareBackToFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

	int getTotalGlyphsNumber() {
		return totalGlyphsNumber;
	}
	void resetTotalGlyphsNumber() {
		totalGlyphsNumber = 0;
	}

private:
	void createVertexArray();
	void fillVbo();

	int totalGlyphsNumber;

	std::vector<Glyph> glyphs;
	std::vector<Glyph*> glyphPointers;

	GlyphSorting sortType;

	std::vector<Glyph> colorGlyphs;
	std::vector<RenderBatch> renderBatches;

	GLuint vboColorId;
	GLuint vaoColorId;

	GLuint vboId;
	GLuint vaoId;
};

}
