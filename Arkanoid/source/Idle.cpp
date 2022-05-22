#include "Idle.h"

void Idle::idle()
{
    ball.lastPosition = ball.position;
    ball.position += ball.velocity;

    if ((ball.position.y >= WINDOW_HEIGHT))
    {
        Initialize::init();
        glutPostRedisplay();

        return;
    }
    if ((ball.position.x < 0) || (ball.position.x >= WINDOW_WIDTH))
    {
        ball.position = ball.lastPosition;
        ball.velocity.x *= -1.0f;
    }
    if ((ball.position.y < 0) || (ball.position.y >= WINDOW_HEIGHT))
    {
        ball.position = ball.lastPosition;
        ball.velocity.y *= -1.0f;
    }

    if ((ball.position.x >= palette.position.x) && (ball.position.x < palette.position.x + PADDLE_WIDTH) && (ball.position.y >= palette.position.y) && (ball.position.y < palette.position.y + PADDLE_HEIGHT))
    {
        ball.position = ball.lastPosition;
        float paddleCenterX = palette.position.x + PADDLE_WIDTH / 2;
        ball.velocity.x = (ball.position.x - paddleCenterX) / (PADDLE_WIDTH / 2) * 2;
        ball.velocity.y = -glm::sign(ball.velocity.y);
        ball.velocity = glm::normalize(ball.velocity) * BALL_SPEED;
    }

    {
        int x = (int)ball.position.x / BLOCK_WIDTH;
        int y = (int)ball.position.y / BLOCK_HEIGHT;
        if ((x >= 0) && (x < BLOCK_COLUMN_MAX) && (y >= 0) && (y < BLOCK_ROW_MAX) && (!blocks[y][x].isBlorken))
        {
            ball.position = ball.lastPosition;
            blocks[y][x].isBlorken = true;

            if ((ball.lastPosition.y < BLOCK_HEIGHT * y) || (ball.lastPosition.y >= BLOCK_HEIGHT * (y + 1)))
            {
                ball.velocity.y *= -1.0f;
            }
            else
            {
                ball.velocity.x *= -1.0f;
            }
        }
    }

    glutPostRedisplay();
}