#include "EntityMob.h"
#include <iostream>
#include "Container.h"
#include <YuEngine\ParticlesRenderer.h>

EntityMob::EntityMob(void) : EntityLiving(){
	timerWayDecision = YuEngine::EventTimer(60*5);
	timerWayDecision.setOver();
	velocityX = 0;
	isHit = false;
	health = 15;
	maxHealth = health;
}


EntityMob::~EntityMob(void){
}

void EntityMob::update() {
	EntityLiving::update();
	if(!dead) {
		handleBehavior();
	} else {
		onDead();
		destroy = true;
	}

}

void EntityMob::hit(float value, bool _hitOnLeft, bool _hitOnRight) { 
	isHit = true;
	hitOnLeft = _hitOnLeft;
	hitOnRight = _hitOnRight;
	health -= value;
}

void EntityMob::onDead() {
	float size = 4;
	float radius = 1;
	for(int i = 0; i <= size; i++) {
		for(int j = 0; j <= size; j++) {


			float velX = (double)rand() / RAND_MAX * 6;
			float velY = (double)rand() / RAND_MAX * 6;
			float negX;
			float negY;
			float r = (double)rand() / RAND_MAX;
			float g = (double)rand() / RAND_MAX;
			float b = (double)rand() / RAND_MAX; 

			r *= -0.1;
			g *= -0.1;
			b *= -0.1;



			float sin_ = sin(j * size + i);
			float cos_ = cos(j * size + i);

			if(cos_ < 0) {
				negX = -1;
			} else if(cos_ > 0) {
				negX = 1;
			} else {
				negX = 0;
			}

			YuEngine::Color color;
			color.r = 1.0f;
			color.g = 1.0f;
			color.b = 1.0f;
			color.a = 1.0f;

			//YuEngine::Particle particle(x + i *width / size , y - j * height / size , 16, velX*neg,velY,color.r + r, color.g + g,color.b + b,color.a);
			YuEngine::Particle particle(x + width/2 + cos_ * radius  , y - height /2 + sin_ * radius , 6, velX*negX,velY,color.r + r, color.g + g,color.b + b,color.a);
			particle.age = 0;
			particle.deathAge = 120;
			particle.useColors = true;
			particle.gravity = 0.3f;
			myContainer->getParticlesRenderer()->addParticle(particle);

		}
	}
}

void EntityMob::checkHit() {
	if(isHit) {

		if(!jumping && collideOnBottom) {
			velocityY = knockbackY;
			jumping = true;
		}
		if(hitOnLeft) {
			velocityX = knockbackX;
		} else if (hitOnRight) {
			velocityX = -knockbackX;
		}

		float size = 2;
		for(int i = 0; i <= size; i++) {
			for(int j = 0; j <= size; j++) {


				float velX = (double)rand() / RAND_MAX;
				float velY = (double)rand() / RAND_MAX * 2;
				float neg = (double)rand() / RAND_MAX;
				float r = (double)rand() / RAND_MAX * 2 - 1;

				r *= 0.5;

				if(neg < 0.5) {
					neg = -1;
				} else {
					neg = 1;
				}

				YuEngine::Color color;
				color.r = 1.0f;
				color.g = 0;
				color.b = 0;
				color.a = 1.0f;

				YuEngine::Particle particle(x + width / 2 , y - height / 2 , 4, velX*neg,velY,color.r + r, color.g,color.b,color.a);
				particle.age = 0;
				particle.deathAge = 60;
				particle.useColors = true;
				particle.gravity = 0.1f;
				myContainer->getParticlesRenderer()->addParticle(particle);

			}
		}

	}
	isHit = false;
	hitOnLeft = false;
	hitOnRight = false;
}


void EntityMob::handleBehavior() {
	timerWayDecision.update();
	if(timerWayDecision.isOver()) {

		float rand_ = (double)rand() / RAND_MAX;
		if(rand_ <= 0.5f) {
			velocityX = -speedX;
		} else {
			velocityX = speedX;
		}


		timerWayDecision.reset();
	}

	if((collideOnLeft || collideOnRight) && !jumping && collideOnBottom) {
		jumping = true;
		velocityY = jumpVel;
	}



	float jumpRand = (double)rand() / RAND_MAX;
	if(jumpRand <= 0.008 && collideOnBottom && !jumping) {
		jumping = true;
		velocityY = jumpVel;
	}
	if(jumping && collideOnBottom) {
		jumping = false;
	}

	checkHit();
	Entity::handleMoving();

}