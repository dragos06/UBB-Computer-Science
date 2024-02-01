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
    a db 5
    b db 3
    c db 2
    d dw 260
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ax, word [d]; AX = d
        div byte [b]; AL = d(AX) / b
        add al, byte [b]; AL = b + d / b
        add al, byte [c]; AL = b + c + d / b
        mul byte [a]; AX = a * [b + c + d / b]
        add ax, word [d]; AX = a * [b + c + d / b] + d
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
