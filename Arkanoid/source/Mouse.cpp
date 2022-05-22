#include "Mouse.h"
#include <iostream>
void Mouse::passiveMotion(int _x, int _y)
{
    palette.position.x = (float)_x - PADDLE_WIDTH / 2;
}