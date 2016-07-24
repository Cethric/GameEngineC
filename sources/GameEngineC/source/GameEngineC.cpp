//
// Created by Blake Rogan on 21/07/2016.
//
#include "GameEngineC/GameEngineC.h"

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    int tweak = TwEventMouseButtonGLFW(button, action);
}

void cursorPosCallback(GLFWwindow *window, double x, double y) {
    int tweak = TwEventMousePosGLFW((int) x, (int) y);
}

void scrollCallback(GLFWwindow *window, double x, double y) {
    int tweak = TwEventMouseWheelGLFW((int) y);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mod) {
    int tweak = TwEventKeyGLFW(key, action);
}

void charCallback(GLFWwindow *window, unsigned int code_point) {
    int tweak = TwEventCharGLFW(code_point, GLFW_PRESS);
}

void windowResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    int tweak = TwWindowSize(width, height);
}


bool GameEngineC::loadGLFW(int width, int height) {
    if (!glfwInit()) {
        return false;
    }

    glfWwindow = glfwCreateWindow(width, height, "Test", NULL, NULL);
    if (glfWwindow) {
        glfwShowWindow(glfWwindow);

        glfwMakeContextCurrent(glfWwindow);

        glfwSetMouseButtonCallback(glfWwindow, mouseButtonCallback);
        glfwSetCursorPosCallback(glfWwindow, (GLFWcursorposfun) cursorPosCallback);
        glfwSetScrollCallback(glfWwindow, (GLFWscrollfun) scrollCallback);
        glfwSetKeyCallback(glfWwindow, (GLFWkeyfun) keyCallback);
        glfwSetCharCallback(glfWwindow, (GLFWcharfun) charCallback);
        glfwSetWindowSizeCallback(glfWwindow, (GLFWwindowsizefun) windowResize);

        if (onGLFWLoad) {
            onGLFWLoad();
        }
        return true;
    }
    return false;
}

void GameEngineC::destroyGLFW(void) {
    if (onGLFWDestroy) {
        onGLFWDestroy();
    }
    glfwTerminate();
}

bool GameEngineC::loadPython(void) {
    Py_SetProgramName((wchar_t *) "GameEngineC Python");
    Py_Initialize();
    PyObject *pName, *pModule, *pDict, *pFunct;
    PyObject *pArgs, *pValue;
    pName = PyUnicode_DecodeFSDefault("this will fail");
    pModule = PyImport_Import(pName);
    PyErr_Print();
    PyRun_SimpleString("print('hello world from python');print(__name__)\n");
    if (onPythonLoad) {
        onPythonLoad();
    }
    return true;
}

void GameEngineC::destroyPython(void) {
    if (onPythonDestroy) {
        onPythonDestroy();
    }
    Py_Finalize();
}

int renderMode = 0;

void toggleModes(void *clientData) {
    renderMode ++;
    if (renderMode == 3) {
        renderMode = 0;
    }
}

bool GameEngineC::loadAntTweakBar(int width, int height) {
    TwInit(TW_OPENGL, NULL);
    TwWindowSize(width, height);
    barOne = TwNewBar("OpenGL Render Controls");
    if (barOne) {
        TwAddSeparator(barOne, "Colours", "");
        TwAddVarRW(barOne, "Clear Color", TW_TYPE_COLOR4F, &clearColor, "");
        TwAddSeparator(barOne, "RenderModes", "");
        TwAddButton(barOne, "ToggleModes", (TwButtonCallback)toggleModes, NULL, "");
    }
    if (onAntTweakBarLoad) {
        onAntTweakBarLoad();
    }
    return true;
}

void GameEngineC::destroyAntTweakBar(void) {
    if (onAntTweakBarDestroy) {
        onAntTweakBarDestroy();
    }
    TwTerminate();
}

bool GameEngineC::prepare(int width, int height, InitialiseCallback callback) {
    if (loadGLFW(width, height) && loadAntTweakBar(width, height) && loadPython()) {
        callback();
        return true;
    }
    return false;
}

void dummyCallback(void) {

}

void GameEngineC::teardown(void) {
    teardown((DestroyCallback)dummyCallback);
}

void GameEngineC::teardown(DestroyCallback callback) {
    destroyPython();
    destroyAntTweakBar();
    destroyGLFW();
    callback();
}

int GameEngineC::registerRenderEvent(RenderCallback callback) {
    renderArray.resize(renderArray.size() + 1);
    renderArray.push_back(callback);

}
void GameEngineC::unregisterRenderEvent(RenderCallback callback) {
    renderArray.erase(std::remove(renderArray.begin(), renderArray.end(), callback), renderArray.end());
    renderArray.shrink_to_fit();
}
void GameEngineC::unregisterRenderEvent(int index) {
    renderArray.erase(renderArray.begin() + index);
    renderArray.shrink_to_fit();
}
int GameEngineC::registerUpdateEvent(UpdateCallback callback) {
    updateArray.resize(updateArray.size() + 1);
    updateArray.push_back(callback);
}
void GameEngineC::unregisterUpdateEvent(UpdateCallback callback) {
    updateArray.erase(std::remove(updateArray.begin(), updateArray.end(), callback), updateArray.end());
    updateArray.shrink_to_fit();
}
void GameEngineC::unregisterUpdateEvent(int index) {
    updateArray.erase(updateArray.begin() + index);
    updateArray.shrink_to_fit();
}

void GameEngineC::gameLoop() {

    while (!glfwWindowShouldClose(glfWwindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

        glPushMatrix();
        switch (renderMode) {
            default:
            case 0:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
            case 1:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case 2:
                glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                break;
        }
        for (RenderCallback render : renderArray) {
            if (render) {
                render();
            }
        }

        for (UpdateCallback update : updateArray) {
            if (update) {
                update(0.001);
            }
        }
        glPopMatrix();

        TwDraw();

        glfwSwapBuffers(glfWwindow);
        glfwPollEvents();
    }

    teardown();
}
