#include "raylib.h"
#include "game.h"

#ifndef COLLISION
#define COLLISION

typedef struct HashMap
{
    int amount;
    Ball *balls[100];
} HashMap;

static const float MIN = 0;
static const float MAX = 1000;
static const float CELL_SIZE = 100;
static const int WIDTH = 10;
static const int GRID_NUMBER = 100;

void add_hash(Vector2 position, Ball *ball, int ball_amount);
void init_hash(void);
void check_brute_collision(Ball *ball_list, int ball_amount);
void elastic_collision(Ball *first_ball, Ball *second_ball);

#endif