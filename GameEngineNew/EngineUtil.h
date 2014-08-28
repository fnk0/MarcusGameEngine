
//-------------------------------------------------------------------------//
// EngineUtil.h
// Some utility stuff - file reading and such
//
// David Cline
// 8/23/2014
//-------------------------------------------------------------------------//

// Prevent visual studio warnings
#define _CRT_SECURE_NO_WARNINGS

// some standard includes
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

// lodePNG stuff (image reading)
#include "lodepng.h"

// OpenGL related includes
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
//#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Sound (irrKlang)
#include <irrKlang.h>
using namespace irrklang;

//-------------------------------------------------------------------------//
// MISCELLANEOUS
//-------------------------------------------------------------------------//

void ERROR(const string &msg, bool doExit = true);
double TIME(void);
void SLEEP(int millis);

//-------------------------------------------------------------------------//
// OPENGL STUFF
//-------------------------------------------------------------------------//

#define MAJOR_VERSION 4
#define MINOR_VERSION 1
GLFWwindow* createOpenGLWindow(int width, int height, const char *title, int samplesPerPixel=0);

#define NULL_HANDLE 0
GLuint loadShader(const string &fileName, GLuint shaderType);
GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

//-------------------------------------------------------------------------//
// GLM UTILITY STUFF
//-------------------------------------------------------------------------//

inline void printVec(const glm::vec2 &v) { printf("[%1.3f %1.3f]\n", v[0], v[1]); }
inline void printVec(const glm::vec3 &v) { printf("[%1.3f %1.3f %1.3f]\n", v[0], v[1], v[2]); }
inline void printVec(const glm::vec4 &v) { printf("[%1.3f %1.3f %1.3f %1.3f]\n", v[0], v[1], v[2], v[3]); }
inline void printQuat(const glm::quat &q) { printf("[%1.3f %1.3f %1.3f %1.3f]\n", q[0], q[1], q[2], q[3]); }
void printMat(const glm::mat4x4 &m);

//-------------------------------------------------------------------------//
// FILE READING
//-------------------------------------------------------------------------//

void addToPath(const string &p);

void removeFromPath(const string &p);

bool getFullFileName(const string &fileName, string &fullName);
FILE *openFileForReading(const string &fileName);

bool getToken(FILE *f, string &token, const string &oneCharTokens);
int getFloats(FILE *f, float *a, int num);
int getInts(FILE *f, int *a, int num);

bool loadFileAsString(const string &fileName, string &buffer);

void replaceIncludes(string &src, string &dest, const string &directive, 
	string &alreadyIncluded, bool onlyOnce);

//-------------------------------------------------------------------------//
// SOUND
//-------------------------------------------------------------------------//

void initSoundEngine(void);
ISound *loadSound();

//-------------------------------------------------------------------------//
// IMAGE
//-------------------------------------------------------------------------//

class RGBAImage
{
public:
	string name;
	vector<unsigned char> pixels;
	unsigned int width, height;
	GLuint textureId;
	GLuint samplerId;

	RGBAImage(void) { width = 0; height = 0; textureId = NULL_HANDLE; samplerId = NULL_HANDLE; }
	~RGBAImage();
	bool loadPNG(const string &fileName, bool doFlipY = true);
	bool writeToPNG(const string &fileName);
	void flipY(void);
	void sendToOpenGL(GLuint magFilter, GLuint minFilter, bool createMipMap);

	unsigned int &operator()(int x, int y) {
		return pixel(x, y);
	}
	unsigned int &pixel(int x, int y) {
		unsigned int *A = (unsigned int*)&pixels[0];
		return A[y*width + x];
	}
	void sendToOpenGL(void) {
		sendToOpenGL(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, true);
	}
};

//-------------------------------------------------------------------------//
// TRANSFORM
//-------------------------------------------------------------------------//

class Transform
{
public:
	// make transform class
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;

	glm::mat4x4 transform;
	glm::mat4x4 invTransform;

	void refreshTransform(void)
	{
		glm::mat4x4 Mtrans = glm::translate(translation);
		glm::mat4x4 Mscale = glm::scale(scale);
		glm::mat4x4 Mrot = glm::toMat4(rotation);
		transform = Mtrans * Mrot * Mscale;  // transforms happen right to left
		invTransform = glm::inverse(transform);
	}
};

//-------------------------------------------------------------------------//
// Camera
//-------------------------------------------------------------------------//

class Camera
{
public:
	// look from, look at, view up
	glm::vec3 eye, center, vup;

	float fovy; // vertical field of view
	float znear, zfar; // near and far clip planes

	glm::mat4x4 worldViewProject;

	void refreshTransform(float screenWidth, float screenHeight)
	{
		glm::mat4x4 worldView = glm::lookAt(eye, center, vup);
		glm::mat4x4 project = glm::perspective((float)fovy,
			(float)(screenWidth / screenHeight), (float)znear, (float)zfar);
		worldViewProject = project * worldView;
	}
};

//-------------------------------------------------------------------------//
// TRIANGLE MESH
//-------------------------------------------------------------------------//

class TriMesh
{
public:
	vector<string> attributes;
	vector<float> vertexData;
	vector<int> indices;
	int numIndices;
    
	GLuint vao; // vertex array handle
	GLuint ibo; // index buffer handle
	
	bool readFromPly(const string &fileName, bool flipZ = false);
	bool sendToOpenGL(void);
	void draw(void);
};

// should extend EngineObject
class TriMeshInstance 
{
public:
	TriMesh *triMesh;
	GLuint shaderProgram;
    
	// replace with material
	glm::vec4 diffuseColor;  
	RGBAImage diffuseTexture;

    
	Transform T;
	
public:
	TriMeshInstance(void);
    
	void setMesh(TriMesh *mesh) { triMesh = mesh; }
	void setShader(GLuint shader) { shaderProgram = shader; }
	void setDiffuseColor(const glm::vec4 &c) { diffuseColor = c; }
	void setScale(const glm::vec3 &s) { T.scale = s; }
	void setRotation(const glm::quat &r) { T.rotation = r; }
	void setTranslation(const glm::vec3 &t) { T.translation = t; }
    
	void refreshTransform(void);
    
	void draw(Camera &camera);
};

//-------------------------------------------------------------------------//
