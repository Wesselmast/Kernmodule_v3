#include <vector>
#include <iostream>
#include <algorithm>

class WesselPerlinNoise {
private: //section for private variables
	int* perm;
private: //section for private functions
	float fade(float t);
	float lerp(float t, float a, float b);
	float grad(int hash, float x, float y);
	double noise(float x, float y);
public: //section for public functions
	WesselPerlinNoise();
	double octaveNoise(float x, float y, int amtOfOctaves);
	~WesselPerlinNoise();
};

