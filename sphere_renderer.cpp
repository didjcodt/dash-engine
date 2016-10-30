/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include "sphere_renderer.hpp"

#include <cmath>

namespace primitive_renderers {

	sphere_renderer::sphere_renderer(int precision) {
		nbr_points = precision;

		// TODO: Generate the VAOs
		// We'll use spherical coordinates so we need a radius, theta and phi
		const float theta = M_PI/16;
		const float phi   = M_PI/16;

		vec3<float> tmpBuffer;
		// Generate points list if it doesn't already exists
		sphere_vertex_position.push_back(tmpBuffer);
		for(float curTheta = theta; curTheta < M_PI - theta; curTheta += theta)
			for(float curPhi = 0; curPhi < 2 * M_PI - theta; curPhi += phi) {
				tmpBuffer = vec3<float>();
				tmpBuffer.setPolar(1.0f, curTheta, curPhi);
				sphere_vertex_position.push_back(tmpBuffer);
			}

		// Last point is the bottom
		tmpBuffer = vec3<float>(0, 0, -1);
		sphere_vertex_position.push_back(tmpBuffer);
		// Very last is the top :)
		tmpBuffer = vec3<float>(0, 0, 1);
		sphere_vertex_position.push_back(tmpBuffer);


		// Precalculate this value;
		int numline = M_PI/theta;

		// (0, 0) is not the top-up point
		for(int i = 0; i < M_PI/theta; i++) {
			for(int j = 0; j < M_PI/phi; j++) {
				// We want to put trangles at
				// (i,j), (i+1, j), (i+1, j+1)
				// (i,j), (i, j+1), (i+1, j+1)
				// The relation between position and (i, j) is
				// position = i * (M_PI/theta) + j
				// Furthermore, we want position * 3 because of serializing

				// Let's start with first triangle
				sphere_vertex_index.push_back((i * numline + j)*3);
				sphere_vertex_index.push_back(((i+1) * numline + j)*3);
				sphere_vertex_index.push_back(((i+1) * numline + j+1)*3);

				// Let's start with first triangle
				sphere_vertex_index.push_back((i * numline + j)*3);
				sphere_vertex_index.push_back((i * numline + j+1)*3);
				sphere_vertex_index.push_back(((i+1) * numline + j+1)*3);
			}
		}

		// First line is different as it only has 1 point

	}

}
