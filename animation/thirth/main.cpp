#include <GL/glut.h>
#include <GL/gl.h>

#include <cmath>
float bodyPosX = 0.0f;
float bodyPosY = -0.5f;
float step = 0.05f;
float armSwing = 0.0f;
float legSwing = 0.0f;
bool forward = true;  // Yürürken hangi yönde adım atılacak

// Yürüyüş animasyonu için karakteri çizen fonksiyon
void drawCharacter() {
    // Gövde
    glPushMatrix();
    glTranslatef(bodyPosX, bodyPosY, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f); // Mavi renk
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.2f);  // Sağ üst
        glVertex2f(0.1f, 0.2f);   // Sağ alt
        glVertex2f(0.1f, -0.4f);  // Sol alt
        glVertex2f(-0.1f, -0.4f); // Sol üst
    glEnd();
    glPopMatrix();

    // Kollar
    glPushMatrix();
    glTranslatef(bodyPosX, bodyPosY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Kollar kırmızı
    // Sol kol
    glPushMatrix();
    glTranslatef(-0.2f, 0.1f, 0.0f);
    glRotatef(armSwing, 0.0f, 0.0f, 1.0f); // Kol hareketi
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
        glVertex2f(-0.05f, 0.0f);
    glEnd();
    glPopMatrix();

    // Sağ kol
    glPushMatrix();
    glTranslatef(0.2f, 0.1f, 0.0f);
    glRotatef(-armSwing, 0.0f, 0.0f, 1.0f); // Kol hareketi
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(0.05f, 0.0f);
    glEnd();
    glPopMatrix();
    glPopMatrix();

    // Bacaklar
    glPushMatrix();
    glTranslatef(bodyPosX, bodyPosY, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Bacaklar yeşil
    // Sol bacak
    glPushMatrix();
    glTranslatef(-0.05f, -0.4f, 0.0f);
    glRotatef(legSwing, 0.0f, 0.0f, 1.0f); // Bacak hareketi
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
        glVertex2f(-0.05f, 0.0f);
    glEnd();
    glPopMatrix();

    // Sağ bacak
    glPushMatrix();
    glTranslatef(0.05f, -0.4f, 0.0f);
    glRotatef(-legSwing, 0.0f, 0.0f, 1.0f); // Bacak hareketi
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(0.05f, 0.0f);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

// Görüntüleme fonksiyonu
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawCharacter();
    glutSwapBuffers();
}

// Güncelleme fonksiyonu
void update(int value) {
    // Yürüme animasyonunu hareket ettir
    if (forward) {
        bodyPosX += step;
        if (bodyPosX > 0.6f) forward = false;
    } else {
        bodyPosX -= step;
        if (bodyPosX < -0.6f) forward = true;
    }

    // Kollar ve bacaklar arasında dönüşüm (swing)
    armSwing = (armSwing > 45.0f) ? -45.0f : armSwing + 5.0f;
    legSwing = (legSwing > 45.0f) ? -45.0f : legSwing + 5.0f;

    glutPostRedisplay();
    glutTimerFunc(100, update, 0); // Animasyonu 10 ms arayla güncelle
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("walker");

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // Arka plan rengi
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // 2D ortografik projeksiyon

    glutDisplayFunc(display);
    glutTimerFunc(100, update, 0);  // Animasyonu başlat

    glutMainLoop();
    return 0;
}