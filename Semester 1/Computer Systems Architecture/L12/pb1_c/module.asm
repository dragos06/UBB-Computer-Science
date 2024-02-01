bits 32
global _interlacing

extern _printf

segment data public data use32
    print_format db "%s", 10, 13, 0
segment code public code use32
_interlacing:
        
        mov ebx, esp
        
        push ebp
        mov ebp, esp
        
        pushad
        
        ; s1 = esp + 4
        ; s2 = esp + 8
        ; s3 = esp + 12
        ; s4 = esp + 16
        ; lens = esp + 20
        
        mov ecx, [ebx+20]
        jecxz final
        mov esi, [ebx+8]
        mov edi, [ebx+12]
    first_loop_s3:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_first_loop_s3
        loop first_loop_s3
        
    end_first_loop_s3:
        
        mov ecx, [ebx+20]
        dec ecx
        jecxz final
        mov esi, [ebx+4]
        inc esi
        mov edi, [ebx+12]
        inc edi
    second_loop_s3:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_second_loop_s3
        loop second_loop_s3
    
    end_second_loop_s3:
    
    mov ecx, [ebx+20]
        jecxz final
        mov esi, [ebx+4]
        mov edi, [ebx+16]
    first_loop_s4:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_first_loop_s4
        loop first_loop_s4
        
    end_first_loop_s4:
        
        mov ecx, [ebx+20]
        dec ecx
        jecxz final
        mov esi, [ebx+8]
        inc esi
        mov edi, [ebx+16]
        inc edi
    second_loop_s4:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_second_loop_s4
        loop second_loop_s4
   
    end_second_loop_s4:
    
    popad
    
    final:
        push dword [ebx+12]
        push dword print_format
        call _printf
        add esp, 4*2
        
        push dword [ebx+16]
        push dword print_format
        call _printf
        add esp, 4*2
        
        mov esp, ebp
        pop ebp
       ret