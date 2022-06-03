#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "display.h"

#include "define_vars.h"
#include "struct.h"

extern struct BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
extern struct BALL ball;
extern struct PALETTE palette;

/**
 * Function that draws circle.
 * 
 * @brief Draw circle.
 * @param numOfTringle number of trigles that make circle.
 * @param ballScale size of ball.
 */
void drawCircle(unsigned const numOfTringle, int const ballScale)
{
    glPushMatrix();
    {
        glTranslatef(ball.position.x, ball.position.y, 0);
        glScalef(ballScale, ballScale, 0);
        glBegin(GL_TRIANGLE_FAN);
        {
            glVertex2f(0, 0);
            for (unsigned i = 0; i <= numOfTringle; i++)
            {
                float r = glm::pi<float>() * 2 * i / numOfTringle;
                glVertex2f(cosf(r), -sinf(r));
            }
        }
        glEnd();
    }
    glPopMatrix();
}

/**
 * Function thast draws rectangle.
 *
 * @brief Draw rectangle.
 * @param width width of rectangle to draw.
 * @param height height of rectangle to draw.
 * @param x rectangle position on x-axis.
 * @param y rectangle position on y-axis.
 * @param offset parameter of distance between rectangles, default value is 0.
 */
void drawRectangle(int const width, int const height, int const x, int const y, unsigned const offset)
{
    glPushMatrix();
    {

        glTranslated(x, y, 0);
        glBegin(GL_QUADS);
        {
            glVertex2d(0, 0);
            glVertex2d(0, height - offset);
            glVertex2d(width - offset, height - offset);
            glVertex2d(width - offset, 0);
        }
        glEnd();
    }
    glPopMatrix();
}

/**
 * Function that preapre background.
 * 
 * @brief Draw backgound.
 */

void background(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}

/**
 * Function that draws blocks.
 * 
 * @brief Draw blocks.
 */
void drawBlocks(void)
{
    for (int y = 0; y < BLOCK_ROW_MAX; y++)
    {
        const unsigned char colors[][3] = {
            {0xff, 0x00, 0x00},
            {0xff, 0xff, 0x00},
            {0x00, 0xff, 0x00},
            {0x00, 0xff, 0xff},
            {0x00, 0x00, 0xff},
            {0xff, 0x00, 0xff}};
        glColor3ubv((GLubyte *)&colors[y]);

        for (int x = 0; x < BLOCK_COLUMN_MAX; x++)
        {
            if (blocks[y][x].isBroken)
            {
                continue;
            }
            drawRectangle(BLOCK_WIDTH, BLOCK_HEIGHT, x * BLOCK_WIDTH, y * BLOCK_HEIGHT, 1);
        }
    }
}

/**
 * Function that initiate draws every elements like block, paddle and ball.
 * 
 * @brief Draw playable models.
 */
void models(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawBlocks();
    glColor3ub(0xff, 0xff, 0xff);
    drawRectangle(PADDLE_WIDTH, PADDLE_HEIGHT, palette.position.x, palette.position.y);
    drawCircle(NUM_OF_TRIANGLE, BALL_SCALE);
}

/**
 * Main function that displays every part of game.
 *
 * @brief Displays the game board.
 */
void display(void)
{
    background();
    models();
    glutSwapBuffers();
}
