#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <sstream>
const int width = 800;
const int height = 600;

#include <vector>

std::vector<int> tokenized;

int oldX = 0, oldY = 0;
float rX = 15, rY = 0;
int state = 1;
float tx = 0, ty = 0, tz = -15;

float wall_size = 1.0f;

//Mouse Events
void OnMouseDown(int button, int s, int x, int y)
{
	if (s == GLUT_DOWN)
	{
		oldX = x;
		oldY = y;	
	}

	if (button == GLUT_MIDDLE_BUTTON)
		state = 0;
	else if (button == GLUT_RIGHT_BUTTON)
		state = 2;
	else
		state = 1;
}

void OnMouseMove(int x, int y)
{
	if (state == 0)
		tz *= (1 + (y - oldY) / 60.0f);
	else if (state == 2) {
		tx -= (x - oldX) / 50.0f;
		ty += (y - oldY) / 50.0f;
	}
	else
	{
		rY += (x - oldX) / 5.0f;
		rX += (y - oldY) / 5.0f;
	}
	oldX = x;
	oldY = y;

	glutPostRedisplay();
}

void DrawGrid(int size = 10) {
	glBegin(GL_LINES);
	glColor3f(0.75, 0.75, 0.75);
	for (int i = -size; i <= size; i++) {
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);

		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
	}

	glEnd();
}

void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//set viewing transformation
	glTranslatef(tx, ty, tz);
	glRotatef(rX, 1, 0, 0);
	glRotatef(rY, 0, 1, 0);

	DrawGrid();

	glColor3f(0, 1, 0);

	float hsize = wall_size / 2.0f;

	//draw floor plan lines
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);	
	for (int i = 0; i < tokenized.size(); i += 2)
	{
		//glVertex2i(tokenized[i], tokenized[i + 1]);

		//scale vertex to 0 to 1 range
		float x = tokenized[i] / 921.0f;
		float z = tokenized[i + 1] / 735.0f;

		//scale to -1 to 1 range
		x = x*2.0f - 1.0f;
		z = z*2.0f - 1.0f;

		//scale to -5 to 5 range
		x = x * 5;
		z = z * 5;
		glVertex3f(x, -hsize, z);
	}

	for (int i = 0; i < tokenized.size(); i += 2)
	{
		//glVertex2i(tokenized[i], tokenized[i + 1]);
		float x = tokenized[i] / 921.0f;
		float z = tokenized[i + 1] / 735.0f;

		x = x*2.0f - 1.0f;
		z = z*2.0f - 1.0f;

		x = x * 5;
		z = z * 5;
		glVertex3f(x, hsize, z);
	}
	glEnd();

	
	//draw a wall
	glBegin(GL_QUADS);
		glColor3f(0, 1, 0);
		glVertex3f(-5, -hsize, 5);
		glVertex3f(5, -hsize, 5);
		glVertex3f(5, hsize, 5);
		glVertex3f(-5, hsize, 5);
	glEnd();

	glutSwapBuffers();
}

std::vector<int> split(std::vector<std::string> linesCood){

	std::vector<int> coods;
	std::string stream;
	std::stringstream ss;
	char delim = ',';
	std::string item;
	std::vector<std::string> elems;
	//cout << linesCood.size() << endl;
	for (int i = 0; i < linesCood.size(); i++)
	{
		stream = linesCood[i];
		//cout << linesCood[i] << endl;
		std::stringstream ss;
		ss.str(stream);
		while (getline(ss, item, delim)){
			coods.push_back(atoi(item.c_str()));
			//cout << item << endl;
		}
	}


	return coods;

}

std::vector<std::string> readfile(){

	std::vector<int> coods;
	int x = 0;
	std::vector<std::string> vec;
	std::string line;
	std::vector<std::string> token;
	int i = 0;
	std::ifstream file("C:/Users/ammar/Documents/Visual Studio 2013/Projects/2DTO3D_/2DTO3D/lines.txt");
	std::string sline;
	if (file.is_open())
	{
		while (getline(file, sline))
		{
			std::cout << sline << std::endl;
			vec.push_back(sline);
		}

		file.close();
	}
	else
		std::cout << "Unable to open file";
	return vec;
}


void OnInit() {
	glClearColor(0.5, 0.5, 1, 1);
	std::vector<std::string> cood = readfile();
	tokenized = split(cood);

	glEnable(GL_DEPTH_TEST);

}

void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);

	glMatrixMode(GL_MODELVIEW);
}


void OnIdle() {
	glutPostRedisplay();
}

void OnKey(unsigned char key, int, int) {
	switch (key) {
		case '-': wall_size -= 0.1f; break;
		case '=': wall_size += 0.1f; break;
	
	}
	glutPostRedisplay();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Test 3D");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	glutIdleFunc(OnIdle);

	glutMouseFunc(OnMouseDown);
	glutMotionFunc(OnMouseMove);
	glutKeyboardFunc(OnKey);

	OnInit();

	glutMainLoop();

	return 0;
}