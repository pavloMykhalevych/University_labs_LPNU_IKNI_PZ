.586P
.MODEL FLAT, STDCALL
;------------------------------------------------
_DATA SEGMENT

string db "Mykhalevych Pavlo   07.07.2003    Lviv  PZ-23 00"
string_len equ $-string

surname db 23 dup(0)
name_ db 23 dup(0)
birthday db 23 dup(0)
city db 23 dup (0)
group_ db 23 dup(0)

surname_len db 0
name_len db 0
birthday_len db 0
city_len db 0
group_len db 0

i dd 0
space db ' '
spacesCound dd 0

_DATA ENDS
_TEXT SEGMENT
START:
 lea edi, string     ; ініціалізуємо edi
 call skipSpaces     ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів

 call getWordLen     ; записуємо довжину слова в  ecx
 add surname_len, cl    ; зберігаємо довжину прізвища в surname_len

 ;копіюємо слово в surname

 mov eax, edi     ; зберігаємо попереднє значення edi перед копіюванням
 mov esi, edi
 sub esi, ecx     ; записуємо в esi початок слова
 lea edi, surname    ; зберігаємо розміщення surname
 rep movsb      ; копіюємо значення
 mov edi, eax     ; відновлюємо попереднє значення edi
 ;==================================
 call skipSpaces     ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів
 call getWordLen     ; записуємо довжину слова в  ecx
 add name_len, cl    ; зберігаємо довжину ім'я в name_len

 ;копіюємо слово в name

 mov eax, edi     ; зберігаємо попереднє значення edi перед копіюванням
 mov esi, edi
 sub esi, ecx     ; записуємо в esi початок слова
 lea edi, name_     ; зберігаємо розміщення name_
 rep movsb      ; копіюємо значення
 mov edi, eax     ; відновлюємо попереднє значення edi
 ;==================================
 call skipSpaces     ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів
 call getWordLen     ; записуємо довжину слова в ecx
 add birthday_len, cl   ; зберігаємо довжину birthday в birthday_len

 ;копіюємо слово в birthday

 mov eax, edi     ; зберігаємо попереднє значення edi перед копіюванням
 mov esi, edi
 sub esi, ecx     ; записуємо в esi початок слова
 lea edi, birthday    ; зберігаємо розміщення birthday
 rep movsb      ; копіюємо значення
 mov edi, eax     ; відновлюємо попереднє значення edi
 ;==================================
 call skipSpaces     ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів
 call getWordLen     ; записуємо довжину слова в ecx
 add city_len, cl    ; зберігаємо довжину назви місця в place_len

 ;копіюємо слово в place

 mov eax, edi      ; зберігаємо попереднє значення edi перед копіюванням
 mov esi, edi
 sub esi, ecx      ; записуємо в esi початок слова
 lea edi, city     ; зберігаємо розміщення place
 rep movsb         ; копіюємо значення
 mov edi, eax      ; відновлюємо попереднє значення edi
 ;==================================
 call skipSpaces        ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів
 call getWordLen        ; записуємо довжину слова в ecx
 add group_len, cl      ; зберігаємо довжину назви місця в group_len

 ;копіюємо слово в group_

 mov eax, edi        ; зберігаємо попереднє значення edi перед копіюванням
 mov esi, edi
 sub esi, ecx        ; записуємо в esi початок слова
 lea edi, group_     ; зберігаємо розміщення place
 rep movsb           ; копіюємо значення
 mov edi, eax        ; відновлюємо попереднє значення edi

 call skipSpaces        ; викликаємо пропуск пробілів
 add spacesCound, ecx   ; збільшуємо кількість пробілів

 jmp PROGRAM_END		; завершуємо виконання програми

 skipSpaces:
  mov ecx, string_len
  inc i
  sub ecx, i
  dec i
  mov ebx, ecx

  mov al, space
  cld
  repe scasb
  dec edi

  sub ebx, ecx
  dec ebx
  mov ecx, ebx

  add i, ebx
 ret

 getWordLen:
  mov ecx, string_len
  inc i
  sub ecx, i
  dec i
  mov ebx, ecx

  mov al, space
  cld
  repne scasb
  dec edi

  sub ebx, ecx
  dec ebx
  mov ecx, ebx

  add i, ebx
 ret

PROGRAM_END:
RET
_TEXT ENDS
END START