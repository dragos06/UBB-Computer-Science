bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, scanf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a resd 1
    scanprint db "a = ", 0
    scanformat db "%d", 0
    ;a dd -854
    printformat db "a = %d (base 10), a = %x (base 16)", 0
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword scanprint
        call [printf]
        add esp, 4*1
        
        push dword a
        push dword scanformat
        call [scanf]
        add esp, 4*2
        
        push dword [a]
        push dword [a]
        push dword printformat
        call [printf]
        add esp, 4*3
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
