/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "batch_renderer.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>

#include <vector>
#include <array>

#include "sphere_renderer.hpp"
#include "sphere_primitive.hpp"

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
		}

		vertexIndexArray = sphere_renderer.getVertexIndexArray();

		// Buffer generation
		glGenBuffers(2, &vertexBuffer[0]);

		// Fill the buffers
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, 
				vertexArray.size()*sizeof(std::array<float, 3>),
				(GLvoid*)vertexArray.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffer[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				vertexIndexArray.size()*sizeof(unsigned int),
				(GLvoid*)vertexIndexArray.data(), GL_STATIC_DRAW);

	}

	void Batch_renderer::add_to_pool(primitives::Sphere sphere) {
		pool.push_back(sphere);
	}

	void Batch_renderer::render() {

		for(auto sphere: pool) {
			// Get parameters : x, y, z, radius
			vec3<float> pos = sphere.getPosition();
			float radius = sphere.getRadius();

			// Change MV matrix
			// Used to translate by (x, y, z) the sphere
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glScalef(radius, radius, radius);
			glTranslatef(pos.getX(), pos.getY(), pos.getZ());

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
			glEnableClientState(GL_NORMAL_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[2]);
			glNormalPointer (GL_FLOAT, 3*sizeof (float), 0);
			glEnable(GL_NORMALIZE);
			glDisableClientState(GL_NORMAL_ARRAY);
			// Now apply the translation
			glPopMatrix();
		}

	}

}
