#ifndef TEXT_H
#define TEXT_H
#include <string.h>
#include <gba_systemcalls.h>
#include "toolkit.h"

// screen width in tiles
#define WIDTH 32
#define HEIGHT 14

void draw_textf(int x, int y, char *text, int value, int size_of_value);
void draw_text(int x, int y, char *text);

#endif