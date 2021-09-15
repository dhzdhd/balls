#include "raylib.h"

#ifndef COLLISION

#define COLLISION

typedef struct Ball
{
    Vector2 position;
    Vector2 velocity;
    Color color;
} Ball;

typedef struct HashMap
{
    int amount;
    Ball *balls[100];
} HashMap;

static const float MIN = 0;
static const float MAX = 2000;
static const float CELL_SIZE = 200;
static const int WIDTH = 10;
static const int GRID_NUMBER = 100;

void hash(Vector2 position, Ball *ball, int ballAmount);
void initHash(void);
void checkCollision(void);

#endif