//
// Created by Blake Rogan on 21/07/2016.
//
#include <cstdio>
#include <OpenGL/gl.h>
#include "../include/GameEngineC/GameEngineC.h"


bool GameEngineC::prepare(int width, int height, void (* callback) (void)) {
    if (!glfwInit()) {
        return false;
    }
    callback();
    return createWindow(width, height);
}

bool GameEngineC::createWindow(int width, int height) {
    glfWwindow = glfwCreateWindow(width, height, "Test", NULL, NULL);
    if (glfWwindow) {
        glfwShowWindow(glfWwindow);
        return true;
    }
    glfwTerminate();
    return false;
}

void GameEngineC::gameLoop() {
    glfwMakeContextCurrent(glfWwindow);
    while (!glfwWindowShouldClose(glfWwindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 1, 0.5, 1);
        glfwSwapBuffers(glfWwindow);
        glfwPollEvents();
    }

    glfwTerminate();
}
