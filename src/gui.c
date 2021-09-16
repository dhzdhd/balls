#include "gui.h"
#include "game.h"

#include "raygui.h"
#include "raylib.h"

void guiSetup(void)
{
    BeginDrawing();

    ClearBackground(BLACK);

    DrawText("Balls!", SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 140, 70, GREEN);
    // if (GuiButton((Rectangle){SCREEN_WIDTH / 2 - 80, SCREEN_HEIGHT / 2 - 140, 50, 50}, "Hello"))
    {
        // printf("yoo");
    }

    EndDrawing();
}