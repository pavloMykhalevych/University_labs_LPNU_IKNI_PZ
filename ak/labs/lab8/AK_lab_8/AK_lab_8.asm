.586P

.model FLAT, STDCALL

.stack

.data

Line BYTE "Mykhalevych Pavlo   07.07.2003  Lviv  PZ-23 00"
Surname BYTE 23 DUP(?)
Name BYTE 23 DUP(?)
date BYTE 23 DUP(?)
City BYTE 23 DUP(?)
Group BYTE 23 DUP(?)

Surname_length EQU $- Surname
Name_length EQU $- Name
date_length EQU $- date
City_length EQU $- City
Group_length EQU $- Group

.code
START:


    RET

END START