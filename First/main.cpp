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

const int width = 512;
const int height = 512;
int angle = 0;
const int N = 5;
float t = 0;



using namespace std;

glm::mat4 MV;
glm::mat4 P;



void DrawGrid(int size = 21) {
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

void DrawRoom(int size=7) {
	float hsize = size/2.0f;
	//float newSize = hsize*1.5;
	glBegin(GL_QUADS);

		// Floor  
		glColor3f(0, 0, 0);
		glVertex3f(-hsize, -hsize, -hsize );
		glVertex3f(-hsize , -hsize , hsize );
		glVertex3f(hsize , -hsize , hsize );
		glVertex3f(hsize , -hsize , -hsize );
		 
		//Ceiling 
		glColor3f(0, 0,1);
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
		cout << item << endl;
	}

	for (int i = 0; i < elems.size(); i++)
	{
		int value = atoi(elems[i].c_str());
		coods.push_back(value);
	}
	return coods;
	/*string t = "90";
	int val = atoi(t.c_str());
	cout << "vl: " << val << endl;*/
}

vector<int> readfile(){
		// reading a text file
	vector<int> coods;
		string line;
		vector<string> token;
		ifstream myfile("opengl.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				//cout << line << '\n';
				coods = split(line, ',', token);
			
			}
			myfile.close();
			
		}

		else cout << "Unable to open file";
		return coods;
}

void DrawRoom1(int size, vector<int>& cood) {

	float hsize = (size / 2.0f) * 2;
	
	
	glTranslated(hsize + 3, hsize + 3, hsize + 3);
	glScalef(8, 8, 8);


	
	//float newSize = hsize*1.5;
	glBegin(GL_QUADS);

	// Floor
	glColor3f(0.545, 0, 0);
	/*glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize , hsize);
	glVertex3f(hsize, -hsize, -hsize);*/

	glColor3f(0.545, 0, 0);
	glVertex3f(-cood[1], -cood[1], -cood[2]);
	glVertex3f(-cood[3], -cood[4], cood[5]);
	glVertex3f(cood[6], -cood[7], cood[8]);
	glVertex3f(cood[9], -cood[10], -cood[11]);


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

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(5, 5, N, 0, 0, 0, 0, 1, 0);
	MV = glm::lookAt(glm::vec3(10, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); 
	glLoadMatrixf(glm::value_ptr(MV));
	
	DrawGrid();

	vector<int> cood = readfile();
	for (int i = 0; i < cood.size(); i++)
	{
		cout << cood[i] << endl;
	}

	/*glBegin(GL_TRIANGLES);
		glVertex3f(-2, 0, -2);		
		glVertex3f(0, 2, 2);
		glVertex3f(2, 0, -2);*/
	glEnd();


	DrawRoom(4);
	//DrawRoom1(1,cood);

//	DrawPoints();

	glutSwapBuffers();
}

void OnInit() {
	glClearColor(1,1,1, 1);
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

	OnInit();

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}