/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <GL/glut.h>
#include "fake_glm.hpp"

namespace primitives {

	class Sphere {
		public:
			// Constructors with every combination
			// No texture by default for now
			Sphere(int id) { this->id = id; }
			Sphere(int id, vec3<float> pos) { 
				this->id = id;
				position = pos;
			}
			Sphere(int id, float radius) {
				this->id = id;
				this->radius = radius;
			}
			Sphere(int id, vec3<float> pos, float radius) {
				this->id = id;
				position = pos;
				this->radius = radius;
			}

			// Getters and setters
			void setId(int id) { this->id = id; };
			int getId() { return id; };

			void setPosition(vec3<float> pos) { position = pos; };
			vec3<float> getPosition() { return position; };
			
			void setRadius(float radius) { this->radius = radius; };
			float getRadius() { return radius; };
			
			void setColor(vec4<GLfloat> color) { material_colors = color; };
			vec4<GLfloat> getColor() { return material_colors; };

			void setSpec(vec4<GLfloat> spec) { material_speculars = spec; };
			vec4<GLfloat> getSpec() {return material_speculars; };

			void setShininess(GLfloat shininess) { this->shininess = shininess; };
			GLfloat getShininess() { return shininess; };

			void setTexture(GLuint tex) { texture = tex; };
			GLuint getTexture() { return texture; };

		private:
			int id;
			vec3<float> position;
			float radius;
			vec4<GLfloat> material_colors;
			vec4<GLfloat> material_speculars;
			GLfloat shininess;
			GLuint texture;

	};

}
