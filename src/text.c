#include "text.h"

// write characters to BG 0
void print_char(int x, int y, char chr)
{
    short *tilemap = g_Toolkit.ptr_5C;
    // force uppercase
    if (chr < 0x61 || chr > 0x7E)
    {
        chr -= 0x20; 
    } else {
        chr -= 0x20;
        // check special characters
        if(chr < 0x20 || chr > 0x5B)
            return;
        else
            chr -= 0x20;
    }

    if (chr != 0)
        tilemap[x + (y * WIDTH)] = 0xF200 | chr;
}

// converts passed value to hex string with leading zeros
void int_to_hex(char* buf, unsigned int value, int digits)
{
    char chr;
    int place;

    for(int i = 0; i < digits; i++)
    {
        // lmao
        place = (digits - (i + 1)) << 2;
        chr = (value & (0xF << place)) >> place;

        // convert A-F to correct letters
        if (chr >= 0xA) 
            chr += 0x07;
        // convert to character index
        chr += 0x30;

        buf[i] = chr;
    }
}

// converts passed value to decimal string with no leading zeros
int int_to_dec(char* buf, unsigned int value, int digits)
{
    char temp_buf[digits];
    char chr;
    int size = 0;

    for(int i = 0; i < digits; i++)
    {
        if (value == 0)
            break;

        // get the rightmost digit and discard it from the value
        chr = DivMod(value, 10);
        value = Div(value, 10);

        // convert to character index
        chr += 0x30;
        temp_buf[size] = chr;
        size++;
    }

    // add 0 if buffer is empty
    if (size == 0)
    {
        temp_buf[0] = 0x30;
        size = 1;
    }

    // reverse buffer
    for (int i = 0; i < size; i++)
        buf[i] = temp_buf[size - (i + 1)];

    return size;
}

struct TextPos draw_text(struct TextPos pos, char str[], int length)
{
    for(int i = 0; i < length && str[i] != '\0'; i++)
    {
        print_char(pos.x, pos.y, str[i]);
        pos.x++;
        if (pos.x > WIDTH)
        {
            pos.y += Div(pos.x, WIDTH);
            pos.x = DivMod(pos.x, WIDTH);
        }
    }

    return pos;
}

void draw_var(struct TextPos pos, char str[], int var)
{
    char var_buf[8];
    int_to_hex(var_buf, var, 8);

    pos = draw_text(pos, str, WIDTH);
    pos = draw_text(pos, var_buf, 8);
}

void draw_var_dec(struct TextPos pos, char str[], int var)
{
    char var_buf[8];
    int var_size = int_to_dec(var_buf, var, 8);

    pos = draw_text(pos, str, WIDTH);
    pos = draw_text(pos, var_buf, var_size);
}