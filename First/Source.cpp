
#include <GL/freeglut.h>
#include <stdlib.h>
#include<iostream>
#include <stdio.h>
#include<cmath>


const GLdouble FRUSTDIM = 100.0f;


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 640.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{	
	glTranslatef(-100, -100, -630.0);
	glBegin(GL_QUADS);
	/* Back Wall */
	glColor3f(1.0f, 0.0f, 0.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(200, 0, 0);
	glVertex3f(200, 200, 0);
	glVertex3f(0, 200, 0);
	glEnd();

	/*glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(50, 50, 420);
	glVertex3f(50, -50, 420);
	glVertex3f(-50, -50, 420);
	glVertex3f(-50, 50, 420);
	glEnd();
	*/
	glutSwapBuffers();
	//glFlush();
}

void renderScene(void) {

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1.9, 1, 0);
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.0, 0.0);
	glVertex3f(0.0, 0.5, 0.0);
	glEnd();

	glutSwapBuffers();
}
int main(int argc, char **argv) {

	// init GLUT and create Window
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(100, 100);
	
	glutInitWindowSize(320, 320);

	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	glutDisplayFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	//waitKey(0);
	return 0;

}
