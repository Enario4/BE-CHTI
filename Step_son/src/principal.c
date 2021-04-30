

#include "DriverJeuLaser.h"
#include "GestionSon.h"


extern void CallbackSon(void);


int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers


CLOCK_Configure();
	
// timer
	Timer_1234_Init_ff(TIM4, 6551)	;
	
	Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);
	
	Timer_1234_Init_ff(TIM3, 720)	;
	
	PWM_Init_ff( TIM3, 3, 720 );
	
	GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
	GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
	
	void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks);
	


	
	

//============================================================================	
	
	
while	(1)
	{
		StartSon();
		for (int i=0 ; i< 10000000;i++);
		
	}
}

