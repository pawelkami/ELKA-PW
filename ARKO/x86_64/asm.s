;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; void epicykle[float* x_cord, float* y_cord, float* omega, float* time];	;;
;;										;;
;; x = 400*cos[12*t] + 200*cos[omega*t]						;;
;; y = 400*sin[12*t] + 200*sin[omega*t]						;;
;;										;;
;; rdi - x_cord	 rdi								;;
;; rsi - y_cord	 rsi								;;
;; rdx - omega	 rdx								;;
;; rcx - time	rcx								;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

section .data
PI: 	dd 	3.1415926535
PI_2: 	dd	1.5707963267
PI_by_1:	dd	0.3183098861
Q: 	dd	3.1
P: 	dd	3.6
dodajemy:	dd	25165824.0
A:	dd	500.0	;300
B:	dd 	200.0	;210
;omega1: 	dd 	12.0 ; 8	

extern omega1

section .text
global epicykle

epicykle:		;; 200*cos[omega*t]
	movss  xmm0, [rdx]   	;; loading omega
	mulss  xmm0, [rcx]   	;; omega*t	
	addss  xmm0, [PI_2]	;; x += PI/2	
	movss  xmm1, [PI_by_1]  ;; loading 1/PI
	mulss  xmm0, xmm1  	;; x=x*[1/PI]
	movss  xmm1, [dodajemy] ;; z = 25165824.0
	addss  xmm1, xmm0  	;; z = x+25165824.0
	movss  xmm2, xmm1	;; xmm2 = z
	movss  xmm3, [dodajemy] ;; xmm3 = dodajemy
	subss  xmm2, xmm3 	;; z -= dodajemy
	subss  xmm0, xmm2 	;; x -= z
	movss  xmm1, xmm0 	;; y = x
	movss  xmm2, xmm0 	;; z = x	
	
	xorps	xmm5, xmm5	;; xmm5 = 0	

	ucomiss    xmm1, xmm5	;; abs[x]
	ja nothing_to_change   	;; positive value
	
	subss	xmm5, xmm1 	;; y = -y
	movss	xmm1, xmm5

nothing_to_change:
	mulss	xmm2, xmm1 	;; x*abs[x] xmm1
	movss   xmm3, xmm0	;; move x
	subss   xmm3, xmm2	;; y = x - x*abso[x]
	movss	xmm1, [P]	;; xmm1 = P
	movss	xmm2, xmm3	;; xmm2 = y
	
	xorps 	xmm5, xmm5	
	ucomiss	xmm3, xmm5
	ja	nothing_to_change2
	
	subss	xmm5, xmm3	;; abs[y]
	movss	xmm3, xmm5

nothing_to_change2:
	mulss	xmm1, xmm3	;; P*abs[y] xmm3
	movss	xmm4, [Q]	;; xmm4 = Q
	addss	xmm4, xmm1	;; xmm4 = Q+P*abs[y]
	mulss	xmm2, xmm4	;; xmm2 = y*[Q + P*abs[y]]
	mulss	xmm2, [B]	;; xmm2 = B*cos[omega*t]
	movss	[rdi], xmm2	;; x_cord = B*cos[omega*t]

second_cos:
	movss  xmm0, [omega1]  	;; loading omega
	mulss  xmm0, [rcx]  	;; omega*t
	addss  xmm0, [PI_2]	;; x += PI/2	
	movss  xmm1, [PI_by_1]  	;; loading 1/PI
	mulss  xmm0, xmm1	;; x=x*[1/PI]
	movss  xmm1, [dodajemy]	;; z = 25165824.0
	addss  xmm1, xmm0	;; z = x+25165824.0
	movss  xmm2, xmm1	;; xmm2 = z
	movss  xmm3, [dodajemy]	;; xmm3 = dodajemy
	subss  xmm2, xmm3	;; z -= dodajemy
	subss  xmm0, xmm2	;; x -= z
	movss  xmm1, xmm0	;; y = x
	movss  xmm2, xmm0	;; z = x	
	
	xorps	xmm5, xmm5
	ucomiss    xmm1, xmm5		;; abs[x]
	ja  nothing_to_change3  ;; positive value
	
	subss	xmm5, xmm1	
	movss   xmm1, xmm5		;; y = -y

nothing_to_change3:
	mulss	xmm2, xmm1	;; x*abs[x]  xmm1
	movss   xmm3, xmm0	;; move x
	subss   xmm3, xmm2	;; y = x - x*abso[x]
	movss	xmm1, [P]		;; xmm1 = P
	movss	xmm2, xmm3	;; xmm2 = y
	
	xorps	xmm5, xmm5	
	ucomiss	xmm3, xmm5
	ja	nothing_to_change4


	subss	xmm5, xmm3		;; abs[y]
	movss	xmm3, xmm5

