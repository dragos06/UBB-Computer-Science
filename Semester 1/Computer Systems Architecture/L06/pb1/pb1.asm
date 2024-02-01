bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    A dd 12345678h, 3456ABCDh, 0CDAB4344h
    lenA equ ($-A)/4
    B1 times lenA db 0
    lenB1 equ $-B1
    B2 times lenA db 0
    lenB2 equ $-B2
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov esi, A
        mov edi, B1
        cld
        mov ecx, lenB1
        jecxz ending1
        first_loop:
            lodsb; AL = ESI, ESI = ESI + 1 , AL = 78h
            stosb; B1 = 78h
            add esi, 3
            loop first_loop
        ending1:
        mov esi, A
        add esi, 3
        mov edi, B2
        cld
        mov ecx, lenB2
        jecxz ending2
        second_loop:
            lodsb; AL = ESI, ESI = ESI + 1, AL = 12h
            stosb; B2 = 12h
            add esi, 3
            loop second_loop
        ending2:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
