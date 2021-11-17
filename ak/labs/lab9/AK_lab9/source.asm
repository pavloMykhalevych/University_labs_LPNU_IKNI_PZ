INCLUDE Irvine32.inc

.686
.model flat, stdcall

_DATA SEGMENT
name_ BYTE "Mykhalevych", 0
lastname_ BYTE "Pavlo", 0
group_ BYTE "PZ-23", 0
_DATA ENDS

_TEXT SEGMENT
START:

infloop:

    mov eax, yellow
    call SetTextColor

    mov dh, 2
    mov dl, 2

    call GoToXY

    lea edx, name_
    call WriteString


    mov dh, 3
    mov dl, 10

    call GoToXY

    mov eax, white
    call Random32
    call SetTextColor

    lea edx, lastname_
    call WriteString

    mov dh, 4
    mov dl, 10

    call GoToXY

    mov eax, white
    call Random32
    call SetTextColor

    lea edx, group_
    call WriteString


    mov eax, white
    call SetTextColor

    jmp infloop

exit
END START
_TEXT ENDS