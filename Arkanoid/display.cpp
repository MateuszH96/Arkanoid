#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "display.h"
#include <iostream>

#include "define_vars.h"
#include "struct.h"

extern struct BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
extern struct BALL ball;
extern struct PALETTE palette;

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

void drawRectangle(unsigned const width, unsigned const height, unsigned const x, unsigned const y, unsigned const offset)
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
void background(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
}
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
 * Function that displays blocks, paddle and ball.
 *
 * @brief Displays the game board.
 */
void display(void)
{
    background();
    models();
    glutSwapBuffers();
}
