#include "ParticlesRenderer.h"

namespace YuEngine {

ParticlesRenderer::ParticlesRenderer(void){

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


			for(int i = 0; i < 100; i++) {
				Particle particle(71,2465,64, 0, 0, 1.0f,1.0f,1.0f,1.0f);
				particlesBuffer.push_back(particle);

			}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


}

void ParticlesRenderer::update() {

	for(int i = 0; i < particlesBuffer.size(); i++) {
		particlesBuffer[i].position.x += particlesBuffer[i].velocity.x;
		particlesBuffer[i].position.y += particlesBuffer[i].velocity.y;
	}

	void* ptr = particlesBuffer.data();

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