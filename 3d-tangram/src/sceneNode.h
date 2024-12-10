#ifndef SCENENODE_H
#define SCENENODE_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include "mgl/mgl.hpp"

using namespace std;

namespace sg {
	class sceneNode
	{
	private:

		GLint modelMatrixId;
		const GLuint UBO_BP = 0;

		mgl::ShaderProgram* shader;
		mgl::Mesh* mesh;

		GLint ModelMatrixId;

		vector<sceneNode> sceneNodes;
	public:
		glm::mat4 modelMatrix;
		sceneNode(string meshFile);
		sceneNode();
		void createMesh(string meshFile) {
			std::string mesh_dir = "./assets/";
			std::string mesh_fullname = mesh_dir + meshFile;

			mesh = new mgl::Mesh();
			mesh->joinIdenticalVertices();
			mesh->create(mesh_fullname);
		}
		void createShaderPrograms() {
			shader = new mgl::ShaderProgram();
			shader->addShader(GL_VERTEX_SHADER, "cube-vs.glsl");
			shader->addShader(GL_FRAGMENT_SHADER, "cube-fs.glsl");

			shader->addAttribute(mgl::POSITION_ATTRIBUTE, mgl::Mesh::POSITION);
			if (mesh->hasNormals()) {
				shader->addAttribute(mgl::NORMAL_ATTRIBUTE, mgl::Mesh::NORMAL);
			}
			if (mesh->hasTexcoords()) {
				shader->addAttribute(mgl::TEXCOORD_ATTRIBUTE, mgl::Mesh::TEXCOORD);
			}
			if (mesh->hasTangentsAndBitangents()) {
				shader->addAttribute(mgl::TANGENT_ATTRIBUTE, mgl::Mesh::TANGENT);
			}

			shader->addUniform(mgl::MODEL_MATRIX);
			shader->addUniformBlock(mgl::CAMERA_BLOCK, UBO_BP);
			shader->create();

			ModelMatrixId = shader->Uniforms[mgl::MODEL_MATRIX].index;
		}
		void addObject(sceneNode sceneNode);
		void transform(glm::mat4 transformation);
		void transform(float rx, float ry ,float rz, glm::vec3 t, float sx, float sy, float sz); //transform the object inside on itself to allign inside parent
		void draw();      //draw object in scene
	};
}
#endif // !SCENENODE_H
