#include <zephyr.h>
#include <device.h>
#include <gpio.h>

#include "input.h"
#include "output.h"

/* Leds */
#define LED0_PORT LED0_GPIO_CONTROLLER
#define LED1_PORT LED1_GPIO_CONTROLLER
#define LED2_PORT LED2_GPIO_CONTROLLER
#define LED3_PORT LED3_GPIO_CONTROLLER

#define LED0_PIN LED0_GPIO_PIN
#define LED1_PIN LED1_GPIO_PIN
#define LED2_PIN LED2_GPIO_PIN
#define LED3_PIN LED3_GPIO_PIN

/* Buttons */
#define SW0_PORT SW0_GPIO_CONTROLLER
#define SW1_PORT SW1_GPIO_CONTROLLER
#define SW2_PORT SW2_GPIO_CONTROLLER
#define SW3_PORT SW3_GPIO_CONTROLLER

#define SW0_PIN SW0_GPIO_PIN
#define SW1_PIN SW1_GPIO_PIN
#define SW2_PIN SW2_GPIO_PIN
#define SW3_PIN SW3_GPIO_PIN

/* GPIO interrupt flags */
#define INTERRUPT GPIO_INT
#define FALLING_EDGE (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#define DEBOUNCE GPIO_INT_DEBOUNCE
#define PULL_UP GPIO_PUD_PULL_UP

#define SW_GPIO_FLAGS (INTERRUPT | FALLING_EDGE | DEBOUNCE | PULL_UP)

/* Sleep time */
#define SLEEP_TIME 500

output_t *led0, *led1, *led2, *led3;
//struct device *led0, *led1, *led2, *led3;

void button_pressed(struct device *gpiob, struct gpio_callback *cb,
                    u32_t pins){
  printk("Button 1 pressed at %d\n", k_cycle_get_32());
}

void led(output_t *led, u32_t pin, char *port){
    output_open(led, port);
    output_configure(led, pin, GPIO_DIR_OUT);  
}

void button(input_t *button, u32_t pin, char *port){
    input_open(button, port);
    input_configure(button, pin, SW_GPIO_FLAGS, button_pressed);
}

void main(void) {
    
    //struct device *sw0, *sw1, *sw2, *sw3;
    input_t *btn0, *btn1, *btn2, *btn3;

    // Creating Leds and Buttons
    led(led0, LED0_PIN, LED0_PORT);
    led(led1, LED1_PIN, LED1_PORT);
    led(led2, LED2_PIN, LED2_PORT);
    led(led3, LED3_PIN, LED3_PORT);

    button(btn0, SW0_PIN, SW0_PORT);
    button(btn1, SW1_PIN, SW1_PORT);
    button(btn2, SW2_PIN, SW2_PORT);
    button(btn3, SW3_PIN, SW3_PORT);

    /* Main loop */
    while(1) {
        u32_t val = 0U;

        input_read(btn0, &val);
        input_read(btn1, &val);
        input_read(btn2, &val);
        input_read(btn3, &val);

        k_sleep(SLEEP_TIME);
    }
}