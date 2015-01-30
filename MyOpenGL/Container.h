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

	void setLightingShader(YuEngine::Shader *s) {
		lightingShader = s;
	}
	YuEngine::Shader* getLightingShader() {
		return lightingShader;
	}

	void setBlurShader(YuEngine::Shader *s) {
		blurShader = s;
	}
	YuEngine::Shader* getBlurShader() {
		return blurShader;
	}
	void setLightRadiusShader(YuEngine::Shader *s) {
		lightRadiusShader = s;
	}
	YuEngine::Shader* getLightRadiusShader() {
		return lightRadiusShader;
	}

protected:
	World* world;
	YuEngine::Shader *lightingShader;
	YuEngine::Shader *blurShader;
	YuEngine::Shader *lightRadiusShader;

};

