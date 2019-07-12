#include "input.h"

/** 
 * Essa função tem como objetivo iniciar o device do driver
 * de entrada.
 * @param in 
 *
 * @return 
 */
int input_open(input_t *in, char *dev_label) {
    in->dev_label = dev_label;
    in->device = device_get_binding(in->dev_label);
    return 0;
}

/** 
 * Essa função tem como objetivo configurar o pino de entrada.
 *
 * @param in 
 * @param pin 
 * @param flags 
 * @param cb 
 *
 * @return 
 */
int input_configure(input_t *in, u32_t pin, int flags, gpio_callback_handler_t cb) {
    in->pin = pin;
    gpio_pin_configure(in->device, in->pin, flags);

    gpio_init_callback(&in->gpio_callback, cb, in->gpio_callback.pin_mask | BIT(in->pin));
    gpio_add_callback(in->device, &in->gpio_callback);
    gpio_pin_enable_callback(in->device, in->pin);

    return 0;
}

/** 
 * Essa função tem como objetivo fazer uma leitura do pino
 * de entrada.
 * @param in 
 * @param state 
 *
 * @return 
 */
int input_read(input_t *in, u32_t *state) {
    gpio_pin_read(in->device, in->pin, state);
    return 0;
}