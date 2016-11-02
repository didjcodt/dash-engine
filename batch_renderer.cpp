/*
 * batch_renderer.cpp
 * Main batch renderer taking the primitives and talking to OpenGL
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */


#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include <vector>
#include <array>
#include <cmath>

#include "sphere_renderer.hpp"
#include "sphere_primitive.hpp"
#include "scene_camera.hpp"
#include "texture.hpp"

#include "batch_renderer.hpp"

namespace scene_renderer {

	Batch_renderer::Batch_renderer() {
		// Get VAOs from primitive renderers
		primitive_renderers::Sphere_renderer sphere_renderer(360);

		for(auto vector: sphere_renderer.getVertexArray()) {
			std::array<float, 3> temp{{
				vector.getX(),
				vector.getY(),
				vector.getZ()
			}};
			vertexArray.push_back(temp);

			std::array<float, 2> tempPolar{{
				static_cast<float>(vector.getTheta()/M_PI),
				static_cast<float>((vector.getPhi() + M_PI) )
			}};
			UVMap.push_back(tempPolar);
		}

		vertexIndexArray = sphere_renderer.getVertexIndexArray();

		for(auto vector: sphere_renderer.getNormals()) {
			std::array<float, 3> temp{{
				vector.getX(),
				vector.getY(),
				vector.getZ()
			}};
			normalsArray.push_back(temp);
		}

		// Buffer generation
		glGenBuffers(4, &vertexBuffer[0]);

		// Fill the buffers
		// Vertex Array
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, 
				vertexArray.size()*sizeof(std::array<float, 3>),
				(GLvoid*)vertexArray.data(), GL_STATIC_DRAW);

		// Vertex Index Array
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				vertexIndexArray.size()*sizeof(unsigned int),
				(GLvoid*)vertexIndexArray.data(), GL_STATIC_DRAW);

		// Normal Array
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
		glBufferData(GL_ARRAY_BUFFER,
				normalsArray.size()*sizeof(std::array<float, 3>),
				(GLvoid*)normalsArray.data(), GL_STATIC_DRAW);

		// UV Map
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[3]);
		glBufferData(GL_ARRAY_BUFFER,
				UVMap.size()*sizeof(std::array<float, 2>),
				(GLvoid*)UVMap.data(), GL_STATIC_DRAW);

	}

	void Batch_renderer::add_to_pool(primitives::Sphere* sphere) {
		pool.push_back(sphere);
	}

	void Batch_renderer::add_camera(scene::Camera* cam) {
		cameras.push_back(cam);
	}

	void Batch_renderer::add_texture(std::string filename) {
		texture::Texture* text = new texture::Texture(filename);
		textures.push_back(text);
	}

	void Batch_renderer::load_textures() {
		// Texture generation
		glEnable(GL_TEXTURE_2D);
		for(auto texture: textures) {
			GLuint id;
			glGenTextures(1, &id);
			texture->setId(id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(),
					texture->getHeight(), 0, GL_RGB,
					GL_UNSIGNED_BYTE, texture->getImage());
		}
	}

	void Batch_renderer::render() {

		for(auto camera: cameras) {
			camera->initRender();

			for(auto sphere: pool) {
				// Get parameters : x, y, z, radius
				vec3<float> pos = sphere->getPosition();
				float radius = sphere->getRadius();

				// Change MV matrix
				// Used to translate by (x, y, z) the sphere
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glScalef(radius, radius, radius);
				glTranslatef(pos.getX(), pos.getY(), pos.getZ());

				// Set UV Map
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[3]);
				glTexCoordPointer(2, GL_FLOAT, 2*sizeof(float), 0);

				// Apply the texture
				if(sphere->hasTexture())
					glBindTexture(GL_TEXTURE_2D,
							textures[sphere->getTexture()]->getId());

				// Set the state machine to Vertex Array enabled
				// Use first buffer for array buffer
				glEnableClientState(GL_VERTEX_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
				glVertexPointer(3, GL_FLOAT, 0, 0);

				// Use second buffer for index buffer
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[1]);
				glDrawElements(GL_TRIANGLES, vertexIndexArray.size(),
						GL_UNSIGNED_INT, 0);

				glDisableClientState(GL_VERTEX_ARRAY);

				// Use third for normals
				glEnableClientState(GL_NORMAL_ARRAY);
				glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
				glNormalPointer (GL_FLOAT, 0, 0);
				glEnable(GL_NORMALIZE);

				// Now is to apply the materials
				if(sphere->hasColor()) {
					vec4<float> specu = sphere->getSpec();
					GLfloat material_specular[4] = {
						specu.getX(), specu.getY(), specu.getZ(), specu.getT()
					};
					vec4<float> col = sphere->getSpec();
					GLfloat material_color[4] = {
						col.getX(), col.getY(), col.getZ(), col.getT()
					};

					glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
					glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_color);
					glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, sphere->getShininess());
				}

				// Now apply the translation
				glPopMatrix();
			}
		}
	}

}
