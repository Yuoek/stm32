#include "stm32f10x.h"

#define TIME_MS  2230
uint16_t tim_count = 0;

void LED_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    // PC13 推挽输出
    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    GPIOC->CRH |= GPIO_CRH_MODE13_0;
    GPIOC->ODR |= GPIO_ODR_ODR13; // 初始熄灭
}

void TIM2_Init(void)
{
    TIM_TimeBaseInitTypeDef tim_cfg;
    NVIC_InitTypeDef nvic_cfg;

    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    tim_cfg.TIM_Prescaler = 71;
    tim_cfg.TIM_Period    = 999;
    tim_cfg.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_cfg.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &tim_cfg);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    nvic_cfg.NVIC_IRQChannel = TIM2_IRQn;
    nvic_cfg.NVIC_IRQChannelPreemptionPriority = 1;
    nvic_cfg.NVIC_IRQChannelSubPriority = 1;
    nvic_cfg.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_cfg);

    TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        tim_count++;
        if(tim_count >= TIME_MS)
        {
            tim_count = 0;
            GPIOC->ODR ^= GPIO_ODR_ODR13;
        }
    }
}

int main(void)
{
    LED_Init();
    TIM2_Init();
    while(1)
    {

    }
}

