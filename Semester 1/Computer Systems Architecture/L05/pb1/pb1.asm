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
    S1 db 'a', 'b', 'c', 'd', 'e', 'f'
    lenS1 equ $-S1
    S2 db '1', '2', '3', '4', '5'
    lenS2 equ $-S2
    D times (lenS1+1)/2+lenS2/2 db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov ecx, lenS2/2
        mov esi, S2
        inc esi
        mov edi, D
        jecxz ending1
        firstLoop:
            mov al, [esi]
            mov [edi], al
            add esi, 2
            inc edi
            loop firstLoop
        ending1:
        mov ecx, (lenS1+1)/2
        mov esi, S1
        jecxz ending2
        secondLoop:
            mov al, [esi]
            mov [edi], al
            add esi, 2
            inc edi
            loop secondLoop
        ending2:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program