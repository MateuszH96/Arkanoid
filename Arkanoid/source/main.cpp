#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

#define BLOCK_WIDTH 128
#define BLOCK_HEIGHT 32

#define BLOCK_COLUMN_MAX (WINDOW_WIDTH / BLOCK_WIDTH)
#define BLOCK_ROW_MAX 6

#define PADDLE_WIDTH 128
#define PADDLE_HEIGHT 32

#define BALL_SCALE 8
#define BALL_SPEED (WINDOW_HEIGHT / 1800.0f)

typedef struct
{
    bool isBlorken;
} BLOCK;

typedef struct
{
    glm::vec2 position;
} PALETTE;

typedef struct
{
    glm::vec2 position;
    glm::vec2 lastPosition;
    glm::vec2 velocity;
} BALL;

BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
PALETTE palette;
BALL ball;

void init(void)
{
    memset(blocks, 0, sizeof blocks);

    palette.position = { WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - PADDLE_HEIGHT * 3 };

    ball.lastPosition =
        ball.position = { WINDOW_WIDTH / 2, BLOCK_HEIGHT * BLOCK_ROW_MAX };
    ball.velocity = { BALL_SPEED, BALL_SPEED };
    ball.velocity = glm::normalize(ball.velocity) * BALL_SPEED;
}

void display(void)
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

void idle(void)
{
    ball.lastPosition = ball.position;
    ball.position += ball.velocity;

    if ((ball.position.y >= WINDOW_HEIGHT))
    {
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

void passiveMotion(int _x, int _y)
{
    palette.position.x = (float)_x - PADDLE_WIDTH / 2;
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Arkanoid");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutPassiveMotionFunc(passiveMotion);
    init();
    glutMainLoop();

    return 0;
}
