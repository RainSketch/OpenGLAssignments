#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>

double windowHeight=800, windowWidth=720;
double camX=8.0, camY=4.0, camZ=8.0, refX = 0, refY=0,refZ=0;
float translation=0.1;
float expansion=0.01;
float speed=0.01;


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

GLfloat HeartCubeColor[][3] = {
    {0.71,0.14,0.41},
    {0.71,0.14,0.41},
    {0.89,0.50,0.75},
    {0.89,0.50,0.75},
    {0.86,0.21,0.34},
    {0.86,0.21,0.34}
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

void draw1HeartCube()
{
    GLfloat mat_emission[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat mat_specular[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);


    glBegin(GL_QUADS);
    for (int i = 0; i < 6; ++i) {
        switch(i)
        {
            case 0:
            case 1:
                glColor3f(0.71,0.14,0.41);
                break;
            case 2:
            case 3:
                glColor3f(0.89,0.50,0.75);
                break;
            case 4:
            case 5:
                glColor3f(0.86,0.21,0.34);
                break;
        }
        drawCube(i);

    }
    glEnd();
}

void heartAnimation(int value)
{
    translation += speed;
    if (translation > 0.2 || translation < -0.1)
    {
        speed = -speed;
    }
    glutPostRedisplay();
    glutTimerFunc(100,heartAnimation,0);
}

void drawHeartCubes()
{
    //center
    glPushMatrix();
    glRotatef(30,1,0,-1);
    glTranslatef(2,6.5+translation,2);
    draw1HeartCube();
    glPopMatrix();

    //top-right
    glPushMatrix();
    glRotatef(30,1,0,-1);
    glTranslatef(1,0,-1);
    glTranslatef(2,6.5+translation,2);
    glRotatef(90,0,0,1);
    draw1HeartCube();
    glPopMatrix();

    //top-left
    glPushMatrix();
    glRotatef(30,1,0,-1);
    glTranslatef(-1,1,0);
    glTranslatef(2,6.5+translation,2);
    glRotatef(90,1,0,0);
    draw1HeartCube();
    glPopMatrix();
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

void drawPenrose()
{
    float anglex=-10;
    float angley=164.2;
    float anglez=30.5;

    glPushMatrix();
    glColor4f(1,0.66,0.24,0.95);
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
    glTranslatef(-0.5,0,0);
    glTranslatef(0,1,2.5);
    glScalef(1,1,-6);
    drawCube1(0.2,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glColor4f(1,0.66,0.24,0.95);
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
    glTranslatef(-0.5,1,-6);
    glTranslatef(0,1,2.5);
    glScalef(1,6,1);
    drawCube1(0.2,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glColor4f(1,0.66,0.24,0.95);
    glRotatef(anglex,1,0,0);
    glRotatef(angley,0,1,0);
    glRotatef(anglez,0,0,1);
    glTranslatef(-0.5,6,-6);
    glTranslatef(0,1,2.5);
    glScalef(-6,1,1);
    drawCube1(0.2,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

}

void treeAnimation(int value)
{
    expansion += speed;
    if (expansion > 0.05 || expansion < -0.02)
    {
        speed = -speed;
    }
    glutPostRedisplay();
    glutTimerFunc(180,treeAnimation,0);
}

void drawTree()
{
    //trunk
    glPushMatrix();
    glTranslated(0,-9,0);
    glScalef(0.5,7,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    //x-axis side
    glPushMatrix();
    glTranslated(0,-5,0);
    glScalef(2,0.5,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();


    glPushMatrix();
    glTranslated(1.5,-5,0);
    glScalef(0.5,1,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();//leaf1
    glTranslated(1.5,-3.8,0);
    glScalef(1.7+expansion,1.2,1.6);
    glColor4f(0.75,1,0.6,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //-x-axis side
    glPushMatrix();
    glTranslated(0,-4.3,0);
    glScalef(-3,0.5,0.6);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();


    glPushMatrix();
    glTranslated(-3,-4.1,0);
    glScalef(0.6,1,0.5);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();//leaf2
    glTranslated(-3,-3.2,-0.2);
    glScalef(2.3,1.3,2.1+expansion);
    glColor4f(0.78,1,0.63,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();


    //front
    glPushMatrix();
    glTranslated(0,-5.3,0);
    glScalef(0.5,0.4,2);
    glColor3f(0.27,0.17,0.12);
    drawCube1(0.5,0.2,0.2,0.25, 0.1, 0.1);
    glPopMatrix();

    glPushMatrix();//leaf3
    glTranslated(0,-4.8,1.7);
    glScalef(1.2,1+expansion,1.2);
    glColor4f(0.72,1,0.65,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //back

    glPushMatrix();//leaf4
    glTranslated(0,-4.5,-1.9);
    glScalef(2,1.5,2.1);
    glColor4f(0.78,1,0.62,0.95);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();

    //top
    glPushMatrix();//leaf5
    glTranslated(-0.5,-2.5,-0.5);
    glScalef(2.1+expansion,1.6+expansion,2.2+expansion);
    glColor4f(0.85,1,0.6,0.98);
    drawCube1(0.5,0.5,0.5,0.25, 0.1, 0.1);
    glPopMatrix();


}

void Line()
{
    glPushMatrix();
    glScalef(0.1,100,0.1);
    glColor3f(1,0,0);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();
}

void drawPlane()
{
    glPushMatrix();
    glTranslated(-10,-8,10);
    glScalef(20,1,-20);
    glColor3f(0.63,0.75,0.36);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

}

void drawSteps()
{
    glPushMatrix();
    glTranslatef(9,-7.85,6.9);
    glScalef(0.6,1,0.5);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-7.9,6.9);
    glScalef(3.5,1,0.5);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5,-7.8,5);
    glScalef(0.5,1,2);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.8,-7.8,5);
    glScalef(-1.5,1,0.5);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.2,-7.9,2);
    glScalef(0.5,1,2.8);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.2,-7.85,1);
    glScalef(0.5,1,0.8);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,-7.9,0);
    glScalef(3,1,0.5);
    glColor3f(1,1,1);
    drawCube1(0.5,0.2,0.2,  0.25, 0.1, 0.1 );
    glPopMatrix();
}

void background()
{
    glPushMatrix();
    glTranslatef(-10,-30,-15);
    glScalef(1,100,50);
    glColor4f(0.1,0.2,0.2,0.98);
    drawCube1(0.9,0.9,0.9,0.25, 0.1, 0.1 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,-30,-10);
    glScalef(50,100,1);
    glColor4f(0.18,0.21,0.2,0.98);
    drawCube1(0.9,0.9,0.9,0.25, 0.1, 0.1 );
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

void lightTwo()
{
    glPushMatrix();
    GLfloat light_ambient[]  = {0.5, 0.5, 0.5, 1.0};
    GLfloat light_diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat light_position[] = { 4.5, 6.0, 4.5, 1.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}

void treeLight()
{
    glPushMatrix();
    GLfloat light_ambient[]  = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_diffuse[]  = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 1, 1, 1, 1.0 };
    GLfloat light_position[] = { 1, -1, 1, 1.0 };

    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glPopMatrix();
}


void bitmap_output(int x, int y, char *string, void *font)
{
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, string[i]);
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
    bitmap_output(-6, 6, "Keep Your Determination.",GLUT_BITMAP_9_BY_15);

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

    treeLight();
    lightOne();
    lightTwo();


    background();

    drawPlane();

    drawTree();
    drawHeartCubes();
    drawPenrose();
    drawSteps();

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);                                          // Glut initialization
    glutInitWindowSize(windowWidth,windowHeight);                   // Window size
    glutInitWindowPosition(600,200);                                // Window position
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);       // RGB depth
    glutCreateWindow("Assignment");                                // Window title
    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );


    glutTimerFunc(100,heartAnimation,0);
    glutTimerFunc(180,treeAnimation,0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();                                                 // Glut cycle
    return 0;
}

