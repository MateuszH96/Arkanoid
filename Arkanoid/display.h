#ifndef DISPLAY_H_
#define DISPLAY_H_
#define NUM_OF_TRIANGLE (32)
void display(void);
void background(void);
void models(void);
void drawBlocks(void);
void drawCircle(unsigned const numOfTringle, int const ballScale);
void drawRectangle(int const width, int const height, int const x, int const y, unsigned const offset = 0);
#endif
