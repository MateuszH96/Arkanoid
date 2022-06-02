#ifndef DISPLAY_H_
#define DISPLAY_H_
#define IS_MATRIX (true)
#define NUM_OF_TRIANGLE (32)
void display(void);
void background(void);
void models(void);
void drawBlocks(void);
void drawCircle(unsigned const numOfTringle, int const ballScale);
void drawRectangle(unsigned const width, unsigned const height,unsigned const x,unsigned const y, unsigned const offset=0);
#endif
