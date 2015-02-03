#include "ParticlesRenderer.h"
#include "Camera2D.h"
#include "Container.h"
namespace YuEngine {

ParticlesRenderer::ParticlesRenderer(void){
	particlesNbr = 0;
	time = 0;
	doUpdateAge = true;
	handleColors = true;
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


	glGenVertexArrays(1, &vaoColors);
	glBindVertexArray(vaoColors);

		glGenBuffers(1, &vboColors);


		glBindBuffer(GL_ARRAY_BUFFER, vboColors);

			glEnableVertexAttribArray(0); // POS
			glEnableVertexAttribArray(1); // SIZE
			glEnableVertexAttribArray(2); // COLORS

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
			glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, size));
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


}


void ParticlesRenderer::updateAge() {

	std::vector<Particle> tempVector;
	std::vector<Particle> tempColorVector;

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

	for(int i = 0; i < colorParticlesBuffer.size(); i++) {

		colorParticlesBuffer[i].age++;
		colorParticlesBuffer[i].position.x += colorParticlesBuffer[i].velocity.x;
		colorParticlesBuffer[i].position.y += colorParticlesBuffer[i].velocity.y;
		colorParticlesBuffer[i].velocity.y -= 0.05;
		colorParticlesBuffer[i].velocity.x *= 0.999;
		
		if(handleColors && doUpdateAge) {
			if(colorParticlesBuffer[i].age < colorParticlesBuffer[i].deathAge) {

				tempColorVector.push_back(colorParticlesBuffer[i]);
			}
		}

	}

	if(doUpdateAge) {

		particlesBuffer = tempVector;
		if(handleColors) {
			colorParticlesBuffer = tempColorVector;
		}
	}
}

void ParticlesRenderer::addParticle(Particle particle) {

	if(handleColors) {
		if(particle.useColors) {
			colorParticlesBuffer.push_back(particle);
			return;
		}
	}
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
		//particle.useColors = true;
		if(g < 0.5) {
			particle.timeSpeed *= -1;
		}
				
		particlesNbr++;
		addParticle(particle);

	}
	}

	updateAge();


	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * particlesBuffer.size(), nullptr, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * particlesBuffer.size(), particlesBuffer.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(handleColors) {
		glBindBuffer(GL_ARRAY_BUFFER, vboColors);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * colorParticlesBuffer.size(), nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * colorParticlesBuffer.size(), colorParticlesBuffer.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}

}


void ParticlesRenderer::render() {

	particlesShader->use();
	particlesShader->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());


	glBindVertexArray(vao);


	glVertexAttribDivisor(0,1);
	glVertexAttribDivisor(1,1);


	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particlesBuffer.size());

	particlesShader->unuse();


	if(handleColors) {


		colorParticlesShader->use();
		colorParticlesShader->sendMatrix4("cameraMatrix", container->getCamera()->getCameraMatrix());


		glBindVertexArray(vaoColors);

		glVertexAttribDivisor(0, 1);
		glVertexAttribDivisor(1, 1);
		glVertexAttribDivisor(2, 1);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, colorParticlesBuffer.size());

		colorParticlesShader->unuse();

	}
}

}