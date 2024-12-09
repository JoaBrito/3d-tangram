#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "mgl/mgl.hpp"

#include "sceneNode.h"

using namespace std;

#define MAIN_CAMERA 0
#define SECOND_CAMERA 1

namespace sg {
	class sceneGraph
	{
	private:
		mgl::Camera* camera;
		const GLuint UBO_BP = 0;
		
		vector<glm::mat4> viewMatrix;
		vector<glm::mat4> projectionMatrix;

		vector<sceneNode> sceneNodes;

		int chosenCamera = MAIN_CAMERA;
	public:
		sceneGraph(vector<glm::mat4> vm, vector<glm::mat4> pm); //initialize cameras and sceneNode
		void createCamera() {
			camera = new mgl::Camera(UBO_BP);
			camera->setViewMatrix(viewMatrix[MAIN_CAMERA]);
			camera->setProjectionMatrix(projectionMatrix[MAIN_CAMERA]);
		}
		void changeCamera(int cameraId); //change camera attributes
		void moveCamera(/**/); //update camera on mouse movement
		void drawScene(); //draw the scene
	};
}
#endif // !SCENEGRAPH_H
