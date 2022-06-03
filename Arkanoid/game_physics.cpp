#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <Windows.h>

#include "game_physics.h"

#include "define_vars.h"
#include "struct.h"
#include "init.h"

extern struct BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
extern struct BALL ball;
extern struct PALETTE palette;

/**
 * A function that performs ball bouncing and removing blocks when touched.
 *
 * @brief Ball, paddle and blocks physics.
 */
void idle(void)
{
    int winGame = 0;
    for (int y = 0; y < BLOCK_ROW_MAX; y++)
    {
        for (int x = 0; x < BLOCK_COLUMN_MAX; x++)
        {
            if (blocks[y][x].isBroken)
            {
                winGame++;
            }
        }
    }
    if (winGame == BLOCK_COLUMN_MAX * BLOCK_ROW_MAX)
    {
        MessageBox(NULL, L"Wygra�e�!", L"Koniec gry", 0);
        exit(0);
    }

    ball.lastPosition = ball.position;
    ball.position += ball.velocity;

    if ((ball.position.y >= WINDOW_HEIGHT))
    {
        MessageBox(NULL, L"Game Over", L"Koniec gry", 0);

        init();
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
        if ((x >= 0) && (x < BLOCK_COLUMN_MAX) && (y >= 0) && (y < BLOCK_ROW_MAX) && (!blocks[y][x].isBroken))
        {
            ball.position = ball.lastPosition;
            blocks[y][x].isBroken = true;

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

/**
 * The function that sets the positions of the palettes.
 *
 * @brief Palettes setting.
 * @param int _x: coordinate x palettes.
 * @param int _y: coordinate x palettes.
 */
void passiveMotion(int _x, int _y)
{
    palette.position.x = (float)_x - PADDLE_WIDTH / 2;
    palette.position.x = palette.position.x < 0.0 ? 0.0 : palette.position.x;
    palette.position.x = palette.position.x > WINDOW_WIDTH-PADDLE_WIDTH ? WINDOW_WIDTH-PADDLE_WIDTH : palette.position.x;
}
