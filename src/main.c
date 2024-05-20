#include <ch32v00x.h>
#include <debug.h>

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0}; //structure variable used for the GPIO configuration

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); // to Enable the clock for Port D
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // to Enable the clock for Port D

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Defines Output Type
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Defines Output Type
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1; // Defines which Pin to configure
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Defines Output Type
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Defines speed
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t Btn_Status = 0; //D0
    uint8_t Btn_Prev_Status = 0; //D0
    uint8_t counter = 0;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();

    while(1)
    {
        Btn_Status = GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0);
        if ((Btn_Status == 0) & (Btn_Prev_Status ==1)) //pressed =0, released =1
        {
            counter++; //debounce ??
        }
        Delay_Ms(100);
        Btn_Prev_Status = Btn_Status;

        (counter>0) ? GPIO_WriteBit(GPIOC, GPIO_Pin_5, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_5, RESET); //C5 - shamash
        
        (counter>0) ? GPIO_WriteBit(GPIOD, GPIO_Pin_3, SET) : GPIO_WriteBit(GPIOD, GPIO_Pin_3, RESET); //D3
        (counter>1) ? GPIO_WriteBit(GPIOD, GPIO_Pin_2, SET) : GPIO_WriteBit(GPIOD, GPIO_Pin_2, RESET); //D2
        (counter>2) ? GPIO_WriteBit(GPIOC, GPIO_Pin_7, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_7, RESET); //C7
        (counter>3) ? GPIO_WriteBit(GPIOC, GPIO_Pin_6, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_6, RESET); //C6
        (counter>4) ? GPIO_WriteBit(GPIOC, GPIO_Pin_4, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_4, RESET); //C4
        (counter>5) ? GPIO_WriteBit(GPIOC, GPIO_Pin_3, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_3, RESET); //C3
        (counter>6) ? GPIO_WriteBit(GPIOC, GPIO_Pin_2, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_2, RESET); //C2
        (counter>7) ? GPIO_WriteBit(GPIOC, GPIO_Pin_1, SET) : GPIO_WriteBit(GPIOC, GPIO_Pin_1, RESET); //C1
        if (counter>8) {counter = 0;}
    }
}