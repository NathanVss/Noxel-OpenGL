#include "Perlin2D.h"
#include <math.h>
#include <time.h>
#include <random>
#include <iostream>

Perlin2D::Perlin2D(void)
{
}


Perlin2D::~Perlin2D(void)
{
}

double Perlin2D::coherentNoise(double x, double persistance) {

	double sum = 0;
	double p = 1;

	int f = 1;

	for(int i = 0; i < octaves; i++) {

		sum += p*noiseFunction(x * f);
		p *= persistance;
		f *= 2;

	}
	// Il se peut que la somme soit supérieure à 1.
	// Donc on divise sum par l'amplitude max
	// Soit : 1 + P + P^2 + P^3 + .. + P^n = (1-p^n) / ( 1 - p ) ( suite géo ) 
	// Donc on multiplie par l'inverse de ce max pour la lisibilité :
	return sum * (1 - persistance) / ( 1 - p);

}

double Perlin2D::noise(int i) {
	return values[i];
}
double Perlin2D::noiseFunction(double x) {

	int i = (int) ( x / this->set );
	return this->cosInterpolation(this->noise(i), this->noise(i+1), fmod(( x / this->set ), 1));

}

double Perlin2D::linearInterpolation(double a, double b, double x) {
	return a * ( 1 - x ) + b * x;
}

double Perlin2D::cosInterpolation(double a, double b, double x) {
	double k = (1- cos(x*3.14159265)) / 2;
	return this->linearInterpolation(a, b, k);
}

void Perlin2D::init(int _size, int _set, int _octaves) {
	octaves = _octaves;
	set = _set;
	size = _size;
	// Imaginons un monde de 1024 blocs de long
	// Avec un pas de 10.
	// on a _size = 1024
	// _set = 10
	// On a besoin de 103 valeurs ( 102,4 )
	// Si on a deux octaves, alors 103 * 2 valeurs
	// Si 3 octaves, 103 * 4
	double power = pow((double)2, (octaves-1));
	int valuesSize = (int)ceil(size*power);
	values = new double[valuesSize];


	srand(time(NULL)+rand());
	for(int i = 0; i <100; i++) { rand(); }

	for(int i = 0 ; i <valuesSize; i++) {

		values[i] = (double)rand() / RAND_MAX;

	}
}