#include "exe3.h"

// resets RNG2 on soft reset
void hooked_rng_reset()
{
    rng2.value = 0xA338244F;
    rng2.index = 0;
}

// increase RNG index and delta when called
void hooked_rng(struct RNG *r)
{
    r->index++;
    r->delta++;
}

void init(void)
{
    exe3.menu_active = true;
    exe3.ready = true;
}

// Runs every frame
void hooked_main(void)
{
    if (!exe3.ready)
        init();

    input_update();

    // use holding L + R to interact with the HUD
    if (input_held(KEY_L) &&
        input_held(KEY_R))
    {   
        // L + R + SELECT toggles the HUD
        if (input_held(KEY_SELECT))
        {
            if (!exe3.state_changed)
            {
                exe3.menu_active = !exe3.menu_active;
                exe3.state_changed = true;
            }
        }else 
        {
            exe3.state_changed = false;
        }
    } else
    {
        if (exe3.state_changed)
            exe3.state_changed = false;
    }

    if (exe3.menu_active)
    {
        draw_textf(1, 1, "RNG1Value: %x",   rng1.value, 8);
        draw_textf(1, 2, "RNG1Idx:   %d",   rng1.index, 8);
        draw_textf(1, 3, "RNG1Delta: %d",   rng1.delta, 8);

        draw_textf(1, 4, "RNG2Value: %X",   rng2.value, 8);
        draw_textf(1, 5, "RNG2Idx:   %D",   rng2.index, 8);
        draw_textf(1, 6, "RNG2Delta: %D",   rng2.delta, 8);
    }

    // reset the RNG deltas at the end of every frame
    rng1.delta = 0;
    rng2.delta = 0;
}