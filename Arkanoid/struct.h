#ifndef STRUCT_H_
#define STRUCT_H_

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

struct BLOCK
{
    bool isBroken;
};

struct PALETTE
{
    glm::vec2 position;
};

struct BALL
{
    glm::vec2 position;
    glm::vec2 lastPosition;
    glm::vec2 velocity;
};

#endif
