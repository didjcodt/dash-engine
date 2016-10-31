/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cctype>

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glut.h>

#include "sphere_primitive.hpp"
#include "sphere_renderer.hpp"
#include "scene_light.hpp"
#include "scene_camera.hpp"
#include "batch_renderer.hpp"

#include "app.hpp"

static std::vector<primitives::Sphere> sphere_primitives;
static std::vector<scene_renderer::Batch_renderer> batch;
static std::vector<scene::Lighting> lights;
static std::vector<scene::Camera> cameras;

/**
 * Taken from Tamy Boubekeur's TP
 */
void printUsage () {
	std::cout << std::endl
		<< "------------------"                  << std::endl
		<< " ?: Print help"                      << std::endl
		<< " w: Toggle wireframe mode"           << std::endl
		<< " <drag>+<left button>: rotate model" << std::endl 
		<< " <drag>+<right button>: move model"  << std::endl
		<< " <drag>+<middle button>: zoom"       << std::endl
		<< " q, <esc>: Quit"                     << std::endl; 
}

/**
 * Initialize OpenGL states
 * First part is taken from Tamy Boubekeur's TP
 */
void init () {  
	// Specifies the faces to cull
	glCullFace (GL_BACK);
	// Enables face culling
	glEnable (GL_CULL_FACE);
	glDepthFunc (GL_LESS);
	// Enable the z-buffer
	glEnable (GL_DEPTH_TEST); 
	// Set the width of edges in GL_LINE polygon mode
	glLineWidth (2.0);

	// Put some lights
	lights.push_back(scene::Lighting());
	lights[0].toggleLight(0);
	lights[0].toggleLight(1);
	lights[0].toggleLight(2);


	// Put some spheres
	sphere_primitives.push_back(primitives::Sphere(0,
								0.0, 0.0, 0.0, 1.0));

	// Add a batch renderer
	batch.push_back(scene_renderer::Batch_renderer());

	// Put the sphere into batch renderer pool
	batch[0].add_to_pool(sphere_primitives[0]);	

	// Add a camera
	cameras.push_back(scene::Camera());

	// Add it to the batch renderer
	batch[0].add_camera(cameras[0]);

	// Background color
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f); 
	glEnable(GL_POLYGON_SMOOTH); // anti-aliasing
	glEnable(GL_LIGHTING);  // Turn on the lights :)
}

/**
 * Change the viewport to fit window size
 */
void reshape (int w, int h) {
	glViewport (0, 0, (GLint)w, (GLint)h);
}

/**
 * Called when redrawing needed
 */
void display () {  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Erase the color and z buffers.
	glFlush(); // Ensures any previous OpenGL call has been executed

	// Start the rendering of the pool
	batch[0].render();

	glutSwapBuffers();  // swap the render buffer and the displayed (screen) one
}

/**
 * Keyboard management
 */
void keyboard (unsigned char keyPressed, int x, int y) {
	if(isdigit(keyPressed))
			lights[0].toggleLight(keyPressed - '0');

	switch (keyPressed) {
		case 'w':
			GLint mode[2];
			glGetIntegerv(GL_POLYGON_MODE, mode);
			glPolygonMode(GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
			break;
		case 'q':
		case 27:
			exit(0);
			break;
		case '?':
			printUsage();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

/**
 * Mouse management
 */
void mouse (int button, int state, int x, int y) {
}

/**
 * Used to move
 */
void motion (int x, int y) {
}

/**
 * Main function
 */
int main (int argc, char ** argv) {
	// Initialize a glut app
	glutInitWindowSize(1024, 768);
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("TP IGR201 - OpenGL");

	// Initialize some OpenGL states
	init(); // Your initialization code (OpenGL states, geometry, material, lights, etc)

	// Callbacks
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	printUsage();

	// Start GLU, no code after that
	glutMainLoop();
	return 0;
}
