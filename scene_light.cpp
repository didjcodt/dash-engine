/*
 * scene_light.cpp
 * File describing the light controller
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "scene_light.hpp"

#include <GL/glut.h>
#include "fake_glm.hpp"
#include <iostream>

namespace scene {
	Lighting::Lighting() {
		// Load every light parameters in GPU
		for(int i = 0; i < 8; i++) {
			glLightfv(gl_lights[i], GL_POSITION, light_position[i]);
			glLightfv(gl_lights[i], GL_DIFFUSE, color[i]);
			glLightfv(gl_lights[i], GL_SPECULAR, color[i]);
		}
	}

	void Lighting::toggleLight(int id) {
		if(glIsEnabled(gl_lights[id]) == GL_TRUE) {
			glDisable(gl_lights[id]);
			std::cout << "Disabling light " << id << std::endl;
		} else {
			glEnable(gl_lights[id]);
			std::cout << "Enabling light " << id << std::endl;
		}
	}

	void Lighting::setLightPosition(int id, vec4<float> pos) {
		light_position[id][0] = pos.getX();
		light_position[id][1] = pos.getY();
		light_position[id][2] = pos.getZ();
		light_position[id][3] = pos.getT();
	}

	vec4<float> Lighting::getLightPosition(int id) {
		vec4<float> vector(light_position[id][0],
						   light_position[id][1],
						   light_position[id][2],
						   light_position[id][3]);
		return vector;
	}

	void Lighting::setLightColor(int id, vec4<float> colorvec) {
		color[id][0] = colorvec.getX();
		color[id][1] = colorvec.getY();
		color[id][2] = colorvec.getZ();
		color[id][3] = colorvec.getT();
	}

	vec4<float> Lighting::getLightColor(int id) {
		vec4<float> vector(color[id][0],
						   color[id][1],
						   color[id][2],
						   color[id][3]);
		return vector;
	}
}
