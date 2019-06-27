/*
 * Copyright (c) 2016 Open-RnD Sp. z o.o.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/util.h>
#include <misc/printk.h>

//////////// SETUP BUTTONS ////////////
// BUTTON ZERO 
#ifndef SW0_GPIO_CONTROLLER
#ifdef SW0_GPIO_NAME
#define SW0_GPIO_CONTROLLER SW0_GPIO_NAME
#else
#error SW0_GPIO_NAME or SW0_GPIO_CONTROLLER needs to be set in board.h
#endif
#endif
#define PORT0	SW0_GPIO_CONTROLLER

#ifdef SW0_GPIO_PIN
#define PIN0     SW0_GPIO_PIN
#else
#error SW0_GPIO_PIN needs to be set in board.h
#endif

#ifdef SW0_GPIO_FLAGS
#define EDGE    (SW0_GPIO_FLAGS | GPIO_INT_EDGE)
#else
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

#ifndef SW0_GPIO_FLAGS
#ifdef SW0_GPIO_PIN_PUD
#define SW0_GPIO_FLAGS SW0_GPIO_PIN_PUD
#else
#define SW0_GPIO_FLAGS 0
#endif
#endif
#define PULL_UP SW0_GPIO_FLAGS

// BUTTON ONE 
#ifndef SW1_GPIO_CONTROLLER
#ifdef SW1_GPIO_NAME
#define SW1_GPIO_CONTROLLER SW1_GPIO_NAME
#else
#error SW1_GPIO_NAME or SW1_GPIO_CONTROLLER needs to be set in board.h
#endif
#endif
#define PORT1	SW1_GPIO_CONTROLLER

#ifdef SW1_GPIO_PIN
#define PIN1     SW1_GPIO_PIN
#else
#error SW1_GPIO_PIN needs to be set in board.h
#endif

#ifdef SW1_GPIO_FLAGS
#define EDGE    (SW1_GPIO_FLAGS | GPIO_INT_EDGE)
#else
/*
*/
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

/* change this to enable pull-up/pull-down */
#ifndef SW1_GPIO_FLAGS
#ifdef SW1_GPIO_PIN_PUD
#define SW1_GPIO_FLAGS SW1_GPIO_PIN_PUD
#else
#define SW1_GPIO_FLAGS 0
#endif
#endif
#define PULL_UP SW1_GPIO_FLAGS

// BUTTON TWO 
#ifndef SW2_GPIO_CONTROLLER
#ifdef SW2_GPIO_NAME
#define SW2_GPIO_CONTROLLER SW2_GPIO_NAME
#else
#error SW2_GPIO_NAME or SW2_GPIO_CONTROLLER needs to be set in board.h
#endif
#endif
#define PORT2	SW2_GPIO_CONTROLLER

/* change this to use another GPIO pin */
#ifdef SW2_GPIO_PIN
#define PIN2     SW2_GPIO_PIN
#else
#error SW2_GPIO_PIN needs to be set in board.h
#endif

/* change to use another GPIO pin interrupt config */
#ifdef SW2_GPIO_FLAGS
#define EDGE    (SW2_GPIO_FLAGS | GPIO_INT_EDGE)
#else
/*
*/
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

/* change this to enable pull-up/pull-down */
#ifndef SW2_GPIO_FLAGS
#ifdef SW2_GPIO_PIN_PUD
#define SW2_GPIO_FLAGS SW2_GPIO_PIN_PUD
#else
#define SW2_GPIO_FLAGS 0
#endif
#endif
#define PULL_UP SW2_GPIO_FLAGS

// BUTTON THREE
#ifndef SW3_GPIO_CONTROLLER
#ifdef SW3_GPIO_NAME
#define SW3_GPIO_CONTROLLER SW3_GPIO_NAME
#else
#error SW3_GPIO_NAME or SW3_GPIO_CONTROLLER needs to be set in board.h
#endif
#endif
#define PORT3	SW3_GPIO_CONTROLLER

#ifdef SW3_GPIO_PIN
#define PIN3     SW3_GPIO_PIN
#else
#error SW3_GPIO_PIN needs to be set in board.h
#endif

#ifdef SW3_GPIO_FLAGS
#define EDGE    (SW3_GPIO_FLAGS | GPIO_INT_EDGE)
#else
/*
*/
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

#ifndef SW3_GPIO_FLAGS
#ifdef SW3_GPIO_PIN_PUD
#define SW3_GPIO_FLAGS SW3_GPIO_PIN_PUD
#else
#define SW3_GPIO_FLAGS 0
#endif
#endif
#define PULL_UP SW3_GPIO_FLAGS

//////////// SETUP LEDS ////////////
#define LED_CONTROLLER_ZERO	    LED0_GPIO_CONTROLLER
#define LED_PIN_ZERO						LED0_GPIO_PIN
#define LED_CONTROLLER_ONE		  LED1_GPIO_CONTROLLER
#define LED_PIN_ONE						  LED1_GPIO_PIN
#define LED_CONTROLLER_TWO	    LED2_GPIO_CONTROLLER
#define LED_PIN_TWO					    LED2_GPIO_PIN
#define LED_CONTROLLER_THREE	  LED3_GPIO_CONTROLLER
#define LED_PIN_THREE					  LED3_GPIO_PIN

//////////// Sleep time ////////////
#define SLEEP_TIME	500

