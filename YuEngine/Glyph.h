#pragma once


#include <gl\glew.h>
#include "Vertex.h"
#include "Spritesheet.h"

namespace YuEngine {

class Glyph {
public:
	Glyph() {}
	void debug() {
		std::cout << "Glyph : " << std::endl;
		std::cout << "[" << topLeft.position.x << ";" << topLeft.position.y << "] => [" << topLeft.uv.u << ";" << topLeft.uv.v << "]" << std::endl;
		std::cout << "[" << topRight.position.x << ";" << topRight.position.y << "] => [" << topRight.uv.u << ";" << topRight.uv.v << "]" << std::endl;
		std::cout << "[" << bottomRight.position.x << ";" << bottomRight.position.y << "] => [" << bottomRight.uv.u << ";" << bottomRight.uv.v << "]" << std::endl;
		std::cout << "[" << bottomLeft.position.x << ";" << bottomLeft.position.y << "] => [" << bottomLeft.uv.u << ";" << bottomLeft.uv.v << "]" << std::endl;
	}
	float width;
	float height;
	GLuint textureId;
    float depth;
    
    Vertex topLeft;
    Vertex bottomLeft;
    Vertex topRight;
    Vertex bottomRight;
};

}