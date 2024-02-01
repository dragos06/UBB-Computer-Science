bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fclose, scanf, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    file_name db "keyboard_to_file.txt", 0
    access_mode db "w", 0
    file_descriptor dd -1
    scanformat db "%d", 0
    number resd 1
    file_format db "%d ", 0
    
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        
    first_loop:
        push dword number
        push dword scanformat
        call [scanf]
        add esp, 4*2
        
        cmp dword [number], dword 0
        je file_close 
        
        push dword [number]
        push dword file_format
        push dword [file_descriptor]
        call [fprintf]
        add esp, 4*3
        
        jmp first_loop
        
    file_close:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4*1
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
