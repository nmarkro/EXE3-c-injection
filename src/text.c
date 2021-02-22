#include "text.h"

// write characters to BG 0
void print_char(int x, int y, char chr)
{
    if (chr == '\0')
        return;

    short *tilemap = g_Toolkit.ptr_5C;

    // force uppercase
    if (chr < 0x61 || chr > 0x7E)
    {
        chr -= 0x20; 
    } else {
        chr -= 0x20;
        // check special characters
        if(!(chr < 0x20 || chr > 0x5B))
        {
            chr -= 0x20;
        }
    }
    
    tilemap[x + (y * WIDTH)] = 0xF200 | chr;
}

// converts passed value to hex string with leading zeros
void to_hex(char *buf, unsigned int value, int size_of_value)
{
    char chr;

    for(int i = 0; i < size_of_value; i++)
    {
        chr = (value << 0x1C) >> 0x1C;
        value = value >> 4;

        // convert to character index
        if (chr < 0xA)
            chr += 0x30;
        else
            chr += 0x37;

        buf[size_of_value - (i + 1)] = chr;
    }
}

// converts passed value to decimal string with no leading zeros
void to_dec(char *buf, int value, int size_of_value)
{
    char temp_buf[size_of_value];
    memset(temp_buf, '\0', size_of_value);

    char chr;
    int size = 0;

    for(int i = 0; i < size_of_value; i++)
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

    if (size == 0)
    {
        // add 0 if buffer is empty
        buf[0] = 0x30;
    } else {
        // reverse buffer
        for (int i = 0; i < size; i++)
            buf[i] = temp_buf[size - (i + 1)];
    }
}

void draw_textf(int x, int y, char *text, int value, int size_of_value)
{
    bool escaped = false;

    for(int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '\\')
        {
            escaped = true;
        } else if (text[i] == '%' && !escaped)
        {
            char command = text[i + 1];
            i++;
    
            char var_buf[size_of_value];
            memset(var_buf, '\0', size_of_value);

            switch (command)
            {
                case 'x': 
                    to_hex(var_buf, value, size_of_value);
                    break;
                case 'X':
                    to_hex(var_buf, value, size_of_value);
                    break;
                case 'd': 
                    to_dec(var_buf, value, size_of_value);
                    break;
                case 'D':
                    to_dec(var_buf, value, size_of_value);
                    break;
                default: 
                    continue;
            }

            for (int j = 0; j < size_of_value; j++)
            {
                print_char(x, y, var_buf[j]);
                x++;
                if (x > WIDTH)
                {
                    y += Div(x, WIDTH);
                    x = DivMod(x, WIDTH);
                }
            }
        } else {
            print_char(x, y, text[i]);
            x++;
            if (x > WIDTH)
            {
                y += Div(x, WIDTH);
                x = DivMod(x, WIDTH);
            }
            if (escaped)
                escaped = false;
        }
    }
}

void draw_text(int x, int y, char *text)
{
    for(int i = 0; i < strlen(text) && text[i] != '\0'; i++)
    {
        print_char(x, y, text[i]);
        x++;
        if (x > WIDTH)
        {
            y += Div(x, WIDTH);
            x = DivMod(x, WIDTH);
        }
    }
}