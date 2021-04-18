#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gl/GL.h>
#include "shaderinit.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Transformations(Shader& ourShader);
void drawBlocks(Shader& ourShader);
void init(void);
void render();

/// <summary>
/// Carlos's Code
void makePlayerPlatform();
void drawPlayer();
void drawCircle();
void makeCircle();

int count = 0;
bool canmove = false;
bool gameStart = false;
const GLuint NumVertices = 6;
GLuint VBO_first;
GLuint VBO_second;
GLuint VBO_third;
GLuint VBO_fourth;
GLuint VBO_fifth;
GLuint VBO_six;
GLuint VBO_seventh;
GLuint VBO_eight;

GLuint VAO_first;
GLuint VAO_second;
GLuint VAO_third;
GLuint VAO_fourth;
GLuint VAO_fifth;
GLuint VAO_six;
GLuint VAO_seventh;
GLuint VAO_eight;

GLuint EBO_first;
GLuint EBO_second;
GLuint EBO_third;
GLuint EBO_fourth;
GLuint EBO_fifth;
GLuint EBO_six;
GLuint EBO_seventh;
GLuint EBO_eight;

/// </summary>

const unsigned int screen_width = 1024;
const unsigned int screen_height = 768;
//int shaderProgram;
const GLuint noOfVerticies = 36;
GLuint VBO,VBO2,VBO3,VBO4,VBO5,VBO6;
GLuint VAO,VAO2,VAO3,VAO4,VAO5,VAO6;
GLuint EBO,EBO2,EBO3,EBO4,EBO5,EBO6;


int main()
{
	if (!glfwInit()) {
		fprintf(stderr, "GLFW FAILED TO START!\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE)
#endif

		GLFWwindow* window;
	window = glfwCreateWindow(screen_width, screen_height, "GL TWO TRIANGLES", NULL, NULL);
	if (window == NULL) {
		std::cout << "Window failed to open." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD failed to initiate\n" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);
	Shader ourShader("shader.vs", "shader.fs");
	glfwMakeContextCurrent(window); //Set the windows to render
	makeCircle();
	makePlayerPlatform();
	init();

	while (!glfwWindowShouldClose(window)) {
		if (glfwGetTime() >= 2.5) {
			if (count == 0) {
				gameStart = true;
			}
		}
		std::cout << glfwGetTime() << " : canStart = " << gameStart << std::endl;
		processInput(window);
		////Add Projection)
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		//glm::mat4 transform = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -15.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)screen_width / (float)screen_height, 0.1f, -14.65f);
		//We specify the uniform variables in the Vertex Shader
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		// We pass thev variables to the shaders
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		//Send the projection
		ourShader.setMat4("projection", projection);
		render();
		Transformations(ourShader);
		drawBlocks(ourShader);

		//ourShader.use();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void drawBlocks(Shader& ourShader)
{
	// REUSE THIS TO DO IT MULTIPLE TIMES!!
	glBindVertexArray(VAO);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 5.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(VAO2);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 4.45f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(VAO3);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 3.9f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(VAO4);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 3.35f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(VAO5);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 2.8f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(VAO6);
	for (unsigned int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-6.95 + i / .65f, 2.25f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, .5f, -1));
		ourShader.setMat4("model", model);
		glDrawElements(GL_TRIANGLES, noOfVerticies, GL_UNSIGNED_INT, 0);
	}
}

void Transformations(Shader& ourShader)
{
	if (canmove) {
		if (count == 0) {
			glfwSetTime(0.0);
			++count;
		}
	}

	//Bind Squares of the Circle
	glBindVertexArray(VAO_first);
	glm::mat4 transform1 = glm::mat4(1.0f);
	if (canmove == true) {
		transform1 = glm::translate(transform1, glm::vec3(0.0, glfwGetTime() * 0.1f, 0.0f));
	}
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

	glBindVertexArray(VAO_second);
	glm::mat4 transform2 = glm::mat4(1.0f);
	if (canmove == true) {
		transform2 = glm::translate(transform2, glm::vec3(0.0, glfwGetTime() * 0.1f, 0.0f));
	}
	unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(transform2));

	glBindVertexArray(VAO_third);
	glm::mat4 transform3 = glm::mat4(1.0f);
	if (canmove == true) {
		transform3 = glm::translate(transform3, glm::vec3(0.0, glfwGetTime() * 0.1f, 0.0f));
	}
	unsigned int transformLoc3 = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(transform3));
	drawCircle();
	ourShader.use();
	//Bind Squares for Player Platform
	glBindVertexArray(VAO_fourth);
	glm::mat4 transform4 = glm::mat4(1.0f);
	transform4 = glm::translate(transform4, glm::vec3(0.0f, 0.0f, 15.0f));
	transform4 = glm::scale(transform4, glm::vec3(2.5f, 2.5f, 2.5f));
	unsigned int transformLoc4 = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc4, 1, GL_FALSE, glm::value_ptr(transform4));
	drawPlayer();
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (gameStart == true) {
			canmove = true;
			glFlush();
		}
	}
}

