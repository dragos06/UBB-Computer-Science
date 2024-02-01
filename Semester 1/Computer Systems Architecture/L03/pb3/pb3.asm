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
        mov ah, 0; AX = a
        mul word [b]; DX:AX = a * b
        mov bl, 2; BL = 2
        mov bh, 0; BX = 2
        mov cx, 0; CX:BX = 2
        add ax, bx
        adc dx, cx; DX:AX = a * b + 2
        mov bl, byte [a]; BL = a
        add bl, 7; BL = a + 7
        sub bl, byte [c]; BL = a + 7 - c
        mov bh, 0; BX = a + 7 - c
        div bx; AX = (a * b + 2) / (a + 7 - c)
        mov ebx, 0
        mov bx, ax; EBX = (a * b + 2) / (a + 7 - c)
        add ebx, dword [d]; EBX = (a * b + 2) / (a + 7 - c) + d
        mov ecx, 0; ECX:EBX = (a * b + 2) / (a + 7 - c) + d
        add ebx, dword [x]
        adc ecx, dword [x+4]; ECX:EBX = (a * b + 2) / (a + 7 - c) + d + x
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
