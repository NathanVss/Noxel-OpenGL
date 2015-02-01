#pragma once

#include "Object.h"
#include <string>

class Commander : public Object
{
public:
	Commander(void);
	~Commander(void);

	void checkCommand(std::string cmd);
};

