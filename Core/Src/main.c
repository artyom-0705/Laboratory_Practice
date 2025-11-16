#include "../Inc/init_lab2.h"
#include "Lab2.h"

uint8_t led_en = 0;                 // Переменная хранящая сколько светодиодов включено
uint8_t num_led_blink = 0;          // Переменная хранящая номер светодиода, частота которого настраивается
uint32_t GlobalTickCount = 0;       // Переменная таймер
uint8_t blink[6][2] = {0};          // Матрица для хранения номера диапозона частоты и номера самой частоты мигания лампочек



int main(void)
{
    RCC_init_clocking();
    GPIO_Init_Led_and_button();
    ITR_init();
    SysTick_Init();

    while (1)
    {
       blinking_func(&led_en, blink, &GlobalTickCount);
    }
}
