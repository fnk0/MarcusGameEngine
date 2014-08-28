
//-------------------------------------------------------------------------//
// Transforms - Tests using transforms for objects
// David Cline
// June 27, 2014
//-------------------------------------------------------------------------//

#include "EngineUtil.h"

//-------------------------------------------------------------------------//
// Callback for Keyboard Input
//-------------------------------------------------------------------------//

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
    
	if (action == GLFW_PRESS &&
		((key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))) {
		printf("\n%c\n", (char)key);
	}
}

//-------------------------------------------------------------------------//
// Global State.  Eventually, this should include the global
// state of the system, including multiple scenes, objects, shaders,
// cameras, and all other resources needed by the system.
//-------------------------------------------------------------------------//

GLFWwindow* gWindow = NULL;
string gWindowTitle = "OpenGL App";
int gWidth = 600; // window width
int gHeight = 600; // window height
int gSPP = 16; // samples per pixel
glm::vec4 backgroundColor;

ISoundEngine* soundEngine = NULL;
ISound* music = NULL;

TriMesh gMesh;
TriMeshInstance gMeshInstance;
Camera gCamera;
RGBAImage textureImage;

//-------------------------------------------------------------------------//
// Parse Scene File
//-------------------------------------------------------------------------//

string ONE_TOKENS = "{}[]()<>+-*/,;";

void loadWorldSettings(FILE *F)
{
	string token, t;
	while (getToken(F, token, ONE_TOKENS)) {
		//cout << "  " << token << endl;
		if (token == "}") break;
		if (token == "windowTitle") getToken(F, gWindowTitle, ONE_TOKENS);
		else if (token == "width") getInts(F, &gWidth, 1);
		else if (token == "height") getInts(F, &gHeight, 1);
		else if (token == "spp") getInts(F, &gSPP, 1);
		else if (token == "backgroundColor") getFloats(F, &backgroundColor[0], 3);
		else if (token == "backgroundMusic") {
			string fileName, fullFileName;
			getToken(F, fileName, ONE_TOKENS);
			getFullFileName(fileName, fullFileName);
			ISound* music = soundEngine->play2D(fullFileName.c_str(), true);
		}
	}
    
	// Initialize the window with OpenGL context
	gWindow = createOpenGLWindow(gWidth, gHeight, gWindowTitle.c_str(), gSPP);
	glfwSetKeyCallback(gWindow, keyCallback);
}

void loadMesh(FILE *F)
{
	string token;
	while (getToken(F, token, ONE_TOKENS)) {
		if (token == "}") {
			break;
		}
		else if (token == "file") {
			string fileName = "";
			getToken(F, fileName, ONE_TOKENS);
			gMesh.readFromPly(fileName, false);
			gMesh.sendToOpenGL();
		}
	}
}

void loadMeshInstance(FILE *F)
{
	string token;
	GLuint vertexShader = NULL_HANDLE;
	GLuint fragmentShader = NULL_HANDLE;
	GLuint shaderProgram = NULL_HANDLE;
    
	while (getToken(F, token, ONE_TOKENS)) {
		if (token == "}") {
			break;
		}
		else if (token == "vertexShader") {
			string vsFileName;
			getToken(F, vsFileName, ONE_TOKENS);
			vertexShader = loadShader(vsFileName.c_str(), GL_VERTEX_SHADER);
		}
		else if (token == "fragmentShader") {
			string fsFileName;
			getToken(F, fsFileName, ONE_TOKENS);
			fragmentShader = loadShader(fsFileName.c_str(), GL_FRAGMENT_SHADER);
		}
		else if (token == "diffuseTexture") {
			string texFileName;
			getToken(F, texFileName, ONE_TOKENS);
			gMeshInstance.diffuseTexture.loadPNG(texFileName);
			gMeshInstance.diffuseTexture.sendToOpenGL();
		}
		else if (token == "mesh") {
			string meshName;
			getToken(F, meshName, ONE_TOKENS);
			// Should go out and find the mesh, but since right now there is
			// only one global mesh, we use that.
			gMeshInstance.setMesh(&gMesh);
		}
	}
    
	shaderProgram = createShaderProgram(vertexShader, fragmentShader);
	gMeshInstance.setShader(shaderProgram);
}

