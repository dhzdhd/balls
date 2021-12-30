#include "gui.h"
#include "game.h"

#include <stdio.h>

void guiSetup(bool *start)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("Balls!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 340, 70, GREEN);
     if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 140, 300, 100}, "Hello"))
     {
         printf("yoo");
     }

    EndDrawing();
}