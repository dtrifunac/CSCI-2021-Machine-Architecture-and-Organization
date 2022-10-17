### coins_funcs_asm.s: Implements several functions in assembly that
### do simple arithmetic operations. The functions also operate on
### structs and pointers to structs requiring an understanding of
### how structs are handled in assmebly.

.text
.globl  set_coinsb
set_coinsb:
### args are
### %edi = int cents
### return:
### packed coins_t struct in eax
                movq $0, %r8
                cmp $0, %edi
                jl .ERROR
                cmp $99, %edi
                jg .ERROR

                movq $0,%rax
                movq $0,%rdx 
                movl %edi, %eax
                cltq
                cqto
                movq $25, %rcx
                idivq %rcx
                // movl $3, %r9d
                movb %al, %r8b

                movq %rdx, %rax
                cqto
                movq $10, %rcx
                idivq %rcx
                shll $8, %eax
                orl %eax, %r8d

                movq %rdx, %rax
                cqto
                movq $5, %rcx
                idivq %rcx
                shll $16, %eax
                orl %eax, %r8d

                shll $24, %edx
                orl %edx, %r8d

                movl %r8d, %eax

                ret
        .ERROR:
                movl $0, %eax
                movb $-1, %al
                movl $1, %r8d
                movb $-1, (%eax, %r8d, 1)
                movl $2, %r8d
                movb $-1, (%eax, %r8d, 1)
                movl $3, %r8d
                movb $-1, (%eax, %r8d, 1)
                ret


.globl  total_coinsb
total_coinsb:
### args are
### %rdi coin_t * struct pointer 
        movl $0, %eax
        movq $0, %r9
        movb (%rdi), %r9b
        imulq $25, %r9
        addq %r9, %rax
        movq $0, %r9

        movb 1(%rdi), %r9b
        imulq $10, %r9
        addq %r9, %rax
        movq $0, %r9

        movb 2(%rdi), %r9b
        imulq $5, %r9
        addq %r9, %rax
        movq $0, %r9

        addb 3(%rdi), %al


        // movb 2(%rdi), %r9b
        // imulb $10, %r9b
        // addb %r9b, %al
        // shlb $8, %al




        
        // addb (%rdi), %al
        // imulb $5, 1(%rdi)
        // addb 1(%rdi), %al
        // imulb $10, 2(%rdi)
        // addb 2(%rdi), %al
        // imulb $25, 3(%rdi)
        // addb 3(%rdi), %al
        ret
