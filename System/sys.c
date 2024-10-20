#include "sys.h"

void Sys_Init(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
}

void Sys_Rest(void)
{

	__set_FAULTMASK(1);
	NVIC_SystemReset();

}
