//#include <windows.h>
#include <iostream>
#include <GL/glut.h>

#include "objects/Cube.hpp"
#include "objects/Cone.hpp"
#include "objects/Cylinder.hpp"
#include "objects/Scenary.hpp"
#include "transform/mirroring.hpp"
#include "transform/rotation.hpp"
#include "transform/scaling.hpp"
#include "transform/translating.hpp"
#include "transform/shearing.hpp"

//#pragma comment(lib, "C:/Users/Derley/source/repos/openGL/openGL/glut-3.7.6-bin/glut32.lib")

using namespace std;

float x_start_position = 100;
float y_start_position = 100;

float H = 500;
float W = 500;

#define PI 3.1415

//HWND hWnd;

float* test;

void renderScene(void) {

	glDrawPixels(HEIGHT, WIDTH, GL_RGB, GL_FLOAT, test);
	glutSwapBuffers();
	glutPostRedisplay();
}

void Raycaster() {
	Point ka1x = { 1, 1, 1 };
	Point kd1x = { 1, 1, 1 };
	Point ks1x = { 1, 1, 1 };
	double m1x = 1;

	auto* mat_1 = new Material(ka1x, kd1x, ks1x, m1x);


	Point ka1 = { 0.6, 0.2, 0 };
	Point kd1 = { 0.7038, 0.27048, 0.0828 };
	Point ks1 = { 0.256777, 0.137622, 0.086014 };
	double m1 = 12.8;

	auto* material1 = new Material(ka1, kd1, ks1, m1);

	//Chrome
	Point ka2 = { 0.1, 0.9, 0.1 };
	Point kd2 = { 0.1, 0.9, 0.1 };
	Point ks2 = { 0.974597, 0.174597, 0.174597 };
	double m2 = 5.8;
	auto* material2 = new Material(ka2, kd2, ks2, m2);

	//Pearl
	Point ka3 = { 0.7, 0.2, 0.5 };
	Point kd3 = { 1.0, 0.129, 0.129 };
	Point ks3 = { 0.296648, 0.296648, 0.296648 };
	double m3 = 11.264;
	auto* material3 = new Material(ka3, kd3, ks3, m3);

	Cube cubo(10, { 2, 0, 0 }, *material1);
	
	//{ 1, 0, -4 }
	//cubo.Scalling(Point(0.2, 1, 1));
	//cubo.Rotate(3.1415 / 8, { 0, 1, 0 });
	//cubo.Rotate(3.1415 / 8, { 1, 0, 0 });
	//cubo.Translating({ 3, 0, 0 });
	//cubo.Translating({ -1, -1, 0 });

	Cone con(0.5, 1.5, 0, { 5, 0, 0 }, {0, 1, 0}, *material2);
	//Cylinder cil(0.5, 1.5, { 16, 5, 0 }, { 0, 1, 0 }, *material2);
	// raio, altura, posicao, orientação 

	//con.translating({1, 1, -5});

	//Sphere bola(1.3, { 1, 0, -7 }, *material2);

	AmbientLighting light(0.3, 0.3, 0.3);

	PointLighting plight(0.9, 0, 0, {0, 0, 0});

	//SpotLighting splight(1 / 255.f, 1 / 255.f, 1 / 255.f, { 0, 0, -15 }, { 0, 0, -20 }, 3.1415 / 2);

	FarLighting frlight(0.7, 0.7, 0.7, Point(0, 0, -1));

	Camera cam({ 0, 0, -30 }, { 2, 0, 0 }, {0, 1, -30}, -4, 4);

	Scenary* cenario = new Scenary();

	//cenario->addLight(&plight);

	cenario->setAmbientLight(light);

	cenario->addShape(&cubo);
	//cenario->addShape(&bola);
	//cenario->addShape(&con);
	//cenario->addShape(&cil);

	cenario->setCamera(cam);

	cenario->rayCasting();

	test = cenario->frame;
}

int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glClearColor(0, 0, 0, 0);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(HEIGHT, WIDTH);
	glutCreateWindow("CUBO");

	glutPostRedisplay();

	test = new float[HEIGHT * WIDTH * 3];
	
	int idx = 0;

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (i < 10) {
				test[idx*3]   = 1 / 255;
				test[idx*3+1] = 1 / 255;
				test[idx*3+2] = 1 / 255;
			}
			else {
				test[idx * 3]     = 1 / 255;
				test[idx * 3 + 1] = 0;
				test[idx * 3 + 2] = 0;
			}
		idx++;
		}
	}

	//Raycaster();

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);


	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
};