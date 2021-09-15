#include "collision.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <malloc.h>

// List amount = Number of grids
HashMap spatialList[100];

void initHash(void)
{
    for (int i = 0; i < GRID_NUMBER; i++)
    {
        spatialList[i] = (HashMap){0, {}};
    }
}

void hash(Vector2 position, Ball *ball, int ballAmount)
{
    // Unique grid cell for a ball position
    int gridCell = (int)(position.x / CELL_SIZE) + (int)(position.y / CELL_SIZE) * WIDTH;

    // Adding balls to the HashMap and spatialList
    int amount = spatialList[gridCell].amount;
    Ball *balls = spatialList[gridCell].balls;
    balls[amount + 1] = *ball;
    spatialList[gridCell] = (HashMap){amount + 1, balls};
}

void checkCollision(void)
{
    for (int i = 0; i < GRID_NUMBER; i++)
    {
        int amount = spatialList[i].amount;
        Ball **balls = spatialList[i].balls;

        if (amount > 1)
        {
            // wrong ranges
            for (int j = 2; j < amount; j++)
            {
                for (int k = 2; k < j; k++)
                {
                    Ball *firstBall = balls[j];
                    Ball *secondBall = balls[k];
                    bool collision = CheckCollisionCircles(firstBall->position, 30, secondBall->position, 30);
                    if (collision)
                    {
                        // (firstBall)->velocity.x = 0;
                        printf("Collision!\n");
                    }
                }
            }
        }
    }
}