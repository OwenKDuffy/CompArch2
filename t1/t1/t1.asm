;t1.asm
.686                                ; create 32 bit code
.model flat, C                      ; 32 bit memory model
 option casemap:none                ; case sensitive


.data								; start of a data section
public g							; export variable g
g DWORD 4							; declare global variable g initialised to 4

.code


public  min               
min:	
		push ebp;
		mov ebp, esp;
		sub esp, 4
		push ebx

		mov eax, [ebp + 8]
		cmp eax, [ebp + 12]
		jle bgreaterthan
		mov eax, [ebp + 12]

bgreaterthan:
		cmp eax, [ebp + 16]
		jle cgreaterthan
		mov eax, [ebp +16]

cgreaterthan:
		pop ebx
		mov esp, ebp
		pop ebp
		ret 0

public p
p:
		push ebp
		mov ebp, esp
		push ebx

		push [ebp + 12]
		push [ebp + 8]
		push g
		call min
	
		add esp, 12
		push [ebp + 20]
		push [ebp + 16]
		push eax
		call min
	
		add esp, 12
		pop ebx
		mov esp, ebp
		pop ebp
		ret 0


public gcd
gcd:
		push ebp				;save ebp
		mov ebp, esp			;ebp -> new stack frame
		mov eax, [ebp + 8]		;eax = a
		mov ebx, [ebp + 12]		;ebx = b
		cmp ebx, 0				;if b == 0
		jne notEqual
		pop ebx					; restore saved registers
		mov esp, ebp			; restore esp
		pop ebp					; restore previous ebp
		ret 0					;return a
notEqual:
		
		mov edx, 0
		cdq
		idiv ebx
		push edx				;push a % b
		push ebx				;push b
		call gcd
		add esp, 8
		pop ebx					; restore saved registers
		mov esp, ebp			; restore esp
		pop ebp					; restore previous ebp
		ret 0

		

end