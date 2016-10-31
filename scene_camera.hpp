/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "fake_glm.hpp"

namespace scene {
	class Camera {
		 public:
			 Camera();
			 void rotate(float theta, float phi);
			 void zoom(float rad);
			 void initRender();

		 private:
			 vec3<float> position;
			 vec3<float> target;
			 vec3<float> updirection;
	};
}
