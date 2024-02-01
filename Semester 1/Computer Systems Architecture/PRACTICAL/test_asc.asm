bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf, fopen, fclose, fprintf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    access_mode db 'w', 0
    string_format db '%s', 0
    number_format db '%d', 0
    number_print_format db '%d',10, 0
    file_name dd 0, 0
    file_descriptor dd -1
    number dd 0
    ten dd 10
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword file_name
        push dword string_format
        call [scanf]
        add esp, 4*2
        
        
        push dword number
        push dword number_format
        call [scanf]
        add esp, 4*2
        
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4*2
        mov [file_descriptor], eax
        
        cmp eax, 0
        je final
        
        
        mov eax, 0
        mov edx, 0
        bucla:
            mov ax, [number]
            mov dx, [number+2]
            idiv dword [ten]; DX = last digit, AX = remaining digits
            
            push eax
            push edx
           
            
            test DX, 1
            jnz continue_bucla
            
            push dword edx
            push dword number_print_format
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4*3
            
            
            pop edx
            pop eax
            
            continue_bucla:
            
            mov [number], ax
            cmp ax, 0
            jne bucla
        
        
        push dword[file_descriptor]
        call [fclose]
        add esp, 4
        final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
