#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stm32f446xx.h>
#include "stm32f4xx_hal.h"
#include "BASE_COM.h"
#include "UART_COM.h"
#include "Debug.h"


extern std::vector<BASE_COM_t *> COM_ABSTRACT;

char generic_buffer[500];
int generic_int;
	 
UART_COM My_UART{115200 , UART4 , GPIOA , 0 , 1 , GPIO_AF8_UART4};


int main(void)
{
		
	HAL_Init();
	HAL_InitTick(0); 
	//Debug_Init();
	
	
	while(1)
	{
		generic_int++;
		memset(generic_buffer , 0 , 500);
		sprintf(generic_buffer , "Yoooo %d\n" , generic_int);
		My_UART.Send(generic_buffer , strlen(generic_buffer));
		//print_DebugMsg(generic_buffer);	
		HAL_Delay(1000);
	}

}

 #ifdef __cplusplus
 extern "C" {
#endif
	 
void HardFault_Handler (void) 
{
 __NVIC_SystemReset();			
}


void UART4_IRQHandler()
{
	My_UART.Interrupt_handler();
}

void SysTick_Handler()
{
	HAL_IncTick();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart == My_UART.Get_UART_HandleTypeDef())
	{
		My_UART.Receive_callback();
	}
}
	 
#ifdef __cplusplus
}
#endif


