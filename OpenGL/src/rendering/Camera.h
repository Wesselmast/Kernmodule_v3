#pragma once
#include "ChunkManager.h"
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>
#include "Chunk.h"
#include <array>


class Camera {
private:
	GLFWwindow* window;
	Chunk* currentChunk;
	ChunkManager* m;
	std::array<glm::vec3, 8> hitbox;
	glm::vec3 cameraPos;
	glm::vec3 relativeCamPos;
	float yVelocity;
public:
	Camera(GLFWwindow* window);
	glm::mat4 getView(const float& deltaTime);
	bool checkCollision(glm::vec3 pos);
	bool checkAll(glm::vec3 pos);
	void SetManager(ChunkManager* manager) { m = manager; }

	float getXPos() { return cameraPos.x; }
	float getYPos() { return cameraPos.y; }
	float getZPos() { return cameraPos.z; }

	int getXGridPos() { return (int)std::round(cameraPos.x); }
	int getYGridPos() { return (int)std::round(cameraPos.y); }
	int getZGridPos() { return (int)std::round(cameraPos.z); }

	glm::vec3 getLookAtBlock();
	glm::vec3 getPlaceBlock();
	Block blockRay(glm::vec3 startPos, glm::vec3 endPos);

	int selectedBlock;
};