#include <vector>
#include <iostream>


class WesselPerlinNoise {
private:
	std::vector<int> perm;
private:
	float fade(float t);
	float lerp(float t, float a, float b);
	float grad(int hash, float x, float y);
public:
	WesselPerlinNoise();
	double noise(float x, float y);
	~WesselPerlinNoise();
};

