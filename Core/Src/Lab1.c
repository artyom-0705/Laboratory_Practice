#include "init_lab1.h"

void Variant_6(uint8_t *en, uint8_t *score, bool *LD_1, bool *LD_2, bool *LD_3, bool *press1, bool *press2) // Функция выполняющая задание из варианта 6, принимает указатели для возможности воспользоваться MCUViewer
{
    while (1)
    {
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_0) != 0)                      // Проверка нажата ли кнопка 2 (меняет режимы работы кнопки 1)
        {
            if (*press2 == 0)
            {
                *en = (*en + 1) % 2;
                *score = 0;
                *press2 = 1;
                for (int i = 0; i < 400000; i++);                           // Задержка для подавления дребезга контактов
            }
        }
        else if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_0) == 0) && (*press2 == 1))
        {
            *press2 = 0;
        }
        if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) != 0) && (*score < 3))   // Если кнопка 1 нажата и при этом счетчик меньше 3, то увеличиваем счетчик на 1
        {
            if (*press1 == 0)
            {
                *score = *score + 1;
                *press1 = 1;
                for (int i = 0; i < 400000; i++);                           // Задержка для подавления дребезга контактов
            }
        }
        else if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0) && (*press1 == 1))
        {
            *press1 = 0;
        }

        if (*score == 1 && *en == 0)                                        // Если счетчик равен 1 и en равен 0, включаем led 1
        {
            *LD_1 = 1;
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);
        }
        if (*score == 2 && *en == 0)                                        // Если счетчик равен 2 и en равен 0, включаем led 2
        {
            *LD_2 = 1;
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BS7);
        }
        if (*score == 3 && *en == 0)                                        // Если счетчик равен 3 и en равен 0, включаем led 3
        {
            *LD_3 = 1;
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
        }

        if (*score == 1 && *en == 1)                                        // Если счетчик равен 1 и en равен 1, выключаем led 1
        {
            *LD_1 = 0;
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR0);
        }
        if (*score == 2 && *en == 1)                                        // Если счетчик равен 2 и en равен 1, выключаем led 2
        {
            *LD_2 = 0;
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BR7);
        }
        if (*score == 3 && *en == 1)                                        // Если счетчик равен 3 и en равен 1, выключаем led 3
        {
            *LD_3 = 0;
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
        }
    }
}

void extra_task(uint8_t *en, uint8_t *score, bool *LD_1, bool *LD_2, bool *LD_3, bool *press1, bool *press2) // Функция выполняющая дополнительное задание, принимает указатели для возможности воспользоваться MCUViewer
{
    while (1)
    {
        if (READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_0) != 0)                      // Проверка нажата ли кнопка 2 (меняет режимы работы кнопки 1)
        {
            if (*press2 == 0)
            {
                *en = (*en + 1) % 6;                                        // Переключение режимов
                *score = 0;
                *press2 = 1;
                for (int i = 0; i < 400000; i++);                           // Задержка для подавления дребезга контактов
            }
        }
        else if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_0) == 0) && (*press2 == 1))
        {
            *press2 = 0;
        }

        if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) != 0) && (*score < 3))   // Если кнопка 1 нажата и при этом счетчик меньше 3, то увеличиваем счетчик на 1
        {
            if (*press1 == 0)
            {
                *score = *score + 1;
                *press1 = 1;
                for (int i = 0; i < 400000; i++);                           // Задержка для подавления дребезга контактов
            }
            
        }
        else if ((READ_BIT(GPIOC->IDR, GPIO_IDR_IDR_13) == 0) && (*press1 == 1))
        {
            *press1 = 0;
        }

        if ((*score == 1) && (*en % 2 == 0))                                // Если счетчик равен 1 и при деление en на 2 остаток от деления равен 0, включаем led 1 и устанавливаем переменную LD_1 в 1
        {
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);
            *LD_1 = 1;
        }
        if ((*score == 2) && (*en % 2 == 0))                                // Если счетчик равен 2 и при деление en на 2 остаток от деления равен 0, включаем led 2 и устанавливаем переменную LD_2 в 1
        {
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BS7);
            *LD_2 = 1;
        }
        if ((*score == 3) && (*en % 2 == 0))                                // Если счетчик равен 3 и при деление en на 2 остаток от деления равен 0, включаем led 3 и устанавливаем переменную LD_3 в 1
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
            *LD_3 = 1;
        }

        if ((*score == 1) && (*en % 2 == 1))                                // Если счетчик равен 1 и при деление en на 2 остаток от деления равен 1, выключаем led 1 и устанавливаем переменную LD_1 в 0
        {
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR0);
            *LD_1 = 0;
        }
        if ((*score == 2) && (*en % 2 == 1))                                // Если счетчик равен 2 и при деление en на 2 остаток от деления равен 1, выключаем led 2 и устанавливаем переменную LD_2 в 0
        {
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BR7);
            *LD_2 = 0;
        }
        if ((*score == 3) && (*en % 2 == 1))                                // Если счетчик равен 3 и при деление en на 2 остаток от деления равен 1, выключаем led 3 и устанавливаем переменную LD_3 в 0
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
            *LD_3 = 0;
        }

        if ((*LD_1 == 1) && (*en == 0 || *en == 1))                         // Если LD_1 = 1 (т.е. led 1 горит) и en равен 0 или 1, то мигаем первой лампочкой (выключаем и через n циклов включаем)
        {
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BR0);
            for (int i = 0; i < 100000; i++);
            SET_BIT(GPIOD->BSRR, GPIO_BSRR_BS0);
            for (int i = 0; i < 100000; i++);
        }
        if ((*LD_2 == 1) && (*en == 2 || *en == 3))                         // Если LD_2 = 1 (т.е. led 2 горит) и en равен 2 или 3, то мигаем второй лампочкой (выключаем и через n циклов включаем)
        {
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BR7);
            for (int i = 0; i < 100000; i++);
            SET_BIT(GPIOE->BSRR, GPIO_BSRR_BS7);
            for (int i = 0; i < 100000; i++);
        }
        if ((*LD_3 == 1) && (*en == 4 || *en == 5))                         // Если LD_3 = 1 (т.е. led 3 горит) и en равен 4 или 5, то мигаем третьей лампочкой (выключаем и через n циклов включаем)
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
            for (int i = 0; i < 100000; i++);
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
            for (int i = 0; i < 100000; i++);
        }
    }
}