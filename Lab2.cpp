#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_POS 20
#define MIN_POS -20

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processExit(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void DrawFloor() {
    float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
    };

    glVertexPointer(3, GL_FLOAT, 0, &vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    for (int i = MIN_POS / 2; i < MAX_POS / 2; i++) {
        for (int j = MIN_POS / 2; j < MAX_POS / 2; j++) {
            glPushMatrix();
            if ((i+j) % 2 == 0) {
                glColor3f(1.0f, 0.5f, 0.0f);
            }
            else {
                glColor3f(1.0f, 0.0f, 1.0f);
            }
            glTranslatef(i * 2, j * 2, -0.1);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
            glPopMatrix();
        }
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawAxises() {
    float xAxis[] = {
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f
    };
    float yAxis[] = {
    -1.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f,
    };
    float zAxis[] = {
    -1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10);
    glVertexPointer(3, GL_FLOAT, 0, &xAxis);
    for (int i = 0; i < MAX_POS; i++) {
        glPushMatrix();
        glTranslatef(-MAX_POS, MAX_POS - 2, 0);
        glTranslatef(i * 2, 0, 0);
        glDrawArrays(GL_LINES, 0, 2);
        glPopMatrix();
    }
    glVertexPointer(3, GL_FLOAT, 0, &yAxis);
    for (int i = 0; i < MAX_POS; i++) {
        glPushMatrix();
        glTranslatef(-MAX_POS, -MAX_POS, 0);
        glTranslatef(0, i * 2, 0);
        glDrawArrays(GL_LINES, 0, 2);
        glPopMatrix();
    }
    glVertexPointer(3, GL_FLOAT, 0, &zAxis);
    glTranslatef(0, 0, 1);
    for (int i = 0; i < MAX_POS; i++) {
        glPushMatrix();
        glTranslatef(-MAX_POS, MAX_POS - 2, 0);
        glTranslatef(0, 0, i * 2);
        glDrawArrays(GL_LINES, 0, 2);
        glPopMatrix();
    }
    glDisableClientState(GL_VERTEX_ARRAY);
}

void MoveCamera(GLFWwindow* window, int &xAngle, int &zAngle, int &xPos, int &yPos) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (++xAngle > 180) {
            xAngle = 180;
        }
        else {
            xAngle = xAngle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (--xAngle < 0) {
            xAngle = 0;
        }
        else {
            xAngle = xAngle;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        zAngle++;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        zAngle--;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (xPos < MAX_POS) {
            xPos++;
        }
        //std::cout << xPos << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (xPos > MIN_POS) {
            xPos--;
        }
        //std::cout << xPos << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (yPos < MAX_POS) {
            yPos++;
        }
        //std::cout << yPos << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (yPos > MIN_POS) {
            yPos--;
        }
        //std::cout << yPos << std::endl;
    }
    glRotatef(-xAngle, 1, 0, 0);
    glRotatef(-zAngle, 0, 0, 1);
    glTranslatef(-xPos, -yPos, -3);
}

int main(void) {

    int xAngle = 0, zAngle = 0, xPos = 0, yPos = 0;

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Amongus", NULL, NULL);
    glfwMakeContextCurrent(window);
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 100);
    glTranslatef(0, 0, -2);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        processExit(window);

        glClearColor(46/255.0f, 202/255.0f, 52/255.0f, 255/255.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        MoveCamera(window, xAngle, zAngle, xPos, yPos);
        DrawFloor();
        DrawAxises();
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}