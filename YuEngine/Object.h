#pragma once

namespace YuEngine {

class Container;

class Object
{
public:
	Object(void);
	virtual ~Object(void);
	virtual void setContainer(Container* c) { this->container = c; }
protected:
	Container* container;

};

}