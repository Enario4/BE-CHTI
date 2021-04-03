	;char FlagCligno
	;void timer_callback(void)
;{
;	if (FlagCligno==1)
;	{
;		FlagCligno=0;
;		GPIOB_Set(1);
;	}
;	else
;	{
;		FlagCligno=1;
;		GPIOB_Clear(1);
;	}
;		
;}
	
		
			PRESERVE8
			THUMB   
				
			export timer_callback
			include DriverJeuLaser.inc
		
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
			area    mesdata,data,readonly


;Section RAM (read write):
			area    maram,data,readwrite
		
			; Char Flagcligno FlagCligno ;
FlagCligno dcb 0	
		
; ===============================================================================================
			


		
;Section ROM code (read only) :		
			area    moncode,code,readonly
; écrire le code ici		
;void timer_callback(void) {
timer_callback proc
			 
; if (FlagCligno==1){
			ldr r0,=FlagCligno
			ldrb r1,[r0]
			subs r1, #1
			bne sinon
;		FlagCligno=0;
			subs r1, #1
			str r1,[r0]
			
			mov r0,#1
			push {lr}
			bl GPIOB_Set
;		GPIOB_Set(1);
			
			b finsi
;	} else {
sinon 
;			FlagCligno=1;
			mov r1,#1
			strb r1, [r0]
;		    GPIOB_Clear(1);	
			mov r0,#1
			push {lr}
			bl GPIOB_Clear 
;		
;	}
finsi
			pop {lr}
			bx lr
			endp
			END	