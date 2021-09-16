#include "raylib.h"
#include "game.h"
#include <stdio.h>

int ballAmount = 0;
Ball ballList[1000];

void gameSetup(bool paused, Camera2D camera)
{
    // Update
    if (IsMouseButtonPressed(0))
    {
        Vector2 ballPos = GetMousePosition();
        Vector2 ballVel = initBallVel();
        ballList[ballAmount] = (Ball){ballPos, ballVel, COLOR_LIST[GetRandomValue(0, COLOR_AMOUNT)]};
        ballAmount += 1;
    }
    if (IsMouseButtonPressed(1))
    {
        if (ballAmount != 0)
            ballAmount -= 1;
    }
    if (IsKeyPressed(KEY_C))
    {
        ballAmount = 0;
    }

    if (paused == false)
    {
        for (int i = 0; i < ballAmount; i++)
        {
            Ball *ball = &ballList[i];
            ball->position.x += ball->velocity.x;
            ball->position.y += ball->velocity.y;

            handleWallCollision(ball);
            // addHash(ball->position, ball, ballAmount);
        }
        // checkCollision();
        checkBruteCollision(ballList, ballAmount);
        initHash();
    }

    // Draw
    BeginDrawing();

    ClearBackground(BLACK);
    BeginMode2D(camera);

    DrawFPS(0, 0);

    // Draw Grid
    for (int i = 0; i < SCREEN_WIDTH; i += 100)
    {
        DrawLine(i, 0, i, SCREEN_HEIGHT, GREEN);
    }
    for (int i = 0; i < SCREEN_HEIGHT; i += 100)
    {
        DrawLine(0, i, SCREEN_WIDTH, i, GREEN);
    }

    // Draw paused text when paused
    if (paused)
    {
        DrawText("PAUSED", SCREEN_WIDTH - 135, 0, 30, GREEN);
    }

    if (ballAmount != 0)
    {
        for (int i = 0; i < ballAmount; i++)
        {
            Ball ball = ballList[i];
            DrawCircle(ball.position.x, ball.position.y, BALL_RADIUS, ball.color);

            if (paused)
            {
                float x = ball.position.x;
                float y = ball.position.y;
                Vector2 mousePos = GetMousePosition();

                // If mouse is centered on the ball
                if ((x - BALL_RADIUS < mousePos.x && x + BALL_RADIUS > mousePos.x) && (y - BALL_RADIUS < mousePos.y && y + BALL_RADIUS > mousePos.y))
                {
                    char buffer[100];
                    sprintf(buffer, "%i, %i", (int)ball.position.x, (int)ball.position.y);
                    DrawText(buffer, ball.position.x - 40, ball.position.y + 30, 20, ball.color);
                }
            }
        }
    }

    EndDrawing();
}

Vector2 initBallVel(void)
{
    return (Vector2){
        GetRandomValue(-10, 10),
        GetRandomValue(-10, 10),
    };
}

void handleWallCollision(Ball *ball)
{
    if (ball->position.x + BALL_RADIUS > SCREEN_WIDTH || ball->position.x - BALL_RADIUS < 0)
    {
        ball->velocity.x *= -1;
    }
    if (ball->position.y + BALL_RADIUS > SCREEN_HEIGHT || ball->position.y - BALL_RADIUS < 0)
    {
        ball->velocity.y *= -1;
    }
}