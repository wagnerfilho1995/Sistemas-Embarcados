/**
 * @file   output.h
 * @author Lucas Peixoto <lucaspeixotoac@gmail.com>
 * @date   Mon Jul  8 08:04:22 2019
 * 
 * @brief  Header file para o driver output.
 * 
 * 
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <device.h>
#include <gpio.h>


struct output {
    struct device *device;
    char *dev_label;
    u32_t pin;
    u8_t state;
};

typedef struct output output_t;

/** 
 * Essa função tem como objetivo iniciar o driver output,
 * ou seja, iniciar o device. 
 * @param out 
 *
 * @return 
 */
int output_open(output_t *out, char *dev_label);

/** 
 * Essa função tem como objetivo configurar o pino de saída
 * de acordo com suas flags.
 * @param out 
 * @param pin 
 * @param flags 
 *
 * @return 
 */
int output_configure(output_t *out, u32_t pin, int flags);

/** 
 * Essa função tem como objetivo setar o estado do pino de
 * saída para algum valor.
 * @param out 
 * @param value 
 *
 * @return 
 */
int output_set(output_t *out, u8_t value);

/** 
 * Essa função tem como objetivo inverter o estado do pino de
 * saída.
 * @param out 
 *
 * @return 
 */
int output_pressed(output_t *out);

#endif
