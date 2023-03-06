#include <GL/freeglut.h>

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_WINDOW_TITLE "Third Dimention"

typedef struct vec3f { float x, y, z; } vec3f;
#define gluLookAtVec3f(eye, center, up) gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z)
const static vec3f cam = { 2.0f, 4.0f, 5.0f },
				   center = {0.0f, 0.0f, 0.0f},
				   up = {0.0f, 1.0f, 0.0f};
static float scene_rotation = 0.0f;

void init(void) {
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAtVec3f(cam, center, up);

	glPushMatrix();
	glRotatef(scene_rotation, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCube(3.0f);

	glRotatef(scene_rotation, 0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireCube(2.0f);

	glRotatef(scene_rotation, 0.0f, 0.0f, 1.0f);
	glColor3f(0.0f, 0.3f, 1.0f);
	glutWireCube(1.0f);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)w / (float)h, 0.01f, 100.0f);

	glutPostRedisplay();
}

void timer(int x) {
	if (scene_rotation >= 360.0f) scene_rotation = 0.0f;
	else scene_rotation += 0.2f;

	glutTimerFunc(x, timer, x);
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	glutCreateWindow(DEFAULT_WINDOW_TITLE);
	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(16, timer, 16);

	glutMainLoop();
	return 0;
}
