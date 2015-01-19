#pragma once
#include <gl\glew.h>
#include <Dependecies\glm\glm.hpp>
#include <Dependecies\glm\gtx\transform.hpp>
#include <Dependecies\glm\gtc\type_ptr.hpp>


#include "Object.h"
namespace YuEngine {


class Camera2D : public Object
{
public:
	Camera2D(void);
	~Camera2D(void);

	void init(int screenWidth, int screenHeight);
	void update();

	void setPosition(const glm::vec2 &newPosition);
	glm::vec2 getPosition();

	void setScale(float newScale);
	float getScale();

	glm::mat4 getCameraMatrix();

	int getScreenWidth() {
		return this->screenWidth;
	}
	int getScreenHeight() {
		return this->screenHeight;
	}

private:
	int screenWidth;
	int screenHeight;
	bool needMatrixUpdate;
	float scale;
	glm::vec2 position;
	glm::mat4 cameraMatrix;
	glm::mat4 orthoMatrix;
	
};

}