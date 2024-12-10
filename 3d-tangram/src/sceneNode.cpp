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
	for (size_t i = 0; i < sceneNodes.size(); i++) {
		sceneNodes[i].transform(transformation);
	}
}

void sceneNode::transform(float rx, float ry, float rz, glm::vec3 t, float sx, float sy, float sz) {
	const glm::mat4 translation = glm::translate(t);
	const glm::mat4 rotationx = glm::rotate(glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 rotationy = glm::rotate(glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 rotationz = glm::rotate(glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
	const glm::mat4 rotation = rotationx * rotationy * rotationz;
	const glm::mat4 scale = glm::scale(glm::vec3(sx, sy, sz));
	const glm::mat4 transform = translation * rotation * scale;
	modelMatrix = transform * modelMatrix;

	for (size_t i = 0; i < sceneNodes.size(); i++) {
		sceneNodes[i].transform(transform);
	}
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