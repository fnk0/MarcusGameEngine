// Veronica Powers

//-------------------------------------------------------------------------//
// Transforms - Tests using transforms for objects
// David Cline
// June 27, 2014
//-------------------------------------------------------------------------//

#include "EngineUtil.h"
#include "Scene.h"
#include <stdlib.h>

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
		//printf("\n%c\n", (char)key);
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

void ryanRedneck() {
    Camera dummyCamera;
    dummyCamera.refreshTransform(0,0);
    exit(EXIT_FAILURE);
}

void keyboardCameraController(Scene *scene) {
    
    float t = 2.5f;
    float r = 0.01f;
    
    glm::vec3 strifeLeft(-t, 0, 0);
    glm::vec3 strifeRight(t, 0, 0);
    glm::vec3 strifeUp(0, t, -t);
    glm::vec3 strifeDown(0, -t, t);
    glm::vec3 moveForward(0, 0, t);
    glm::vec3 moveBack(0, 0, -t);
    glm::vec3 rotate(0, 1, 0);
    
    if(!scene->hasPlayer) {
        if(glfwGetKey(scene->gWindow, '1')) scene->switchCamera(1);
        if(glfwGetKey(scene->gWindow, '2')) scene->switchCamera(2);

    }
    
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

void updateJson(Scene *scene) {
    /*static float dScale = 0.0005f;
    for(int i = 0; i < scene->getMeshInstances().size(); i++) {
        // scale mesh instance
        
        float scale = scene->getNodes()[i]->T.scale[0];
        scale += dScale;
        if (scale > 1.25f) dScale = -0.0005f;
        if (scale < 0.25f) dScale = 0.0005f;
        scene->getNodes()[i]->getMeshInstance()->setScale(glm::vec3(scale));
        
        // rotate mesh
        glm::quat r = glm::quat(glm::vec3(0.0f, 0.0051f, 0.00f));
        scene->getNodes()[i]->T.rotation *= r;
    } */
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
    const map<std::string, Node*> _map = scene->getMapNodes();
    for(auto outer_iter = _map.begin(); outer_iter!= _map.end(); ++outer_iter) {
        outer_iter->second->draw(*scene->getCamera());
    }
}

void gameUpdate(Scene* scene) {
    
}

void mouseUpdate(Scene* scene, double x, double y, int w, int h) {
    //double horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
    //double verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
}


//-------------------------------------------------------------------------//
// Main method
//-------------------------------------------------------------------------//

//const int FRAMES_PER_SECOND = 30;
//const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

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

	// Play 3D sound
	//string soundFileName = scene->getWorldSettings()->getBackgroundMusic();
	//ISound* music = scene->getSoundEngine()->play3D(soundFileName.c_str(), vec3df(0, 0, 10), true); // position and looping
	//if (music) music->setMinDistance(5.0f); // distance of full volume
    
    //loadScene(args[1]);
    //soundEngine->play2D(scene->getWorldSettings()->getBackgroundMusic().c_str(), true);
    
	// start time (used to time framerate)
	double startTime = TIME();
//    double next_game_tick = startTime;
    
	// render loop
	while (true) {

        int w, h;
        glfwGetWindowSize(scene->gWindow, &w, &h);
        glfwSetCursorPos(scene->getGWindow(), w / 2, h / 2);

        //updateJson(scene);
        renderJson(scene);
        updateSound(scene);
        gameUpdate(scene);
        //keyboardCameraController(scene);
        
		// handle input
		glfwPollEvents();
		if (glfwGetKey(scene->gWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;
		if (glfwWindowShouldClose(scene->gWindow) != 0) break;
        
		double xx, yy;
		glfwGetCursorPos(scene->gWindow, &xx, &yy, w, h);
		//printf("%1.3f %1.3f ", xx, yy);

        mouseUpdate(scene, xx, yy);
        
//        next_game_tick += SKIP_TICKS;
		double endTime = TIME();
//        double time_elapsed = startTime - endTime;
//        double sleep_time = next_game_tick - time_elapsed;
//        if(sleep_time > 0) {
//            SLEEP(sleep_time);
//        }

		startTime = endTime;
        
		// swap buffers
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