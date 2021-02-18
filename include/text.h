#ifndef TEXT_H
#define TEXT_H
#include <gba_systemcalls.h>

// screen width in tiles
#define WIDTH 32
#define HEIGHT 14

struct TextPos
{
    int x, y;
};

void int_to_hex(char* buf, unsigned int value, int digits);
int int_to_dec(char* buf, unsigned int value, int digits);
struct TextPos draw_text(struct TextPos pos, char str[], int length);
void draw_var(struct TextPos pos, char str[], int var);
void draw_var_dec(struct TextPos pos, char str[], int var);

// probably make this an actual struct in exe3.h
extern unsigned int g_Toolkit[];

#endif