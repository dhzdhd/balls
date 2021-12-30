#include "raylib.h"
#include "game.h"
#include "gui.h"
#include "collision.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "balls!");
    initHash();

    Camera2D camera = {0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    bool paused = true;
    bool start = false;

    while (!WindowShouldClose())
    {
        if (start)
        {
            if (IsKeyPressed(KEY_SPACE))
                paused = !paused;
            if (IsKeyPressed(KEY_Q))
                start = false;

            gameSetup(paused, camera);
        }
        else
        {
            if (IsKeyPressed(KEY_ENTER))
                start = true;

            guiSetup(&start);
        }
    }

    CloseWindow();
    return 0;
}
