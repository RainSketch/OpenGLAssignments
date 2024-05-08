#include <GL/glut.h>

GLfloat ctrlPoints[3][2] =
{
    {-40.0, -40.0},
    {0.0, 40.0},
    {40.0, -40.0}
};

GLfloat ctrlPoints2[3][2] =
{
    {-40.0, 40.0},
    {0.0, -40.0},
    {40.0, 40.0}
};

GLfloat ctrlPoints3[3][2] =
{
    {40.0, -40.0},
    {0.0, -40.0},
    {-40.0, 40.0}
};

GLfloat ctrlPoints4[3][2] =
{
    {-40.0, 40.0},
    {0.0, 40.0},
    {40.0, -40.0}
};


void BezierCurve(GLfloat points[3][2],float R,float G,float B) {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 3; ++i) {
        glVertex2fv(points[i]);
    }
    glEnd();

    glLineWidth(2);
    glColor3f(R,G,B);
    glBegin(GL_LINE_STRIP);
    for (float t = 0.0; t <= 1.0; t += 0.01) {
        GLfloat x = (1 - t) * (1 - t) * points[0][0] + 2 * (1 - t) * t * points[1][0] + t * t * points[2][0];
        GLfloat y = (1 - t) * (1 - t) * points[0][1] + 2 * (1 - t) * t * points[1][1] + t * t * points[2][1];
        glVertex2f(x, y);
    }
    glEnd();
}

void drawTwoBezierCurves() {
    glClear(GL_COLOR_BUFFER_BIT);

    BezierCurve(ctrlPoints,1,1,0);
    BezierCurve(ctrlPoints2,1,0,1);
    BezierCurve(ctrlPoints3,0,1,1);
    BezierCurve(ctrlPoints4,0,1,0);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-50, 50, -50, 50);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Bezier Curves");

    init();
    glutDisplayFunc(drawTwoBezierCurves);
    glutMainLoop();

    return 0;
}
