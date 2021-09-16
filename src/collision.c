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

void addHash(Vector2 position, Ball *ball, int ballAmount)
{
    // Grid cell for a ball position
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
            for (int j = 0; j < amount; j++)
            {
                for (int k = 0; k < amount; k++)
                {
                    if (j != k)
                    {
                        Ball *firstBall = balls[j];
                        Ball *secondBall = balls[k];
                        bool collision = CheckCollisionCircles((*firstBall).position, 10, (*secondBall).position, 10);
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
}

void checkBruteCollision(Ball *ballList, int ballAmount)
{
    for (int i = 0; i < ballAmount; i++)
    {
        for (int j = 0; j < ballAmount; j++)
        {
            Ball firstBall = ballList[i];
            Ball secondBall = ballList[j];

            bool collision = CheckCollisionCircles(firstBall.position, BALL_RADIUS, secondBall.position, BALL_RADIUS);
            if (collision && (i != j))
            {
                elasticCollision(&ballList[i], &ballList[j]);
                printf("collision! %i, %i\n", i, j);
            }
        }
    }
}

void elasticCollision(Ball *firstBall, Ball *secondBall)
{
    float firstVelX = firstBall->velocity.x;
    float firstVelY = firstBall->velocity.y;
    float secondVelX = secondBall->velocity.x;
    float secondVelY = secondBall->velocity.y;

    firstBall->velocity.x = -secondVelX;
    firstBall->velocity.y = -secondVelY;
    secondBall->velocity.x = -firstVelX;
    secondBall->velocity.y = -firstVelY;
}
