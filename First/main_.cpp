#include <GL/freeglut.h>

const int width = 800, height = 600;
float angle = 0;

void OnInit() {
	glClearColor(1, 1, 1, 1);
}

void OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluOrtho2D(-1, 1, -1, 1);
	gluPerspective(60, float(nw) / nh, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
}

void DrawGrid() { 
	glBegin(GL_LINES);
		glColor3f(0.5, 0.5, 0.5);
		for (int i = -10; i <= 10; i++) { 
			glVertex3f(i, 0,-10);
			glVertex3f(i, 0, 10);

			glVertex3f(-10, 0, i);
			glVertex3f(10, 0, i);
		}
	glEnd();
}
void OnRender() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	
	gluLookAt(10, 10, 10, 0, 0, 0, 0, 1, 0);
	/*
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	for (int i = 0; i < width; i += 10) {
		float x = float(i) / width;
		glVertex2f(x, 0);
		glVertex2f(x, 1);

		glVertex2f(0, x);
		glVertex2f(1, x);
	}
	glEnd();
	*/

	DrawGrid();

	glBegin(GL_TRIANGLES);
		glColor3f(1, 0, 0);		glVertex2f(-0.5, -0.5);
		glColor3f(0, 1, 0);		glVertex2f(0.5, -0.5);
		glColor3f(0, 0, 1);		glVertex2f(0, 0.5);
	glEnd();

	glutSwapBuffers();
}
 

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Hello OpenGL"); 

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnResize);
	

	OnInit();

	glutMainLoop();


	return 0;
}