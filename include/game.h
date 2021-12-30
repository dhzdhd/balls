#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

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

Vector2 init_ball_vel(void);
void handle_wall_collision(Ball *ball);
void handle_ball_collision(Ball *first_ball, Ball *second_ball);
void game_setup(bool paused, Camera2D camera);

#endif