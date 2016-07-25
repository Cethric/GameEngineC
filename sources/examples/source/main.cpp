//
// Created by Blake Rogan on 21/07/2016.
//
#include <iostream>
#include <GameEngineC/GameEngineC.h>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>

void onInit(void) {
    printf("Hello World!");
}

TwBar *bar;
GameEngineC engineC;

double position[3] = {0, 0, 0};
double scale[3] = {1, 1, 1};
float rotation[4] = {0, 0, 0, 0};

float colorArray[4] = {1, 0, 0, 1};
bool tranRot = true;

float eye_array[3] = {10, 10, 10};
float center_array[3] = {0, 0, 0};

glm::mat4 Projection = glm::perspective<double>(glm::pi<double>() * 0.25, 4.0 / 3.0, 0.1, 100);
glm::mat4 View = glm::lookAt<float>(glm::make_vec3<float>(eye_array), glm::make_vec3<float>(center_array), glm::vec3(0, 1, 0));
glm::mat4 Model = glm::tmat4x4<double>(1);

void antTweakBar(void) {
    bar = TwNewBar("Triangle Test");
    {
        TwAddSeparator(bar, "Triangle Data", "");
        TwAddVarRW(bar, "Position", TW_TYPE_DIR3D, &position, "");
        TwAddVarRW(bar, "Rotation", TW_TYPE_QUAT4F, &rotation, "");
        TwAddVarRW(bar, "Scale", TW_TYPE_DIR3D, &scale, "");
        TwAddVarRW(bar, "Colour", TW_TYPE_COLOR4F, &colorArray, "");
        TwAddSeparator(bar, "Render Options", "");
        TwAddVarRW(bar, "Rotation Order", TW_TYPE_BOOLCPP, &tranRot, "");
    }

    {
        TwAddSeparator(engineC.barOne, "Camera Data", "");
        TwAddVarRW(engineC.barOne, "Position X", TW_TYPE_FLOAT, &eye_array[0], "");
        TwAddVarRW(engineC.barOne, "Position Y", TW_TYPE_FLOAT, &eye_array[1], "");
        TwAddVarRW(engineC.barOne, "Position Z", TW_TYPE_FLOAT, &eye_array[2], "");
        TwAddVarRW(engineC.barOne, "Look Position X", TW_TYPE_FLOAT, &center_array[0], "");
        TwAddVarRW(engineC.barOne, "Look Position Y", TW_TYPE_FLOAT, &center_array[1], "");
        TwAddVarRW(engineC.barOne, "Look Position Z", TW_TYPE_FLOAT, &center_array[2], "");
    }
}

void onRender(void) {
    View = glm::lookAt<float>(glm::make_vec3<float>(eye_array), glm::make_vec3<float>(center_array), glm::vec3(0, 1, 0));
    Model = glm::mat4(1);

    Model = Model * glm::translate(Model, glm::vec3(position[0], position[1], position[2]));
    Model = Model * glm::toMat4<float>(glm::make_quat<float>(rotation));
    Model = Model * glm::scale(glm::vec3(scale[0], scale[1], scale[2]));

    glm::mat4 MVP = Projection * View * Model;
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH);
    glPushMatrix();
    glLoadMatrixf(glm::value_ptr(MVP));
    glColor4fv(colorArray);
    glBegin(GL_TRIANGLES);
    glVertex2d(0, 0);
    glVertex2d(100, 0);
    glVertex2d(100, 100);
    glEnd();
    glPopMatrix();
}

int main()
{
    engineC = GameEngineC();
    engineC.registerRenderEvent(onRender);
    engineC.onAntTweakBarLoad = antTweakBar;
    bool result = engineC.prepare(800, 600, &onInit);
    if (result) {
        engineC.gameLoop();
    } else {
        engineC.teardown();
        return 1;
    }
    return 0;
}