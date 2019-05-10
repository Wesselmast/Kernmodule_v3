#include "Block.h"

glm::vec2 Block::typeToTex(Side s, BlockType t) const {

#pragma region Generic Blocks
	if (t == BlockType::Grass) {
		if (s == Side::Left || s == Side::Right || s == Side::Front || s == Side::Back) {
			return glm::vec2(3, 0);
		}
		if (s == Side::Top) {
			return glm::vec2(0, 0);
		}
		if (s == Side::Bottom) {
			return glm::vec2(2, 0);
		}
	}

	if (t == BlockType::Sand) return glm::vec2(2, 1);
	if (t == BlockType::Dirt) return glm::vec2(2, 0);
	if (t == BlockType::Stone) return glm::vec2(1, 0);
	if (t == BlockType::Bedrock) return glm::vec2(1, 1);
	if (t == BlockType::GrayBrick) return glm::vec2(6, 0);
	if (t == BlockType::RedBrick) return glm::vec2(7, 0);

#pragma endregion

#pragma region Trees
	if (t == BlockType::OakLog) {
		if (s == Side::Left || s == Side::Right || s == Side::Front || s == Side::Back) {
			return glm::vec2(4, 1);
		}
		if (s == Side::Top || s == Side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == BlockType::BirchLog) {
		if (s == Side::Left || s == Side::Right || s == Side::Front || s == Side::Back) {
			return glm::vec2(5, 7);
		}
		if (s == Side::Top || s == Side::Bottom) {
			return glm::vec2(5, 1);
		}
	}

	if (t == BlockType::OakLeaf) return glm::vec2(5, 3);
	if (t == BlockType::OakPlank) return glm::vec2(4, 0);
	if (t == BlockType::BirchLeaf) return glm::vec2(5, 3);
	if (t == BlockType::BirchPlank) return glm::vec2(3, 1);

#pragma endregion

#pragma region Plants
	if (t == BlockType::CactusMiddle) {
		if (s == Side::Left || s == Side::Right || s == Side::Front || s == Side::Back) {
			return glm::vec2(6, 4);
		}
		if (s == Side::Top || s == Side::Bottom) {
			return glm::vec2(7, 4);
		}
	}

	if (t == BlockType::CactusTop) {
		if (s == Side::Left || s == Side::Right || s == Side::Front || s == Side::Back) {
			return glm::vec2(6, 4);
		}
		if (s == Side::Bottom) {
			return glm::vec2(7, 4);
		}
		if (s == Side::Top) {
			return glm::vec2(5, 4);
		}
	}


#pragma endregion

#pragma region Liquids
	if (t == BlockType::Water) {
		return glm::vec2(3, 4);
	}
#pragma endregion
}

Block::Block(int x, int y, int z, BlockType type) : x(x), y(y), z(z), type(type) {
	for (int i = 0; i < 6; i++) {
		glm::vec2 t = typeToTex((Side)i, type);
		BlockPlane p((Side)i, t.x, t.y);
		planes.insert(std::pair<Side, BlockPlane>((Side)i, p));
	}
}

Block::~Block() {
}



