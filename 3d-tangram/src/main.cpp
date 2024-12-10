////////////////////////////////////////////////////////////////////////////////
//
//  Loading meshes from external files
//
// Copyright (c) 2023-24 by Carlos Martinho
//
// INTRODUCES:
// MODEL DATA, ASSIMP, mglMesh.hpp
//
////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/ext.hpp"

#include <iostream>

#include "mgl/mgl.hpp"
#include "sceneNode.h"
#include "sceneGraph.h"

using namespace sg;

////////////////////////////////////////////////////////////////////////// MYAPP

class MyApp : public mgl::App {
 public:
  sceneGraph* scene = nullptr;
  void initCallback(GLFWwindow *win) override;
  void displayCallback(GLFWwindow *win, double elapsed) override;
  void windowSizeCallback(GLFWwindow *win, int width, int height) override;
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
  void cursorCallback(GLFWwindow* window, double xpos, double ypos) override;
  void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) override;
 private:
  void drawScene();
};

///////////////////////////////////////////////////////////////////////// CAMERA

// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
const glm::mat4 ViewMatrix1 =
    glm::lookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));

// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
const glm::mat4 ViewMatrix2 =
    glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));

// Orthographic LeftRight(-2,2) BottomTop(-2,2) NearFar(1,10)
const glm::mat4 ProjectionMatrix1 =
    glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 1.0f, 10.0f);

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
const glm::mat4 ProjectionMatrix2 =
    glm::perspective(glm::radians(30.0f), 640.0f / 480.0f, 1.0f, 10.0f);

const vector<glm::mat4> vm = { ViewMatrix1, ViewMatrix2 };
const vector<glm::mat4> pm = { ProjectionMatrix1, ProjectionMatrix2};
/////////////////////////////////////////////////////////////////////////// DRAW

void MyApp::drawScene() {
    scene->drawScene();
}

////////////////////////////////////////////////////////////////////// CALLBACKS

void MyApp::initCallback(GLFWwindow *win) {
    //initialize all sceneNodes with the corresponding meshes and shaders
    sceneNode turtle = sceneNode();
    sceneNode turtleHead = sceneNode("turtlesquare.obj");
    sceneNode turtleNeck = sceneNode("turtleparalelogram.obj");
    sceneNode turtleBack = sceneNode("turtletriangle.obj");
    sceneNode turtleShell = sceneNode("turtletriangle.obj");
    sceneNode turtleTail = sceneNode("turtletriangle.obj");
    sceneNode turtleFrontLeg = sceneNode("turtletriangle.obj");
    sceneNode turtleBackLeg = sceneNode("turtletriangle.obj");
    
    //move all sceneNodes to position inside the turtle node
    turtleHead.transform(0.0f, 0.0f, 90.0f, glm::vec3(0.0f, 0.5f, 1.0f), 0.15f, 0.15f, 0.15f);
    turtleNeck.transform(0.0f, 0.0f, -90.0f, glm::vec3(0.0f, 0.20f, 0.40f), 0.15f, 0.15f, 0.15f);
    turtleBack.transform(0.0f, 0.0f, 90.0f, glm::vec3(0.0f, 0.10f, -0.40f), 0.25f, 0.15f, 0.25f);
    turtleShell.transform(135.0f, 0.0f, -90.0f, glm::vec3(0.0f, 0.59f, -0.895f), 0.35f, 0.15f, 0.35f);
    turtleTail.transform(-135.0f, 0.0f, 90.0f, glm::vec3(0.0f, -0.4f, -1.88f), 0.35f, 0.15f, 0.35f);
    turtleFrontLeg.transform(135.0f, 0.0f, -90.0f, glm::vec3(0.0f, -0.41f, -0.4f), 0.175f, 0.15f, 0.175f);
    turtleBackLeg.transform(135.0f, 0.0f, -90.0f, glm::vec3(0.0f, -0.41f, -1.8f), 0.175f, 0.15f, 0.175f);
    
    //add scenodes to parent turtle
    turtle.addObject(turtleHead);
    turtle.addObject(turtleNeck);
    turtle.addObject(turtleBack);
    turtle.addObject(turtleShell);
    turtle.addObject(turtleTail);
    turtle.addObject(turtleFrontLeg);
    turtle.addObject(turtleBackLeg);

    //move turtle to fit the scene inside the scenegraph's camera
    turtle.transform(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.5f), 0.75f, 0.75f, 0.75f);
    
    //initialize sceneGraph and add turtle to the scene
    scene = new sceneGraph(vm, pm);
    scene->addSceneNode(turtle);
}

void MyApp::windowSizeCallback(GLFWwindow *win, int winx, int winy) {
  glViewport(0, 0, winx, winy);
  
  // place for window resize logic
  
  // change projection matrices to maintain aspect ratio
}

void MyApp::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        std::cout << "animating tangram" << std::endl;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
        std::cout << "stopping animating tangram" << std::endl;
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        std::cout << "animating box" << std::endl;
    }
    else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
        std::cout << "stopping animating box" << std::endl;
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        std::cout << "changed camera position" << std::endl;
        scene->switchCameraId();
    }
    else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        std::cout << "changed camera perspective" << std::endl;
        scene->switchCameraPerspective();
    }
}

void MyApp::displayCallback(GLFWwindow *win, double elapsed) {
    drawScene(); 
}

void MyApp::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "(" << xpos << "; " << ypos << ")" << std::endl;
    scene->moveCamera(xpos, ypos);
}

void MyApp::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    std::cout << "(" << xoffset << "; " << yoffset << ")" << std::endl;
}

/////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
  mgl::Engine& engine = mgl::Engine::getInstance();
  engine.setApp(new MyApp());
  engine.setOpenGL(4, 6);
  engine.setWindow(800, 600, "Mesh Loader", 0, 1);
  engine.init();
  engine.run();
  exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
