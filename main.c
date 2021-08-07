#include "raylib.h"
#include "raygui.h"

void constraintCheck(Vector2 *, float *, float *);

static const int SCREENHEIGHT = 1080;
static const int SCREENWIDTH = 1920;
static const int ballRadius = 50;

int main(void)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "balls!");

    Camera2D camera = {0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;

    Vector2 firstBallPos = {SCREENWIDTH / 2 - 100, SCREENHEIGHT / 2};
    Vector2 secondBallPos = {SCREENWIDTH / 2 + 100, SCREENHEIGHT / 2};

    float firstBallVX = GetRandomValue(5, 10);
    float firstBallVY = GetRandomValue(5, 10);
    float secondBallVX = GetRandomValue(5, 10);
    float secondBallVY = GetRandomValue(5, 10);

    SetTargetFPS(120);

    bool flag = false;

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_SPACE))
        {
            flag = true;
        }

        if (flag == true)
        {
            firstBallPos.x += firstBallVX;
            firstBallPos.y += firstBallVY;
            secondBallPos.x -= secondBallVX;
            secondBallPos.y -= secondBallVY;
        }

        constraintCheck(&firstBallPos, &firstBallVX, &firstBallVY);
        constraintCheck(&secondBallPos, &secondBallVX, &secondBallVY);

        if (abs(firstBallPos.x - secondBallPos.x) < ((ballRadius * 2) + 5.0f) && abs(firstBallPos.y - secondBallPos.y) < ((ballRadius * 2) + 5.0f))
        {
            if (abs(firstBallVX) > abs(secondBallVX))
            {
                firstBallVX *= -1;
            }
            else
            {
                secondBallVX *= -1;
            }

            if (abs(firstBallVY) > abs(secondBallVY))
            {
                firstBallVY *= -1;
            }
            else
            {
                secondBallVY *= -1;
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(GRAY);
        BeginMode2D(camera);

        DrawGrid(50, 10);
        DrawCircle(firstBallPos.x, firstBallPos.y, ballRadius, PURPLE);
        DrawCircle(secondBallPos.x, secondBallPos.y, ballRadius, ORANGE);

        DrawFPS(0, 0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void constraintCheck(Vector2 *ballPos, float *ballVX, float *ballVY)
{
    if (ballPos->x + ballRadius > SCREENWIDTH)
    {
        *ballVX *= -1;
    }

    if (ballPos->x - ballRadius < 0)
    {
        *ballVX *= -1;
    }

    if (ballPos->y + ballRadius > SCREENHEIGHT)
    {
        *ballVY *= -1;
    }

    if (ballPos->y - ballRadius < 0)
    {
        *ballVY *= -1;
    }
}