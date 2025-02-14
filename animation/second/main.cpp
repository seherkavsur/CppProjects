#include <GL/glut.h>
#include <GL/gl.h>

#include <cmath>
float xPos = 0.0f;
float yPos = 0.0f;
float speed = 0.02f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Topu çiz
    glTranslatef(xPos, yPos, 0.0f);  // Topun pozisyonunu değiştirmek için

    glBegin(GL_POLYGON);  // Bir daire çizeceğiz
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cos(angle) * 0.1f, sin(angle) * 0.1f);  // Dairenin noktaları
        }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // Topun hareketi
    xPos += speed;
    if (xPos > 1.0f || xPos < -1.0f) {
        speed = -speed;  // Top yön değiştiriyor
    }

    glutPostRedisplay();  // Ekranı yeniden çiz

    glutTimerFunc(16, update, 0);  // 60 FPS için güncellemeyi devam ettir
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Basit Animasyon");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Arka plan rengini ayarla
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // 2D çizim için ortografik projeksiyon

    glutDisplayFunc(display);  // Ekran güncelleme fonksiyonunu ayarla
    glutTimerFunc(25, update, 0);  // Animasyonu başlat

    glutMainLoop();  // Sonsuz döngüde animasyonu çalıştır

    return 0;
}