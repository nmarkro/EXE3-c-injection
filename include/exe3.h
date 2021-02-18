#ifndef EXE3_H
#define EXE3_H
#include "input.h"
#include "text.h"

struct Joypad
{
    short raw_pad;
    int button_time[10];
    short keys_pressed;
    short keys_released;
};

struct RNG 
{
    unsigned int value;
    unsigned int index;
    int delta;
};

// this struct is for global variables
struct exe3
{
    bool ready;
    bool menu_active;
    bool state_changed;
    struct Joypad joypad;
};

// for ARMIPS linking
extern struct exe3 exe3;
extern struct RNG rng1;
extern struct RNG rng2;

#endif