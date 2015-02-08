#pragma once

#include <YuEngine\Object.h>

class Container;


class Object: public YuEngine::Object
{
public:
	Object(void) {
	};
	Object(Container* c) {
		myContainer = c;
	}
	~Object(void) {
	};
	void setMyContainer(Container* c) {
		myContainer = c;
	}

protected:
	Container* myContainer;
};

