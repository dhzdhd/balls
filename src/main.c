#include "raylib.h"
#include "raygui.h"

static const int SCREEN_HEIGHT = 1080;
static const int SCREEN_WIDTH = 1920;
static const int BALL_RADIUS = 25;

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    Color color;
} Ball;

// Function prototypes
void constraintCheck(Vector2 *, float *, float *);
Vector2 initBallPos(void);
Vector2 initBallVel(void);
void handleWallCollison(Ball *);

const int COLOR_AMOUNT = 9;
const Color COLOR_LIST[] = {GREEN, RED, YELLOW, PURPLE, BLUE, DARKBLUE, DARKGREEN, DARKPURPLE, ORANGE};

int ballAmount = 0;
Ball ballList[1000] = {};

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "balls!");

    Camera2D camera = {0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0f;

    SetTargetFPS(60);

    bool flag = false;

    while (!WindowShouldClose())
    {
        // Update
        if (IsKeyPressed(KEY_SPACE))
        {
            if (flag == true)
            {
                flag = false;
            }
            else
            {
                flag = true;
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

        if (flag == true)
        {
            for (int i = 0; i < ballAmount; i++)
            {
                Ball *ball = &ballList[i];
                ball->position.x += ball->velocity.x;
                ball->position.y += ball->velocity.y;

                handleWallCollision(ball);
            }
        }

        // Draw
        BeginDrawing();

        ClearBackground(BLACK);
        BeginMode2D(camera);

        DrawFPS(0, 0);

        if (ballAmount != 0)
        {
            for (int i = 0; i < ballAmount; i++)
            {
                Ball ball = ballList[i];
                DrawCircle(ball.position.x, ball.position.y, BALL_RADIUS, ball.color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Vector2 initBallPos(void)
{
    return (Vector2){
        GetRandomValue(0 + BALL_RADIUS, SCREEN_WIDTH - BALL_RADIUS),
        GetRandomValue(0 + BALL_RADIUS, SCREEN_HEIGHT - BALL_RADIUS),
    };
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
    if (ball->position.x + BALL_RADIUS > SCREEN_WIDTH)
    {
        ball->velocity.x *= -1;
    }
    if (ball->position.x - BALL_RADIUS < 0)
    {
        ball->velocity.x *= -1;
    }
    if (ball->position.y + BALL_RADIUS > SCREEN_HEIGHT)
    {
        ball->velocity.y *= -1;
    }
    if (ball->position.y - BALL_RADIUS < 0)
    {
        ball->velocity.y *= -1;
    }
}