int led_zero  = 1;   // Led Inicialmente apagado
int led_one   = 1;   // Led Inicialmente apagado
int led_two   = 1;   // Led Inicialmente apagado
int led_three = 1;   // Led Inicialmente apagado

struct device *devZero;
struct device *devOne;
struct device *devTwo;
struct device *devThree;

void blinky_led(int n){
	switch(n){
		case 0:
			if(led_zero){
				// Acender
				gpio_pin_write(devZero, LED_PIN_ZERO, led_zero);
				led_zero = 0;
			}
			else{
				// Apagar
				gpio_pin_write(devZero, LED_PIN_ZERO, led_zero);
				led_zero = 1;
			}
			break;
		;
		case 1:
			if(led_one){
				// Acender
				gpio_pin_write(devOne, LED_PIN_ONE, led_one);
				led_one = 0;
			}
			else{
				// Apagar
				gpio_pin_write(devOne, LED_PIN_ONE, led_one);
				led_one = 1;
			}
			break;
		;
		case 2:
			if(led_two){
				// Acender
				gpio_pin_write(devTwo, LED_PIN_TWO, led_two);
				led_two = 0;
			}
			else{
				// Apagar
				gpio_pin_write(devTwo, LED_PIN_TWO, led_two);
				led_two = 1;
			}
			break;
		;
		case 3:
			if(led_three){
				// Acender
				gpio_pin_write(devThree, LED_PIN_THREE, led_three);
				led_three = 0;
			}
			else{
				// Apagar
				gpio_pin_write(devThree, LED_PIN_THREE, led_three);
				led_three = 1;
			}
			break;
		;
		default:
		;
	}
}

void button_zero_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(0);
}

void button_one_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(1);
}

void button_two_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(2);
}

void button_three_pressed(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins){
	printk("Button pressed at %d\n", k_cycle_get_32());
	blinky_led(3);
}

static struct gpio_callback gpio_cb_zero;
static struct gpio_callback gpio_cb_one;
static struct gpio_callback gpio_cb_two;
static struct gpio_callback gpio_cb_three;

void main(void)
{
	struct device *gpiob_zero;
	struct device *gpiob_one;
	struct device *gpiob_two;
	struct device *gpiob_three;

	/// Configuracao dos pinos dos leds
	// Led 0
	devZero = device_get_binding(LED_CONTROLLER_ZERO);
	gpio_pin_configure(devZero,   LED_PIN_ZERO,   GPIO_DIR_OUT);
	gpio_pin_write(devZero, LED_PIN_ZERO, led_zero);

	// Led 1
    devOne = device_get_binding(LED_CONTROLLER_ONE);
	gpio_pin_configure(devOne,   LED_PIN_ONE,   GPIO_DIR_OUT);
	gpio_pin_write(devOne, LED_PIN_ONE, led_one);

	// Led 2
	devTwo = device_get_binding(LED_CONTROLLER_TWO);
	gpio_pin_configure(devTwo,   LED_PIN_TWO,   GPIO_DIR_OUT);
	gpio_pin_write(devTwo, LED_PIN_TWO, led_two);

	// Led 3
	devThree = device_get_binding(LED_CONTROLLER_THREE);
	gpio_pin_configure(devThree,   LED_PIN_THREE,   GPIO_DIR_OUT);
	gpio_pin_write(devThree, LED_PIN_THREE, led_three);

	gpiob_zero = device_get_binding(PORT0);
	gpiob_one = device_get_binding(PORT1);
	gpiob_two = device_get_binding(PORT2);
	gpiob_three = device_get_binding(PORT3);

	/// Configuracao do callback dos botoes
	// Button 0
	gpio_pin_configure(gpiob_zero, PIN0,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE);
	gpio_init_callback(&gpio_cb_zero, button_zero_pressed, BIT(PIN0));
	gpio_add_callback(gpiob_zero, &gpio_cb_zero);
	gpio_pin_enable_callback(gpiob_zero, PIN0);

	// Button 1
	gpio_pin_configure(gpiob_one, PIN1,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE);
	gpio_init_callback(&gpio_cb_one, button_one_pressed, BIT(PIN1));
	gpio_add_callback(gpiob_one, &gpio_cb_one);
	gpio_pin_enable_callback(gpiob_one, PIN1);

	// Button 2
	gpio_pin_configure(gpiob_two, PIN2,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE);
	gpio_init_callback(&gpio_cb_two, button_two_pressed, BIT(PIN2));
	gpio_add_callback(gpiob_two, &gpio_cb_two);
	gpio_pin_enable_callback(gpiob_two, PIN2);

	// Button 3
	gpio_pin_configure(gpiob_three, PIN3,
			   GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE);
	gpio_init_callback(&gpio_cb_three, button_three_pressed, BIT(PIN3));
	gpio_add_callback(gpiob_three, &gpio_cb_three);
	gpio_pin_enable_callback(gpiob_three, PIN3);

	while (1) {
		u32_t val = 0U;

		gpio_pin_read(gpiob_zero,  PIN0, &val);
		gpio_pin_read(gpiob_one,   PIN1, &val);
		gpio_pin_read(gpiob_two,   PIN2, &val);
		gpio_pin_read(gpiob_three, PIN3, &val);

		k_sleep(SLEEP_TIME);
	}
}
