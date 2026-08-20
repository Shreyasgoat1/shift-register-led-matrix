#include "shift_register.h"
#include "driver/gpio.h"
#include "soc/gpio_struct.h"

#define DATA_PIN 23
#define CLOCK_PIN 18
#define LATCH_PIN 5

static inline void set_pin(int pin) { GPIO.out_w1ts = (1UL << pin); }
static inline void clear_pin(int pin) { GPIO.out_w1tc = (1UL << pin); }

static void shift_byte(uint8_t value)
{
    for (int bit = 7; bit >= 0; --bit) {
        if (value & (1U << bit)) set_pin(DATA_PIN);
        else clear_pin(DATA_PIN);
        set_pin(CLOCK_PIN);
        clear_pin(CLOCK_PIN);
    }
}

void shift_register_init(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = (1ULL << DATA_PIN) | (1ULL << CLOCK_PIN) | (1ULL << LATCH_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&cfg);
    clear_pin(DATA_PIN);
    clear_pin(CLOCK_PIN);
    clear_pin(LATCH_PIN);
}

void shift_register_write16(uint8_t first, uint8_t second)
{
    shift_byte(first);
    shift_byte(second);
    set_pin(LATCH_PIN);
    clear_pin(LATCH_PIN);
}
