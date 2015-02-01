#pragma once


#include "Vertex.h"
#include <vector>
#include "Object.h"

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
	~Particle() {

	};
	Position velocity;
	Position position;
	Color color;
	float size;

};

class ParticlesRenderer : public Object
{
public:
	ParticlesRenderer(void);
	~ParticlesRenderer(void);
	void init();
	void update();
	void render();

private:

	GLuint vbo;
	GLuint vao;
	std::vector<Particle> particlesBuffer;
	std::vector<Particle> aliveParticlesBuffer;
};

}