#include <stdint.h>

// Definição dos endereços base dos periféricos do RP2040
#define SIO_BASE 0xD0000000
#define SIO_GPIO_OUT_SET (*(volatile uint32_t *)(SIO_BASE + 0x010))
#define SIO_GPIO_OE_SET  (*(volatile uint32_t *)(SIO_BASE + 0x024))

// Função de delay rudimentar por ciclo de clock
void delay(volatile uint32_t count) {
    while (count--) {
        __asm__("nop"); // Instrução nula para gastar ciclo de clock
    }
}

// Ponto de entrada direto chamado pelo Reset_Handler
int main(void) {
    uint32_t pin = 25; // Pino 25 é o LED onboard do Raspberry Pi Pico

    // 1. Configura o pino 25 como saída (Output Enable)
    SIO_GPIO_OE_SET = (1 << pin);

    while (1) {
        // 2. Liga o LED
        SIO_GPIO_OUT_SET = (1 << pin);
        delay(1000000);

        // 3. Desliga o LED (escrevendo no registrador de clear)
        (*(volatile uint32_t *)(SIO_BASE + 0x018)) = (1 << pin);
        delay(1000000);
    }

    return 0;
}