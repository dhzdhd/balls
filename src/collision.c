#include "collision.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <malloc.h>

// List amount = Number of grids
HashMap spatial_list[100];

void init_hash(void)
{
    for (int i = 0; i < GRID_NUMBER; i++)
    {
        spatial_list[i] = (HashMap){0, {}};
    }
}

void add_hash(Vector2 position, Ball *ball, int ball_amount)
{
    // Grid cell for a ball position
    int grid_cell = (int)(position.x / CELL_SIZE) + (int)(position.y / CELL_SIZE) * WIDTH;

    // Adding balls to the HashMap and spatial_list
    int amount = spatial_list[grid_cell].amount;
    Ball *balls = spatial_list[grid_cell].balls;
    printf("%i, %i\n", grid_cell, amount);
    balls[amount + 1] = *ball;
    spatial_list[grid_cell] = (HashMap){amount + 1, balls};
}

void checkCollision(void)
{
    for (int i = 0; i < GRID_NUMBER; i++)
    {
        int amount = spatial_list[i].amount;
        Ball **balls = spatial_list[i].balls;

        if (amount > 1)
        {
            for (int j = 0; j < amount; j++)
            {
                for (int k = 0; k < amount; k++)
                {
                    if (j != k)
                    {
                        Ball *first_ball = balls[j];
                        Ball *second_ball = balls[k];
                        bool collision = CheckCollisionCircles((*first_ball).position, BALL_RADIUS, (*second_ball).position, BALL_RADIUS);
                        if (collision)
                        {
                            elastic_collision(&balls[i], &balls[j]);
                            printf("collision! %i, %i\n", i, j);
                        }
                    }
                }
            }
        }
    }
}

void check_brute_collision(Ball *ball_list, int ball_amount)
{
    for (int i = 0; i < ball_amount; i++)
    {
        for (int j = 0; j < ball_amount; j++)
        {
            Ball first_ball = ball_list[i];
            Ball second_ball = ball_list[j];

            bool collision = CheckCollisionCircles(first_ball.position, BALL_RADIUS, second_ball.position, BALL_RADIUS);
            if (collision && (i != j))
            {
                elastic_collision(&ball_list[i], &ball_list[j]);
                printf("collision! %i, %i\n", i, j);
            }
        }
    }
}

void elastic_collision(Ball *first_ball, Ball *second_ball)
{
    float first_vel_x = first_ball->velocity.x;
    float first_vel_y = first_ball->velocity.y;
    float second_vel_x = second_ball->velocity.x;
    float second_vel_y = second_ball->velocity.y;

    printf("%f, %f, %f, %f\n", first_vel_x, first_vel_y, second_vel_x, second_vel_y);

    first_ball->velocity.x = second_vel_x;
    first_ball->velocity.y = second_vel_y;
    second_ball->velocity.x = first_vel_x;
    second_ball->velocity.y = first_vel_y;
}
