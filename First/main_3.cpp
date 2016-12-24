#include <GL/freeglut.h>
#include <cmath>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
const int width = 921;// 512;
const int height = 800;// 512;
int angle = 0;
const int N = 5;
float t = 0;
int minMax[4] = { 0, 0, 0, 0 };
vector<int> tokenized;

glm::mat4 MV;
glm::mat4 P;

void DrawGrid(int size = 50) {
	glBegin(GL_LINES);
	glColor3f(0, 0.75, 1);
	for (int i = -size; i <= size; i++) {
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);

		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
	}
	glEnd();
}

void DrawRoom(int size = 7) {
	float hsize = size / 2.0f;
	glBegin(GL_QUADS);

	// Floor  
	glColor3f(0, 0, 0);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);

	//Ceiling 
	glColor3f(0, 0, 1);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, hsize, -hsize);

	// Walls 
	glColor3f(1, 1, 0);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(-hsize, hsize, hsize);

	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);

	glEnd();
}

vector<int> split(vector<string> linesCood){

	vector<int> coods;
	string stream;
	stringstream ss;
	char delim = ',';
	string item;
	vector<string> elems;
	//cout << linesCood.size() << endl;
	for (int i = 0; i < linesCood.size(); i++)
	{
		stream = linesCood[i];
		//cout << linesCood[i] << endl;
		stringstream ss;
		ss.str(stream);
		while (getline(ss, item, delim)){
			coods.push_back(atoi(item.c_str()));
			//cout << item << endl;
		}
	}


	return coods;

}

vector<string> readfile(){

	vector<int> coods;
	int x = 0;
	vector<string> vec;
	string line;
	vector<string> token;
	int i = 0;
	ifstream file("lines.txt");
	string sline;
	if (file.is_open())
	{
		while (getline(file, sline))
		{
			cout << sline << endl;
			vec.push_back(sline);
		}

		file.close();
	}
	else
		cout << "Unable to open file";
	return vec;
}

void DrawRoom1(int size, vector<int>& cood) {

	float hsize = (size / 2.0f) * 2;


	//	glTranslated(hsize , hsize, hsize);
	//glScalef(8, 8, 8);


	//float newSize = hsize*1.5;
	glBegin(GL_QUADS);

	//cout << cood.size() << endl;

	//cieling
	glColor3f(0, 0, 1);

	for (int i = 0; i < cood.size(); i += 2)
	{
		glVertex2f(cood[i] + 1, cood[i + 1] + 2);
	}

	/*glVertex2f(-2, 0);// 309, 277);
	glVertex2f(2, 0);
	glVertex2f(2, 2);
	glVertex2f(-2,2);*/

	/*
	//Ceiling
	glColor3f(0,0,0);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, hsize, -hsize);

	// Walls

	//left wall
	glColor3f(1, 0, 0);
	glVertex3f(-hsize * 5, -hsize * 5, hsize * 5);
	glVertex3f(hsize * 5, -hsize * 5, hsize * 5);
	glVertex3f(hsize * 5, hsize * 5, hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, hsize * 5);



	//right wall
	glVertex3f(hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, -hsize * 5);
	glVertex3f(hsize * 5, hsize * 5, -hsize * 5);


	//front wall
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	//back wall
	glVertex3f(-hsize * 5, hsize * 5, hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, hsize * 5);
	*/
	glEnd();
}

void DrawPoints() {
	glScalef(0.5, 0.5, 0.5);

	glBegin(GL_POINTS);
	for (int z = -N; z <= N; ++z) {
		for (int x = -N; x <= N; ++x) {
			float r = (x + N) / (2.0f*N);
			float b = (z + N) / (2.0f*N);
			glColor3f(0, 1, b);
			float y = sinf(x + t);
			//float y = sinf(z + t);
			//float y = sinf(x + z + t);
			//float y = sinf(10*sqrtf(x*x + z*z)+t);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
}

void OnRender() {
	assert(glGetError() == GL_NO_ERROR);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	for (int i = 0; i < tokenized.size(); i += 2)
	{
		glVertex2i(tokenized[i], height - tokenized[i + 1]);
	}

	glEnd();

	glutSwapBuffers();
}

void OnInit() {
	glClearColor(1, 1, 1, 1);
	//glPointSize(51);

	//glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_BACK, GL_LINE);

	/*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);*/

}

void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);
	//gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
}

void OnIdle() {
	t += 0.1f;
	glutPostRedisplay();
}

int main(int argc, char** argv) {


	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);// | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Test 3D");

	// register callbacks
	vector<string> cood = readfile();
	tokenized = split(cood);

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutIdleFunc(OnIdle);

	OnInit();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}