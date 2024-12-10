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

#define ORTHO_CAMERA 0
#define PERSPECTIVE_CAMERA 1

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
		int chosenPerspective = ORTHO_CAMERA;

		vector<float> scaleFactor;
		vector<float> cameraRadius;
	public:
		sceneGraph(vector<glm::mat4> vm, vector<glm::mat4> pm); //initialize cameras and sceneNode
		void createCamera() {
			cameraRadius = { 5.0f, 5.0f };
			scaleFactor = { 1.0f, 1.0f };
			camera = new mgl::Camera(UBO_BP);
			camera->setViewMatrix(viewMatrix[MAIN_CAMERA]);
			camera->setProjectionMatrix(projectionMatrix[MAIN_CAMERA]);
		}
		void addSceneNode(sceneNode node) {
			sceneNodes.push_back(node);
		}
		void switchCameraId() { 
			chosenCamera = (chosenCamera + 1) % 2; 

			float sf = (cameraRadius[chosenCamera]) / cameraRadius[(chosenCamera+1)%2];

			for (size_t i = 0; i < sceneNodes.size(); i++) {
				sceneNodes[i].transform(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), sf, sf, sf);
			}

			changeCamera(chosenCamera, chosenPerspective);
		}
		void switchCameraPerspective() { 
			chosenPerspective = (chosenPerspective+1)%2; 
			changeCamera(chosenCamera, chosenPerspective); 
		}
		void changeRadius(double yoffset) {
			// Zoom factor: adjust this value for smoother zooming
			const float zoomSpeed = 0.5f;

			// Adjust the camera position based on scroll input
			float sf = (cameraRadius[chosenCamera] + static_cast<float>(yoffset) * zoomSpeed) / cameraRadius[chosenCamera];
			if (scaleFactor[chosenCamera] * sf <= 0.15f || scaleFactor[chosenCamera]*sf >= 60.00f) {

				return; 
			}
			scaleFactor[chosenCamera] = scaleFactor[chosenCamera] * sf;
			std::cout << scaleFactor[chosenCamera] << std::endl;
			cameraRadius[chosenCamera] = cameraRadius[chosenCamera] + static_cast<float>(yoffset) * zoomSpeed;

			for (size_t i = 0; i < sceneNodes.size(); i++) {
				sceneNodes[i].transform(0.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), sf, sf, sf);
			}

			viewMatrix[chosenCamera] = camera->getViewMatrix();
		}
		void changeCamera(int cameraId, int perspectiveId); //change camera attributes
		void moveCamera(float angleX, float angleY); //update camera on mouse movement
		void drawScene(); //draw the scene
	};
}
#endif // !SCENEGRAPH_H
