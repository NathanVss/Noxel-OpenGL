#pragma once

#include <YuEngine\Object.h>

class Container;


class Object: public YuEngine::Object
{
public:
	Object(void) {
	};
	~Object(void) {
	};
	void setMyContainer(Container* c) {
		myContainer = c;
	}

protected:
	Container* myContainer;
};

