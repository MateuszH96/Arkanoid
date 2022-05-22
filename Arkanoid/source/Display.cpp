#include "Display.h"


void Display::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for (int y = 0; y < BLOCK_ROW_MAX; y++)
    {
        const unsigned char colors[][3] = {
            {0xff, 0x00, 0x00},
            {0xff, 0xff, 0x00},
            {0x00, 0xff, 0x00},
            {0x00, 0xff, 0xff},
            {0x00, 0x00, 0xff},
            {0xff, 0x00, 0xff}
        };
        glColor3ubv((GLubyte*)&colors[y]);

        for (int x = 0; x < BLOCK_COLUMN_MAX; x++)
        {
            if (blocks[y][x].isBlorken)
            {
                continue;
            }
            glPushMatrix();
            {
                glTranslated(BLOCK_WIDTH * x, BLOCK_HEIGHT * y, 0);
                glBegin(GL_QUADS);
                {
                    glVertex2d(0, 0);
                    glVertex2d(0, BLOCK_HEIGHT - 1);
                    glVertex2d(BLOCK_WIDTH - 1, BLOCK_HEIGHT - 1);
                    glVertex2d(BLOCK_WIDTH - 1, 0);
                }
                glEnd();
            }
            glPopMatrix();
        }
    }

    glColor3ub(0xff, 0xff, 0xff);
    glPushMatrix();
    {
        glTranslatef(palette.position.x, palette.position.y, 0);
        glBegin(GL_QUADS);
        {
            glVertex2d(0, 0);
            glVertex2d(0, PADDLE_HEIGHT);
            glVertex2d(PADDLE_WIDTH, PADDLE_HEIGHT);
            glVertex2d(PADDLE_WIDTH, 0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(ball.position.x, ball.position.y, 0);
        glScalef(BALL_SCALE, BALL_SCALE, 0);
        glBegin(GL_TRIANGLE_FAN);
        {
            glVertex2f(0, 0);
            int n = 32;
            for (int i = 0; i < n + 1; i++)
            {
                float r = glm::pi<float>() * 2 * i / n;
                glVertex2f(cosf(r), -sinf(r));
            }
        }
        glEnd();
    }
    glPopMatrix();

    glutSwapBuffers();
}