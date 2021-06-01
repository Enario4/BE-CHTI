

#include "DriverJeuLaser.h"
#include "GestionSon.h"
#include "Affichage_Valise.h"


extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal[];
short int dma_buf[64];
int dft[6];
int k[6]={17,18,19,20,23,24};
int seuil=2000;
int scores[6]={0,0,0,0,0,0};
int compteur_score=0;

/*void affichage (int joueur) {
	
	// Configuration affichage 
	Prepare_Afficheur((char)joueur, (char)scores[joueur]);
	Prepare_Set_Point_Unite((char)joueur);
	Prepare_Clear_Point_Unite((char)joueur);
	Prepare_Set_LED(LED_Cible_1);
	Prepare_Clear_LED(LED_Cible_1);
	Mise_A_Jour_Afficheurs_LED();
}*/

void callbackSyst(){
	compteur_score= (compteur_score+1)%20;
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for(int i=0; i<6; i++){
			dft[i]= DFT_ModuleAuCarre(dma_buf , k[i]);
			if ((compteur_score==0) && (dft[i]>= seuil)) {
				scores[i]+=1;
				StartSon();
				//affichage((char)i);
			}
				
	}
}



int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Apr�s ex�cution : le coeur CPU est clock� � 72MHz ainsi que tous les timers
	
	// Configuration DMA
CLOCK_Configure();
Systick_Period_ff(360232);
Systick_Prio_IT( 2, callbackSyst );
SysTick_On;
SysTick_Enable_IT;	

Init_TimingADC_ActiveADC_ff( ADC1, 72 );
Single_Channel_ADC( ADC1, 2 );
Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
Init_ADC1_DMA1( 0, dma_buf );
	
	//Configuration Son
Timer_1234_Init_ff(TIM4, 6551)	;
Active_IT_Debordement_Timer( TIM4, 2, CallbackSon);		
Timer_1234_Init_ff(TIM3, 720)	;		
PWM_Init_ff( TIM3, 3, 720 );		
GPIO_Configure(GPIOB, 1, OUTPUT, OUTPUT_PPULL);
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);
void PWM_Set_Value_TIM3_Ch3( unsigned short int Thaut_ticks);

// Configuration Affichage
//Init_Affichage();
	

//============================================================================	

	
while	(1)
	{

	}
}

