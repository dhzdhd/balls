#include "raylib.h"
#include "game.h"
#include "collision.h"
#include <stdio.h>

int ball_amount = 0;
Ball ball_list[1000];

void game_setup(bool paused, Camera2D camera)
{
    // Update
    if (IsMouseButtonPressed(0))
    {
        Vector2 ball_pos = GetMousePosition();
        Vector2 ball_vel = init_ball_vel();
        ball_list[ball_amount] = (Ball){ball_pos, ball_vel, COLOR_LIST[GetRandomValue(0, COLOR_AMOUNT)]};
        ball_amount += 1;
    }
    if (IsMouseButtonPressed(1))
    {
        if (ball_amount != 0)
            ball_amount -= 1;
    }
    if (IsKeyPressed(KEY_C))
    {
        ball_amount = 0;
    }

    if (paused == false)
    {
        for (int i = 0; i < ball_amount; i++)
        {
            Ball *ball = &ball_list[i];
            ball->position.x += ball->velocity.x;
            ball->position.y += ball->velocity.y;

            handle_wall_collision(ball);
            // addHash(ball->position, ball, ball_amount);
        }
        // checkCollision();
        check_brute_collision(ball_list, ball_amount);
        init_hash();
    }

    // Draw
    BeginDrawing();

    ClearBackground(BLACK);
    BeginMode2D(camera);

    DrawFPS(0, 0);

    char ballAmountStr[1000];
    sprintf(ballAmountStr, "%i", ball_amount);
    DrawText("Amount: ", 100, 0, 20, GREEN);
    DrawText(ballAmountStr, 180, 0, 20, GREEN);

    // Draw Grid
    // for (int i = 0; i < SCREEN_WIDTH; i += 100)
    // {
    //     DrawLine(i, 0, i, SCREEN_HEIGHT, GREEN);
    // }
    // for (int i = 0; i < SCREEN_HEIGHT; i += 100)
    // {
    //     DrawLine(0, i, SCREEN_WIDTH, i, GREEN);
    // }

    // Draw paused text when paused
    if (paused)
    {
        DrawText("PAUSED", SCREEN_WIDTH - 135, 0, 30, GREEN);
    }

    if (ball_amount != 0)
    {
        for (int i = 0; i < ball_amount; i++)
        {
            Ball ball = ball_list[i];
            DrawCircle(ball.position.x, ball.position.y, BALL_RADIUS, ball.color);

            if (paused)
            {
                float x = ball.position.x;
                float y = ball.position.y;
                Vector2 mouse_pos = GetMousePosition();

                // If mouse is centered on the ball
                if ((x - BALL_RADIUS < mouse_pos.x && x + BALL_RADIUS > mouse_pos.x) && (y - BALL_RADIUS < mouse_pos.y && y + BALL_RADIUS > mouse_pos.y))
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

Vector2 init_ball_vel(void)
{
    return (Vector2){
        GetRandomValue(-5, 5),
        GetRandomValue(-5, 5),
    };
}

void handle_wall_collision(Ball *ball)
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