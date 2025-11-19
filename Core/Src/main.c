#include "../Inc/init_lab2.h"

uint8_t led_en = 0;                                         // Переменная хранящая сколько светодиодов включено
uint8_t num_led_blink = 0;                                  // Переменная хранящая номер светодиода, частота которого настраивается
uint32_t GlobalTickCount = 0;                               // Переменная таймер
uint8_t blink[6][2] = {0};                                  // Матрица для хранения номера диапазона частоты и номера самой частоты мигания лампочек
// uint8_t blink_1_1;                                          // Переменные для вывода в MCUViewer массива данных
// uint8_t blink_1_2;
// uint8_t blink_2_1;
// uint8_t blink_2_2;
// uint8_t blink_3_1;
// uint8_t blink_3_2;
// uint8_t blink_4_1;
// uint8_t blink_4_2;
// uint8_t blink_5_1;
// uint8_t blink_5_2;
// uint8_t blink_6_1;
// uint8_t blink_6_2;

int main(void)
{
    RCC_init_clocking();                                    // Настройка тактирования микроконтроллера
    ITR_init();                                             // Настройка прерывания по кнопкам (PC12 и PC13)
    TIM1_PWM_PE14();
    TIM3_Init();
    while (1)
    {
        
    }
}
