#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "BlockRenderer.h"
#include "Camera.h"
#include "ChunkGenerator.h"
#include "ChunkMeshGenerator.h"
#include "Renderable.h"
#include "ChunkMesh.h"
#include "WorldGeneration.h"
#include <ctime>

#include "Chunk.h"

const bool FULLSCREEN = false;

float pos[] = {
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  -0.5f,  0.5f,  0.0f, 1.0f,
};




float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool endApp = false;


int SCREENWIDTH = FULLSCREEN ? 1920 : 800;
int SCREENHEIGHT = FULLSCREEN ? 1080 : 800; 

const glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCREENWIDTH / SCREENHEIGHT, 0.1f, 100.0f);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREENWIDTH = width;
	SCREENHEIGHT = height;
}

void processInput(GLFWwindow *window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			endApp = true;
	}
		
		

}

int main(void)
{
		glm::mat4 view(1.0f);

		std::srand(time(0));

		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		/* Create a windowed mode window and its OpenGL context */


		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);


		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Hello World", NULL, NULL);
		
		if(FULLSCREEN)
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

		if (!window)
		{
			glfwTerminate();
			return -1;
		}
		
		glfwSetWindowSizeCallback(window, framebuffer_size_callback);

		

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		glfwSwapInterval(0);

		if (glewInit() != GLEW_OK) {
			std::cout << "Error!" << std::endl;
		}

		glClearColor(0.5f, 0.75f, 0.94f, 1.0f);
		glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);

		std::cout << glGetString(GL_VERSION);

		
			
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		glEnable(GL_DEPTH_TEST);

		
		
		
		//RENDERINGSCOPE------------------------------------------------------------------------------------------------------
		{
			Renderer renderer(proj, &view);
			BlockRenderer r(renderer);
			Camera cam(window);
			ChunkGenerator c(64, 25);
			ChunkMeshGenerator mg;
			//WorldGeneration world(3,30,30,10);
			Shader s("res/shaders/Sprite.shader");
			
			
			VertexBufferLayout l;
			l.Push<float>(3);
			l.Push<float>(2);

			VertexBuffer vb(pos, 6 * 5 * sizeof(float));

			VertexArray v;
			v.AddBuffer(vb, l);


			unsigned int indices[] = {
				0,1,2,
				0,2,3
			};

			IndexBuffer b = IndexBuffer(indices, 6);
			/* Loop until the user closes the window */
			
			Chunk* chunk = new Chunk(15, 0, 0, 0);

			for (size_t x = 0; x < 15; x++)
			{
				for (size_t y = 0; y < 15; y++)
				{
					for (size_t z = 0; z < 15; z++)
					{
						if(y == 14)
							chunk->AddBlock(x, y, z, blockType::Grass);
						else
							chunk->AddBlock(x, y, z, blockType::Dirt);
					}
				}
			}
			c.generateChunk();
			ChunkMesh* mesh = mg.generateMesh(*c.displayChunk());

			while (!glfwWindowShouldClose(window) && !endApp)
			{
				processInput(window);
				view = cam.getView(deltaTime);


				std::cout << 1/deltaTime << std::endl;

				float currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;

				if(endApp)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


				//world.displayWorld(&r);
				renderer.Draw(*(mesh->va), s, glm::mat4(1),mesh->buffer->size());
				//c.displayChunk(&r);

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();
			}

			delete mesh;
		}
	
	glfwTerminate();
	return 0;
}
