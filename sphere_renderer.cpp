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

	Sphere_renderer::Sphere_renderer(int precision) {
		nbr_points = precision;

		// We'll use spherical coordinates so we need a radius, theta and phi
		const float theta = M_PI/40;
		const float phi   = M_PI/20;
		const int nbrCol = M_PI / theta + 1;
		const int nbrPtsLine = 2 * M_PI / phi + 1;

		vec3<float> tmpBuffer;
		// Generate points list if it doesn't already exists
		for(float curTheta = theta; curTheta < M_PI; curTheta += theta)
			for(float curPhi = 0; curPhi < 2 * M_PI; curPhi += phi) {
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
		int lastPosition = sphere_vertex_position.size() - 1;

		// Indices for top
		for(int i = 0; i < nbrPtsLine; i++) {
			sphere_vertex_index.push_back(lastPosition);
			sphere_vertex_index.push_back(i);
			sphere_vertex_index.push_back(i+1);
		}
		sphere_vertex_index.pop_back(); // Last one is 0, not i
		sphere_vertex_index.push_back(0);

		// Indices for bottom
		for(int i = 0; i < nbrPtsLine; i++) {
			sphere_vertex_index.push_back(lastPosition-nbrPtsLine+i-1);
			sphere_vertex_index.push_back(lastPosition-nbrPtsLine+i);
			sphere_vertex_index.push_back(lastPosition-1);
		}
		sphere_vertex_index[sphere_vertex_index.size()-2] =
			lastPosition-nbrPtsLine-1;

		// (0, 0) is not the top-up point
		// We don't want the two extreme lines
		for(int i = 0; i < nbrCol - 2; i++) {
			// Each last line must be taken differently
			for(int j = 0; j < nbrPtsLine - 1; j++) {
				// We want to put triangles at
				// (i,j), (i+1, j), (i+1, j+1)
				// (i,j), (i, j+1), (i+1, j+1)
				// The relation between position and (i, j) is
				// position = i * nbrPtsLine + j

				// Let's start with first triangle
				sphere_vertex_index.push_back(i * nbrPtsLine + j);
				sphere_vertex_index.push_back(((i+1) * nbrPtsLine + j));
				sphere_vertex_index.push_back(((i+1) * nbrPtsLine + j+1));

				// Let's start with first triangle
				sphere_vertex_index.push_back((i * nbrPtsLine + j));
				sphere_vertex_index.push_back(((i+1) * nbrPtsLine + j+1));
				sphere_vertex_index.push_back((i * nbrPtsLine + j+1));
			}
			// Let's start with first triangle
			sphere_vertex_index.push_back((i+1) * nbrPtsLine - 1);
			sphere_vertex_index.push_back(((i+2) * nbrPtsLine - 1));
			sphere_vertex_index.push_back(((i+1) * nbrPtsLine));

			// Let's start with first triangle
			sphere_vertex_index.push_back(((i+1) * nbrPtsLine - 1 ));
			sphere_vertex_index.push_back(((i+1) * nbrPtsLine));
			sphere_vertex_index.push_back((i * nbrPtsLine));
		}
	}
}
