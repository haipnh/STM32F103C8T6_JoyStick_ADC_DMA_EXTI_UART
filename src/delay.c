#include "delay.h"

void DelayUs(uint32_t us){
		us*=CPUS;
		while(us--);
}
void DelayMs(uint32_t ms){
		while(ms--){
				DelayUs(1000);
		}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
