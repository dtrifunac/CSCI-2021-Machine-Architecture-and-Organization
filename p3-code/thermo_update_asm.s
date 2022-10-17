### Begin with functions/executable code in the assmebly file via '.text' directive
.text
.global  set_temp_from_ports
        
## ENTRY POINT FOR REQUIRED FUNCTION
set_temp_from_ports:
        movw  THERMO_SENSOR_PORT(%rip), %dx             #load THERMO_SENSOR_PORT to register %dx
        movb  THERMO_STATUS_PORT(%rip), %cl             #load THERMO_STATUS_PORT to %cl
        #Testing for failure case
        cmpw $0, %dx          #checks if THERMO_SENSOR_PORT < 0
        js .ERROR
        cmpw $28800, %dx      #checks if THERMO_SENSOR_PORT >28800
        jg .ERROR
        movb %cl, %r10b
        andb $4, %r10b           #checks the second bit of THERMO_SENSOR_PORT to test for failure
        jne .ERROR

        #Assign values to temp->tenths_degrees and temp->temp_mode (in Celsius)
        movq $0, %rax
        movw %dx, %ax         #save input into %rax register
        sarw  $5, %ax          #divide 
        subw $450, %ax         #subtract 450
        movw %ax, 0(%rdi)       #set temp->tenths_degrees to tenths in Celsius
        movb $1 ,2(%rdi)        # set temp->temp_mode to 1 to show Celsius
        movq $0, %rax           #set return to 0


        #Checks if temp->tenth_degrees should be rounded up
        andw $31, %dx
        cmpw $15, %dx              #checks if numerator of remainder is greater than 15    
        jle .FARCHECK              #Skips to farhenheit check if doesn't need to be rounded up
        incb 0(%rdi)               #rounds up if > 15

        

        #checks if temp should converted to Farhenheit
        .FARCHECK:
        andb $32, %cl           #checks fifth bit of THERMO_STATUS_PORT
        jnz .FAR 

        
        jmp .AFTER      #goes to return in C

        .ERROR:
                movw $0, 0(%rdi)        #set temp->tenths_degrees to 0
                movb $3 ,2(%rdi)        #set temp->temp_mode to 3
                movq $1, %rax           #set return to 1
                jmp .AFTER

        .FAR:
                movq $0, %rdx
                movw (%rdi), %ax
                imul $9, %ax           #multiply temp->tenths_degrees in C by 9  
                cwtl
                cltq
                cqto   
                movq $5, %rcx
                idivq %rcx              #divide by 5
                add $320, %ax          #add 320

                movw %ax, 0(%rdi)       #set temp->tenths_degrees to tenths in F
                movb $2 ,2(%rdi)        #set temp->temp_mode to 2    
                movq $0, %rax           #set return to 0

        .AFTER:
                ret                     # eventually return from the function

### Change to definine semi-global variables used with the next function 
### via the '.data' directive
.data
	
array:                       # array of masks for digits on display
        .int 0b1111011
        .int 0b1001000
        .int 0b0111101
        .int 0b1101101
        .int 0b1001110
        .int 0b1100111
        .int 0b1110111
        .int 0b1001001
        .int 0b1111111
        .int 0b1101111


### Change back to defining functions/execurable instructions
.text
.global  set_display_from_temp

