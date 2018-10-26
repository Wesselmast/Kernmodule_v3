#pragma once
#include <map>
#include <glm/glm.hpp>

enum side { 
	Front, Back, Right, Left, Top, Bottom 
};

//first 10 block types are in the players' inventory
enum blockType { 
	Dirt, Stone, Sand, GrayBrick, RedBrick,
	OakLog, BirchLog, OakPlank, BirchPlank, 
	BirchLeaf, OakLeaf, CactusMiddle, CactusTop, 
	Grass, Water, Bedrock, Air
};

class BlockPlane {
public: //section for public variables
	side s;
	int xTex;
	int yTex;
public: //section for public functions
	BlockPlane() {}
	BlockPlane(side s, int xTex, int yTex) : s(s), xTex(xTex), yTex(yTex){}
};

class Block {
private: //section for private variables
	int x, y, z;
	blockType type;
private: //section for private functions
	glm::vec2 typeToTex(side s, blockType t) const;
public: //section for public variables
	std::map<side, BlockPlane> planes;
public: //section for public functions
	Block(int x, int y, int z, blockType type);
	int getXPos() const { return x; }
	int getYPos() const { return y; }
	int getZPos() const { return z; }
	blockType getType() const { return type; }
	~Block();
};