#include "Camera2D.h"
#include "Container.h"
#include "Input.h"
#include <iostream>

namespace YuEngine {


Camera2D::Camera2D(void) {
	this->position = glm::vec2(0.0f, 0.0f);
	this->cameraMatrix = glm::mat4(1.0f);
	this->orthoMatrix = glm::mat4(1.0f);
	this->scale = 1.0f;
	this->needMatrixUpdate = true;
}


Camera2D::~Camera2D(void)
{
}

glm::mat4 Camera2D::getCameraMatrix() {
	return this->cameraMatrix;

}
void Camera2D::setPosition(const glm::vec2 &newPosition) {
	this->position = newPosition;
	this->needMatrixUpdate = true;
}
void Camera2D::setScale(float newScale) {
	this->scale = newScale;
	this->needMatrixUpdate = true;
}

glm::vec2 Camera2D::getPosition() {
	return this->position;
}
float Camera2D::getScale() {
	return this->scale;
}





void Camera2D::init(int screenWidth, int screenHeight) {

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->orthoMatrix = glm::ortho(0.0f, (float)this->screenWidth, 0.0f, (float)this->screenHeight);
}

void Camera2D::update() {
	float cameraSpeed = 20.0f;
	float scaleSpeed = 0.1f;

	Input* iInput = this->container->getInput();

	if(iInput->getKeyZ()) {
		this->setPosition(this->position + glm::vec2(0.0f, cameraSpeed));
	}
	if(iInput->getKeyS()) {
		this->setPosition(this->position + glm::vec2(0.0f, -cameraSpeed));
	}
	if(iInput->getKeyQ()) {
		this->setPosition(this->position + glm::vec2(-cameraSpeed, 0.0f));
	}
	if(iInput->getKeyD()) {
		this->setPosition(this->position + glm::vec2(cameraSpeed, 0.0f));
	}
	if(iInput->getKeyA()) {
		this->setScale(this->scale + scaleSpeed);
	}	
	if(iInput->getKeyE()) {
		this->setScale(this->scale - scaleSpeed);
	}	
	if(this->needMatrixUpdate) {

		glm::vec3 translate(-this->position.x + this->screenWidth/2, -this->position.y + this->screenHeight/2, 0.0f);
		this->cameraMatrix = glm::translate(this->orthoMatrix, translate);

		glm::vec3 scale(this->scale, this->scale, 0.0f);
		this->cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * this->cameraMatrix;

		this->needMatrixUpdate = false;
	}
}

}