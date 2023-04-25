#include <GL/glut.h>
#include <stdio.h>

#include "config.h"

int *values;

void onMouseButton(int button, int state, int x, int y) {
    if (state == 1) {
        return;
    }
    int clicked;
    switch(button) {
        case GLUT_LEFT_BUTTON:
            clicked = 0;
            break;
    }
    printf("Clicked on %d %d %d\n", x, y);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    int dx = values[1] / values[2], dy = values[0] / values[3];
    for (int i = 0; i < values[2]; i++) {
        glVertex2d(dx * i, values[0]);
        glVertex2d(dx * i, 0);
    }

    for (int i = 0; i < values[3]; i++) {
        glVertex2d(values[1], dy * i);
        glVertex2d(0, dy * i);
    }
    glEnd();
    glFlush();
}

void key(unsigned char key, int x, int y)
{
  if( key == 'q' ) exit(0);
}

// void tick(int) {

//     // Code for the game.

//     glutPostRedisplay();
//     glutTimerFunc(1000, tick, 0);
// }

int main(int argc, char *argv[]) {
    values = readConfig("/home/sandwitch/Documents/gameoflife/data/config.conf");
    int window;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowSize(values[1], values[0]);
    window = glutCreateWindow("Triangle");

    glClearColor(1.0,1.0,1.0,1.0);
    gluOrtho2D(0,values[1],0,values[0]);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(onMouseButton);

    // tick(0);

    glutMainLoop();

    return 0;
}
