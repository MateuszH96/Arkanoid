#include "MainApp.h"

MainApp::MainApp(int argc, char* argv[]){
    this->argc=argc;
    this->argv=argv;
}
void MainApp::startApp(){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Arkanoid");
    glutDisplayFunc(Display::display);
    glutIdleFunc(Idle::idle);
    glutPassiveMotionFunc(Mouse::passiveMotion);
    Initialize::init();
    //init();
    glutMainLoop();
}