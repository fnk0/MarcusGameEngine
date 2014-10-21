//-------------------------------------------------------------------------//
// Transforms - Tests using transforms for objects
// David Cline
// June 27, 2014
//-------------------------------------------------------------------------//

#include "EngineUtil.h"
#include "Scene.h"

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

int gWidth = 600; // window width
int gHeight = 600; // window height

//ISoundEngine* soundEngine = NULL;
ISound* music = NULL;
Camera dummyCamera;

void keyboardCameraController(Scene *scene) {
    
    float t = 0.025f;
    float r = 0.01f;
    
    glm::vec3 strifeLeft(-t, 0, 0);
    glm::vec3 strifeRight(t, 0, 0);
    glm::vec3 strifeUp(0, t, 0);
    glm::vec3 strifeDown(0, -t, 0);
    glm::vec3 moveForward(0, 0, t);
    glm::vec3 moveBack(0, 0, -t);
    glm::vec3 rotate(0, 1, 0);
    if(glfwGetKey(scene->gWindow, '1')) scene->switchCamera(1);
    if(glfwGetKey(scene->gWindow, '2')) scene->switchCamera(2);
    if(glfwGetKey(scene->gWindow, 'A')) scene->getCamera()->translateLocal(strifeLeft);
    if(glfwGetKey(scene->gWindow, 'D')) scene->getCamera()->translateLocal(strifeRight);
    if(glfwGetKey(scene->gWindow, 'W')) scene->getCamera()->translateLocal(strifeUp);
    if(glfwGetKey(scene->gWindow, 'S')) scene->getCamera()->translateLocal(strifeDown);
    if(glfwGetKey(scene->gWindow, 'Q')) scene->getCamera()->rotateGlobal(rotate, r);
    if(glfwGetKey(scene->gWindow, 'E')) scene->getCamera()->rotateGlobal(rotate, -r);
    if(glfwGetKey(scene->gWindow, GLFW_KEY_UP)) scene->getCamera()->translateLocal(moveForward);
    if(glfwGetKey(scene->gWindow, GLFW_KEY_DOWN)) scene->getCamera()->translateLocal(moveBack);
    if(glfwGetKey(scene->gWindow, GLFW_KEY_LEFT)) scene->getCamera()->rotateGlobal(rotate, r);
    if(glfwGetKey(scene->gWindow, GLFW_KEY_RIGHT)) scene->getCamera()->rotateGlobal(rotate, -r);

    
    
    scene->getCamera()->refreshTransform(scene->getWorldSettings()->getWidth(), scene->getWorldSettings()->getHeight());
}

void ryanRedneck(FILE *F) {
    cout << "Unicorn!!" << endl;
    dummyCamera.refreshTransform((float)gWidth, (float)gHeight);
}

void updateJson(Scene *scene) {
    static float dScale = 0.0005f;
    for(int i = 0; i < scene->getMeshInstances().size(); i++) {
        // scale mesh instance
        
        float scale = scene->getMeshInstances()[i]->T.scale[0];
        scale += dScale;
        if (scale > 1.25f) dScale = -0.0005f;
        if (scale < 0.25f) dScale = 0.0005f;
        scene->getMeshInstances()[i]->setScale(glm::vec3(scale));
        
        // rotate mesh
        glm::quat r = glm::quat(glm::vec3(0.0f, 0.0051f, 0.00f));
        scene->getMeshInstances()[i]->T.rotation *= r;
    }
}

void updateSound(Scene *scene) {
    glm::vec3 eye = scene->getCamera()->getEye();
    glm::vec3 center = scene->getCamera()->getCenter();
    scene->getSoundEngine()->setListenerPosition(vec3df(eye[0], eye[1], eye[2]), vec3df(center[0], center[1], center[2]));
}

void renderJson(Scene *scene) {
    // clear color and depth buffer
    glClearColor(scene->getWorldSettings()->getBackgroundColors().r, scene->getWorldSettings()->getBackgroundColors().g, scene->getWorldSettings()->getBackgroundColors().b, 1.0f);
    //glClearColor(0.5, 0.2, 0.6, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene->updateLights();
    
    // draw scene
    //cout << "Number of instances: " << scene->meshInstances.size() << "\n";
    for(int i = 0; i < scene->getMeshInstances().size(); i++) {
        scene->getMeshInstances()[i]->draw(*scene->getCamera());
    }
}


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

    Scene* scene = new Scene();
    string fileName = args[1];
    scene->loadScene(fileName);

    scene->setSoundEngine(createIrrKlangDevice());
	// Start sound engine
	//soundEngine = createIrrKlangDevice();
	if (!scene->getSoundEngine()) return 0;
	scene->getSoundEngine()->setListenerPosition(vec3df(0, 0, 0), vec3df(0, 0, 1));
    scene->getSoundEngine()->setSoundVolume(0.25f); // master volume control
    
	// Play 3D sound
	string soundFileName = scene->getWorldSettings()->getBackgroundMusic();
	ISound* music = scene->getSoundEngine()->play3D(soundFileName.c_str(), vec3df(0, 0, 10), true); // position and looping
	if (music) music->setMinDistance(5.0f); // distance of full volume
    
    //loadScene(args[1]);
    


    //soundEngine->play2D(scene->getWorldSettings()->getBackgroundMusic().c_str(), true);
    
	// start time (used to time framerate)
	double startTime = TIME();
    
	// render loop
	while (true) {
        //updateJson(scene);
        renderJson(scene);
        updateSound(scene);
        keyboardCameraController(scene);
        
		// handle input
		glfwPollEvents();
		if (glfwGetKey(scene->gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
		if (glfwWindowShouldClose(scene->gWindow) != 0) break;
        
		double xx, yy;
		glfwGetCursorPos(scene->gWindow, &xx, &yy);
		//printf("%1.3f %1.3f ", xx, yy);
        
		// print framerate
		double endTime = TIME();
		//printf("\rFPS: %1.0f  ", 1.0/(endTime-startTime));
		startTime = endTime;
        
		// swap buffers
		//SLEEP(1); // sleep 1 millisecond to avoid busy waiting
		glfwSwapBuffers(scene->gWindow);
	}
    
	// Shut down sound engine
	if (music) music->drop(); // release music stream.
    scene->getSoundEngine()->drop(); // delete engine
    
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	return 0;
}

//-------------------------------------------------------------------------//