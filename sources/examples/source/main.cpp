//
// Created by Blake Rogan on 21/07/2016.
//
#include <iostream>
#include <GameEngineC/GameEngineC.h>

void onInit(void) {
    printf("Hello World!");
}

int main()
{
    GameEngineC engineC = GameEngineC();
    bool result = engineC.prepare(800, 600, &onInit);
    if (result) {
        engineC.gameLoop();
    } else {
        return 1;
    }
    return 0;
}