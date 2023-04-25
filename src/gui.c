#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialise GLFW\n");
        return -1;
    }

    GLFWwindow* window;
    window = glfwCreateWindow(1024, 768, "A Window", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open a window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialise GLEW\n");
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    return 0;
}