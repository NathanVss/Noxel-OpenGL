#pragma once

#include <YuEngine\Container.h>
class World;

class Container: public YuEngine::Container
{
public:
	Container(void) {

	};
	~Container(void) {
	};

	void setWorld(World* _world) {
		world = _world;
	}
	World* getWorld() {
		return world;
	}

protected:
	World* world;
};

