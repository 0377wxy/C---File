#include "stm32f10x.h"

#define RCC (unsigned int)0x40021000
#define GPIO_B (unsigned int)0x40010C00
#define GPIO_A (unsigned int)0x40010800
#define GPIO_C (unsigned int)0x40011000

#define RCC_APB2ENR (unsigned int *)(RCC + 0x18)  //外设时钟使能寄存器
#define GPIOC_CRL (unsigned int *)GPIO_C          //端口配置低寄存器
#define GPIOC_ODR (unsigned int *)(GPIO_C + 0x0C) //端口输出数据寄存器

void soft_delay(unsigned int count)
{
    for (; count != 0; count--)
        ;
}

void SystemInit(void)
{
}

int main()
{
    *RCC_APB2ENR |= (1 << 4);

    *GPIOC_CRL &= ~(15 << 8);
    *GPIOC_CRL |= (3 << 8);
    *GPIOC_CRL &= ~(3 << 10);

    *GPIOC_ODR &= ~(1 << 2);
    *GPIOC_ODR &= ~(1 << 3);

    while (1)
    {
        *GPIOC_ODR &= ~(1 << 2);
        soft_delay(0xfffff);
        *GPIOC_ODR |= (1 << 2);

        *GPIOC_ODR &= ~(1 << 3);
        soft_delay(0xfffff);
        *GPIOC_ODR |= (1 << 3);
    }
}
