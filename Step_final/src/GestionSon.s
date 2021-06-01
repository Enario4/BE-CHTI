	PRESERVE8
	THUMB   
	export 	CallbackSon
	export StartSon
	import Son
	import LongueurSon
	export SortieSon
	include DriverJeuLaser.inc
; ====================== zone de r�servation de donn�es,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly
		



;Section RAM (read write):
	area    maram,data,readwrite
		
index dcd 0
SortieSon dcd 0
		

	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; �crire le code ici		

CallbackSon proc
	; r1: son
	; r2: index
	push{r4}
	ldr r1,=Son
	ldr r2,=index
	ldr r12,=LongueurSon
	ldr r12, [r12]
	ldr r3, [r2]
	
	ldrsh r0, [r1, r3, lsl #1]
	CMP r3, r12
	bge finsi

	add r3, r3, #1
	
	
	ldr r1,=SortieSon; probl�me: sortie son est � 0
	
	
	
	mov r4, #719
	
	add r0,r0, #32768
	mul r0, r4
	asr r0,#16
	
	
	str r0, [r1]
	push{r0-r3,r12,lr}
	bl PWM_Set_Value_TIM3_Ch3
	pop{r0-r3,r12,lr}
	b finsi

	
finsi
	str r3, [r2]
	
	pop{r4}
	bx lr
	endp

		
StartSon proc
	
	ldr r2,=index
	ldr r1,[r2]
	mov r1, #0
	str r1, [r2]
	bx lr 
	endp
	END	
