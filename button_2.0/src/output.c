#include "output.h"
#include <gpio.h>

/** 
 * Essa função tem como objetivo iniciar o driver output,
 * ou seja, iniciar o device. 
 * @param out 
 *
 * @return 
 */

int output_open(output_t *out, char *dev_label) {
    out->dev_label = dev_label;
    out->device = device_get_binding(out->dev_label);
    if(!out->device){
        printk("error\n");
        return 1; // Fazer uma função de tratamento do erro
    }
    return 0;
}

/** 
 * Essa função tem como objetivo configurar o pino de saída
 * de acordo com suas flags.
 * @param out 
 * @param pin 
 * @param flags 
 *
 * @return 
 */
int output_configure(output_t *out, u32_t pin, int flags) {
    out->pin = pin;
    gpio_pin_configure(out->device, out->pin, flags);
    return 0;
}

/** 
 * Essa função tem como objetivo setar o estado do pino de
 * saída para algum valor.
 * @param out 
 * @param value 
 *
 * @return 
 */
int output_set(output_t *out, u8_t value) {
    out->state = value;
    gpio_pin_write(out->device, out->pin, out->state);
    return 0;
}