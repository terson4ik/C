global _start
extern main
section     .text
_start:     mov ecx, [esp]      ; argc in ecx
            mov eax, esp
            add eax, 4          ; argv in eax

            push ecx
            push eax
            call main
            add esp, 8          ; clean the stack

            mov ebx, eax        ; now call exit
            mov eax, 1
            int 80h
