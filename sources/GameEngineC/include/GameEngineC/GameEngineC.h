//
// Created by Blake Rogan on 21/07/2016.
//
#include <GLFW/glfw3.h>
//#include <AntTweakBar.h>

#ifndef PROJECT_GAMEENGINEC_H
#define PROJECT_GAMEENGINEC_H

class GameEngineC {
private:
    typedef void (* callback) (void);
    GLFWwindow *glfWwindow;
    bool createWindow(int width, int height);
public:
    bool prepare(int width, int height, void (* callback) (void));
    void gameLoop();
};


#endif //PROJECT_GAMEENGINEC_H
