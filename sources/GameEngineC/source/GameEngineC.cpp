//
// Created by Blake Rogan on 21/07/2016.
//
#include "../include/GameEngineC/GameEngineC.h"

bool loadGLFW(void) {
    return false;
}

bool loadPython(void) {
    return false;
}

bool loadAntTweakBar(void) {
    return false;
}

bool GameEngineC::prepare(int width, int height, void (* callback) (void)) {
    if (!glfwInit()) {
        return false;
    }
    TwInit(TW_OPENGL, NULL);
    Py_SetProgramName((wchar_t *) "GameEngineC Python");
    fprintf(stdout, (const char *) Py_GetProgramName());
    Py_Initialize();
    PyObject *pName, *pModule, *pDict, *pFunct;
    PyObject *pArgs, *pValue;
    pName = PyUnicode_DecodeFSDefault("this will fail");
    pModule = PyImport_Import(pName);
    PyErr_Print();
    PyRun_SimpleString("print('hello world from python');print(__name__)\n");
    TwWindowSize(width, height);
    callback();
    barOne = TwNewBar("This is a Test Bar");
    TwAddVarRW(barOne, "Test", TW_TYPE_FLOAT, &float_var, "");
    TwAddVarRW(barOne, "string_var", TW_TYPE_STDSTRING, &string_var, "");
    glfWwindow = glfwCreateWindow(width, height, "Test", NULL, NULL);
    if (glfWwindow) {
        glfwShowWindow(glfWwindow);
        return true;
    }
    glfwTerminate();
    return false;
}


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
    int tweak = TwWindowSize(width, height);
}


void GameEngineC::gameLoop() {
    glfwMakeContextCurrent(glfWwindow);

    glfwSetMouseButtonCallback(glfWwindow, mouseButtonCallback);
    glfwSetCursorPosCallback(glfWwindow, (GLFWcursorposfun) cursorPosCallback);
    glfwSetScrollCallback(glfWwindow, (GLFWscrollfun) scrollCallback);
    glfwSetKeyCallback(glfWwindow, (GLFWkeyfun) keyCallback);
    glfwSetCharCallback(glfWwindow, (GLFWcharfun) charCallback);
    glfwSetWindowSizeCallback(glfWwindow, (GLFWwindowsizefun) windowResize);

    while (!glfwWindowShouldClose(glfWwindow)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0, 1, 0.5, 1);
        TwDraw();

        glfwSwapBuffers(glfWwindow);
        glfwPollEvents();
    }

    TwTerminate();
    Py_Finalize();
    glfwTerminate();
}
