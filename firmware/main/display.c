#include "display.h"
#include "shift_register.h"

uint8_t framebuffer[8] = {0};

void display_init(void)
{
    for (int i = 0; i < 8; ++i) framebuffer[i] = 0;
}

void display_refresh_row(uint8_t row)
{
    if (row > 7) row = 0;

    /* Common-anode example: rows are active LOW through P-MOSFET gates.
       Columns are active HIGH into ULN2803 inputs. Adjust polarity for the
       exact matrix/driver wiring used on the fabricated PCB. */
    uint8_t rows_off = 0xFF;
    uint8_t columns_off = 0x00;
    shift_register_write16(rows_off, columns_off);

    uint8_t row_select = (uint8_t)~(1U << row);
    uint8_t columns = framebuffer[row];
    shift_register_write16(row_select, columns);
}

void display_scroll_step(uint8_t font_column)
{
    for (int row = 0; row < 7; ++row) {
        framebuffer[row] <<= 1;
        if (font_column & (1U << row)) framebuffer[row] |= 1U;
    }
    framebuffer[7] = 0;
}
