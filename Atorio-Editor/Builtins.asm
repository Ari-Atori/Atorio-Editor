.DATA
ALIGN 16

const_0 dword 0,0,0,0
const_255 dword 437F0000h, 437F0000h, 437F0000h, 437F0000h

i420_y_mul dword 3F94FDF4h, 3F94FDF4h, 3F94FDF4h, 0
i420_u_mul dword 0, 0BEC83127h, 400126E9h, 0
i420_v_mul dword 3FCC49BAh, 0BF5020C5h, 0, 0
i420_c_add dword 0C35E3127h, 043077CEEh, 0C38A76C9h, 0


.CODE
;guraentees that each register output is four bytes
; so we do not have to do sizeof checks
bi_cpuid PROC
	mov eax, ecx
	mov ecx, edx
	cpuid
	mov [r8], eax
	mov [r8+4], ebx
	mov [r8+8], ecx
	mov [r8+12], edx
	ret
bi_cpuid ENDP


; converts yuv color space into rgb
; rather than compute each channel r, g, and b individually
; we shall take advantage of the fact that
;
; R = 1.164(Y - 16) + 1.596(V - 128)
; G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
; B = 1.164(Y - 16) + 2.018(U - 128)
;
; can be rewritten as:
;
; R = 1.164*Y + 0.000*U + 1.596*V - 222.912
; G = 1.164*Y - 0.391*U - 0.813*V + 135.488
; B = 1.164*Y + 2.018 U + 0.000*V - 276.928
;
; allowing parallelization
i420_rgb PROC
	; back up registers we shall be using
	sub rsp, 32 
	movdqu [rsp], xmm0
	movdqu [rsp+16], xmm1

	;cast y into a float and store into parallel register
	cvtsi2ss xmm0, rcx
	shufps xmm0, xmm0, 0
	mulps xmm0, i420_y_mul
	;cast u into a float and store into parallel register
	cvtsi2ss xmm1, rdx
	shufps xmm1, xmm1, 0
	mulps xmm1, i420_u_mul
	addps xmm0, xmm1
	cvtsi2ss xmm1, r8
	shufps xmm1, xmm1, 0
	mulps xmm1, i420_v_mul
	addps xmm0, xmm1
	addps xmm0, i420_c_add
	minps xmm0, const_255
	maxps xmm0, const_0

	xor rax, rax
	cvttss2si rax, xmm0
	shufps xmm0, xmm0, 39h
	cvttss2si rdx, xmm0
	shl rdx, 8
	or rax, rdx
	shufps xmm0, xmm0, 39h
	cvttss2si rdx, xmm0
	shl rdx, 16
	or rax, rdx
	or rax, 0FF000000h

	;return them to undo clobbering
	movdqu  xmm0, [rsp]
	movdqu  xmm1, [rsp+16]
	add rsp, 32
	ret
i420_rgb ENDP

; TODO: rewrite as this still has i420 formula 
; converts yuv color space into rgb
; rather than compute each channel r, g, and b individually
; we shall take advantage of the fact that
;
; R = 1.164(Y - 16) + 1.596(V - 128)
; G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
; B = 1.164(Y - 16) + 2.018(U - 128)
;
; can be rewritten as:
;
; R = 1.164*Y + 0.000*U + 1.596*V - 222.912
; G = 1.164*Y - 0.391*U - 0.813*V + 135.488
; B = 1.164*Y + 2.018 U + 0.000*V - 276.928
;
; allowing parallelization
j420_rgb PROC
	; back up registers we shall be using
	sub rsp, 32 
	movdqu [rsp], xmm0
	movdqu [rsp+16], xmm1

	;cast y into a float and store into parallel register
	cvtsi2ss xmm0, rcx
	shufps xmm0, xmm0, 0
	mulps xmm0, i420_y_mul
	;cast u into a float and store into parallel register
	cvtsi2ss xmm1, rdx
	shufps xmm1, xmm1, 0
	mulps xmm1, i420_u_mul
	addps xmm0, xmm1
	cvtsi2ss xmm1, r8
	shufps xmm1, xmm1, 0
	mulps xmm1, i420_v_mul
	addps xmm0, xmm1
	addps xmm0, i420_c_add
	minps xmm0, const_255
	maxps xmm0, const_0

	xor rax, rax
	cvttss2si rax, xmm0
	shufps xmm0, xmm0, 39h
	cvttss2si rdx, xmm0
	shl rdx, 8
	or rax, rdx
	shufps xmm0, xmm0, 39h
	cvttss2si rdx, xmm0
	shl rdx, 16
	or rax, rdx
	or rax, 0FF000000h

	;return them to undo clobbering
	movdqu  xmm0, [rsp]
	movdqu  xmm1, [rsp+16]
	add rsp, 32
	ret
j420_rgb ENDP

END