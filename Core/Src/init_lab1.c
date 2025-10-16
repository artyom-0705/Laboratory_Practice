#include "init_lab1.h"



void GPIO_Init_my_macros(void)
{
    SET_BIT_my(RCC_AHB1ENR_my, RCC_AHB1ENR_GPIODEN_my);                          // Включаем тактирование D пинов, регистр RCC_AHB1ENR
    SET_BIT_my(GPIOD_MODER_my, GPIOD_MODE_PIN0_OUT);                             // Настройка работы 0-го пина GPIOD в режиме вывода сигнала (Output mode), регистр GPIOx_MODER
    SET_BIT_my(GPIOD_OTYPER_my, GPIOD_OTYPER_PIN0_PP);                           // Настройка на PushPull работу 0-го пина GPIOD (Output Push-Pull), регистр GPIOx_OTYPER
    SET_BIT_my(GPIOD_OSPEEDR_my, GPIOD_OSPEED_PIN0_MID);                         // Настройка скорости работы 0-го пина GPIOD на среднюю, регистр GPIOx_OSPEEDR
    SET_BIT_my(GPIOD_PUPDR_my, GPIOD_PUPDR_PIN0_NOPUPDR);                        // Отключение PU/PD резисторов для 0-го пина GPIOD, регистр GPIOx_PUPDR 
    SET_BIT_my(GPIOD_BSRR_my, GPIOD_BSRR_PIN0_RESET);                            // Установление на пине PD0 0, регистр GPIOx_BSRR
}

void GPIO_Init_accessing_memory(void)
{
    *(uint32_t*)(0x40023800UL + 0x30UL) |= 0x00000010UL;                         // Включение тактирования для PE, регистр RCC (стр. 65) и регистр RCC_AHB1ENR (cтр. 182)
    *(uint32_t*)(0x40021000UL + 0x00UL) |= 0x00004000UL;                         // Настройка работы 7-го пина GPIOE в режиме вывода сигнала (Output mode), регистр GPIOx_MODER
    *(uint32_t*)(0x40021000UL + 0x04UL) |= 0x00000000UL;                         // Настройка на PushPull работу 7-го пина GPIOE (Output Push-Pull), регистр GPIOx_OTYPER
    *(uint32_t*)(0x40021000UL + 0x08UL) |= 0x00004000UL;                         // Настройка скорости работы 7-го пина GPIOE на среднюю, регистр GPIOx_OSPEEDR
    *(uint32_t*)(0x40021000UL + 0x0CUL) |= 0x00000000UL;                         // Отключение PU/PD резисторов для 7-го пина GPIOE, регистр GPIOx_PUPDR 
    *(uint32_t*)(0x40021000UL + 0x18UL) |= 0x00800000UL;                         // Установление на пине PE7 0, регистр GPIOx_BSRR
}

void GPIO_Init_CMSIS(void){
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);            // Включение тактирования GPIOB и GPIOC             
    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE14_0);                                  // Настройка пина PB14 на выход, регистр GPIOx_MODER
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_14);                                 // Установление PB14 в режим pull-push, регистр OTYPER
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR14_0);                          // Устанавливаем скорость бита PB14 (средняя), регистр OSPEEDR
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPD14_0);                                // Отключаем подтягивающий резистор PB14, регистр PUPDR
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);                                        // Установление на пине PB14 0, регистр GPIOx_BSRR
}