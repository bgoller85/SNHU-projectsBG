#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// GLOBAL VARIABLES ----------------------------------------------
// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// Camera properties
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f); // Adjust the Z value as needed
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float fov = 45.0f;				// Initial field of view
float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;
float cameraSpeed = 0.001f;		// Adjust this value for movement speed
float cameraSensitivity = 0.1f; // Adjust this value for mouse sensitivity

// Mouse properties
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//lighting
struct Material {
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float shininess;
};

struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

// Object Data
const float planeVerts[] = {
	// positions         texture coords
	 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f    // top left 
};
const unsigned int planeIndices[] = {
	  0, 1, 3, // first triangle
	  1, 2, 3  // second triangle
};
const unsigned int planeStride = 5;
const unsigned int planePosOffset = 0, planeTexCoordOffset = 3;
unsigned int planeVao = 0, planeVbo = 0, planeEbo = 0;

const float cubeVerts[] = {
	// position (x, y, z) texcoord(u, v)  color(rgba)
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f, 0.0f, 0.0f, 1.0f
};
const unsigned int cubeStride = 9;
const unsigned int cubePosOffset = 0, cubeTexCoordOffset = 3, cubeColorOffset = 5;
unsigned int cubeVao = 0, cubeVbo = 0;

const float pyramidVerts[] = {	
	// positions(x, y, z)	color(r, b, g, a)
	 0.0f,  1.0f,  0.0f,	1.0f, 0.0f, 0.0f, 1.0f,	// 0: top
	 0.5f,  0.0f,  0.5f,	0.0f, 1.0f, 0.0f, 1.0f,	// 1: front right
	-0.5f,  0.0f,  0.5f,	0.0f, 0.0f, 1.0f, 1.0f,	// 2: front left
	-0.5f,  0.0f, -0.5f,	0.0f, 1.0f, 1.0f, 1.0f,	// 3: back left
	 0.5f,  0.0f, -0.5f,	1.0f, 0.0f, 1.0f, 1.0f	// 4: back right
};
const unsigned int pyramidIndices[] = {
	0, 1, 2,	// front
	0, 3, 2,	// left
	0, 4, 1,	// right
	0, 3, 4,	// back

	2, 3, 4,	// bottom 
	2, 4, 1
};
unsigned int pyramidStride = 7;
unsigned int pyramidPosOffset = 0, pyramidColorOffset = 3;
unsigned int pyramidVao = 0, pyramidVbo = 0, pyramidEbo = 0;

std::vector<float> cylinderVerts;				
int numSideVerts = 0, numTopBotVerts = 0;
unsigned int cylinderStride = 7;
unsigned int cylinderPosOffset = 0, cylinderColorOffset = 3;
unsigned int cylinderVao = 0, cylinderVbo = 0;


// FUNCTION PROTOTYPES -------------------------------------------
GLFWwindow* InitWindow(const char* winName, int winWidth, int winHeight);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

char* LoadFile(const char* const filename);
void LoadTexture(const char* filename, unsigned int& texID);
void CreateShaders(const char* const vertShader, const char* const fragShader, int& program);
bool CompileShader(int& shaderobj, const char* filename, GLenum type);

void GenerateCylinder(float raidus, float height, float slices);


