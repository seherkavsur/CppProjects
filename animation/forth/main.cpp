#include <GL/glut.h>
#include <cmath>

// Çocuğun pozisyonu
float childPosX = -0.5f;
float childPosY = -0.5f;
float ballPosX = -0.5f;
float ballPosY = -0.4f;
float ballDirection = 1.0f;  // Topun yukarı hareketi
float ballVelocityY = 0.05f; // Topun dikey hız bileşeni

float armAngle = 0.0f;
float step = 0.02f;
bool moveRight = true;  // Çocuğun sağa hareket etme durumu

// Çocuk karakterini çizen fonksiyon
void drawChild() {
    // Gövde
    glPushMatrix();
    glTranslatef(childPosX, childPosY, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);  // Mavi renk
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.2f);   // Gövde üst
        glVertex2f(0.1f, 0.2f);    // Gövde üst
        glVertex2f(0.1f, -0.4f);   // Gövde alt
        glVertex2f(-0.1f, -0.4f);  // Gövde alt
    glEnd();

    // Yüz
    glPushMatrix();
    glTranslatef(childPosX, childPosY + 0.2f, 0.0f);
    glColor3f(1.0f, 0.8f, 0.6f);  // Ten rengi
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cos(angle) * 0.1f, sin(angle) * 0.1f);  // Yüz
        }
    glEnd();
    glPopMatrix();

    // Gözler
    glPushMatrix();
    glTranslatef(childPosX, childPosY + 0.25f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);  // Gözler siyah
    // Sol göz
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cos(angle) * 0.02f - 0.03f, sin(angle) * 0.02f);
        }
    glEnd();
    // Sağ göz
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cos(angle) * 0.02f + 0.03f, sin(angle) * 0.02f);
        }
    glEnd();
    glPopMatrix();

    // Saç
    glPushMatrix();
    glTranslatef(childPosX, childPosY + 0.25f, 0.0f);
    glColor3f(0.5f, 0.25f, 0.0f);  // Saç rengi
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, 0.05f);  // Saç üst sol
        glVertex2f(0.05f, 0.05f);   // Saç üst sağ
        glVertex2f(0.07f, 0.08f);   // Saç sağ
        glVertex2f(-0.07f, 0.08f);  // Saç sol
    glEnd();
    glPopMatrix();

    // Kollar (Çocuğun kolları topu tutuyor)
    glPushMatrix();
    glTranslatef(childPosX, childPosY, 0.0f);

    // Sol kol
    glPushMatrix();
    glTranslatef(-0.1f, 0.1f, 0.0f);
    glRotatef(armAngle, 0.0f, 0.0f, 1.0f);  // Kolun hareket açısı
    glColor3f(0.9f, 0.8f, 0.7f);  // Kolların ten rengi
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
        glVertex2f(-0.05f, 0.0f);
    glEnd();
    glPopMatrix();

    // Sağ kol (topu tutuyor)
    glPushMatrix();
    glTranslatef(0.1f, 0.1f, 0.0f);
    glRotatef(-armAngle, 0.0f, 0.0f, 1.0f);  // Kolun hareket açısı
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
    glTranslatef(childPosX, childPosY, 0.0f);

    // Sol bacak
    glPushMatrix();
    glTranslatef(-0.05f, -0.4f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);  // Ayakkabı rengi
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
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(0.05f, 0.0f);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

// Topu çizen fonksiyon
void drawBall() {
    glPushMatrix();
    glTranslatef(ballPosX, ballPosY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);  // Kırmızı renk
    glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.14159f / 180.0f;
            glVertex2f(cos(angle) * 0.1f, sin(angle) * 0.1f);  // Daire
        }
    glEnd();
    glPopMatrix();
}

// Görüntüleme fonksiyonu
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Çocuk ve topu çiz
    drawChild();
    drawBall();

    glutSwapBuffers();
}

// Güncelleme fonksiyonu
void update(int value) {
    // Çocuğun sağa ve sola hareketi
    if (moveRight) {
        childPosX += step;
        ballPosX += step;
        if (childPosX > 0.6f) moveRight = false;
    } else {
        childPosX -= step;
        ballPosX -= step;
        if (childPosX < -0.6f) moveRight = true;
    }

    // Kol hareketi (topu zıplatmak için)
    armAngle = (armAngle > 30.0f) ? -30.0f : armAngle + 5.0f;

    // Topun zıplaması
    if (ballDirection > 0) {
        ballPosY += ballVelocityY;
        ballVelocityY -= 0.001f;  // Yer çekimi etkisi
        if (ballPosY > 0.2f) ballDirection = -1.0f;
    } else {
        ballPosY -= ballVelocityY;
        ballVelocityY += 0.001f;  // Yer çekimi etkisi
        if (ballPosY < -0.4f) {
            ballDirection = 1.0f;
            ballVelocityY = 0.05f;  // Top yere çarptığında hız yeniden başlar
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);  // Animasyonu 30 ms arayla güncelle
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Top Oynayan Çocuk");

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // Arka plan rengini beyaz yap
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);  // Ortografik proje

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);  // Animasyonun güncellenmesi

    glutMainLoop();  // GLUT ana döngüsünü başlat

    return 0;
}
