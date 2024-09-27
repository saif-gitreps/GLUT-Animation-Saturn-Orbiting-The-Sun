#include <GL/glut.h>
#include <cmath>

float sunRadius = 0.2;
float saturnRadius = 0.1;
float orbitRadius = 0.6;
float ringOuterRadius = 0.15;
float ringInnerRadius = 0.12;
float angle = 0.0f;

void drawCircle(float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float radian = i * (M_PI / 180.0f);
        glVertex2f(cos(radian) * radius, sin(radian) * radius);
    }
    glEnd();
}

void drawRing(float innerRadius, float outerRadius) {
    glBegin(GL_POINTS);
    for (int i = 0; i <= 360; i++) {
        float radian = i * (M_PI / 180.0f);
        glVertex2f(cos(radian) * innerRadius, sin(radian) * innerRadius);
        glVertex2f(cos(radian) * outerRadius, sin(radian) * outerRadius);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(sunRadius);
    
    float saturnX = orbitRadius * cos(angle);
    float saturnY = orbitRadius * sin(angle);
    
    glPushMatrix();
    glTranslatef(saturnX, saturnY, 0.0f);
    
    glColor3f(0.9f, 0.7f, 0.5f);
    drawCircle(saturnRadius);
    
    glColor3f(0.8f, 0.8f, 0.8f);
    drawRing(ringInnerRadius, ringOuterRadius);
    
    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    angle += 0.02f;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Saturn Orbiting Sun");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);
    glutMainLoop();
    return 0;
}
