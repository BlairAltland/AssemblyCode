;Blair Altland
;CS220 FA16
;12/2/2016
;This programs takes in a user defined string and determines if said string is a palindrome.
.486
include \masm32\include\pmacros.inc

.data

inputArray db 5 dup(0)

x dd 0

outputTrue db "It is a palindrome!",0
outputFalse db "It is not a palindrome",0
output1 dd "1",0

.code
start:

    lea EBX, inputArray

    inputLoop: ;Fills an array with the characters entered by user
        get_ch
        cmp al, 10
        jz setUp
        add EBX, 1
        mov [EBX], al
        put_str output1
        jmp inputLoop
        
    setUp: ;sets EDX to the begining of the inputArray
        put_str output1
        lea EDX, inputArray
        jmp compare
        
    compare: ;Walks from the begining and end of the array comparing the two values
       
        cmp EBX, EDX ;compare both registers
        je isPalindrome ;if no more chars left, break, its a palindrome

        mov ECX, [EDX]
        cmp [EBX], ECX
        jne isNotPalindrome ;if not equal, break out, not a palindrome

        sub EBX, 1 ;move back to next memory location
        add EDX, 1 ;move forward to next memory location
        jmp compare


    isPalindrome:
        put_str outputTrue
        exit

    isNotPalindrome:
        put_str outputFalse
        exit

end start   
