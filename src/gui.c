#include "gui.h"
#include "game.h"

#include <stdio.h>

void gui_setup(bool *start)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("Balls!", SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 340, 70, GREEN);
     if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100}, "Hello"))
     {
         *start = true;
     }

    EndDrawing();
}