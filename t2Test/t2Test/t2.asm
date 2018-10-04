includelib legacy_stdio_definitions.lib
extrn printf:near
.data


option casemap:none             ; case sensitive
 

.data								; start of a data section
public g							; export variable g
g QWORD 4							; declare global variable g initialised to 4

.code

public min
min:
	mov rax, rcx		;v = a
	cmp rdx, rax		;if (b<v)
	jge bgreaterthan
	mov rax, rdx		;v = b

bgreaterthan:
	cmp r8, rax			;if (c<v)
	jge cgreaterthan
	mov rax, r8			;v = c

cgreaterthan:
	ret 0


public p
p:
	sub rsp, 32			;allocate shadow space
	mov rbx, r8			;tmp = k
	mov r8, rdx
	mov rdx, rcx
	mov rcx, g
	call min
	
	mov rcx, rax
	mov rdx, rbx
	mov r8, r9
	call min
	add rsp, 32			;deallocate shadow space
	ret 0


;_int64 gcd(_int64 a, _int64 b) {
;if (b == 0) {
;return a;
;} else {
;return gcd(b, a % b);
;}
;}


public gcd
gcd:
	mov rax, rcx
	mov rbx, rdx
	cmp rbx, 0
	jne notEqual
	ret 0;
notEqual:
	mov rdx, 0
	cqo
	idiv rbx
	mov rcx, rbx
	sub rsp, 32
	call gcd
	add rsp, 32
	ret 0


;	_int64 q(_int64 a, _int64 b, _int64 c, _int64 d, _int64 e) {
;	_int64 sum = a + b + c + d + e;
;	printf("a = %I64d b = %I64d c = %I64d d = %I64d e = %I64d sum = %I64d\n", a, b, c, d, e, sum);
;	return sum;
;	}

fq db 'a = %I64d b = %I64d c = %I64d d = %I64d e = %I64d sum = %I64d\n', 0AH, 00H


public q
q:
	
	mov rbx, [rsp+32]		;e
	sub rsp, 56				;allocate stack space
	add rax, rcx
	add rax, rdx
	add rax, r8
	add rax, r9
	add rax, rbx

	mov [rsp + 48], rax
	mov [rsp + 40], rbx
	mov [rsp + 32], r9
	mov r9, r8
	mov r8, rdx
	mov rdx, rcx
	lea rcx, fq
	call printf
	ret 0

end	