#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "mgl/mgl.hpp"
#include "sceneNode.h"
#include "sceneGraph.h"

using namespace sg;
using namespace std;

sceneGraph::sceneGraph(vector<glm::mat4> vm, vector<glm::mat4> pm) {
	viewMatrix = vm;
	projectionMatrix = pm;
}//initialize cameras and sceneNode
void sceneGraph::changeCamera(int cameraId) {
}//change camera attributes
void sceneGraph::moveCamera(/**/) {
}//update camera on mouse movement
void sceneGraph::drawScene() {
	for (size_t i = 0; i < sceneNodes.size(); i++) {
		sceneNodes[i].draw();
	}
} //draw the scene