#pragma once

#include <string>
#include <vector>
#include "Object.h"
namespace YuEngine {
class DebugOverlay: public Object
{
public:
	DebugOverlay(void);
	~DebugOverlay(void);
	void addDebugString(std::string);
	void update();
	void render();


private:
	std::vector<std::string> debugStrings;
};

}