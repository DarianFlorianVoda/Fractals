#include <iostream>
#include <windows.h>
#include <cmath>
#include <GL/freeglut.h>
#include <algorithm>

// window's width and height
#define X_DIM 800
#define Y_DIM 600

// Numbers of points that should be calculated before redrawing.
// Redrawing is slow, so higher number --> faster rendering
#define POINTS_PER_DRAW 10

// define the domain/range of the coordinates that will be represented in window
#define X_MIN (-5)
#define X_MAX (5)
#define Y_MIN (0)
#define Y_MAX (10)

// The image buffer. (Y_DIM) x (X_DIM) image matrix, with 3 values for each of R, G, and B
char image[Y_DIM][X_DIM][3];

// current point used for the Barnsley fern
double x, y;

// initial setup.
void init() {
    glClearColor(1.0,1.0,1.0,0.0);
    for(int i=0; i<Y_DIM;i++){
        for(int j=0;j<X_DIM;j++){
            image[i][j][0] = 255;
            image[i][j][1] = 255;
            image[i][j][2] = 255;
        }
    }
}

// mapping from a point in the Barnsley fern to a point in the window (x value)
int xPoint(double x_value) {
    return static_cast<int>((x_value - X_MIN) * X_DIM / (X_MAX - X_MIN));
}

// same mapping for y-value
int yPoint(double y_value) {
    return static_cast<int>((y_value - Y_MIN) * Y_DIM / (Y_MAX - Y_MIN));
}

// Generates the next point in the Barnsley fern, given the previous point (x, y)
void nextPoint() {
    float random = (float) rand() / RAND_MAX;

    double next_x = 0;
    double next_y = 0;

    if (random < 0.1) {         // 1% chance
        next_x = 0;
        next_y = 0.16 * y;
    } else if (random < 0.86) { // 85% chance
        next_x = 0.85 * x + 0.04 * y;
        next_y = -0.04 * x + 0.85 * y + 1.6;
    } else if (random < 0.93) { // 7% chance
        next_x = 0.2 * x - 0.26 * y;
        next_y = 0.23 * x + 0.22 * y + 1.6;
    } else {                    // 7% chance
        next_x = -0.15 * x + 0.28 * y;
        next_y = 0.26 * x + 0.24 * y + 0.44;
    }

    x = next_x;
    y = next_y;
}

// The GL display function called by "glutMainLoop" and "glutPostRedisplay"
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    // Calculate POINTS_PER_DRAW points before drawing. Each point gets drawn green

    for (int i = 0; i < POINTS_PER_DRAW; i++) {
        nextPoint();
        int xp = xPoint(x);
        int yp = yPoint(y);

        image[yp][xp][0] = 34;
        image[yp][xp][1] = 139;
        image[yp][xp][2] = 34;
    }

    // Draw the image buffer to the window.
    glDrawPixels(X_DIM, Y_DIM, GL_RGB, GL_UNSIGNED_BYTE, image);
    glFlush();
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(X_DIM, Y_DIM);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Barnsley fern Fractal");
    glutDisplayFunc(display);
    init();
    // Specify callback function
    glutMainLoop();
    return 0;
}
