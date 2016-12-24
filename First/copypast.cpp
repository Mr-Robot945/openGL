#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdio.h>
void drawCube();
float vertices[8][3];
int facets[6][4];
void read_file(char **argv);
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawCube();
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
int main(int argc, char** argv)
{
	read_file(argv);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
void drawCube()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(225.0f, 225.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (i = 0; i < 6; ++i)
	{
		glVertex3fv(vertices[facets[i][0]]);
		glVertex3fv(vertices[facets[i][1]]);
		glVertex3fv(vertices[facets[i][2]]);
		glVertex3fv(vertices[facets[i][3]]);
	}

	glEnd();
	glFlush();
	glutSwapBuffers();
}
void read_file(char **argv)
{
	FILE *Map;
	int loopcounter;
	Map = fopen("opengl.txt", "r");

	if (Map == NULL)
	{
		printf("\ncan't open input file\n");
		exit(1);
	}

	for (loopcounter = 0; loopcounter < 8; loopcounter++)
	{
		fscanf(Map, "%f", &vertices[loopcounter][0]);
		printf("%f ", vertices[loopcounter][0]);

		fscanf(Map, "%f", &vertices[loopcounter][1]);
		printf("%f ", vertices[loopcounter][1]);

		fscanf(Map, "%f", &vertices[loopcounter][2]);
		printf("%f\n", vertices[loopcounter][2]);
	}

	for (loopcounter = 0; loopcounter < 6; loopcounter++)
	{
		fscanf(Map, "%d", &facets[loopcounter][0]);
		printf("%d ", facets[loopcounter][0]);

		fscanf(Map, "%d", &facets[loopcounter][1]);
		printf("%d ", facets[loopcounter][1]);

		fscanf(Map, "%d", &facets[loopcounter][2]);
		printf("%d ", facets[loopcounter][2]);

		fscanf(Map, "%d", &facets[loopcounter][3]);
		printf("%d\n", facets[loopcounter][3]);
	}
}