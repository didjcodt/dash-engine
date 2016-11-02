/*
 * sphere_renderer.hpp
 * main header for primitive renderer
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <vector>

#include "fake_glm.hpp"

namespace primitive_renderers {

	class Sphere_renderer {
		public:
			Sphere_renderer(int precision);
			
			std::vector<vec3<float> > getVertexArray() {
				return sphere_vertex_position;
			};

			std::vector<unsigned int> getVertexIndexArray() {
				return sphere_vertex_index;
			}

			std::vector<vec3<float> > getNormals() {
				return sphere_vertex_position;
			}

		private:
			int nbr_points;
			std::vector<vec3<float> > sphere_vertex_position;
			std::vector<unsigned int> sphere_vertex_index;
	};

}
