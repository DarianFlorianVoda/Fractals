#include <windows.h>
#include <GL/freeglut.h>
#include <cmath>
/* initial tetrahedron */

// tetrahedron vertexes: 0 - z-index; 1: upper; 2: left; 3: right
GLfloat v[4][3]={{0.0, 0.0, 1.0}, {0.0, 2.0, -1.0},
                 {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}};

// colors
GLfloat colors[4][3] = {{0.0, 0.9, 0.2}, {0.0, 0.5, 0.2},
                        {0.0, 0.5, 0.3}, {0.0, 0.9, 0.4}};

GLfloat myIdentityMatrix[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
};

GLfloat myTranslationMatrix[16] = {
        1.0, 0.0, 0.0, 0.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        1.0, 1.0, 5.0, 1.0
};
GLfloat angle = 0;
GLfloat angle2 = 0;
int n;


const GLfloat *my_rotation_matrix() {
    return new GLfloat[16]{
            cosf(angle * 0.02f), 0, sinf(angle * 0.02f), 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sinf(angle * 0.02f), cosf(angle * 0.02f), 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };
}

// draw the triangle
void triangle(GLfloat *va, GLfloat *vb, GLfloat *vc) {
    glVertex3fv(va);
    glVertex3fv(vb);
    glVertex3fv(vc);
}

// create the tetrahedron and color it
void tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d) {
    glColor3fv(colors[0]);
    triangle(a, b, c);
    glColor3fv(colors[1]);
    triangle(a, c, d);
    glColor3fv(colors[2]);
    triangle(a, d, b);
    glColor3fv(colors[3]);
    triangle(b, d, c);
}

// dividing the tetrahedron
void divide_tetra(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m) {
    GLfloat mid[6][3];
    if(m>0) {

        // compute six midpoints
        for (int j = 0; j < 3; j++) {
            mid[0][j]=(a[j]+b[j])/2;
            mid[1][j]=(a[j]+c[j])/2;
            mid[2][j]=(a[j]+d[j])/2;
            mid[3][j]=(b[j]+c[j])/2;
            mid[4][j]=(c[j]+d[j])/2;
            mid[5][j]=(b[j]+d[j])/2;
        }

        // create 4 tetrahedrons by subdivision
        divide_tetra(a, mid[0], mid[1], mid[2], m-1);
        divide_tetra(mid[0], b, mid[3], mid[5], m-1);
        divide_tetra(mid[1], mid[3], c, mid[4], m-1);
        divide_tetra(mid[2], mid[4], d, mid[5], m-1);
    }
    else
        tetra(a,b,c,d); // draw tetrahedron at end of recursion
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //right square
    glPushMatrix();
//    glMultMatrixf(myTranslationMatrix);
    glMultMatrixf(my_rotation_matrix());
    glBegin(GL_TRIANGLES);
    divide_tetra(v[0], v[1], v[2], v[3], n);
    glEnd();
    glPopMatrix();
    glFlush();
}

void handle_keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r' :
            angle += 5;
            break;
        case 't' :
            angle2 += 5;
            break;
        case 'q' :
            exit(EXIT_SUCCESS);
    }
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
                2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
                2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void init() {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(myIdentityMatrix);
    glOrtho(-2, 2, -2, 2, -3, 3);
}

void function(){
    glutPostRedisplay();
}


int main(int argc, char **argv)
{
    // number of subdivision steps
    n = 4;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Sierpinkski");
    init();
    glutReshapeFunc(myReshape);
    glutIdleFunc(function);
    glutDisplayFunc(display);
    glutKeyboardFunc(handle_keyboard);
    glEnable(GL_DEPTH_TEST);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
}