## ENTRY POINT FOR REQUIRED FUNCTION
set_display_from_temp:  
        leaq array(%rip),%r10  # load pointer to beginning array with masks
        movq %rdi, %r8
        movq %rdi, %r9
        andw $0b1111111111111111, %r9w                 #r9w = temp.tenths_degrees
        shrl $16, %r8d              #r8b = temp.temp_mode           
        
        #Test for first Error Case 
        cmpb $1, %r8b       #checks if temp is set in C
        jne .ERRORCHECK2
        cmpw $-450, %r9w     #checks if temp.tenths_degrees >= -450
        jl .ERRORCHECK2
        cmpw $450, %r9w      #checks if temp.tenths_degrees <= 450
        jg .ERRORCHECK2

        #sets digits in reverse order to minimize division
        .SETC:                          
                
                movl $1, (%rsi)         #checks for F condition
                cmpb $1, %r8b
                jne .SETF
                shll $28, (%rsi)        #set C symbol
                jmp .SETABS
        .SETF:
                shll $29, (%rsi)        #set F symbol
        .SETABS: #takes the absolute value of temp_tenths
                movq $0, %r8            #set r8 to 0 for future negativity checks
                cmpw $0, %r9w    
                jge .SETTENTHS
                imul $-1, %r9w      #multiplies by -1 if found to be negative
                movq $1, %r8            #set r8 =1 if found to be negative to check where to put negative sign  
        .SETTENTHS:
                movq $0, %rax
                movq $0, %rdx
                movw %r9w, %ax
                cwtl
                cltq
                cqto
                movq $10, %rcx           #calculate  temp.tenths_degrees)%10    
                idivq %rcx
                movl (%r10, %rdx, 4), %r11d 
        orl %r11d, (%rsi)               #set tenths place
        .SETHUNDREDS:
                movq $0, %rax
                movq $0, %rdx
                movw %r9w, %ax
                cwtl
                cltq
                cqto
                movq $1000, %rcx              
                idivq %rcx                      #calculate (temp.tenths_degrees)/1000
                cmpq $0, %rax                  #checks if there is a hundreds place
                je .SETTENS
                movl (%r10, %rax, 4), %r11d 
                sall $21, %r11d
                orl %r11d, (%rsi)               #set hundreds place
        .SETTENS:
                movw %ax, %r9w
                movw %dx, %r11w
                movq $0, %rax
                movq $0,%rdx
                movw %r11w, %ax
                cwtl
                cltq
                cqto
                movq $100, %rcx
                idivq %rcx              #calculate (temp.tenths_degrees)%1000/100
                cmpq $0, %rax           #checks if tens place is zero
                je .SETTENS2
                movl (%r10, %rax, 4), %r11d
                sall $14, %r11d
                orl %r11d, (%rsi)       #set tens place
                cmpq $0, %r8           #checks for negative sign in the hundreds place
                jne .SETNEGHUND
                jmp .SETONES
        
        .SETTENS2:
                cmpq $0, %r8           #checks for negative sign in the tens place
                jne .SETNEGTENS
                cmpw $0, %r9w            #sets tens place to 0 if there is a hundreds place and empty tens place
                je .SETONES
                movl (%r10), %r11d
                sall $14, %r11d
                orl %r11d, (%rsi)       #set tens place to 0
                jmp .SETONES
        
        .SETNEGHUND:
                orl $8388608, (%rsi)    #set negative sign in hundreds place
                jmp .SETONES
        .SETNEGTENS:
                orl $65536, (%rsi)      #set negative sign in tens place
        .SETONES:
                movw %dx, %r11w         #save remainder from previous division
                movq $0, %rax
                movq $0,%rdx
                movw %r11w, %ax
                cwtl
                cltq
                cqto
                movq $10, %rcx
                idivq %rcx                      #calculate (temp.tenths_degrees)%100/10
                movl (%r10, %rax, 4), %r11d
                sall $7, %r11d
                orl %r11d, (%rsi)               #set ones place

        movq $0, %rax                           #set return to 0
        jmp .SETAFTER

        .ERRORCHECK2: #checks for second error case, continues to set temp if no error is found
                cmpb $2, %r8b        #checks if temp.temp_mode ==2
                jne .SETERROR
                cmpw $-490, %r9w     #checks if temp.tenths_degrees >= -490
                jl .SETERROR
                cmpw $1130, %r9w     #checks if temp.tenths_degrees <= 1130
                jg .SETERROR
                jmp .SETC

        .SETERROR:
                movl $0b000110111101111110111110000000, (%rsi)     #sets display to show ERR
                movq $1, %rax   #set return to 1

        .SETAFTER:
                ret                     # eventually return from the function

.text
.global thermo_update
        
## ENTRY POINT FOR REQUIRED FUNCTION
thermo_update:
	## assembly instructions here
        subq $40, %rsp          #allocate stack space
        movq %rsp, %rdi         #point arg1 at new space
        call set_temp_from_ports        #set temp with func call
        movl %eax, %r12d         #save return from set_temp_from_ports
        movl (%rsp), %edi       #change arg1 into a pointer
        leaq THERMO_DISPLAY_PORT(%rip), %rsi    #set arg2 to point at &THERMO_DISPLAY_PORT
        call set_display_from_temp      #set display with func call
        addl %eax, %r12d                #save total return of both funcs

        addq $40, %rsp          #deallocate stack space
        cmpl $0, %r12d          #check for failure
        jne .FAIL 
        movl $0, %eax           #set return to 0
        jmp .UPAFTER
        .FAIL:
                movl $1, %eax   #set return to 1 for failure case
        .UPAFTER:
                ret                     # eventually return from the function