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
    a db 5h
    b dw 100h
    c db 8h
    d dd 200h
    x dq 500h
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, byte [a]; AL = a
        cbw; AX = a
        imul word [b]; DX:AX = a * b
        mov bx, ax
        mov cx, dx; CX:BX = a * b
        mov eax, 0
        mov edx, 0
        mov al, 2; AL = 2
        cbw; AX = 2
        cwd; DX:AX = 2
        add bx, ax
        adc cx, dx; CX:BX = a * b + 2
        mov al, byte [a]; AL = a
        add al, 7; AL = a + 7
        sub al, byte [c]; AL = a + 7 - c
        cbw; AX = a + 7 - c
        push ax; SS = AX(a+7-c)
        mov ax, bx
        mov dx, cx; DX:AX = a * b + 2
        pop bx; BX = a + 7 - c
        idiv bx; AX = (a * b + 2) / (a + 7 - c)
        cwde; EAX = (a * b + 2) / (a + 7 - c)
        add eax, dword [d]; EAX = (a * b + 2) / (a + 7 - c) + d
        cdq; EDX:EAX = (a * b + 2) / (a + 7 - c) + d
        add eax, dword [x]
        adc edx, dword [x+4]; EDX:EAX = (a * b + 2) / (a + 7 - c) + d + x
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
