#include <vector>
#include <iostream>


class WesselPerlinNoise {
private: //section for private variables
	std::vector<int> perm;
private: //section for private functions
	float fade(float t);
	float lerp(float t, float a, float b);
	float grad(int hash, float x, float y);
public: //section for public functions
	WesselPerlinNoise();
	double noise(float x, float y);
	~WesselPerlinNoise();
};

