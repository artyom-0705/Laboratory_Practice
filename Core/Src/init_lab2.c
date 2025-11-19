#include "init_lab2.h"

void GPIO_Init_Led_and_button(void)
{

    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN); // Включение тактирования GPIOB и GPIOC

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODE8_0);              // Настройка пина PB8 на выход, регистр GPIOx_MODER
    CLEAR_BIT(GPIOB->OTYPER, GPIO_OTYPER_OT_8);             // Установление PB8 в режим pull-push, регистр OTYPER
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR8_0);      // Устанавливаем скорость бита PB8 (средняя), регистр OSPEEDR
    CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPD8_0);            // Отключаем подтягивающий резистор PB8, регистр PUPDR
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR8);                    // Установление на пине PB8 0, регистр GPIOx_BSRR
}

void RCC_init_clocking(void) // Настройка тактирования
{
    /*----------------Произведем очистку регистров RCC, с целью не попадания лишней информации----------------*/
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80U);                  // Настройка внутренней высокоскоростной синхронизации тактовых импульсов, для возможности корректировки частоты (регистр RCC_CR)
    CLEAR_REG(RCC->CFGR);                                        // Очистка регистра RCC_CFGR
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);          // Проверка очистки RCC_CFGR, если очистка была, то продолжаем, если нет то цикл бесконечно длится
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);                            // Очистка бита PLLON (регистр RCC_CR)
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);           // Проверка был ли очищен PLLON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);             // Очистка бита CSSON и HSEON (регистр RCC_CR)
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);           // Проверка был ли очищен HSERDY
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                           // Очистка бита HSEBYP (регистр RCC_CR)

    /*---------------------------------------Настройка регистра RCC_CR----------------------------------------*/
    SET_BIT(RCC->CR, RCC_CR_HSEON);                              // Запускаем внешний кварцевый резонатор (регистр RCC_CR, бит HSEON)
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);           // Ждём пока запустится внешний резонатор
    SET_BIT(RCC->CR, RCC_CR_CSSON);                              // Запускаем систему безопасности тактирования (регистр RCC_CR, бит CSSON)
    SET_BIT(RCC->CR, RCC_CR_HSEBYP);                             // Использование внешнего резонатора (регистр RCC_CR, бит HSEBYP)
    CLEAR_BIT(RCC->CR, RCC_CR_HSION);                            // Выключаем внутренний RC-генератор (HSI), так как используем HSE

    /*----------------------------------------Настройка регистров PLL-----------------------------------------*/
    CLEAR_REG(RCC->PLLCFGR);                                                                                  // Предварительная очистка (регистр PLLCFGR)
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);                                                            // В качестве источника тактирования для PLL выбираем HSE (регистр PLLCFGR) (выдает частоту 8МГц)                                         // Включение тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_2);                                                                // Установим делитель /M на 4 (регистр PLLCFGR) (теперь частота шины 2 МГц)
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_8); // Настройка множителя xN на 360 (регистр PLLCFGR) (теперь частота 720 МГц)
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                                                                // Установим делитель /P на 4 (регистр PLLCFGR) (теперь частота шины 180 МГц)
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_3); // Делитель для USB /Q установим 15 (регистр PLLCFGR) (частота на шине USB 48 МГц)

    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                         // Источник системного тактирования -> выход PLL
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                    // Делитель AHB1 устанавливаем 1
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV4);                     // Делитель APB1 устанавливаем 4 (45 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV2);                     // Делитель APB2 устанавливаем 2 (90 МГц)
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                         // Выход  MCO2 для Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_1 | RCC_CFGR_MCO2PRE_2); // Делитель для MCO2 устанавливаем 4

    /*--------------------------------Устанавливаем задержку для памяти (Flash)-----------------------------------*/
    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_5WS);                  // Задержка памяти FLASH = 5 тактов (для 180 МГц)

    SET_BIT(RCC->CR, RCC_CR_PLLON);                              // Включение PLL
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);           // Ожидание включения PLL
}

void ITR_init(void)                                                                             // Настройка прерывания кнопки
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);                                                // Включение тактирования SYSCFG - необходим для настройки EXTI

    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC);         // Настройка EXTI13 на PC13

    SET_BIT(EXTI->IMR, EXTI_IMR_MR13);                                          // Разрешает прерывания по линиям PC13
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);                                       // Настраиваем триггер по нарастанию фронта для кнопок (переход от 0 к 1)
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13);                                       // Настраиваем триггер по спадающему фронту для кнопок (переход от 1 к 0)

    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));    // Устанавливаем приоритет прерывания (высший)
    NVIC_EnableIRQ(EXTI15_10_IRQn);                                                             // Включаем прерывания в контроллере NVIC (теперь процессор будет их обрабатывать)
}

void TIM1_PWM_PE14(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);

    // Настройка PE14 как альтернативной функции (TIM1_CH4)
    MODIFY_REG(GPIOE->MODER, GPIO_MODER_MODER14_Msk, GPIO_MODER_MODER14_1);
    MODIFY_REG(GPIOE->AFR[1], GPIO_AFRH_AFSEL14_Msk, 1 << GPIO_AFRH_AFSEL14_Pos);
    
    // Остановка таймера
    CLEAR_BIT(TIM1->CR1, TIM_CR1_CEN);
    
    // Настройка для 1 кГц при 180 MHz
    TIM1->PSC = 179;       // Делитель 180
    TIM1->ARR = 999;       // Период 1000
    TIM1->CCR4 = 1000;      // 50% скважность
    
    // Настройка канала 4 (в CCMR2)
    TIM1->CCMR2 |= TIM_CCMR2_OC4PE;
    TIM1->CCMR2 &= ~TIM_CCMR2_OC4M_Msk;
    TIM1->CCMR2 |= (6 << TIM_CCMR2_OC4M_Pos);
    
    // Включение канала 4
    SET_BIT(TIM1->CCER, TIM_CCER_CC4E);
    
    // Включение основного выхода
    SET_BIT(TIM1->BDTR, TIM_BDTR_MOE);
    
    // Запуск таймера
    SET_BIT(TIM1->CR1, TIM_CR1_CEN);
}

void TIM3_Init(void)
{
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);
    CLEAR_BIT(TIM3->CR1, TIM_CR1_CEN);

    // Правильный расчет для 50 мс:
    // 90 MHz / (44999 + 1) = 2000 Гц (период 0.5 мс)
    // Для 50 мс нужно: 50 / 0.5 = 100 тиков
    MODIFY_REG(TIM3->PSC, TIM_PSC_PSC_Msk, 8999UL);  // PSC = 44999 (делитель 45000)
    MODIFY_REG(TIM3->ARR, TIM_ARR_ARR_Msk, 499UL);     // ARR = 99 (100 тиков)
    
    SET_BIT(TIM3->CR1, TIM_CR1_ARPE);
    SET_BIT(TIM3->EGR, TIM_EGR_UG);
    SET_BIT(TIM3->DIER, TIM_DIER_UIE);
    
    NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 1, 0));
    NVIC_EnableIRQ(TIM3_IRQn);
    SET_BIT(TIM3->CR1, TIM_CR1_CEN);
}