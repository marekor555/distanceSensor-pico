#include <stdio.h>

#include "pico/stdio_usb.h"
#include "pico/stdlib.h"

#define TRIQ 17  // trigger of signal
#define ECHO 16  // receiver of signal
#define BTN 18   // button

int time_us = 0;  // time in micro seconds

int main() {
    stdio_init_all();
    stdio_usb_init();

    gpio_init(TRIQ);  // TRIQ is output
    gpio_set_dir(TRIQ, GPIO_OUT);

    gpio_init(ECHO);  // ECHO is input with internal pulldown resistor
    gpio_set_dir(ECHO, GPIO_IN);
    gpio_pull_down(ECHO);

    gpio_init(BTN);  // BTN is input with internal pullup resistor
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_up(BTN);

    while (true) {
        if (!gpio_get(BTN)) {   // if signal from btn is false, button has been pressed
            gpio_put(TRIQ, 1);  // fire TRIQ for 10us
            sleep_us(10);
            gpio_put(TRIQ, 0);

            while (!gpio_get(ECHO)) tight_loop_contents();  // wait for signal to appear
            int start_time = time_us_64();
            while (gpio_get(ECHO)) tight_loop_contents();         // wait for signal to disappear
            time_us = time_us_64() - start_time;                  // time between signal appearance and disappearance
        	/*
				0.034cm/us is the speed of signal in air
				it went both directions, so time should be halved
				equation is s=t/V
			*/
            printf("Distance: %dcm\n", time_us / 2 * 34 / 1000);
        }
        sleep_ms(200); // don't spam measurements
    }
}
