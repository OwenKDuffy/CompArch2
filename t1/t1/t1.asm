min : 
	push ebp
	mov ebp, esp
	sub esp, 4
	push ebx

	mov eax, [ebp + 8]
	cmp eax, [ebp + 12]
	jle bgreaterthan
	mov eax, [ebp + 12]

bgreaterthan:
	cmp eax, [ebp + 16]
	jle cgreatertha
	mov eax, [ebp +16]

cgreaterthan:
	pop ebx
	mov esp, ebp
	pop ebp
	ret 0

p :
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

gcd:
	push ebp
	mov ebp, esp
	sub esp, 4
	push ebx

	mov eax, [ebp + 8] ;eax = a
	mov ebx, [ebp + 12] ;ebx = b
	cmp ebx, 0
	jne else
	ret 0
else:
	
	mov edx, 0
	cdq
	idiv ebx ; a % b

	push edx
	push ebx
	call gcd
	return 0