void loadCamera(FILE *F)
{
	string token;
    
	while (getToken(F, token, ONE_TOKENS)) {
		if (token == "}") break;
		else if (token == "eye") getFloats(F, &(gCamera.eye[0]), 3);
		else if (token == "center") getFloats(F, &(gCamera.center[0]), 3);
		else if (token == "vup") getFloats(F, &(gCamera.vup[0]), 3);
		else if (token == "znear") getFloats(F, &(gCamera.znear), 1);
		else if (token == "zfar") getFloats(F, &(gCamera.zfar), 1);
		else if (token == "fovy") getFloats(F, &(gCamera.fovy), 1);
	}
    
	gCamera.refreshTransform((float)gWidth, (float)gHeight);
}

void loadScene(const char *sceneFile)
{
	FILE *F = openFileForReading(sceneFile);
	string token;
    
	while (getToken(F, token, ONE_TOKENS)) {
		//cout << token << endl;
		if (token == "worldSettings") {
			loadWorldSettings(F);
		}
		else if (token == "mesh") {
			loadMesh(F);
		}
		else if (token == "meshInstance") {
			loadMeshInstance(F);
		}
		else if (token == "camera") {
			loadCamera(F);
		}
	}
}

//-------------------------------------------------------------------------//
// Update
//-------------------------------------------------------------------------//

void update(void)
{
	/*
     // move mesh instance
     gMeshInstance.translation[0] += 0.003f;
     if (gMeshInstance.translation[0] >= 1.0f) gMeshInstance.translation[0] = -1.0f;
     */
	
	// scale mesh instance
	static float dScale = 0.0005f;
	float scale = gMeshInstance.T.scale[0];
	scale += dScale;
	if (scale > 1.25f) dScale = -0.0005f;
	if (scale < 0.25f) dScale = 0.0005f;
	gMeshInstance.setScale(glm::vec3(scale));
    
	// rotate mesh
	glm::quat r = glm::quat(glm::vec3(0.0f, 0.0051f, 0.00f));
	gMeshInstance.T.rotation *= r;
	
	gMeshInstance.diffuseColor += glm::vec4(0.0013f, 0.000921f, 0.00119f, 0.0f);
	if (gMeshInstance.diffuseColor[0] > 1.0f) gMeshInstance.diffuseColor[0] = 0.25f;
	if (gMeshInstance.diffuseColor[1] > 1.0f) gMeshInstance.diffuseColor[1] = 0.25f;
	if (gMeshInstance.diffuseColor[2] > 1.0f) gMeshInstance.diffuseColor[2] = 0.25f;
}

//-------------------------------------------------------------------------//
// Draw a frame
//-------------------------------------------------------------------------//

void render(void)
{
	// clear color and depth buffer
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// draw scene
	
	gMeshInstance.draw(gCamera);
}
// change
//-------------------------------------------------------------------------//
// Main method
//-------------------------------------------------------------------------//

int main(int numArgs, char **args)
{
	// check usage
	if (numArgs < 2) {
		cout << "Usage: Transforms sceneFile.scene" << endl;
		exit(0);
	}
    
	// Start sound engine
	soundEngine = createIrrKlangDevice();
	if (!soundEngine) return 0;
	soundEngine->setListenerPosition(vec3df(0, 0, 0), vec3df(0, 0, 1));
	soundEngine->setSoundVolume(0.25f); // master volume control
    
	// Play 3D sound
	string soundFileName;
	ISound* music = soundEngine->play3D(soundFileName.c_str(), vec3df(0, 0, 10), true); // position and looping
	if (music) music->setMinDistance(5.0f); // distance of full volume
    
	loadScene(args[1]);
    
	// start time (used to time framerate)
	double startTime = TIME();
    
	// render loop
	while (true) {
		// update and render
		update();
		render();
        
		// handle input
		glfwPollEvents();
		if (glfwGetKey(gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
		if (glfwWindowShouldClose(gWindow) != 0) break;
        
		double xx, yy;
		glfwGetCursorPos(gWindow, &xx, &yy);
		printf("%1.3f %1.3f ", xx, yy);
        
		// print framerate
		double endTime = TIME();
		printf("\rFPS: %1.0f  ", 1.0/(endTime-startTime));
		startTime = endTime;
        
		// swap buffers
		//SLEEP(1); // sleep 1 millisecond to avoid busy waiting
		glfwSwapBuffers(gWindow);
	}
    
	// Shut down sound engine
	if (music) music->drop(); // release music stream.
	soundEngine->drop(); // delete engine
    
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

//-------------------------------------------------------------------------//