int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		printf("GLFW initialisation failed!");
		glfwTerminate();
		return 1;
	}

	// Create the window
	GLFWwindow* mainWindow = InitWindow("3D Drill Scene", WIDTH, HEIGHT);
	if (!mainWindow) { return -1; }

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);
	glfwSetCursorPosCallback(mainWindow, mouse_callback);
	glfwSetScrollCallback(mainWindow, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW initialisation failed!");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// Load Shaders
	int colorProgram = -1, texProgram = -1;
	CreateShaders("color.vs", "color.fs", colorProgram);
	CreateShaders("texture.vs", "texture.fs", texProgram);

	// Load Texture(s)
	unsigned int concreteTex = 0;
	LoadTexture("concrete.jpg", concreteTex);	

	unsigned int woodTex = 0;
	LoadTexture("wood-grain-texture.jpg", woodTex);

	unsigned int dewaltTex = 0;
	LoadTexture("dewalt.jpg", dewaltTex);

	// Create VAO & VBOs
	// plane object
	{
		glGenVertexArrays(1, &planeVao);
		assert(planeVao != 0);
		glBindVertexArray(planeVao);

		glGenBuffers(1, &planeVbo);
		assert(planeVbo != 0);
		glBindBuffer(GL_ARRAY_BUFFER, planeVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVerts), planeVerts, GL_STATIC_DRAW);

		//vertex position data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, planeStride * sizeof(float), (void*)planePosOffset);
		glEnableVertexAttribArray(0);

		// texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, planeStride * sizeof(float), (void*)(planeTexCoordOffset * sizeof(float)));
		glEnableVertexAttribArray(2);

		glGenBuffers(1, &planeEbo);
		assert(planeEbo != 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(planeIndices), planeIndices, GL_STATIC_DRAW);
	}
	
	// 3D Cube object
	{
		glGenVertexArrays(1, &cubeVao);
		assert(cubeVao != 0);
		glBindVertexArray(cubeVao);

		glGenBuffers(1, &cubeVbo);
		assert(cubeVbo != 0);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

		// vertex postitions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cubeStride * sizeof(float), (void*)cubePosOffset);
		glEnableVertexAttribArray(0);

		// vertex color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, cubeStride * sizeof(float), (void*)(cubeColorOffset * sizeof(float)));
		glEnableVertexAttribArray(1);

		// tex coord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, cubeStride * sizeof(float), (void*)(cubeTexCoordOffset * sizeof(float)));
		glEnableVertexAttribArray(2);
	}
	
	// 3D Pyramid object
	{
		glGenVertexArrays(1, &pyramidVao);
		assert(pyramidVao != 0);
		glBindVertexArray(pyramidVao);

		glGenBuffers(1, &pyramidVbo);
		assert(pyramidVbo != 0);
		glBindBuffer(GL_ARRAY_BUFFER, pyramidVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVerts), pyramidVerts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, pyramidStride * sizeof(float), (void*)pyramidPosOffset);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, pyramidStride * sizeof(float), (void*)(pyramidColorOffset * sizeof(float)));
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &pyramidEbo);
		assert(pyramidEbo != 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidEbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);
	}

	// 3D Cylinder object
	GenerateCylinder(0.5f, 1.0f, 20);
	{
		glGenVertexArrays(1, &cylinderVao);
		assert(cylinderVao != 0);
		glBindVertexArray(cylinderVao);

		glGenBuffers(1, &cylinderVbo);
		assert(cylinderVbo != 0);
		glBindBuffer(GL_ARRAY_BUFFER, cylinderVbo);
		glBufferData(GL_ARRAY_BUFFER, (cylinderVerts.size() * sizeof(float)), cylinderVerts.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cylinderStride * sizeof(float), (void*)cylinderPosOffset);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, cylinderStride * sizeof(float), (void*)(cylinderColorOffset * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	// Define Material Properties
	Material material;
	material.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	material.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	material.shininess = 32.0f;

	// Define Light Properties
	Light light;
	light.position = glm::vec3(1.0f, 0.75f, -2.0f); // Position of the point light
	light.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	light.diffuse = glm::vec3(0.2f, 0.5f, 0.5f);
	light.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	// Render Loop (loops until window is closed)
	while (!glfwWindowShouldClose(mainWindow))
	{
		float currFrame = (float)glfwGetTime();
		deltaTime = currFrame - lastFrame;
		lastFrame = currFrame;

		processInput(mainWindow);

		// Clear window
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Camera Update
		glm::mat4 mView = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
		glm::mat4 mProjection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		// set this shader active
		glUseProgram(colorProgram);

		// send camera data to color shader
		unsigned int viewLoc = 0, projLoc = 0, modelLoc = 0;
		viewLoc = glGetUniformLocation(colorProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));
		
		projLoc = glGetUniformLocation(colorProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));

		// Pass Material to Shader
		glUniform3fv(glGetUniformLocation(colorProgram, "material.ambient"), 1, &material.ambient[0]);
		glUniform3fv(glGetUniformLocation(colorProgram, "material.diffuse"), 1, &material.diffuse[0]);
		glUniform3fv(glGetUniformLocation(colorProgram, "material.specular"), 1, &material.specular[0]);
		glUniform1f(glGetUniformLocation(colorProgram, "material.shininess"), material.shininess);

		// Pass Light to Shader
		glUniform3fv(glGetUniformLocation(colorProgram, "light.position"), 1, &light.position[0]);
		glUniform3fv(glGetUniformLocation(colorProgram, "light.ambient"), 1, &light.ambient[0]);
		glUniform3fv(glGetUniformLocation(colorProgram, "light.diffuse"), 1, &light.diffuse[0]);
		glUniform3fv(glGetUniformLocation(colorProgram, "light.specular"), 1, &light.specular[0]);

		// Pass Camera (View) Position to Shader
		glUniform3fv(glGetUniformLocation(colorProgram, "viewPos"), 1, &cameraPosition[0]);

		// Material for the pyramid
		Material pyramidMaterial;
		pyramidMaterial.ambient = glm::vec3(1.0f, 0.0f, 0.0f); // Red
		pyramidMaterial.diffuse = glm::vec3(1.0f, 0.0f, 0.5f);
		pyramidMaterial.specular = glm::vec3(0.5f, 0.5f, 0.5f);
		pyramidMaterial.shininess = 32.0f;

		// 3D Pyramid
		glBindVertexArray(pyramidVao);
		glm::mat4 mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(-0.95f, -0.20f, -0.5f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.5f, 0.05f));

		modelLoc = glGetUniformLocation(colorProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices) / sizeof(pyramidIndices[0]), GL_UNSIGNED_INT, 0);

		// Material for the cylinder
		Material cylinderMaterial;
		cylinderMaterial.ambient = glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
		cylinderMaterial.diffuse = glm::vec3(1.0f, 1.0f, 0.0f);
		cylinderMaterial.specular = glm::vec3(0.5f, 0.5f, 0.5f);
		cylinderMaterial.shininess = 32.0f;

		// 3D Cylinder
		glBindVertexArray(cylinderVao);

		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(0.5f, 0.20f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(0.20f, 0.55f, 0.25f));
		modelLoc = glGetUniformLocation(colorProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, numSideVerts);	// draw sides
		glDrawArrays(GL_TRIANGLE_FAN, numSideVerts, numTopBotVerts); // top
		glDrawArrays(GL_TRIANGLE_FAN, (numSideVerts + numTopBotVerts), numTopBotVerts); // bottom

		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(0.4f, 0.5f, 0.0f));
		mModel = glm::rotate(mModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		mModel = glm::scale(mModel, glm::vec3(0.20f, 0.57f, 0.25f));
		modelLoc = glGetUniformLocation(colorProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		glDrawArrays(GL_TRIANGLE_STRIP, 0, numSideVerts);	// draw sides
		glDrawArrays(GL_TRIANGLE_FAN, numSideVerts, numTopBotVerts); // top
		glDrawArrays(GL_TRIANGLE_FAN, (numSideVerts + numTopBotVerts), numTopBotVerts); // bottom

		// 3D Cube
		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(0.5f, -0.15f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.20f, 0.5f));
		modelLoc = glGetUniformLocation(colorProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		glBindVertexArray(cubeVao);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// shader program we want to use
		glUseProgram(texProgram);

		// send camera data to texture shader
		viewLoc = glGetUniformLocation(texProgram, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mView));
		
		projLoc = glGetUniformLocation(texProgram, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mProjection));

		// 2D Plane 
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, concreteTex);

		// calculate transformations & send data to shader
		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(0.0f, -0.25f, 0.0f));
		mModel = glm::rotate(mModel, glm::radians(-85.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(2.5f, 2.5f, 2.5f));

		modelLoc = glGetUniformLocation(texProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));

		glBindVertexArray(planeVao);
		glDrawElements(GL_TRIANGLES, sizeof(planeIndices)/sizeof(planeIndices[0]), GL_UNSIGNED_INT, 0);

		// 3D Cubes
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_2D, dewaltTex);
		glBindVertexArray(cubeVao);

		// cube 1
		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(-0.25f, -0.1f, 0.25f));
		mModel = glm::scale(mModel, glm::vec3(0.25f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, woodTex);

		// cube 2
		mModel = glm::mat4(1.0f);
		mModel = glm::translate(mModel, glm::vec3(-0.75f, -0.20f, 0.5f));
		mModel = glm::rotate(mModel, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mModel = glm::scale(mModel, glm::vec3(0.5f, 0.15f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mModel));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(mainWindow);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}


// FUNCTION DEFINITIONS --------------------------------------------------
GLFWwindow* InitWindow(const char* winName, int winWidth, int winHeight)
{
	assert(winName);
	GLFWwindow* window = nullptr;

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Core Profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// Allow Forward Compatbility

	window = glfwCreateWindow(winWidth, winHeight, winName, NULL, NULL);
	if (!window)
	{
		printf("GLFW window creation failed!");
		return nullptr;
	}

	return window;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera movement
	float cameraSpeed = float(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPosition += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPosition -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // Reversed since y-coordinates range from bottom to top
	lastX = (float)xpos;
	lastY = (float)ypos;

	xoffset *= cameraSensitivity;
	yoffset *= cameraSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}

char* LoadFile(const char* const filename)
{
	FILE* pFile = fopen(filename, "r");
	if (!pFile)
	{
		printf("File Load Failed: %s\n", filename);
		assert(false);
	}

	// get file size
	std::fseek(pFile, 0, SEEK_END);
	size_t fileSize = (size_t)std::ftell(pFile);
	std::rewind(pFile);

	// copy file into buffer
	char* buffer = new char[fileSize]();
	assert(buffer);
	size_t result = fread(buffer, 1, fileSize, pFile);

	std::fclose(pFile);

	return buffer;
}

bool CompileShader(int& shaderobj, const char* filename, GLenum type)
{
	// Load shader from file
	char* buffer = LoadFile(filename);
	assert(buffer);

	// Create shader
	shaderobj = glCreateShader(type);
	assert(shaderobj);

	glShaderSource(shaderobj, 1, &buffer, nullptr);
	glCompileShader(shaderobj);

	// Check for errors
	GLint status = 0;
	glGetShaderiv(shaderobj, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char errbuffer[4096];
		glGetShaderInfoLog(shaderobj, 4096, NULL, errbuffer);
		printf("Error Compiling Shader %s: %s\n", filename, errbuffer);

		glDeleteShader(shaderobj);
		assert(false);
		return false;
	}

	return true;
}

void CreateShaders(const char* const vertShader, const char* const fragShader, int& program)
{
	assert(vertShader);
	assert(fragShader);
	bool status = false;
	int vShader = -1;
	int fShader = -1;

	// vertex shader
	status = CompileShader(vShader, vertShader, GL_VERTEX_SHADER);
	assert(status == true);

	// fragment shader
	status = CompileShader(fShader, fragShader, GL_FRAGMENT_SHADER);
	assert(status == true);

	// create shader program
	program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);
	
	// linke & check for errors
	GLint loadStatus = 0;
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &loadStatus);
	if (!loadStatus)
	{
		char errbuffer[4096];
		glGetShaderInfoLog(program, 4096, NULL, errbuffer);
		printf("Error Shader Linking: %s\n", errbuffer);
		assert(false);
	}

	/*glDeleteShader(vShader);
	glDeleteShader(fShader);*/
}

