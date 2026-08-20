#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "shift_register.h"
#include "display.h"

static volatile uint8_t current_row = 0;

static void refresh_timer_cb(void *arg)
{
    display_refresh_row(current_row);
    current_row = (current_row + 1) & 7;
}

void app_main(void)
{
    shift_register_init();
    display_init();

    /* Example test pattern: border */
    framebuffer[0] = 0xFF;
    framebuffer[7] = 0xFF;
    for (int r = 1; r < 7; ++r) framebuffer[r] = 0x81;

    const esp_timer_create_args_t timer_args = {
        .callback = &refresh_timer_cb,
        .name = "matrix_refresh"
    };
    esp_timer_handle_t timer;
    esp_timer_create(&timer_args, &timer);

    /* 8 rows x 1 ms = 125 Hz frame refresh. */
    esp_timer_start_periodic(timer, 1000);

    while (1) {
        /* Animation/text updates can run here at a much slower rate. */
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
