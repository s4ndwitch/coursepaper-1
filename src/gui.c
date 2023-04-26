#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "board.h"

int *values;
char *board;

void syncBoard() {
    int dx = values[1] / values[2];
    int dy = values[0] / values[3];

    for (int i = 0; i < values[2]; i++) {
        for (int j = 0; j < values[3]; j++) {
            if (*(board + i * values[3] + j)) {
                glColor3f(0.0, 0.0, 0.0);
                glBegin(GL_POLYGON);
                glVertex2d(dx * i, dy * j);
                glVertex2d(dx * (i + 1), dy * j);
                glVertex2d(dx * (i + 1), dy * (j + 1));
                glVertex2d(dx * i, dy * (j + 1));
                glEnd();
            }
        }
    }
    glFlush();
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

    syncBoard();
}

void onMouseButton(int button, int state, int x, int y) {
    if (state == 1 || button != GLUT_LEFT_BUTTON) {
        return;
    }

    x /= values[1] / values[2];
    y = values[3] - y / (values[0] / values[3]) - 1;
    
    *(board + x * values[3] + y) = (*(board + x * values[3] + y) + 1) % 2;
    
    display();
}

void key(unsigned char key, int x, int y)
{
    switch(key) {
        case 'q':
            exit(0);
            break;
        case 't':
            turn(board, values[2], values[3]);
            break;
    }

    display();
}

// void tick(int) {

//     // Code for the game.

//     glutPostRedisplay();
//     glutTimerFunc(1000, tick, 0);
// }

int main(int argc, char *argv[]) {

    values = readConfig("/home/sandwitch/Documents/gameoflife/data/config.conf");

    board = (char *)malloc(sizeof(char) * values[2] * values[3]);
	for (int i = 0; i < values[2]; i++)
		for (int j = 0; j < values[3]; j++)
			*(board + i * values[3] + j) = 0;

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
