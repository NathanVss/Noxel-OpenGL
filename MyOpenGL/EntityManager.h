#pragma once

#include "Object.h"
#include "Entity.h"
#include "EntityMob.h"
#include <vector>

class EntityManager : public Object
{
public:
	EntityManager(void);
	~EntityManager(void);

	void update();
	void render();
	void renderText();
	void addEntity(Entity* entity) {
		entities.push_back(entity);
	}
	void addMobEntity(EntityMob* entity) {
		mobEntities.push_back(entity);
	}
	int getEntitiesNumber() {
		return entities.size() + mobEntities.size()  ;
	}

	void hit(float _x, float _y);

private:
	std::vector<Entity*> entities;
	std::vector<EntityMob*> mobEntities;
};

