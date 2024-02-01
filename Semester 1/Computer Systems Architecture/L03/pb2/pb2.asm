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
    a db 15h
    b dw 105h
    c dd 150h
    d dq 1000h
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov al, byte [a]; AL = a
        cbw; AX = a
        sub ax, word [b]; AX = a - b
        cwde; EAX = a - b
        sub eax, dword [c]; EAX = a - b - c
        push eax; SS = EAX(a - b - c)
        mov eax, 0
        mov ax, word [b]; AX = b
        cwde; EAX = b
        cdq; EDX:EAX = b 
        mov ebx, eax
        mov ecx, edx; ECX:EBX = b
        mov eax, dword [d]
        mov edx, dword [d+4]; EDX:EAX = d
        sub eax, ebx
        sbb edx, ecx; EDX:EAX = d - b
        mov ebx, eax
        mov ecx, edx; ECX:EBX = d - b
        mov eax, dword [c]; EAX = c
        cdq; EDX:EAX = c
        sub ebx, eax
        sbb ecx, edx; ECX:EBX = d - b - c
        pop eax; EAX = a - b - c
        cdq; EDX:EAX = a - b - c
        add eax, ebx
        adc edx, ecx; EDX:EAX = (a - b - c) + (d - b - c)
        mov ebx, eax
        mov ecx,0
        mov ecx, edx; ECX:EBX = (a - b - c) + (d - b - c)
        mov eax, 0
        mov al, byte [a]; AL = a
        cbw; AX = a
        cwde; EAX = a
        cdq; EDX:EAX = a
        sub eax, dword [d];
        sbb edx, dword [d+4]; EDX:EAX = a - d
        sub ebx, eax
        sbb ecx, edx; ECX:EBX = (a - b - c) + (d - b - c) - (a - d)
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
