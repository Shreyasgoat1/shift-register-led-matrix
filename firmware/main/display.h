#pragma once
#include <stdint.h>
extern uint8_t framebuffer[8];
void display_init(void);
void display_refresh_row(uint8_t row);
void display_scroll_step(uint8_t font_column);
