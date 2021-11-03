include C:\LPNU\ak\labs\lab9\AK_lab9\Debug\irvine\Irvine32-master\Irvine32.inc

.586P
.MODEL FLAT, STDCALL
;------------------------------------------------
_DATA SEGMENT

fileName db "Mykhalevych_Pavlo.txt"
fileHandle dd ?

string db "Mykhalevych Pavlo   07.07.2003    Lviv  PZ-23", 0
stringLen equ $-string

string2 db "OP 89 English 95", 0
stringLen2 equ $-string2
writtenBytes dd ?

readStr db stringLen dup(0)
readBytesCount dd 0

i dd 0
sym db ?
symCount dd 0

_DATA ENDS
_TEXT SEGMENT
START:

	;INVOKE CreateFile,
		;ADDR filename, GENERIC_WRITE, DO_NOT_SHARE, NULL,
		;CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0

	;mov fileHandle, eax

	;INVOKE WriteFile,
		;fileHandle, ADDR string,
		;stringLen, ADDR writtenBytes, 0

	;INVOKE CloseHandle,
		;fileHandle

 ; ������� �� �����
 ;==================================================================
	INVOKE CreateFile,
		ADDR filename, GENERIC_READ, DO_NOT_SHARE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0

	mov fileHandle, eax

	INVOKE ReadFile,
		fileHandle, ADDR readStr, stringLen, ADDR readBytesCount, 0

	mov esi, readBytesCount
	mov readStr [esi], 0
	mov edx, OFFSET readStr

	lea edi, readStr
	call skipSpaces;

	mov eax, [edi]
	mov sym, al

 ; ���������� ������ ���� ������� ������ ������ � ������� ������
 ;==================================================================
	mov edx, stringLen
	dec edx

L:
	inc symCount
	call findChar

	mov ebx, i

	cmp ebx, edx
jb L
	dec symCount
 ;==================================================================

 ; �������� � ����
 ;==================================================================
INVOKE CloseHandle,
  fileHandle

	;INVOKE CreateFile,
		;ADDR fileName, GENERIC_WRITE,
		;DO_NOT_SHARE, NULL, OPEN_EXISTING,
		;FILE_ATTRIBUTE_NORMAL, 0

	;mov fileHandle, eax

	;INVOKE SetFilePointer,
		;fileHandle, 0, 0, FILE_END

	;INVOKE WriteFile,
		;fileHandle, ADDR string2,
		;stringLen2, ADDR writtenBytes, 0

	;INVOKE CloseHandle,
		;fileHandle
 ;==================================================================

	jmp PROGRAM_END

;====================================================================
; �������� �������� �������
;====================================================================
	skipSpaces:
		mov ecx, stringLen
		inc i
		sub ecx, i
		dec i
		mov ebx, ecx

		mov al, ' '
		cld
		repe scasb
		dec edi

		sub ebx, ecx
		dec ebx
		mov ecx, ebx

		add i, ebx
	ret
;====================================================================
; ���� ������ ������
;====================================================================
	findChar:
		mov ecx, stringLen
		inc i
		sub ecx, i
		dec i
		mov ebx, ecx

		mov al, sym
		cld
		repne scasb
		;dec edi

		sub ebx, ecx
		dec ebx
		mov ecx, ebx

		add i, ebx
		inc i
	ret

PROGRAM_END:
RET
_TEXT ENDS
END START