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
#include <vector>
#include <algorithm>

#ifndef PROJECT_GAMEENGINEC_H
#define PROJECT_GAMEENGINEC_H

using namespace std;

class GameEngineC {
public:
    typedef void (* InitialiseCallback) (void);
    typedef void (* DestroyCallback) (void);
    typedef void (* RenderCallback) (void);
    typedef void (* UpdateCallback) (double);

    InitialiseCallback onPythonLoad = InitialiseCallback();
    InitialiseCallback onGLFWLoad = InitialiseCallback();
    InitialiseCallback onAntTweakBarLoad = InitialiseCallback();

    DestroyCallback onPythonDestroy = DestroyCallback();
    DestroyCallback onGLFWDestroy = DestroyCallback();
    DestroyCallback onAntTweakBarDestroy = DestroyCallback();

    TwBar *barOne;

    GLFWwindow *glfWwindow;

private:
    std::vector<RenderCallback> renderArray;
    std::vector<UpdateCallback> updateArray;

    float clearColor[4] = {0.5960784313725490196f, 0.7843137254901960743f, 1.0f, 1.0f};
    bool loadGLFW(int width, int height);
    void destroyGLFW(void);
    bool loadPython(void);
    void destroyPython(void);
    bool loadAntTweakBar(int width, int height);
    void destroyAntTweakBar(void);

public:
    bool prepare(int width, int height, InitialiseCallback callback);
    void teardown(DestroyCallback callback);
    void teardown(void);
    void gameLoop();
    int registerRenderEvent(RenderCallback callback);
    void unregisterRenderEvent(RenderCallback callback);
    void unregisterRenderEvent(int index);
    int registerUpdateEvent(UpdateCallback callback);
    void unregisterUpdateEvent(UpdateCallback callback);
    void unregisterUpdateEvent(int index);
};


#endif //PROJECT_GAMEENGINEC_H
