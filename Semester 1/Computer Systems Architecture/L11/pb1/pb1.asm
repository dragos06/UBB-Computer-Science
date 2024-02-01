bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
extern interlacing
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    s1 db "abcdef", 0
    lens equ $-s1-1
    s2 db "123456", 0
    s3 times lens+1 db 0
    s4 times lens+1 db 0
    print_format_s3 db "First string letters on even positions, second string letters on odd positions: %s", 13, 10, 0
    print_format_s4 db "First string letters on odd positions, second string letters on even positions: %s", 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword lens
        push dword s4
        push dword s3
        push dword s2
        push dword s1
        call interlacing
        
        push dword s3
        push dword print_format_s3
        call [printf]
        add esp, 4*2
 
        push dword s4
        push dword print_format_s4
        call [printf]
        add esp, 4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
