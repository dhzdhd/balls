#include "raylib.h"

#ifndef GAME
#define GAME

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    Color color;
} Ball;

static const int SCREEN_HEIGHT = 1000;
static const int SCREEN_WIDTH = 1000;
static const int BALL_RADIUS = 10;

static const int COLOR_AMOUNT = 10;
static const Color COLOR_LIST[] = {GREEN, RED, YELLOW, PURPLE, BLUE, DARKBLUE, DARKGREEN, DARKPURPLE, ORANGE, LIME, VIOLET};

Vector2 initBallVel(void);
void handleWallCollision(Ball *ball);
void handleBallCollision(Ball *firstBall, Ball *secondBall);
void gameSetup(bool paused, Camera2D camera);

#endif