#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "ChunkGenerator.h"
#include "ChunkMeshGenerator.h"
#include "ChunkMesh.h"
#include "WorldGeneration.h"
#include <ctime>

#include "Chunk.h"
#include "ChunkManager.h"

const bool FULLSCREEN = false;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

bool endApp = false;
bool firstFrame = true;


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

//void LoadChunks(WorldGeneration* w) {
//	w->updateChunks();
//}


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
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK) {
			std::cout << "Error!" << std::endl;
		}

		glClearColor(0.5f, 0.75f, 0.94f, 1.0f);
		glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT);

		std::cout << glGetString(GL_VERSION) << std::endl;

		
			
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));
		glEnable(GL_DEPTH_TEST);
		
		
	







		//RENDERINGSCOPE------------------------------------------------------------------------------------------------------
		{

			float quad[] = {
				-0.01f, -0.01f, 0, 0,
				-0.01f,  0.01f, 1, 0,
				 0.01f,  0.01f, 1, 1,
				 0.01f,  0.01f, 1, 1,
				 0.01f, -0.01f, 0, 1,
				-0.01f, -0.01f, 0, 0,
			};

			VertexBuffer vb(quad, 6 * 4 * sizeof(float));
			VertexBufferLayout layout;
			layout.Push<float>(2);
			layout.Push<float>(2);
			VertexArray va;
			va.AddBuffer(vb, layout);


			//--------------------------------------------------------------------------------------------------------------------

			Renderer renderer(proj, &view);
			Camera cam(window);
			
			
			ChunkMeshGenerator mg;
			ChunkManager manager(renderer);
			WorldGeneration w(&manager, &cam);

			/*size | height | amount of chunks | amount of perlin octaves | height scale*/
			w.generateWorld(10, 40, 15*15, 3, 3.5f, 30);
			cam.SetManager(&manager);
		
			/* Loop until the user closes the window */
			while (!glfwWindowShouldClose(window) && !endApp)
			{
				processInput(window);
				view = cam.getView(deltaTime);

				//chance at biome switch!
				w.updateChunks();

				float currentFrame = glfwGetTime();
				
				if (!firstFrame) {
					deltaTime = currentFrame - lastFrame;
				}
				else {
					firstFrame = false;
				}
				
				lastFrame = currentFrame;

				if(endApp)
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				else
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

				/* Render here */
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				manager.DisplayAllChunks();
				renderer.DrawUi(va);

				/* Swap front and back buffers */
				glfwSwapBuffers(window);

				/* Poll for and process events */
				glfwPollEvents();
			}

		}
	
	glfwTerminate();
	return 0;
}
