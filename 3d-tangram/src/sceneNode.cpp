#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>

#include "mgl/mgl.hpp"
#include "sceneNode.h"

using namespace sg;
using namespace std;

sceneNode::sceneNode(string meshFile) {
	createMesh(meshFile);
	createShaderPrograms();
	modelMatrix = glm::mat4(1.0f);
}

sceneNode::sceneNode() {
	mesh = nullptr;
	shader = nullptr;
	modelMatrix = glm::mat4(1.0f);
}

void sceneNode::addObject(sceneNode obj){
	obj.transform(modelMatrix);
	sceneNodes.push_back(obj);
}

void sceneNode::transform(glm::mat4 transformation) {
	modelMatrix = transformation * modelMatrix;
}

void sceneNode::transform(float r, glm::vec3 t, float sx, float sy) {
	const glm::mat4 translation = glm::translate(t);
	const glm::mat4 rotation = glm::rotate(glm::radians(r), glm::vec3(0.0f, 0.0f, 1.0f));
	const glm::mat4 scale = glm::scale(glm::vec3(sx, sy, 0));
	const glm::mat4 transform = translation * rotation * scale;
	modelMatrix = transform * modelMatrix;

} //transform the object inside on itself to allign inside parent

void sceneNode::draw() {
	if (mesh) {
		//draw mesh and shader
		shader->bind();
		glUniformMatrix4fv(ModelMatrixId, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		mesh->draw();
		shader->unbind();
	}
	for (size_t i = 0; i < sceneNodes.size(); i++) {
		sceneNodes[i].draw();
	}
	
}      //draw object in scene