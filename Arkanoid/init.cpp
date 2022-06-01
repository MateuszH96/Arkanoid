#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "init.h"

#include "define_vars.h"
#include "struct.h"

struct BLOCK blocks[BLOCK_ROW_MAX][BLOCK_COLUMN_MAX];
struct BALL ball;
struct PALETTE palette;

/**
 * Initialization function, sets the size of the board, racket position, ball, ball direction and speed.
 *
 * @brief Initialization function.
 */
void init(void)
{
    memset(blocks, 0, sizeof blocks);

    palette.position = { WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - PADDLE_HEIGHT * 3 };

    ball.lastPosition = ball.position = { WINDOW_WIDTH / 2, BLOCK_HEIGHT * BLOCK_ROW_MAX };
    ball.velocity = { BALL_SPEED, BALL_SPEED };
    ball.velocity = glm::normalize(ball.velocity) * BALL_SPEED;
}
