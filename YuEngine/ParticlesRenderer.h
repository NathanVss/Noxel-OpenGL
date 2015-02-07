#pragma once


#include "Vertex.h"
#include <vector>
#include "Object.h"
#include "Shader.h"

namespace YuEngine {




class Particle {
public:

	Particle(float _x, float _y, float _size, float _velX, float _velY, float _r, float _g, float _b, float _a) {
		position.x = _x;
		position.y = _y;
		color.r = _r;
		color.g = _g;
		color.b = _b;
		color.a = _a;
		size = _size;
		velocity.x = _velX;
		velocity.y = _velY;
	}
	Particle() {

	};
	~Particle() {

	};
	Position velocity;
	Position position;
	Color color;
	float size;
	float age;
	float deathAge;
	float gravity;

	bool useColors;

	float time;
	float radius;
	float timeSpeed;

	float step;
};

class ParticlesRenderer : public Object
{
public:
	ParticlesRenderer(void);
	~ParticlesRenderer(void);
	void init();
	void update();
	void updateAge();
	void render();


	void addParticle(Particle particle);


	int getParticlesNbr() {
		return particlesBuffer.size() + colorParticlesBuffer.size();
	}


	void setColorParticlesShader(Shader* s) {
		colorParticlesShader = s;
	}
	void setParticlesShader(Shader* s) {
		particlesShader = s;
	}

private:
	int time;
	GLuint vbo;
	GLuint vao;

	GLuint vboColors;
	GLuint vaoColors;

	int particlesNbr;

	bool doUpdateAge;
	bool handleColors;

	Shader* particlesShader;
	Shader* colorParticlesShader;

	std::vector<Particle> colorParticlesBuffer;
	std::vector<Particle> aliveColorParticlesBuffer;

	std::vector<Particle> particlesBuffer;
	std::vector<Particle> aliveParticlesBuffer;
};

}