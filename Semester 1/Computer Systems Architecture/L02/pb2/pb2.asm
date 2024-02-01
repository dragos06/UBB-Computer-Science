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
    a db 8
    b db 12
    c db 3
    d db 10
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, 2; AL = 2
        mov bl, byte [c]; BL = c
        add bl, byte [d]; BL = c + d
        mov cl, byte [a]; CL = a
        add cl, byte [b]; CL = a + b
        sub cl, byte [c]; CL = a + b - c
        sub al, bl; AL = 2 - (c + d)
        add al, cl; AL = 2 - (c + d) + (a + b - c)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
