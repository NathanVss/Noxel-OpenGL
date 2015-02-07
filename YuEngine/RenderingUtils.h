#pragma once
#include <gl\glew.h>

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

class RenderingUtils {
public:
	static bool RenderingUtils::compareBackToFront(Glyph* a, Glyph* b) {
		return ( a->depth > b->depth );
	}
	static bool RenderingUtils::compareFrontToBack(Glyph* a, Glyph* b) {
		return ( a->depth < b->depth );
	}
	static bool RenderingUtils::compareTexture(Glyph* a, Glyph* b) {
		return ( a->textureId > b->textureId );
	}

};

}