void LoadTexture(const char* filename, unsigned int& texID)
{
	assert(filename);

	// Read in texture file
	int width = -1;
	int height = -1;
	int channels = -1;
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);
	assert(data);

	// Generate OpenGL rep of texture
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLenum colorComp = GL_RGB;
	if (channels == 4) { colorComp = GL_RGBA; }
	glTexImage2D(GL_TEXTURE_2D, 0, colorComp, width, height, 0, colorComp, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// clean up
	stbi_image_free(data);
}

void GenerateCylinder(float radius, float height, float slices)
{
	numSideVerts = (slices + 1) * 2;
	numTopBotVerts = slices + 2;

	// Pre-calculate cos & sine for each slice
	float sliceAngleStep = 2.0f * glm::pi<float>() / (float)slices;
	float currSliceAngle = 0.0f;

	std::vector<float> sines, cosines;
	for (int i = 0; i <= slices; ++i)
	{
		sines.push_back(sinf(currSliceAngle));
		cosines.push_back(cosf(currSliceAngle));

		// update slice angle
		currSliceAngle += sliceAngleStep;
	}

	// Calculate cylinder vertices
	float y = height / 2.0f;
	std::vector<float> x, z;
	for (int i = 0; i <= slices; ++i)
	{
		x.push_back(cosines[i] * radius);
		z.push_back(sines[i] * radius);
	}

	// cylinder sides
	for (int i = 0; i <= slices; ++i)
	{
		cylinderVerts.push_back(x[i]);		// top position
		cylinderVerts.push_back(y);
		cylinderVerts.push_back(z[i]);

		cylinderVerts.push_back(1.0f);	// color
		cylinderVerts.push_back(1.0f);
		cylinderVerts.push_back(0.0f);
		cylinderVerts.push_back(1.0f);

		cylinderVerts.push_back(x[i]);		// bottom pos
		cylinderVerts.push_back(-y);
		cylinderVerts.push_back(z[i]);

		cylinderVerts.push_back(1.0f);	// color
		cylinderVerts.push_back(1.0f);
		cylinderVerts.push_back(0.0f);
		cylinderVerts.push_back(1.0f);
	}

	// cylinder top
	cylinderVerts.push_back(0.0f);			// center point
	cylinderVerts.push_back(y);
	cylinderVerts.push_back(0.0f);

	cylinderVerts.push_back(1.0f);	// color
	cylinderVerts.push_back(1.0f);
	cylinderVerts.push_back(0.0f);
	cylinderVerts.push_back(1.0f);
	for (int i = 0; i <= slices; ++i)
	{
		cylinderVerts.push_back(x[i]);	// pos
		cylinderVerts.push_back(y);
		cylinderVerts.push_back(z[i]);

		cylinderVerts.push_back(1.0f);	// color
		cylinderVerts.push_back(1.0f);
		cylinderVerts.push_back(0.0f);
		cylinderVerts.push_back(1.0f);
	}

	// cylinder bottom
	cylinderVerts.push_back(0.0f);	// center point
	cylinderVerts.push_back(-y);
	cylinderVerts.push_back(0.0f);

	cylinderVerts.push_back(1.0f);	// color
	cylinderVerts.push_back(1.0f);
	cylinderVerts.push_back(0.0f);
	cylinderVerts.push_back(1.0f);
	for (int i = 0; i <= slices; ++i)
	{
		cylinderVerts.push_back(x[i]);	// pos
		cylinderVerts.push_back(-y);
		cylinderVerts.push_back(z[i]);

		cylinderVerts.push_back(1.0f);	// color
		cylinderVerts.push_back(1.0f);
		cylinderVerts.push_back(0.0f);
		cylinderVerts.push_back(1.0f);
	}
}
