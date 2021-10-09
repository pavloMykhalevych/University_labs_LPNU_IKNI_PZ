.586P

.MODEL FLAT, STDCALL

_DATA SEGMENT
Num1 DD 17, 3, -51, 242, -113, -43, 78, 50, 100, -100, 4, 8, 12, 32, 34, 45, 65 
N DD 17 
Sum DD 0 
Count DD 0 
_DATA ENDS

_TEXT SEGMENT 
START:
	lea EBX, Num1 
	mov EDX, 0
	mov ECX, N 
	mov EAX, 0 
	M1: 
		mov EAX, [EBX]
		cmp EAX, -43 
		jl L2
		cmp EAX, 78
		jg L2
		add SUM, EAX
		inc EDX
	L2:
		add EBX, 4 
		loop M1 
		mov Count, EDX
		mov EAX, SUM
		RET 
_TEXT ENDS 
END START

