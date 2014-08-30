//
//  Utils.h
//  GameEngineNew
//
//  Created by Marcus Gabilheri on 8/30/14.
//  Copyright (c) 2014 Marcus Gabilheri. All rights reserved.
//

#ifndef __GameEngineNew__Utils__
#define __GameEngineNew__Utils__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GL/glew.h>

#define NULL_HANDLE 0

using namespace std;
using namespace glm;

class Utils {

private:
    vector<string> PATH;
    
public:
    Utils();
    
    FILE* openFileForReading(const string &fileName);
    bool getFullFileName(const string &fileName, string &fullName);
    bool getToken(FILE *f, string &token, const string &oneCharTokens);
    void ERROR(const string &msg, bool doExit = true);
    double TIME(void);
    void SLEEP(int millis);
    void addToPath(const string &p);
    void removeFromPath(const string &p);
    
    vector<string> getPath(void) {
        return PATH;
    }
    
};

//-------------------------------------------------------------------------//
// IMAGE
//-------------------------------------------------------------------------//

class RGBAImage {
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


class Transform {
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


#endif /* defined(__GameEngineNew__Utils__) */
