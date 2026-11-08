/*
 * ============================================================================
 *                    PASSO A PASSO (STEP-BY-STEP) DO CÓDIGO
 * ============================================================================
 * 
 * STEP 1: Inclusão de Headers Padrão
 *    - <stdint.h>: Fornece o tipo `uint32_t` (inteiro sem sinal de exatamente 32 bits / 4 bytes).
 *      Isso garante que o registrador tenha o tamanho correto em qualquer arquitetura (ex: ARM 32-bit).
 *    - <stdio.h>: Disponibiliza a função `printf` para exibir dados formatados no terminal.
 *
 * STEP 2: Definição do Endereço de Memória (Macro)
 *    - `#define FAKE_LED_REG_ADDR 0x40000000`: O pré-processador substitui o texto
 *      `FAKE_LED_REG_ADDR` pelo valor hexadecimal `0x40000000` antes da compilação.
 *    - Esse valor representa o **endereço físico de hardware** onde a CPU acessa o registrador do pino do LED.
 *
 * STEP 3: Mapeamento do Registrador com Ponteiro `volatile`
 *    - `(volatile uint32_t *)FAKE_LED_REG_ADDR`: Faz o cast (conversão explícita) do número
 *      hexadecimal `0x40000000` para um **ponteiro para uint32_t**.
 *    - `volatile`: **Diz ao compilador para NÃO otimizar leituras/escritas nessa memória.**
 *      Sem `volatile`, o compilador acharia que a escrita de `1` seguida da escrita de `0` seria "código inútil"
 *      e removeria a primeira escrita. O `volatile` obriga a CPU a emitir instruções reais de barramento (escrita em memória).
 *    - `p_led_reg`: Guarda exatamente o endereço de memória `0x40000000`.
 *
 * STEP 4: Impressão do Endereço Mapeado
 *    - `printf("Endereço... %p", (void*)p_led_reg)`: O especificador `%p` exibe o endereço armazenado no ponteiro.
 *
 * STEP 5: Operação de Escrita de Hardware (Ligar o LED)
 *    - `*p_led_reg = 1;`: O operador `*` (desreferência) diz: "vá até o endereço armazenado em `p_led_reg` (0x40000000)
 *      e escreva o valor numérico `1` nos seus 32 bits de memória".
 *    - No hardware real, isso altera o nível lógico do pino GPIO para HIGH (3.3V), acendendo o LED físico.
 *
 * STEP 6: Operação de Leitura e Escrita de Hardware (Desligar o LED)
 *    - `printf(... *p_led_reg)`: O operador `*` lê o valor atual presente no endereço `0x40000000`.
 *    - `*p_led_reg = 0;`: Escreve o valor numérico `0` no mesmo endereço de memória.
 *    - No hardware real, isso altera o nível lógico do pino GPIO para LOW (0V), apagando o LED.
 * ============================================================================
 */

#include <stdint.h>
#include <stdio.h>

// Simulador de registrador em memória RAM para testes seguros no PC
static uint32_t simulated_hardware_register = 0;

int main(void) {
    // Apontando para o registrador simulado
    volatile uint32_t *p_led_reg = &simulated_hardware_register;

    // --- PRINT 1: Endereço de memória mapeado ---
    printf("[PRINT 1] Endereço do registrador do LED: %p\n", (void*)p_led_reg);

    // 1. Ligando o LED (escreve 1)
    *p_led_reg = 1;
    
    // --- PRINT 2: Estado após ligar ---
    printf("[PRINT 2] Estado do registrador (LIGADO): %u\n", *p_led_reg);

    // 2. Desligando o LED (escreve 0)
    *p_led_reg = 0;
    
    // --- PRINT 3: Estado após desligar ---
    printf("[PRINT 3] Estado do registrador (DESLIGADO): %u\n", *p_led_reg);

    return 0;
}