nothing_to_change4:
	mulss	xmm1, xmm3	;; P*abs[y]
	movss	xmm4, [Q]		;; xmm4 = Q
	addss	xmm4, xmm1	;; xmm4 = Q+P*abs[y]
	mulss	xmm2, xmm4	;; xmm2 = y*[Q + P*abs[y]]
	mulss	xmm2, [A]		;; xmm2 = A*cos[omega*t]
	movss	xmm7, [rdi]
	addss	xmm7, xmm2
	movss	[rdi], xmm7	


sinus_1: ;; 200*sin[omega*t]
	movss  xmm0, [rdx]  	;; loading omega
	mulss  xmm0, [rcx]  	;; omega*t
	movss  xmm1, [PI_by_1]  	;; loading 1/PI
	mulss  xmm0, xmm1	;; x=x*[1/PI]
	movss  xmm1, [dodajemy]	;; z = 25165824.0
	addss  xmm1, xmm0	;; z = x+25165824.0
	movss  xmm2, xmm1	;; xmm2 = z
	movss  xmm3, [dodajemy]	;; xmm3 = dodajemy
	subss  xmm2, xmm3	;; z -= dodajemy
	subss  xmm0, xmm2	;; x -= z
	movss  xmm1, xmm0	;; y = x
	movss  xmm2, xmm0	;; z = x	

	xorps	xmm5, xmm5
	ucomiss    xmm1, xmm5		;; abs[x]
	ja  nothing_to_change5  ;; positive value
	
	subss	xmm5, xmm1
	movss  xmm1, xmm5		;; y = -y

nothing_to_change5:
	mulss	xmm2, xmm1	;; x*abs[x]
	movss   xmm3, xmm0	;; move x
	subss   xmm3, xmm2	;; y = x - x*abso[x]
	movss	xmm1, [P]		;; xmm1 = P
	movss	xmm2, xmm3	;; xmm2 = y
	xorps 	xmm5, xmm5	
	ucomiss	xmm3, xmm5
	ja	nothing_to_change6
	
	subss	xmm5, xmm3
	movss	xmm3, xmm5	;; abs[y]

nothing_to_change6:
	mulss	xmm1, xmm3	;; P*abs[y]
	movss	xmm4, [Q]	;; xmm4 = Q
	addss	xmm4, xmm1	;; xmm4 = Q+P*abs[y]
	mulss	xmm2, xmm4	;; xmm2 = y*[Q + P*abs[y]]
	mulss	xmm2, [B]	;; xmm2 = B*sin[omega*t]
	movss	[rsi], xmm2	;; y_cord = B*sin[omega*t]

second_sin:
	movss  xmm0, [omega1]  	;; loading omega
	mulss  xmm0, [rcx]  	;; omega*t	
	movss  xmm1, [PI_by_1]  	;; loading 1/PI
	mulss  xmm0, xmm1	;; x=x*[1/PI]
	movss  xmm1, [dodajemy]	;; z = 25165824.0
	addss  xmm1, xmm0	;; z = x+25165824.0
	movss  xmm2, xmm1	;; xmm2 = z
	movss  xmm3, [dodajemy]	;; xmm3 = dodajemy
	subss  xmm2, xmm3	;; z -= dodajemy
	subss  xmm0, xmm2	;; x -= z
	movss  xmm1, xmm0	;; y = x
	movss  xmm2, xmm0	;; z = x	
	
	xorps	xmm5, xmm5
	ucomiss    xmm1, xmm5		;; abs[x]
	ja  nothing_to_change7  ;; positive value
	
	subss	xmm5, xmm1
	movss	xmm1, xmm5		;; y = -y

nothing_to_change7:
	mulss	xmm2, xmm1	;; x*abs[x]
	movss   xmm3, xmm0	;; move x
	subss   xmm3, xmm2	;; y = x - x*abso[x]
	movss	xmm1, [P]		;; xmm1 = P
	movss	xmm2, xmm3	;; xmm2 = y
	xorps	xmm5, xmm5	
	ucomiss	xmm3, xmm5
	ja	nothing_to_change8
	
	subss	xmm5, xmm3
	movss	xmm3, xmm5		;; abs[y]

nothing_to_change8:
	mulss	xmm1, xmm3	;; P*abs[y]
	movss	xmm4, [Q]		;; xmm4 = Q
	addss	xmm4, xmm1	;; xmm4 = Q+P*abs[y]
	mulss	xmm2, xmm4	;; xmm2 = y*[Q + P*abs[y]]
	mulss	xmm2, [A]		;; xmm2 = A*sin[omega*t]
	movss	xmm8, [rsi]	;; loading y_cord
	addss	xmm8, xmm2	;; sin + sin
	movss	[rsi], xmm8	;; loading our sum to rsi what is x_cord

end:
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;float sine[float x]
;;{
;;    // Convert the input value to a range of -1 to 1
;;    x = x * [1.0 / PI];
;; 
;;    // Wrap around
;;    float z = [x + 25165824.0];
;;    x = x - [z - 25165824.0];
;;    float y = x - x * abso[x];
;; 
;;    z= y * [Q + P * abso[y]];
;;
;;}
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
