bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
extern printf
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    
    mesaj db "Numar: %d", 0
    numar dd 44
    numar2 dd 59
    rez dd 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov eax, [numar]
        mov ebx, [numar2]
        add eax, ebx
        mov [rez], eax
        ; exit(0)
        push dword [rez]
        push    mesaj      ; push the parameter for exit onto the stack
        call    [printf]       ; call exit to terminate the program
        add esp, 4*2
        push dword 0
        call [exit]
