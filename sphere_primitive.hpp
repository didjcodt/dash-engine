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

	class sphere {
		public:
			// Constructors with every combination
			// No texture by default for now
			sphere() { position.set(0, 0, 0); };
			sphere(vec3<float> pos) { position = pos; };
			sphere(float radius) { this->radius = radius; };
			sphere(vec3<float> pos, float radius) {
				position = pos;
				this->radius = radius;
			}

			// Getters and setters
			void setPosition(vec3<float> pos) { position = pos; };
			vec3<float> getPosition() { return position; };
			void setRadius(float radius) { this->radius = radius; };
			float getRadius() { return radius; };
			void setTexture(GLuint tex) { texture = tex; };
			GLuint getTexture() { return texture; };

		private:
			vec3<float> position;
			float radius;
			GLuint texture;

	};

}
