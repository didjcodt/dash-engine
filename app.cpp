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

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glut.h>

#include "app.hpp"
#include "structs.hpp"

/*
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

void init () {  
	// OpenGL states initialization

	// Specifies the faces to cull
	glCullFace (GL_BACK);
	// Enables face culling
	glEnable (GL_CULL_FACE);
	glDepthFunc (GL_LESS);
	// Enable the z-buffer
	glEnable (GL_DEPTH_TEST); 
	// Set the width of edges in GL_LINE polygon mode
	glLineWidth (2.0);

	// Background color
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f); 
	glEnable(GL_POLYGON_SMOOTH); // anti-aliasing
	glEnable(GL_LIGHTING);  // Turn on the lights :)
}

void reshape (int w, int h) {
	glViewport (0, 0, (GLint)w, (GLint)h);
}

void display () {  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Erase the color and z buffers.
	glFlush(); // Ensures any previous OpenGL call has been executed
	glutSwapBuffers();  // swap the render buffer and the displayed (screen) one
}

void keyboard (unsigned char keyPressed, int x, int y) {
	switch (keyPressed) {
		case 'w':
			GLint mode[2];
			glGetIntegerv(GL_POLYGON_MODE, mode);
			glPolygonMode(GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
			break;
		case 'q':
		case 27:
			exit (0);
			break;
		default:
			printUsage ();
			break;
	}
	glutPostRedisplay ();
}

void mouse (int button, int state, int x, int y) {
}

void motion (int x, int y) {
}

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
