#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <iostream>

#include "mgl/mgl.hpp"
#include "sceneNode.h"
#include "sceneGraph.h"

using namespace sg;
using namespace std;

sceneGraph::sceneGraph(vector<glm::mat4> vm, vector<glm::mat4> pm) {
	viewMatrix = vm;
	projectionMatrix = pm;
	createCamera();
}//initialize cameras and sceneNode
void sceneGraph::changeCamera(int cameraId, int perspectiveId) {
	camera->setProjectionMatrix(projectionMatrix[perspectiveId]);
	camera->setViewMatrix(viewMatrix[cameraId]);
}//change camera attributes
void sceneGraph::moveCamera(float angleX, float angleY) {
	glm::mat4 cameraView = camera->getViewMatrix();
	glm::vec3 cameraPosition = glm::vec3(glm::inverse(cameraView)[3]);
	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);


	glm::quat qX = glm::angleAxis(angleX, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 camDirection = glm::normalize(center - cameraPosition);
	glm::vec3 camRight = glm::normalize(glm::cross(camDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::quat qY = glm::angleAxis(angleY, camRight);
	glm::quat q = qX * qY;

	cameraPosition = q * cameraPosition;
	camera->setViewMatrix(glm::lookAt(cameraPosition, center, glm::vec3(0.0f, 1.0f, 0.0f)));

	viewMatrix[chosenCamera] = camera->getViewMatrix();

}//update camera on mouse movement
void sceneGraph::drawScene() {
	for (size_t i = 0; i < sceneNodes.size(); i++) {
		sceneNodes[i].draw();
	}
} //draw the scene