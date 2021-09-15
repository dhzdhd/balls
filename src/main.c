#include "raylib.h"
#include "raygui.h"
#include "stdio.h"
#include "collision.h"

const int SCREEN_HEIGHT = 2000;
const int SCREEN_WIDTH = 2000;
const int BALL_RADIUS = 30;

// Function prototypes
Vector2 initBallVel(void);
void handleWallCollision(Ball *ball);
void handleBallCollision(Ball *firstBall, Ball *secondBall);

const int COLOR_AMOUNT = 10;
const Color COLOR_LIST[] = {GREEN, RED, YELLOW, PURPLE, BLUE, DARKBLUE, DARKGREEN, DARKPURPLE, ORANGE, LIME, VIOLET};

int ballAmount = 0;
Ball ballList[1000] = {};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "balls!");
    initHash();

    Camera2D camera = {0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    bool unPaused = false;

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_SPACE))
        {
            if (unPaused == true)
            {
                unPaused = false;
            }
            else
            {
                unPaused = true;
            }
        }

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

        if (unPaused == true)
        {
            for (int i = 0; i < ballAmount; i++)
            {
                Ball *ball = &ballList[i];
                ball->position.x += ball->velocity.x;
                ball->position.y += ball->velocity.y;

                handleWallCollision(ball);
                hash(ball->position, ball, ballAmount);
            }
            checkCollision();
            initHash();
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode2D(camera);

        DrawFPS(0, 0);

        // Draw Grid
        for (int i = 0; i < SCREEN_WIDTH; i += 200)
        {
            DrawLine(i, 0, i, SCREEN_HEIGHT, GREEN);
        }
        for (int i = 0; i < SCREEN_HEIGHT; i += 200)
        {
            DrawLine(0, i, SCREEN_WIDTH, i, GREEN);
        }

        // Draw paused text when paused
        if (!unPaused)
        {
            DrawText("PAUSED", SCREEN_WIDTH - 135, 0, 30, GREEN);
        }

        if (ballAmount != 0)
        {
            for (int i = 0; i < ballAmount; i++)
            {
                Ball ball = ballList[i];
                DrawCircle(ball.position.x, ball.position.y, BALL_RADIUS, ball.color);

                if (!unPaused)
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

    CloseWindow();
    return 0;
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
