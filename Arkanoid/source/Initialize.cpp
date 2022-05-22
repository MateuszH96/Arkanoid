#include "Initialize.h"

void Initialize::init(){
    memset(blocks, 0, sizeof blocks);

    palette.position = { WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - PADDLE_HEIGHT * 3 };
    ball.lastPosition =
        ball.position = { WINDOW_WIDTH / 2, BLOCK_HEIGHT * BLOCK_ROW_MAX };
    ball.velocity = { BALL_SPEED, BALL_SPEED };
    ball.velocity = glm::normalize(ball.velocity) * BALL_SPEED;
}