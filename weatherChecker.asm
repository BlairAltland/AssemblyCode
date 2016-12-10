;Blair Altland
;12/9/2016

;This program accepts 7 temperatures (in the form of integers) and calculates the average, highest and lowest from these values

.486
include \masm32\include\pmacros.inc

.data
temperatureWeekArray db 5 dup(0)
input dd ?
temperature dd ?
sum dd 0
average dd 0
weekDay dd 0
daysInWeek dd 7
newline	dd	0ah
prompt db 'Enter the temperatures:' , 0
averageIs db 'Average Temperature' , 0
highTempString db 'Hottest Temperature: ' , 0
coolestTempString db 'Coolest Temperature' , 0

.code
main:
    call get_temperatures

    calc_average

    calc_high

    calc_low


; Procedure GET_TEMPERATURE
; Fills an array with the entered weekday temperatures
get_temperatures:

    push EBP
    mov EBP, ESP
    push EBX ;Holds the address of the tempuerature array
    lea EBX, temperatureWeekArray
    put_str prompt

fill_array:

    get_ch, input
    cmp input, 10
    je calc_average

    add EBX, 1
    mov [EBX], input
    jmp fill_array


got_array:

    pop EBX
    mov ESP, EBP
    pop EBP

    ret

; End of GET_TEMPERATURE


; Procedure CALC_AVERAGE
; Adds all the values in the array and divides the sum by 7
calc_average:

    push EBP
    mov EBP, ESP

    push EAX
    push ECX ;holds the sum
    push EBX ;holds the address of the temperature array

    lea EBX, temperatureWeekArray
    mov [ECX], sum

add_temps:

    cmp weekDay, daysInWeek
    je divide_sum
    mov sum, [ECX]
    mov temperature, [EBX]
    add sum, temperature
    mov [ECX], sum
    add EBX, 1
    add weekDay, 1
    jmp add_temps


divide_sum:
    mov EAX, [ECX] ;move the sum into EAX --> prepare to divide
    mov [EDX], 0 ;zero out the remainder

    div daysInWeek

got_average:
    put_str averageIs
    mov average, [EAX]
    put_i average
    put_str newline			;procedure done
    pop ECX
    pop EBX
    pop EAX
    mov ESP, EBP
    pop EBP
    ret

; End of CALC_AVERAGE


; Procedure CALC_HIGH
; Compares each value in the array to see which value is the highest

calc_high:

    push EBP
    mov EBP, ESP

    push EDX ;holds element 1 to compare
    push EDI ;holds element 2 to compare

    mov weekDay, 2

    ;load the first two elements in the array
    lea EDX, temperatureWeekArray ;--> element 1
    lea EDI, temperatureWeekArray ;--> element 2
    add EDI, 4
    jmp loop


loop:
    cmp weekDay, daysInWeek
    je got_high
    cmp [EDX], [EDI]
    jl lessThan
    jmp greaterThan

lessThan: ;if EDX is less than EDI, replace EDX with EDI and get the next value in the array

    mov [EDX], [EDI]
    add EDI, 4
    add weekDay, 1
    jmp loop

greaterThan: ;if EDX is greater than EDI, store EDX and compare to the next value

    add EDI, 4
    add weekDay, 1
    jmp loop

got_high: ;Print out the high and clear the activation record

    put_str highTempString
    put_str newline

    pop EDX
    pop EDI
    mov ESP, EBP
    pop EBP
    ret

; End of CALC_HIGH


; Procedure CALC_LOW
; Compares values in the array and determines the lowest.

calc_low:

    push EBP
    mov EBP, ESP

    push EDX ;holds element 1 to compare
    push EDI ;holds element 2 to compare

    mov weekDay, 2

    ;load the first two elements in the array
    lea EDX, temperatureWeekArray ;--> element 1
    lea EDI, temperatureWeekArray ;--> element 2
    add EDI, 4
    jmp loop


loop:
    cmp weekDay, daysInWeek
    je got_low
    cmp [EDX], [EDI]
    jl lessThan
    jmp greaterThan

greaterThan: ;if EDX is greater than EDI, replace EDI with the next value in the array

    mov [EDX], [EDI]
    add EDI, 4
    add weekDay, 1
    jmp loop

lessThan: ;If EDX is less tha EDI, keep EDI to compare to the next value in the array

    add EDI, 4
    add weekDay, 1
    jmp loop

got_low: ;Print out the low and clear the activation record

    put_str coolestTempString
    put_str newline

    pop EDX
    pop EDI
    mov ESP, EBP
    pop EBP
    ret

; End of procedure CALC_LOW

end start
