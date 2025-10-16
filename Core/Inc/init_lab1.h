#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"

#define RCC_AHB1ENR_my             (*(uint32_t*)(0x40023800UL + 0x30UL))       // Включение тактирования, регистр RCC (стр. 65) и регистр RCC_AHB1ENR (cтр. 182)
#define GPIOD_MODER_my             (*(uint32_t*)(0x40020C00UL + 0x00UL))       // Установление выхода для порта, регистр GPIOx_MODER (RM стр 65 GPIOD и стр 284 GPIOx_MODER)
#define GPIOD_OTYPER_my            (*(uint32_t*)(0x40020C00UL + 0x04UL))       // Настройка типа ввода вывода (push-pull), регистр GPIOx_OTYPER (RM стр 65 GPIOD и стр 284 GPIOx_OTYPER)
#define GPIOD_OSPEEDR_my           (*(uint32_t*)(0x40020C00UL + 0x08UL))       // Настройка скорости ввода вывода, регистр GPIOx_OSPEEDR (RM стр 65 GPIOD и стр 285 GPIOx_OSPEEDR)
#define GPIOD_PUPDR_my             (*(uint32_t*)(0x40020C00UL + 0x0CUL))       // Настройка типа ввода/вывода, регистр GPIOx_PUPDR (RM стр 65 GPIOD и стр 285 GPIOx_PUPDR)
#define GPIOD_BSRR_my              (*(uint32_t*)(0x40020C00UL + 0x18UL))       // Установление на выход 1 или сброс, регистр GPIOx_BSRR (RM стр 65 GPIOD и стр 287 GPIOx_BSRR)          

#define RCC_AHB1ENR_GPIODEN_my     0x00000008UL                                 // Включение тактирования для PD, регистр RCC_AHB1ENR
#define GPIOD_MODE_PIN0_OUT        0x00000001UL                                 // Настройка на выход пин PD0, регистр GPIOx_MODER
#define GPIOD_OTYPER_PIN0_PP       0x00000000UL                                 // Настройка push-pull на пине PD0, регистр GPIOx_OTYPER
#define GPIOD_OSPEED_PIN0_MID      0x00000001UL                                 // Настройка скорости вывода (средняя) на пине PD0, регистр GPIOx_OSPEEDR
#define GPIOD_PUPDR_PIN0_NOPUPDR   0x00000000UL                                 // Настройка подтягивающего резистра (отключить) на пине PD0, регистр GPIOx_PUPDR
#define GPIOD_BSRR_PIN0_SET        0x00000001UL                                 // Установление 1 на выходе пина PD0, регистр GPIOx_BSRR
#define GPIOD_BSRR_PIN0_RESET      0x00010000UL                                 // Установление 0 на выходе пина PD0, регистр GPIOx_BSRR

#define SET_BIT_my(REG, BIT)       (REG |= BIT)                                 // Макрос записи бита в регистр    
#define READ_BIT_my(REG, BIT)      (REG & BIT)                                  // Макрос чтения бита из регистра

void GPIO_Init_my_macros(void);                                                 // Прототип функции инициализации лампочки через собственные макросы (led 1)
void GPIO_Init_accessing_memory(void);                                          // Прототип функции инициализации лампочки через прямое обращение к памяти (led 2)
void GPIO_Init_CMSIS(void);                                                     // Прототип функции инициализации лампочки через CMSIS (led 3)