void init(void) {
	// Vertices this is the input for our shaders
	float verticesRed[] = {	 
		-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // RED
		 0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.7f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.0f
	};

	float verticesGreen[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.0f, // GREEN
		 0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.7f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.0f
	};

	float verticesBlue[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, // BLUE
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.8f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.7f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.5f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.5f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.5f
	};

	float verticesYellow[] = {
		-0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.0f,// YELLOW
		 0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.7f, 0.7f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.5f, 0.5f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.5f, 0.5f, 0.0f
	};

	float verticesPurple[] = {
		-0.5f, -0.5f, -0.5f, 0.5f, 0.0f, 0.5f,//PURPLE
		 0.5f, -0.5f, -0.5f, 0.8f, 0.0f, 0.8f,
		 0.5f,  0.5f, -0.5f, 0.7f, 0.0f, 0.7f,
		-0.5f,  0.5f, -0.5f, 0.5f, 0.0f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.5f,
		 0.5f, -0.5f,  0.5f, 0.5f, 0.0f, 0.5f,
		 0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.5f,
		-0.5f,  0.5f,  0.5f, 0.5f, 0.0f, 0.5f
	};

	float verticesCyan[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f,//CYAN
		 0.5f, -0.5f, -0.5f, 0.0f, 0.8f, 0.8f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.7f, 0.7f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.5f, 0.5f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.5f,
		 0.5f, -0.5f,  0.5f, 0.0f, 0.5f, 0.5f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.5f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.5f, 0.5f
	};

	int indices[] = {
		5, 4, 0,
		1, 5, 0,
		6, 5, 1,
		2, 6, 1,
		7, 6, 2,
		3, 7, 2,
		4, 7, 3,
		0, 4, 3,
		6, 7, 4,
		5, 6, 4,
		1, 0, 3,
		2, 1, 3
	};
	

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRed), verticesRed, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesGreen), verticesGreen, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	glGenBuffers(1, &EBO3);
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesBlue), verticesBlue, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	glGenBuffers(1, &EBO4);
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesYellow), verticesYellow, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	glGenVertexArrays(1, &VAO5);
	glGenBuffers(1, &VBO5);
	glGenBuffers(1, &EBO5);
	glBindVertexArray(VAO5);

	glBindBuffer(GL_ARRAY_BUFFER, VBO5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPurple), verticesPurple, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO5);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO6);
	glGenBuffers(1, &VBO6);
	glGenBuffers(1, &EBO6);
	glBindVertexArray(VAO6);

	glBindBuffer(GL_ARRAY_BUFFER, VBO6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCyan), verticesCyan, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO6);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void render()
{
	static const float black[] = { 1.25f, 0.25f, 1.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// glfw: viewport to window adjustment
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void makeCircle() {

	//first square
	float vertices[] = {
		0.005f, -0.905f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
		0.005f, -0.935f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.015f, -0.935f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.015f, -0.905f, 0.0f, 1.0f, 0.0f, 0.0f // top left
	};

	unsigned int indices[] = {  // note that we start from 0
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &VAO_first);

	// Create Buffer memory
	glGenBuffers(1, &VBO_first);
	glGenBuffers(1, &EBO_first);

	glBindVertexArray(VAO_first);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_first);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_first);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Y crossing square
	float vertices3[] = {
 0.0029f, -0.94f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right diff 0.007 of buttom part
 0.0029f, -0.90f, 0.0f, 1.0f, 0.0f, 0.0f, // top right diff 0.004 buttom of main sq
 -0.012f, -0.90f, 0.0f, 1.0f, 0.0f, 0.0f, // top left
 -0.012f, -0.94f, 0.0f, 1.0f, 0.0f, 0.0f // bottom left
	};
	unsigned int indices3[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &VAO_second);
	glGenBuffers(1, &VBO_second);
	glGenBuffers(1, &EBO_second);
	glBindVertexArray(VAO_second);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_second);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_second);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//X Crossing Square

	float vertices5[] = {
0.009f, -0.909f, 0.0f, 1.0f, 0.0f, 0.0f, // top right diff 0.002
 0.009f, -0.930f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right diff 0.005
 -0.019f, -0.930f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
  -0.019f, -0.909f, 0.0f, 1.0f, 0.0f, 0.0f // top left
	};
	unsigned int indices5[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glGenVertexArrays(1, &VAO_third);
	glGenBuffers(1, &VBO_third);
	glGenBuffers(1, &EBO_third);
	glBindVertexArray(VAO_third);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_third);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices5), vertices5, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_third);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices5), indices5, GL_STATIC_DRAW);

	// position attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute pointer
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void makePlayerPlatform() {
	//main square for player platform
	float vertices[] = {
		-1.5f, -0.75f, -0.75f, 0.5f, 0.5f, 0.0f,//CYAN
		 1.5f, -0.75f, -0.75f, 0.8f, 0.8f, 0.0f,
		 1.5f,  0.75f, -0.75f, 0.7f, 0.7f, 0.0f,
		-1.5f,  0.75f, -0.75f, 0.5f, 0.5f, 0.0f,
		-1.5f, -0.75f,  0.75f, 0.5f, 0.5f, 0.0f,
		 1.5f, -0.75f,  0.75f, 0.5f, 0.5f, 0.0f,
		 1.5f,  0.75f,  0.75f, 0.5f, 0.5f, 0.0f,
		-1.5f,  0.75f,  0.75f, 0.5f, 0.5f, 0.0f
	};

	int indices[] = {
		5, 4, 0,
		1, 5, 0,
		6, 5, 1,
		2, 6, 1,
		7, 6, 2,
		3, 7, 2,
		4, 7, 3,
		0, 4, 3,
		6, 7, 4,
		5, 6, 4,
		1, 0, 3,
		2, 1, 3
	};

	glGenVertexArrays(1, &VAO_fourth);

	// Create Buffer memory
	glGenBuffers(1, &VBO_fourth);
	glGenBuffers(1, &EBO_fourth);

	glBindVertexArray(VAO_fourth);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_fourth);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fourth);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Green outline square left
	float vertices2[] = {
		-0.6f, -0.6f, -0.0f, 0.0f, 0.5f, 0.0f,//GREEN
		 0.6f, -0.6f, -0.0f, 0.0f, 0.8f, 0.0f,
		 0.6f,  0.6f, -0.0f, 0.0f, 0.7f, 0.0f,
		-0.6f,  0.6f, -0.0f, 0.0f, 0.5f, 0.0f,
		-0.6f, -0.6f,  0.0f, 0.0f, 0.5f, 0.0f,
		 0.6f, -0.6f,  0.0f, 0.0f, 0.5f, 0.0f,
		 0.6f,  0.6f,  0.0f, 0.0f, 0.5f, 0.0f,
		-0.6f,  0.6f,  0.0f, 0.0f, 0.5f, 0.0f
	};

	int indices2[] = {
		5, 4, 0,
		1, 5, 0,
		6, 5, 1,
		2, 6, 1,
		7, 6, 2,
		3, 7, 2,
		4, 7, 3,
		0, 4, 3,
		6, 7, 4,
		5, 6, 4,
		1, 0, 3,
		2, 1, 3
	};

	glGenVertexArrays(1, &VAO_fifth);

	// Create Buffer memory
	glGenBuffers(1, &VBO_fifth);
	glGenBuffers(1, &EBO_fifth);

	glBindVertexArray(VAO_fifth);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_fifth);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_fifth);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawPlayer() {
	glBindVertexArray(VAO_fourth);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO_fifth);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void drawCircle() {
	glBindVertexArray(VAO_first);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO_second);
	glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(VAO_third);
	glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
}