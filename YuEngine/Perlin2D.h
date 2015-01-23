#pragma once

namespace YuEngine {

class Perlin2D
{
public:
	Perlin2D(void);
	~Perlin2D(void);
	void init(int _size, int _set, int _octaves);
	void init(int _size, int _set, int _octaves, float firstValue);
	double noise(int i);
	double noiseFunction(double x);
	double linearInterpolation(double a, double b, double x);
	double cosInterpolation(double a, double b, double x);
	double coherentNoise(double x, double persistance);

private:
	double* values;
	int octaves;
	int set;
	int size;
};

}