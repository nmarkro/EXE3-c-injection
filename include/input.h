#ifndef INPUT_H
#define INPUT_H

#define input_pad_addr      0x04000130
#define input_pad           *(short*)input_pad_addr

#define INPUT_REPEAT_DELAY  8

#define KEY_A               0
#define KEY_B		        1
#define KEY_SELECT	        2
#define KEY_START	        3
#define KEY_RIGHT	        4
#define KEY_LEFT	        5
#define KEY_UP		        6
#define KEY_DOWN	        7
#define KEY_R		        8
#define KEY_L		        9

void input_update(void);
short key_get_bitmask(int index);
_Bool input_pressed(int index);
_Bool input_held(int index);

#endif