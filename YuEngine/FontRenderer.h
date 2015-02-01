#pragma once

#include <string>
#include "Object.h"
namespace YuEngine {
class FontRenderer: public Object
{
public:
	FontRenderer(void);
	~FontRenderer(void);

	static float letterHeight;
	void renderText(std::string, float x, float y, float depth, float size, float r, float g, float b, float a);
};

}