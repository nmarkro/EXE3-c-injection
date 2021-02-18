#include "input.h"
#include "exe3.h"

void input_update(void)
{
    short pad = (input_pad & 0x03ff) ^ 0x03ff;
    exe3.joypad.keys_released = pad ^ exe3.joypad.raw_pad;

    exe3.joypad.raw_pad = pad;
    exe3.joypad.keys_pressed = 0;

    for (int i = 0; i < 10; i++)
    {
        short p = key_get_bitmask(i);
        if (pad & p)
            exe3.joypad.button_time[i]++;
        else
            exe3.joypad.button_time[i] = 0;
        if ((pad & p) || exe3.joypad.button_time[i] >= INPUT_REPEAT_DELAY)
            exe3.joypad.keys_pressed |= p;
    }
}

// converts key index into bitmask
short key_get_bitmask(int index)
{
    return (1 << index);
}

// checks for the inital pressing of a button (will only be true for the first frame held)
_Bool input_pressed(int index)
{
    return (exe3.joypad.button_time[index] <= 1 && exe3.joypad.raw_pad & key_get_bitmask(index));
}

// checks for if a button is pressed/held
_Bool input_held(int index)
{
    return (exe3.joypad.button_time[index] > 0 && exe3.joypad.raw_pad & key_get_bitmask(index));
}