	PRESERVE8
	THUMB   
	export 	CallbackSon
	import Son
	import LongueurSon
	export SortieSon
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly
		



;Section RAM (read write):
	area    maram,data,readwrite
		
index dcd 0
SortieSon dcd 0
		

	
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

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
	
	
	ldr r1,=SortieSon; problème: sortie son est à 0
	
	
	
	mov r4, #719
	
	add r0,r0, #32768
	mul r0, r4
	asr r0,#16
	
	
	str r0, [r1]
	b finsi

	
finsi
	str r3, [r2]
	
	pop{r4}
	bx lr
	endp
	END	