#pragma once
#include <map>
#include <glm/glm.hpp>

enum Side {
	Front, Back, Right, Left, Top, Bottom
};

//first 10 block types are in the players' inventory
enum BlockType {
	Dirt, Stone, Sand, GrayBrick, RedBrick,
	OakLog, BirchLog, OakPlank, BirchPlank,
	BirchLeaf, OakLeaf, CactusMiddle, CactusTop,
	Grass, Water, Bedrock, Air
};

class BlockPlane {
public: //section for public variables
	Side side;
	int xTex;
	int yTex;
public: //section for public functions
	BlockPlane() {}
	BlockPlane(Side side, int xTex, int yTex) : side(side), xTex(xTex), yTex(yTex) {}
};

class Block {
private: //section for private variables
	int x, y, z;
	BlockType type;
private: //section for private functions
	glm::vec2 typeToTex(Side side, BlockType t) const;
public: //section for public variables
	std::map<Side, BlockPlane> planes;
public: //section for public functions
	Block(int x, int y, int z, BlockType type);
	int getXPos() const { return x; }
	int getYPos() const { return y; }
	int getZPos() const { return z; }
	BlockType getType() const { return type; }
	~Block();
};