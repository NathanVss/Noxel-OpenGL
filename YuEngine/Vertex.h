#pragma once

#include <GL/glew.h>

#include <iostream>

namespace YuEngine {

class TexturingRectangle {
public:

	float topLeftX;
	float topLeftY;

	float topRightX;
	float topRightY;

	float bottomLeftX;
	float bottomLeftY;

	float bottomRightX;
	float bottomRightY;

	TexturingRectangle() {}
	TexturingRectangle(float _topLeftX, float _topLeftY, float _topRightX, float _topRightY, float _bottomRightX, float _bottomRightY,  float _bottomLeftX, float _bottomLeftY) :
		topLeftX(_topLeftX),
		topLeftY(_topLeftY),
		topRightX(_topRightX),
		topRightY(_topRightY),
		bottomRightX(_bottomRightX),
		bottomRightY(_bottomRightY),
		bottomLeftX(_bottomLeftX),
		bottomLeftY(_bottomLeftY) {

	}

	void debug() {
		std::cout << "Rectangle Texturing :" << std::endl;
		std::cout << "[" << topLeftX << ";" << topLeftY << "]" << std::endl;
		std::cout << "[" << topRightX << ";" << topRightY << "]" << std::endl;
		std::cout << "[" << bottomRightX << ";" << bottomRightY << "]" << std::endl;
		std::cout << "[" << bottomLeftX << ";" << bottomLeftY << "]" << std::endl;
	}



};

struct Position {
        float x;
        float y;
};

class Color {
public:
	Color() {

	};
	Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {

	};
	~Color() {

	};
    float r;
    float g;
    float b;
    float a;
};

struct UV {
    float u;
    float v;
};

//The vertex definition
class Vertex {
public:
    //This is the position struct. When you store a struct or class
    //inside of another struct or class, it is called composition. This is
    //layed out exactly the same in memory as if we had a float position[2],
    //but doing it this way makes more sense.
    Position position;

    //4 bytes for r g b a color.
    Color color;

    //UV texture coordinates.
    UV uv;

	Vertex() {

	};
	~Vertex() {

	};

    void setPosition(float x, float y) {
        position.x = x;
        position.y = y;
    }

    void setColor(float r, float g, float b, float a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    void setUV(float u, float v) {
        uv.u = u;
        uv.v = v;
    }
};

}