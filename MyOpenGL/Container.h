#pragma once

#include <YuEngine\Container.h>
class World;
class Commander;
class FocusManager;
class GameConsole;
class Player;
class Config;
class GuiManager;
class EntityManager;

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

	void setCommander(Commander* c) {
		commander = c;
	}
	Commander* getCommander() {
		return commander;
	}

	void setFocusManager(FocusManager* f) {
		focusManager = f;
	}
	FocusManager* getFocusManager() {
		return focusManager;
	}

	void setGameConsole(GameConsole* g) {
		gameConsole = g;
	}
	GameConsole* getGameConsole() {
		return gameConsole;
	}

	void setPlayer(Player* p) {
		player = p;
	}
	Player* getPlayer() {
		return player;
	}

	void setConfig(Config* c) {
		config = c;
	}
	Config* getConfig() {
		return config;
	}

	void setParticlesShader(YuEngine::Shader* s) {
		particlesShader = s;
	}
	YuEngine::Shader* getParticlesShader() {
		return particlesShader;
	}

	void setGuiManager(GuiManager* g) {
		guiManager = g;
	}
	GuiManager* getGuiManager() {
		return guiManager;
	}

	void setEntityManager(EntityManager* m) {
		entityManager = m;
	}
	EntityManager* getEntityManager() {
		return entityManager;
	}

protected:
	World* world;
	YuEngine::Shader *lightingShader;
	YuEngine::Shader *blurShader;
	YuEngine::Shader *lightRadiusShader;
	YuEngine::Shader *particlesShader;
	Commander* commander;
	FocusManager* focusManager;
	GameConsole* gameConsole;
	Player* player;
	Config* config;
	GuiManager* guiManager;
	EntityManager* entityManager;

};

