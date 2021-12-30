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

void addHash(Vector2 position, Ball *ball, int ballAmount);
void initHash(void);
void checkBruteCollision(Ball *ballList, int ballAmount);
void elasticCollision(Ball *firstBall, Ball *secondBall);

#endif