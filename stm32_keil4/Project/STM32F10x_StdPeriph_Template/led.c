
#include "stm32f10x.h"

void LED0_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

void LED0_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_8);
}

void Delay(unsigned long x)
{
    unsigned long i;
    for(i = 0; i < x; i++);
}



int main(void)
{
    LED0_Config();   
    while(1)         
    {
        LED0_On();                
        Delay(0x3FFFFF);          
        LED0_Off();               
        Delay(0x3FFFFF);          
    }
}

