#include "stm32f10x.h"

// PB5 拨动开关初始化 上拉输入
void PB5_SW_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

// PC13 LED初始化 推挽输出
void PC13_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

int main(void)
{
    PB5_SW_Init();
    PC13_LED_Init();

    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5) == 0)
        {
            GPIO_ResetBits(GPIOC, GPIO_Pin_13);
        }
        else
        {
            GPIO_SetBits(GPIOC, GPIO_Pin_13);
        }
    }
}

