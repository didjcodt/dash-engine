/*
 * app.cpp file
 * Main file containing the whole demo of the dash engine
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

static std::vector<primitives::Sphere*> sphere_primitives;
static std::vector<scene_renderer::Batch_renderer*> batch;
static std::vector<scene::Lighting*> lights;
static std::vector<scene::Camera*> cameras;

static float current_time = 0;
static float sup_velocity = 0;
static float traj         = 0;

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
	lights.push_back(new scene::Lighting());
	lights[0]->toggleLight(0);
	lights[0]->toggleLight(1);
	lights[0]->toggleLight(2);

	// Add a batch renderer
	batch.push_back(new scene_renderer::Batch_renderer());

	// Add a texture
	batch[0]->add_texture("textures/brick_256x256.ppm");
	batch[0]->load_textures();

	// Put some spheres
	for(int i = 0; i < 10; i++)
		sphere_primitives.push_back(new primitives::Sphere(0,
									0.0, 0.0, 0.0, 1.0));

	// Apply some texture to sphere
	for(auto sph: sphere_primitives) {
		sph->setColor(vec4<GLfloat>(0.9, 0, 0, 1));
		sph->setSpec(vec4<GLfloat>(1, 1.0, 1, 1));
		sph->setShininess(50.0);
		sph->enableColor(true);
		sph->setTexture(0);
		sph->enableTexture(true);
		// Put the sphere into batch renderer pool
		batch[0]->add_to_pool(sph);
	}

	// Add a camera
	cameras.push_back(new scene::Camera());

	// Add it to the batch renderer
	batch[0]->add_camera(cameras[0]);

	// Background color
	glClearColor (0.0f, 0.0f, 0.0f, 1.0f); 
	glEnable(GL_POLYGON_SMOOTH); // anti-aliasing
	glEnable(GL_LIGHTING);  // Turn on the lights :)
}

/**
 * Change the viewport to fit window size
 */
void reshape (int w, int h) {
	cameras[0]->setAspectRatio(static_cast<float>(w)/static_cast<float>(h));
	glViewport (0, 0, (GLint)w, (GLint)h);
	glutPostRedisplay();
}

/**
 * Called when redrawing needed
 */
void display () {  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Erase the color and z buffers.
	glFlush(); // Ensures any previous OpenGL call has been executed

	// Start the rendering of the pool
	batch[0]->render();

	glutSwapBuffers();  // swap the render buffer and the displayed (screen) one
}

// Just for testing
static int isRight = 0;
static int MLAStep = 0;
static bool firstTime = true;

void startMyLittleAnimation() {
	// First time is for recentering purposes
	if(firstTime) {
		if(MLAStep < 100 + 200) {
			sup_velocity -= 0.01;
			MLAStep++;
		} else {
			MLAStep = 0;
			firstTime = false;
		}
	} else {
		if(MLAStep < 400) {
			sup_velocity += 0.01;
			MLAStep++;
		} else {
			sup_velocity -= 0.01;
			MLAStep++;
			if(MLAStep >= 800)
				MLAStep = 0;
		}
	}
}

/**
 * Keyboard management
 */
void keyboard (unsigned char keyPressed, int x, int y) {
	if(isdigit(keyPressed))
			lights[0]->toggleLight(keyPressed - '0');

	// Just for testing
	if(isRight == 8)
		if(keyPressed == 'b') {
			isRight++;
		} else isRight = 0;
	else if(isRight == 9)
		if(keyPressed == 'a') {
			isRight = 50;
		} else isRight = 0;
	else isRight = 0;


	switch (keyPressed) {
		case 'w':
			GLint mode[2];
			glGetIntegerv(GL_POLYGON_MODE, mode);
			glPolygonMode(GL_FRONT_AND_BACK, mode[1] ==  GL_FILL ? GL_LINE : GL_FILL);
			break;
		case '+':
			sup_velocity += 0.1;
			std::cout << "Changed velocity to " << sup_velocity;
			break;
		case '-':
			sup_velocity -= 0.1;
			std::cout << "Changed velocity to " << sup_velocity;
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
 * Special keys management
 */
void specialinput(int key, int x, int y) {
	switch(key)
	{
		case GLUT_KEY_UP:
			cameras[0]->rotate(0.1, 0);
			if(isRight == 0 || isRight == 1) {
				isRight++;
			} else isRight = 0;
			break;	
		case GLUT_KEY_DOWN:
			cameras[0]->rotate(-0.1, 0);
			if(isRight == 2 || isRight == 3) {
				isRight++;
			} else isRight = 0;
			break;
		case GLUT_KEY_LEFT:
			cameras[0]->rotate(0, 0.1);
			if(isRight == 4 || isRight == 6) {
				isRight++;
			} else isRight = 0;
			break;
		case GLUT_KEY_RIGHT:
			cameras[0]->rotate(0, -0.1);
			if(isRight == 5 || isRight == 7) {
				isRight++;
			} else isRight = 0;
			break;
		case GLUT_KEY_PAGE_DOWN:
			cameras[0]->zoom(-0.1);
			isRight = 0;
			break;
		case GLUT_KEY_PAGE_UP:
			cameras[0]->zoom(0.1);
			isRight = 0;
			break;
	}
	glutPostRedisplay();
}

static bool left_button_state;
static bool right_button_state;
static bool middle_button_state;
int last_x = -1, last_y = -1;

/**
 * Mouse management
 */
void mouse (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON)
		left_button_state = (state == GLUT_DOWN) ? true : false;
	
	else if (button == GLUT_RIGHT_BUTTON)
		right_button_state = (state == GLUT_DOWN) ? true : false;

	else if (button == GLUT_MIDDLE_BUTTON)
		middle_button_state = (state == GLUT_DOWN) ? true : false;
}

/**
 * Used to move
 */
void motion (int x, int y) {
	float delta_x = (last_x == -1) ? 0 : x - last_x;
	float delta_y = (last_y == -1) ? 0 : y - last_y;

	delta_x = (delta_x > 10) ? 0 : delta_x;
	delta_y = (delta_y > 10) ? 0 : delta_y;

	if(left_button_state)
		cameras[0]->rotate(delta_y/20, -delta_x/20);

	else if(right_button_state)
		cameras[0]->move_target(delta_y/20, -delta_x/20);

	else if(middle_button_state)
		cameras[0]->zoom(-delta_y/20 + delta_x/20);

	last_x = x;
	last_y = y;
	glutPostRedisplay();
}

/**
 * Idle function used for animation...
 * TODO: Make a physics engine to control the primitives
 */
void idle() {
	float old_time = current_time;
	current_time = glutGet((GLenum)GLUT_ELAPSED_TIME);
	traj +=  (sup_velocity + 1) * (current_time - old_time)/500;
	int i = 0;
	for(auto sph: sphere_primitives) {
		vec3<float> nextPos(
			sphere_primitives.size() * 0.6 *
			std::sin(traj + 2 * M_PI * i / sphere_primitives.size()),

			sphere_primitives.size() * 0.6 *
			std::cos(traj + 2 * M_PI * i / sphere_primitives.size()),

			sphere_primitives.size() * 0.9 *
			std::sin(traj + 2 * M_PI * i / sphere_primitives.size()) *
			std::sin(traj + 2 * M_PI * i / sphere_primitives.size())
			);
		sph->setPosition(nextPos);
		i++;
	}

	// Just for testing
	if(isRight == 50)
		startMyLittleAnimation();
	glutPostRedisplay();
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
	glutSpecialFunc(specialinput);
	glutIdleFunc(idle);
	printUsage();

	// Start GLU, no code after that
	glutMainLoop();
	return 0;
}
