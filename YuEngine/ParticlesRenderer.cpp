#include "ParticlesRenderer.h"

namespace YuEngine {

ParticlesRenderer::ParticlesRenderer(void){
	particlesNbr = 0;
	time = 0;
	doUpdateAge = true;
}


ParticlesRenderer::~ParticlesRenderer(void){

}

void ParticlesRenderer::init() {

	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glEnableVertexAttribArray(0); // POS
			glEnableVertexAttribArray(1); // SIZE
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,sizeof(Particle), (void*)offsetof(Particle, position));
			glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE,sizeof(Particle), (void*)offsetof(Particle, size));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


}


void ParticlesRenderer::updateAge() {

	std::vector<Particle> tempVector;

	for(int i = 0; i < particlesBuffer.size(); i++) {

		particlesBuffer[i].age++;
		particlesBuffer[i].position.x += particlesBuffer[i].velocity.x;
		particlesBuffer[i].position.y += particlesBuffer[i].velocity.y;
		particlesBuffer[i].velocity.y -= 0.05;
		particlesBuffer[i].velocity.x *= 0.999;

		if(doUpdateAge) {
			if(particlesBuffer[i].age < particlesBuffer[i].deathAge) {

				tempVector.push_back(particlesBuffer[i]);
			}
		}
	}

	if(doUpdateAge) {

		particlesBuffer = tempVector;
	}
}

void ParticlesRenderer::addParticle(Particle particle) {


	particlesBuffer.push_back(particle);
}


void ParticlesRenderer::update() {
	time++;
	int radius = 0;
	if(time % 1 == 0 ) {
	for(int i = 0; i < 10; i++) {
		Particle particle;
		float f = (double)rand() / RAND_MAX * 0;
		float g = (double)rand() / RAND_MAX ;
		float velX = (double)rand() / RAND_MAX;
		float velY = (double)rand() / RAND_MAX;

		float sin_ = sin(i);
		float cos_ = cos(i);
		//float velX = 0.1;
		velX *= cos_ * 2;
		if(sin_ < 0) {
			velY *= -sin_ * 2;

		} else {
			velY *= sin_ * 2;

		}
		float partRadius = radius + f;
		sin_ *= partRadius;
		cos_ *= partRadius;

		particle = Particle(-30*30 + cos_,2700 + sin_,2*g, velX*15, velY*15, 2.0f,1.0f,1.0f,1.0f);
		particle.time = i;
		particle.radius = partRadius;
		particle.timeSpeed = g * 0.1;
		particle.deathAge = 60*4*(g);
		particle.age = 0;
		if(g < 0.5) {
			particle.timeSpeed *= -1;
		}
				
		particlesNbr++;
		particlesBuffer.push_back(particle);

	}
	}

	updateAge();


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particlesBuffer.size(), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * particlesBuffer.size(), particlesBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void ParticlesRenderer::render() {
	glBindVertexArray(vao);


	glVertexAttribDivisor(0,1);
	glVertexAttribDivisor(1,1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesBuffer.size());
}

}