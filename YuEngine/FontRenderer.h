#pragma once

#include <string>
#include "Object.h"
namespace YuEngine {
class FontRenderer: public Object
{
public:
	FontRenderer(void);
	~FontRenderer(void);
	void renderText(std::string, float x, float y, float size, float r, float g, float b, float a);
};

}