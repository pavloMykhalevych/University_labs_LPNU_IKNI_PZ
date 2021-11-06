.586

.model flat, stdcall

option casemap:none

include c:\LPNU\ak\labs\lab9\AK_lab9\Debug\MASM32-SDK-master\include\windows.inc
include c:\LPNU\ak\labs\lab9\AK_lab9\Debug\MASM32-SDK-master\include\kernel32.inc
include c:\LPNU\ak\labs\lab9\AK_lab9\Debug\MASM32-SDK-master\include\user32.inc
include c:\LPNU\ak\labs\lab9\AK_lab9\Debug\MASM32-SDK-master\include\masm32.inc
;includelib c:\masm32\lib\kernel32.lib
;includelib c:\masm32\lib\user32.lib
;includelib c:\masm32\lib\masm32.lib

.stack

.data

surname byte "Mykhalevych",0
nname byte "Pavlo",0
mgroup byte "PZ-23",0

color DWORD 0
SSize DWORD 5
Counter dword 200000
hStdHnd DWORD ?
written DWORD ?
colors word 55 DUP(?)
black word 55 DUP(?)

.code

main PROC

LOCAL systime:SYSTEMTIME
invoke GetStdHandle,STD_OUTPUT_HANDLE
mov hStdHnd,EAX
invoke nrandom, 20
invoke SetConsoleCursorPosition, hStdHnd, EAX
lea ESI,surname
mov ECX, 7
print:
invoke GetSystemTime, addr systime
invoke nseed, systime.wSecond
invoke nrandom,4
or color, EAX
invoke nrandom,8
or color, EAX
invoke nrandom,64
or color,EAX
invoke nrandom,128
or color,EAX
invoke SetConsoleTextAttribute, hStdHnd, color
invoke WriteConsole, hStdHnd, ESI, 1, addr written, NULL
mov color,0
invoke Sleep, 1500
add ESI,1
dec SSize
loop print
mov ECX, 6
invoke nrandom, 20
add EAX,25
invoke SetConsoleCursorPosition, hStdHnd, EAX
lea ESI,nname

name:

invoke GetSystemTime, addr systime
invoke nseed, systime.wSecond
invoke nrandom,4
or color, EAX
invoke nrandom,8
or color, EAX
invoke nrandom,64
or color,EAX
invoke nrandom,128
or color,EAX
or color, 256
invoke SetConsoleTextAttribute, hStdHnd, color
invoke WriteConsole, hStdHnd, ESI, 1, addr written, NULL
mov color,0
invoke Sleep, 1500
inc ESI
dec SSize

loop name

mov ECX, 5
invoke nrandom, 20
add EAX,50
invoke SetConsoleCursorPosition, hStdHnd, EAX
lea ESI,mgroup

group:

invoke GetSystemTime, addr systime
invoke nseed, systime.wSecond
invoke nrandom,4
or color, EAX
invoke nrandom,8
or color, EAX
invoke nrandom,64
or color,EAX
invoke nrandom,128
or color,EAX
or color, 256
invoke SetConsoleTextAttribute, hStdHnd, color
invoke WriteConsole, hStdHnd, ESI, 1, addr written, NULL
mov color,0
invoke Sleep, 1500
add ESI,1
dec SSize

loop group

invoke ReadConsoleOutputAttribute, hStdHnd, addr colors, 56, 25, addr written
invoke ReadConsoleOutputAttribute, hStdHnd, addr black, 56, 76, addr written

.REPEAT

invoke WriteConsoleOutputAttribute, hStdHnd, addr black,56,25, addr written
invoke WriteConsoleOutputAttribute, hStdHnd, addr colors,56,25, addr written
lea ESI,black
dec Counter

.UNTIL Counter == 0

invoke SetConsoleTextAttribute, hStdHnd, FOREGROUND_BLUE or FOREGROUND_GREEN or FOREGROUND_RED
invoke ClearScreen
invoke WriteConsoleOutputAttribute, hStdHnd, addr black,56,0, addr written
invoke WriteConsoleOutputAttribute, hStdHnd, addr black,30,56, addr written

ret
main ENDP
end main