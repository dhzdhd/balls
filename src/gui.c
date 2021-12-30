#include "gui.h"
#include "game.h"

#include <stdio.h>

void gui_setup(bool *start)
{
    BeginDrawing();

    ClearBackground(BLACK);
    GuiSetStyle(DEFAULT, 1, 2);
    GuiSetFont(GuiGetFont());

    DrawText("Balls!", SCREEN_WIDTH / 2 - 95, SCREEN_HEIGHT / 2 - 340, 70, GREEN);
     if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 100}, ""))
     {
         *start = true;
     }
     DrawText("Enter", SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 10, 30, GREEN);

    EndDrawing();
}