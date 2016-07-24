//
// Created by Blake Rogan on 21/07/2016.
//
#include <GLFW/glfw3.h>
#include <AntTweakBar.h>
#include <cstdio>
#include <OpenGL/gl.h>
#include <string>
#include <strings.h>
#include <Python.h>

#ifndef PROJECT_GAMEENGINEC_H
#define PROJECT_GAMEENGINEC_H

using namespace std;

class GameEngineC {
private:
    typedef void (* callback) (void);
    GLFWwindow *glfWwindow;
    TwBar *barOne;
    float float_var = 0.0f;
    std::string string_var = "hello world";
public:
    bool prepare(int width, int height, void (* callback) (void));
    void gameLoop();
};


#endif //PROJECT_GAMEENGINEC_H
