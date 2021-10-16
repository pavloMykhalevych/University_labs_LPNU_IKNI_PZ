.586P

.MODEL FLAT, STDCALL
;------------------------------------------------

_DATA SEGMENT

Arr1 dd 17, 3, -51, 242, -113, -43
  dd 78, 50, 100, -100, 4, 8
  dd 15, 32, 34, 45, 65, 4
  dd 5, 6, 7, 8, 9, 10
  dd 11, 12, 13, 14, 16, -1
  dd -1, -32, -42, 114, 101, 20
  dd 21, 22, 23, 24, 25, 26
  dd 27, 28, 29, 30, 31, 32
  dd 33, 35, 36, 37, 38, 39
Arr2 dd 56 dup(0)
Arr3 dd 56 dup(0)

RowCount db 9
ColCount db 6

Row dd 9+1

SumOf9Column dd 0

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
 mov eax, 10

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
 ;===================================================================

RET
_TEXT ENDS
END START