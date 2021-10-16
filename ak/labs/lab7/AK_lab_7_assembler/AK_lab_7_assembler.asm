.586P

.MODEL FLAT, STDCALL
;------------------------------------------------

_DATA SEGMENT

Arr1 dd 17, 3, -51, 2, 3, -43
  dd 78, 50, 100, 10, 4, 8
  dd 15, 32, 34, 1, 5, 4
  dd 5, 6, 7, 8, 9, 10
  dd 11, 12, 13, 4, 3, -1
  dd -1, -32, -42, 1, 1, 20
  dd 21, 22, 23, 1, 7, 26
  dd 27, 28, 29, 1, 2, 32
  dd 33, 35, 36, 8, 1, 39
Arr2 dd 56 dup(0)
Arr3 dd 56 dup(0)

RowCount db 9
ColCount db 6

Row dd 9+1

SumOf9Row dd 0
SkalarMultof5and4Column dd 0

i dd 0

_DATA ENDS


_TEXT SEGMENT

START:
 mov eax, 0
 mov al, RowCount
 mov bl, ColCount
 mul bl

 mov ecx, eax

 lea ebx, Arr1
 lea edx, Arr2

 ;copying values from arr1 to arr2
 copy:
  mov eax, [ebx]
  mov [edx], eax

  add ebx, 4
  add edx, 4
 loop copy
 ;===================================================================
 ;transposing matrix
 lea eax, Arr1
 rows:
  lea ebx, Arr3
  add ebx, i

  mov ecx, 0
  mov cl, ColCount

  cols:
   mov edx, [eax]
   mov [ebx], edx

   add eax, 4
   add ebx, 4*9

  loop cols

  add i, 4
  dec Row
  mov ecx, Row
 loop rows
 ;===================================================================
 ;calculating sum of 9th row
 lea ebx, Arr1
 add ebx, 4*48
 mov ecx, 0
 mov cl, ColCount
 mov eax, 0
 sum:
  add eax, [ebx]

  add ebx, 4

 loop sum

 mov SumOf9Row, eax
 ;===================================================================
 ;calculating skalar multiplying of 5 and 4 columns

 lea ebx, Arr1
 add ebx, 4*3

 mov ecx, 0
 mov cl, RowCount
 mov eax, 0

 mult:
	mov eax, [ebx]
	add ebx, 4
	mov edx, [ebx]
	mul edx

	add SkalarMultof5and4Column, eax

	add ebx, 4*5

 loop mult
 ;===================================================================
 ;Change 7 and 8 rows


 mov ecx, 0
 mov cl, ColCount

 lea ebx, Arr1
 lea edx, Arr2
 add ebx, 4*6*6
 add edx, 4*6*7

 ;copying values from 7 to 8
 copy78:
  mov eax, [ebx]
  mov [edx], eax

  add ebx, 4
  add edx, 4
 loop copy78

 mov ecx, 0
 mov cl, ColCount

 lea ebx, Arr1
 lea edx, Arr2
 add ebx, 4*6*7
 add edx, 4*6*6

 ;copying values from 8 to 7
 copy87:
  mov eax, [ebx]
  mov [edx], eax

  add ebx, 4
  add edx, 4
 loop copy87
 ;===================================================================
RET
_TEXT ENDS
END START