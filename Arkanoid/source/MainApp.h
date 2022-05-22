#ifndef MAIN_APP_H
#define MAIN_APP_H
#include "DefHeaders.h"
#include "Initialize.h"
#include "Display.h"
#include "Mouse.h"
#include "Idle.h"
class MainApp
{
private:
    int argc;
    char** argv;
public:
    MainApp(int argc, char* argv[]);
    void startApp();
};
#endif