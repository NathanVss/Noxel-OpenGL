#include "ParticlesRenderer.h"

namespace YuEngine {

ParticlesRenderer::ParticlesRenderer(void){
	particlesNbr = 0;
	time = 0;
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

			float radius = 100;


			for(int i = 0; i < 10000; i++) {
				Particle particle;
				float f = (double)rand() / RAND_MAX * 50;
				float g = (double)rand() / RAND_MAX ;
				float velX = (double)rand() / RAND_MAX;
				float velY = (double)rand() / RAND_MAX;
				//float velX = 0.5 * 1;
				//float velY = 0.5 * 1;

				float sin_ = sin(i);
				float cos_ = cos(i);

				velX *= -cos_ * 2;
				velY *= -sin_ * 2;
				float partRadius = radius + f;
				sin_ *= partRadius;
				cos_ *= partRadius;


				//if(cos_ < 0) {
				//	velX = -velX;
				//}
				//if(sin_ < 0) {
				//	velY = -velY;
				//}
				//if( f < 0.5) {
				//	velX = -velX;
				//}
				//if( g < 0.5) {
				//	velY = -velY;
				//}

				particle = Particle(-20*30 + cos_,2700 + sin_,2*g, velX*1, velY*1, 1.0f,1.0f,1.0f,1.0f);
				particle.time = i;
				particle.radius = partRadius;
				particle.timeSpeed = g * 0.1;
				if(g < 0.5) {
					particle.timeSpeed *= -1;
				}
				
				particlesNbr++;
				particlesBuffer.push_back(particle);

			}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


}

void ParticlesRenderer::update() {
	time++;
	for(int i = 0; i < particlesBuffer.size(); i++) {
		particlesBuffer[i].position.x += particlesBuffer[i].velocity.x;
		particlesBuffer[i].position.y += particlesBuffer[i].velocity.y;

		//		particlesBuffer[i].position.x =-20*30 + cos(particlesBuffer[i].time) * particlesBuffer[i].radius;
		//particlesBuffer[i].position.y = 2700 + sin(particlesBuffer[i].time) * particlesBuffer[i].radius;
		//particlesBuffer[i].time += particlesBuffer[i].timeSpeed;

		//particlesBuffer[i].radius -= 1;


		////int a = 5;
		//particlesBuffer[i].velocity.y -= 0.001;
		//particlesBuffer[i].velocity.x *= 0.999;
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

	glPointSize(32);

	//for(int i = 0; i < particlesBuffer.size(); i++) {
	//	glDrawArrays(GL_TRIANGLES, 0, 1);
	//}
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesBuffer.size());
}

}