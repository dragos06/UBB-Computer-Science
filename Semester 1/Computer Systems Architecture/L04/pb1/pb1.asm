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
    a dw 0100110010110110b
    b dw 1101110000111111b
    c dd 00000000h
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, word [a]
        shl ax, 7
        and ax, 0000001110000000b
        mov bx, word [b]
        shl bx, 2
        and bx, 1111110000000000b
        and ax, 0000001111111111b
        or ax, bx
        and ax, 1111111110000000b
        movzx eax, ax
        or eax, 0FFFF0000h
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
