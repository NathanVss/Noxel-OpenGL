#pragma once

namespace YuEngine {


class Input;
class SpritesheetsManager;
class Camera2D;
class Shader;
class FontRenderer;
class GameRenderer;
class ParticlesRenderer;

class Container
{
public:
	Container(void);
	~Container(void);
	void setInput(Input* i) { this->input = i; }
	Input* getInput() { return this->input; }

	void setCamera(Camera2D* c) {
		this->camera = c;
	}
	Camera2D* getCamera() {
		return this->camera;
	}

	void setSpritesheetsManager(SpritesheetsManager* sp) {
		this->spritesheetsManager = sp;
	}
	SpritesheetsManager* getSpritesheetsManager() {
		return this->spritesheetsManager;
	}

	void setClassicShader(Shader* s) {
		this->classicShader = s;
	}
	Shader* getClassicShader() {
		return this->classicShader;
	}

	void setFontRenderer(FontRenderer* f) {
		this->fontRenderer = f;
	}
	FontRenderer* getFontRenderer() {
		return this->fontRenderer;
	}

	void setGameRenderer(GameRenderer* g) {
		this->gameRenderer = g;
	}
	GameRenderer* getGameRenderer() {
		return this->gameRenderer;
	}

	void setParticlesRenderer(ParticlesRenderer* p) {
		particlesRenderer = p;
	}
	ParticlesRenderer* getParticlesRenderer() {
		return particlesRenderer;
	}


protected:
	ParticlesRenderer* particlesRenderer;
	Input *input;
	Camera2D *camera;
	SpritesheetsManager *spritesheetsManager;
	Shader* classicShader;
	FontRenderer* fontRenderer;
	GameRenderer* gameRenderer;
};

}

