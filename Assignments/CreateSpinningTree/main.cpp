#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

double windowHeight=800, windowWidth=720;
double camX=8.0, camY=4.0, camZ=8.0, refX = 0, refY=0,refZ=0;
float angle=0;


GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 1.0}, //1
    {1.0, 0.0, 1.0}, //2
    {1.0, 0.0, 0.0}, //3
    {0.0, 1.0, 0.0}, //4
    {0.0, 1.0, 1.0}, //5
    {1.0, 1.0, 1.0}, //6
    {1.0, 1.0, 0.0}  //7
};

GLint cube_f[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}
void drawCube(int i)
{
    glBegin(GL_QUADS);

        getNormal3p(v_cube[cube_f[i][0]][0], v_cube[cube_f[i][0]][1], v_cube[cube_f[i][0]][2],
                    v_cube[cube_f[i][1]][0], v_cube[cube_f[i][1]][1], v_cube[cube_f[i][1]][2],
                    v_cube[cube_f[i][2]][0], v_cube[cube_f[i][2]][1], v_cube[cube_f[i][2]][2]);
        glVertex3fv(&v_cube[cube_f[i][0]][0]);
        glVertex3fv(&v_cube[cube_f[i][1]][0]);
        glVertex3fv(&v_cube[cube_f[i][2]][0]);
        glVertex3fv(&v_cube[cube_f[i][3]][0]);

    glEnd();
}

void drawCube1(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX=0.2, GLfloat ambY=0.2, GLfloat ambZ=0.2, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    for (int i = 0; i < 6; ++i)
        drawCube(i);
}

void animation(int value) {
    angle += 2.0;
    if (angle > 360.0) {
        angle -= 360.0;
    }
    glutPostRedisplay();
    glutTimerFunc(32,animation, 0);
}

void drawTree()
{
    //trunk
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-9,0);
    glScalef(0.5,7,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    //x-axis side
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-5,0);
    glScalef(2,0.5,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();


    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(1.5,-5,0);
    glScalef(0.5,1,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(1.5,-3.8,0);
    glScalef(1.7,1.2,1.6);
    glColor4f(0.75,1,0.6,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //-x-axis side
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-4.3,0);
    glScalef(-3,0.5,0.6);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();


    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(-3,-4.1,0);
    glScalef(0.6,1,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(-4,-3.2,-0.2);
    glScalef(2.3,1.3,2.1);
    glColor4f(0.78,1,0.63,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();


    //front
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-5.3,0);
    glScalef(0.5,0.4,2);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-4.8,1.7);
    glScalef(1.2,1,1.2);
    glColor4f(0.72,1,0.65,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //back

    glPushMatrix();//leaf4
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(0,-4.5,-1.9);
    glScalef(2,1.5,2.1);
    glColor4f(0.78,1,0.62,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //top
    glPushMatrix();//leaf5
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(-0.5,-2.5,-0.5);
    glScalef(2.1,1.6,2.2);
    glColor4f(0.85,1,0.6,0.98);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

}

void drawPlane()
{
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    glTranslated(-10,-8,10);
    glScalef(20,1,-20);
    glColor3f(0.63,0.75,0.36);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

}

void lightOne()
{
    glPushMatrix();
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 2.0, 5.0, -4.0, 1.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void reshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(-15,15,-15,15,1,200);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(camX,camY,camZ,refX,refY,refZ,0,1,0);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    lightOne();
    drawPlane();
    drawTree();

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth,windowHeight);
    glutInitWindowPosition(600,200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Rotating Tree");
    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(50,animation, 0);
    glutMainLoop();
    return 0;
}


