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
    a db 0FEh
    b dw 105h
    c dd 99h
    d dq 110h
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov bl, byte [a]; BL = a
        mov bh, 0; BX = a
        add bx, word [b]; BX = a + b
        mov ecx, 0; ECX = 0
        mov cx, bx; ECX = a + b
        mov edx, 0; EDX = 0
        add ecx, dword [d]
        adc edx, dword [d+4]; EDX:ECX = a + b + d
        push edx; SS = EDX
        push ecx; SS = ECX, EDX
        mov eax, 0; EAX = 0
        mov al, byte [a]; EAX = a
        sub eax, dword [c]; EAX = a - c
        mov edx, 0; EDX:EAX = a - c
        add eax, dword [d]
        adc edx, dword [d+4]; EDX:EAX = a - c + d
        pop ebx
        pop ecx; ECX:EBX = a + b + d
        sub ebx, eax
        sub ecx, edx; ECX:EBX = (a + b + d) - (a - c + d)
        mov eax, 0; EAX = 0
        mov ax, word [b]; EAX = b
        sub eax, dword [c]; EAX = b - c
        mov edx, 0; EDX:EAX = b - c
        add ebx, eax
        adc ecx, edx; ECX:EBX = (a + b + d) - (a - c + d) + (b - c)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
