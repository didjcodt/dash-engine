/*
 * scene_light.hpp
 * Light controller main header
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

namespace scene {

	// List of supported lights
	GLenum const gl_lights[8] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
							   GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};

	class Lighting {
		public:
			Lighting();
			void toggleLight(int id);

			// Positions
			void setLightPosition(int id, vec4<float> pos);
			vec4<float> getLightPosition(int id);

			// Colors
			void setLightColor(int id, vec4<float> color);
			vec4<float> getLightColor(int id);

		private:
			GLfloat light_position[8][4] = {{10.0f,  10.0f,  10.0f, 1.0f},
											{-10.0f, 0.0f,   -1.0f, 1.0f},
											{10.0f, -10.0f,  10.0f, 1.0f},
											{10.0f,  10.0f, -10.0f, 1.0f},
											{-10.0f,-10.0f,  10.0f, 1.0f},
											{-10.0f, 10.0f, -10.0f, 1.0f},
											{10.0f, -10.0f, -10.0f, 1.0f},
											{-10.0f,-10.0f, -10.0f, 1.0f}};

			GLfloat color[8][4]  = {{1.0f, 0.9f, 0.8f, 1.0f},
									{0.0f, 0.1f, 0.3f, 1.0f},
									{1.0f, 0.0f, 0.0f, 1.0f},
									{1.0f, 1.0f, 0.0f, 1.0f},
									{1.0f, 0.0f, 1.0f, 1.0f},
									{0.0f, 1.0f, 1.0f, 1.0f},
									{1.0f, 1.0f, 1.0f, 1.0f},
									{0.5f, 1.0f, 0.0f, 1.0f}};


	};
}
