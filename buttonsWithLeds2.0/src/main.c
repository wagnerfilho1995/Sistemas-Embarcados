#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <misc/printk.h>
#include <shell/shell.h>

#include "setup.h"
#include "input.h"
#include "output.h"

// Structs globais de saida do tipo output_t
output_t led_zero, led_one, led_two, led_three; // Leds

/* Comando Shell press -> parametros: (Struct do tipo shell, argc é o numero de argumentos do comando, argv é um array de tring
   contendo os argumentos em si)*/
static int cmd_run_skol(const struct shell *shell, size_t argc, char **argv) {
        
        // 0 - Led aceso
        // 1 - Led apagado
        int state_led = 1;
        int loops = 2;

        // Reproduzir a ação 2 vezes 
        for(int i = 0; i < loops; i++){
            state_led = 1;
            // Inicialmente todos os Leds apagados
            output_set(&led_zero, state_led);
            output_set(&led_one, state_led);
            output_set(&led_two, state_led);
            output_set(&led_three, state_led);

            state_led = 0;
            // Acender no sentido horario
            output_set(&led_zero, state_led);
            k_sleep(SLEEP_TIME);
            output_set(&led_one, state_led);
            k_sleep(SLEEP_TIME);
            output_set(&led_three, state_led);
            k_sleep(SLEEP_TIME);
            output_set(&led_two, state_led);
            k_sleep(SLEEP_TIME);

            // Apague voltando "Backtrack"
            state_led = 1;
            output_set(&led_two, state_led);
            k_sleep(SLEEP_TIME-200);
            output_set(&led_three, state_led);
            k_sleep(SLEEP_TIME)-200;
            output_set(&led_one, state_led);
            k_sleep(SLEEP_TIME-200);
            output_set(&led_zero, state_led);
            k_sleep(SLEEP_TIME-200);
        }
        // Printando no terminal do shell que a ação foi executada
        shell_print(shell, "Os leds que descem redondo!");
        return 0;
}

/* Comando Shell press -> parametros: (Struct do tipo shell, argc é o numero de argumentos do comando, argv é um array de tring
   contendo os argumentos em si)*/
static int cmd_run_press(const struct shell *shell, size_t argc, char **argv) {

        // Acessar: Array de Strings -> String na posição argc+1
        char led = *(*(argv+1));

        switch (led) {
        case '0':
            output_pressed(&led_zero);
            break;
        case '1':
            output_pressed(&led_one);
            break;
        case '2':
            output_pressed(&led_two);
            break;
        case '3':
            output_pressed(&led_three);
            break;
        default:
            shell_print(shell, "Botao invalido");
            return -1;
        }
        // Printando no terminal do shell que a ação foi executada
        shell_print(shell, "Led %c pressionado.", led);
        return 0;
}

// Colocando os comandos criados como subcomandos do run
SHELL_STATIC_SUBCMD_SET_CREATE(sub_run,
    SHELL_CMD_ARG(skol, NULL, "Comando Skol.", cmd_run_skol, 1, NULL),
    SHELL_CMD_ARG(press, NULL, "Comando Press.", cmd_run_press, 2, NULL),
    SHELL_SUBCMD_SET_END
);

// Setando o comando run no root
SHELL_CMD_REGISTER(run, &sub_run, "Comandos Run.", NULL);

// Função para botão pressionado
void button_pressed(struct device *btn, struct gpio_callback *cb, u32_t pins){
    if(pins & BIT(SW0_PIN)) {
        output_pressed(&led_zero);
        printk("Botao 0 pressionado em %d ciclos\n", k_cycle_get_32());
    } else if(pins & BIT(SW1_PIN)) {
        output_pressed(&led_one);
        printk("Botao 1 pressionado em %d ciclos\n", k_cycle_get_32());
    } else if(pins & BIT(SW2_PIN)) {
        output_pressed(&led_two);
        printk("Botao 2 pressionado em %d ciclos\n", k_cycle_get_32());
    } else {
        output_pressed(&led_three);
        printk("Botao 3 pressionado em %d ciclos\n", k_cycle_get_32());
    }
}

// Inicializador Led
void led(output_t *led, u32_t pin, char *port, u8_t state){
    int e = output_open(led, port);
    if(e){
        printk("Alerta: Led para o PIN%d não inicializado.\n", pin);
        return;
    }
    output_configure(led, pin, GPIO_DIR_OUT);
    output_set(led, state);
    printk("Led em PIN%d inicializado.\n", pin);
}

// Inicializador Botão
void button(input_t *button, u32_t pin, char *port){
    int e = input_open(button, port);
    if(e){
        printk("Alerta: Botao para o PIN%d não inicializado.\n", pin);
        return;
    }
    input_configure(button, pin, GPIO_DIR_IN | SW_GPIO_FLAGS, button_pressed);
    printk("Botao em PIN%d inicializado.\n", pin);
}

void main(void) {

    // Structs do tipo input_t representando cada botão
    input_t btn0, btn1, btn2, btn3;

    // Estado inicial dos leds
    u8_t state = 1; // Inicialmente apagados

    // Criando e definindo Leds
    led(&led_zero, led_zero_PIN, led_zero_PORT, state);
    led(&led_one, led_one_PIN, led_one_PORT, state);
    led(&led_two, led_two_PIN, led_two_PORT, state);
    led(&led_three, led_three_PIN, led_three_PORT, state);

    printk("\n");

    // Criando e definindo botoes
    button(&btn0, SW0_PIN, SW0_PORT);
    button(&btn1, SW1_PIN, SW1_PORT);
    button(&btn2, SW2_PIN, SW2_PORT);
    button(&btn3, SW3_PIN, SW3_PORT);

    printk("Aguardando comandos ...\n");
    while(1) {
        u32_t val = 0U;

        input_read(&btn0, &val);
        input_read(&btn1, &val);
        input_read(&btn2, &val);
        input_read(&btn3, &val);

        k_sleep(SLEEP_TIME);
    }
}