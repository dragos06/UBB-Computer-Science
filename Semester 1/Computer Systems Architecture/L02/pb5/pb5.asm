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
    a db 3
    b db 2
    c db 4
    d db 5
    e dw 260
    f dw 259
    g dw 268
    h dw 262
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, byte [a]; AL = a
        mul byte [d]; AX = a * d
        add ax, word [e]; AX = a * d + e
        mov bx, ax; BX = a * d + e
        mov ax, word [h]; AX = h
        mov cl, byte [c]; CL = c
        sub cl, byte [b]; CL = c - b
        div cl; AL = h / (c - b)
        add al, byte [c]; AL = c + h / (c - b)
        mov cl, al; CL = c + h / (c - b)
        mov ax, bx; AX = a * d + e
        div cl; AL = (a * d + e) / [c + h / (c - b)]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
