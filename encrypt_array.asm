;Blair Altland & Katheryn Weeden
;CS220 FA16
;11/9/2016
;This program allows a user to encrypt an entered string with an entered key.
;Program will print out the key, the string and the encrypted result
.486
include \masm32\include\sasmacros.inc

.data
;Output Strings
output1 db "Enter key: ", 0
output2 db "Enter plain text: ",0
output3 db "Encrypted: ",0

;Arrays
textArray dd 25 dup(0)
keyArray dd 25 dup(0)
sumArray dd 25 dup(0)

;Various Array Address
address dd 0
keyAddress dd 0
textAddress dd 0
sumAddress dd 0

;Values
keyValue dd 0
textValue dd 0

sum dd 0
x dd 0
textCounter dd 0
tempTextCount dd 0
keyCounter dd 0
encryptCounter dd 0


.code
start:
    put_str output1 ;Prompts user to enter encryption key
    la address, keyArray

    loadKeyArray: ;Fills an array with characters from entered key
        get_ch x
        compare x, 10
        bez loadText
        ;add to array
        iadd address, 4
        move M(address), x
        put_ch M(address)
        br loadKeyArray
       
    loadTextArray: ;Fills an array with characters from entered string
        get_ch x
        compare x, 10
        bez comparison
        ;add to array
        move M(address), x
        put_ch M(address)
        iadd address, 4
        iadd textCounter, 1
        iadd tempTextCount, 1
        br loadTextArray
        
    loadText: ;Prepares second array
        put_ch 0ah
        put_str output2
        move address, 0
        la sumAddress, sumArray
        la keyAddress, keyArray
        la textAddress, textArray
        la address, textArray
        br loadTextArray

    keyRepeater:
        ;Handles repeating the key so that the size of plain text and key are always the same
        ;If keyCounter hits 5 (size of key) then reset the keyAddress and the keyCounter
        la keyAddress, keyArray
        move keyCounter, 0
                
    comparison: ;Bulk Encryption code
        iadd sumAddress, 4
        iadd keyAddress, 4
        move keyValue, M(keyAddress) ;get value for key at address
        move textValue, M(textAddress) ;get value for plain text at address
        isub keyValue, 97
        isub textValue, 97
        move sum, keyValue
        iadd sum, textValue 
        irem sum, 26
        move M(sumAddress), sum
        iadd textAddress, 4
        iadd keyCounter, 1
        compare keyCounter, 5
        bez keyRepeater
        isub textCounter, 1
        compare textCounter, 1
        bez finished
        br comparison
    finished:
        put_ch 0ah
        put_str output3
        la sumAddress, sumArray
    encrypt: ; Print out the final encrypted string
        iadd sumAddress, 4
        iadd M(sumAddress), 97
        put_ch M(sumAddress)
        iadd encryptCounter, 1
        compare encryptCounter, tempTextCount
        bez done
        br encrypt
    done:
    exit
end start
