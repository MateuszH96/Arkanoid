#include <GL/glut.h>

#include "define_vars.h"
#include "init.h"
#include "display.h"
#include "game_physics.h"

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
