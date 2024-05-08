#include <GL/glut.h>

GLfloat RedPolygon[][2]=
{
    {0.1,3.5},{17,3.5},{15,6.9},{6,6.9},{14,22},{10.5,22},
};
GLfloat GreenPolygon[][2]=
{
    {14,15.3},{22.5,0.0},{24.5,3.5},{14,22},{6,6.9},{10,6.9},
};
GLfloat BluePolygon[][2]=
{
    {22.5,0.0},{14.0,15.3},{12.0,12},{17,3.5},{0.1,3.5},{2,0},
};
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-25.0, 25.0, -25.0, 25.0);

    glTranslatef(-10,-10,0);
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    for(int i=0;i<6;i++)
    {
        glVertex2fv(RedPolygon[i]);

    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,1,0);
    for(int i=0;i<6;i++)
    {
        glVertex2fv(GreenPolygon[i]);

    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    for(int i=0;i<6;i++)
    {
        glVertex2fv(BluePolygon[i]);
    }
    glEnd();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(400,400);                                    // Window size
    glutInitWindowPosition(800,150);
    glutCreateWindow("Penrose Triangle Shape");


    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
