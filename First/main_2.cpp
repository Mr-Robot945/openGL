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
const int width = 512;
const int height = 512;
int angle = 0;
const int N = 5;
float t = 0;
int minMax[4] = { 0, 0, 0, 0 };
vector<int> cood;
//vector<int> readfile();
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
	//float newSize = hsize*1.5;
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
vector<int> split(const string &stream, char delim, vector<string> &elems){
	stringstream ss;
	vector<int> coods;
	ss.str(stream);
	string item;
	while (getline(ss, item, delim)){
		elems.push_back(item);
		//cout << item << endl;
	}

	return coods;

}
vector<int> readfile(){

	vector<int> coods;
	int x = 0;
	vector<string> vec;
	string line;
	vector<string> token;
	int i = 0;
	ifstream myfile("minMax.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			int value = atoi(line.c_str());
			minMax[x] = value;
			x++;
		}
		myfile.close();
		x = 0;
	}
	//cout << minMax[0] << "," << minMax[1] << "," << minMax[2] << "," << minMax[3] << endl;
	ifstream file("lines.txt");
	string sline;
	if (file.is_open())
	{
		while (getline(file, sline))
		{
			vec.push_back(sline);
		}

		file.close();
	}
	else
		cout << "Unable to open file";
	for (int i = 0; i < vec.size(); i++)
	{
		split(vec[i], ',', token);
	}
	int norm = 0;
	for (int i = 0; i < token.size(); i++)
	{
		int value = atoi(token[i].c_str());
		cout << minMax[0] << "," << minMax[1] << "," << minMax[2] << "," << minMax[3] << endl;
		if (i % 2 == 0)
		{
			norm = 1 + ((value - minMax[0])*(15 - 1)) / (minMax[2] - minMax[0]); //norm on scale:1-15 ; a+(x-A)(b-a)/(B-A); a=b= to norm range, A=B=min/max of data,x+value to be scaled
		}
		else
		{
			norm = 1 + ((value - minMax[1])*(15 - 1)) / (minMax[3] - minMax[1]);
		}
		coods.push_back(norm);
	}

	return coods;
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//gluLookAt(5, 5, N, 0, 0, 0, 0, 1, 0);
	MV = glm::lookAt(glm::vec3(90, 30, 40), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glLoadMatrixf(glm::value_ptr(MV));

	DrawGrid();

	/*for (int i = 0; i < cood.size(); i++)
	{
	cout << cood[i] << endl;
	}*/
	DrawRoom1(1, cood);
	//	DrawPoints();
	glutSwapBuffers();
}
void OnInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(51);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK, GL_LINE);
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
	glMatrixMode(GL_MODELVIEW);
}
void OnIdle() {
	t += 0.1f;
	glutPostRedisplay();
}
int main(int argc, char** argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Test 3D");
	// register callbacks
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutIdleFunc(OnIdle);
	cood = readfile();
	OnInit();
	// enter GLUT event processing cycle
	glutMainLoop();
	return 0;
}