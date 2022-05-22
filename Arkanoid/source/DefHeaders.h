#ifndef DEF_HEADERS_H
#define DEF_HEADERS_H

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

    static BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
    static PALETTE palette;
    static BALL ball;
    

#endif