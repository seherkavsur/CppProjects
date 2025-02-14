#include <GL/glut.h>
#include <GL/gl.h>

#include <cmath>

float xPos = -0.5f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float theta = i * 3.1415926 / 180;
        glVertex2f(xPos + 0.1 * cos(theta), 0.1 * sin(theta));
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    xPos += 0.01f;
    if (xPos > 1.0f) xPos = -1.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("C++ OpenGL Animasyon");

    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}

