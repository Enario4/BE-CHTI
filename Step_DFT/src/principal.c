

#include "DriverJeuLaser.h"


extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal[];
short int dma_buf[64];
int dft[64];	

void callbackSyst(){
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int k=0; k<64; k++){
			dft[k]= DFT_ModuleAuCarre(dma_buf , k);
	}
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();
Systick_Period_ff(360232);
Systick_Prio_IT( 2, callbackSyst );
SysTick_On;
SysTick_Enable_IT;	

Init_TimingADC_ActiveADC_ff( ADC1, 72 );
Single_Channel_ADC( ADC1, 2 );
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
Init_ADC1_DMA1( 0, dma_buf );
	

//============================================================================	

	
while	(1)
	{

	}
}

