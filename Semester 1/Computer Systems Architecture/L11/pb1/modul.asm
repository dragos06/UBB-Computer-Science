bits 32
global interlacing
segment code use32 public code

interlacing:
        ; s1 = esp + 4
        ; s2 = esp + 8
        ; s3 = esp + 12
        ; s4 = esp + 16
        ; lens = esp + 20
        mov ecx, [esp+20]
        jecxz final
        mov esi, [esp+8]
        mov edi, [esp+12]
    first_loop_s3:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_first_loop_s3
        loop first_loop_s3
        
    end_first_loop_s3:
        
        mov ecx, [esp+20]
        jecxz final
        mov esi, [esp+4]
        inc esi
        mov edi, [esp+12]
        inc edi
    second_loop_s3:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_second_loop_s3
        loop second_loop_s3
    
    end_second_loop_s3:
    
    mov ecx, [esp+20]
        jecxz final
        mov esi, [esp+4]
        mov edi, [esp+16]
    first_loop_s4:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_first_loop_s4
        loop first_loop_s4
        
    end_first_loop_s4:
        
        mov ecx, [esp+20]
        jecxz final
        mov esi, [esp+8]
        inc esi
        mov edi, [esp+16]
        inc edi
    second_loop_s4:
        movsb
        inc esi
        inc edi
        dec ecx
        jecxz end_second_loop_s4
        loop second_loop_s4
   
    end_second_loop_s4:
    
    final:
        ret 4*5
   