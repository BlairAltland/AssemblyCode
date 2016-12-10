;Blair Altland
;CS220 FA16
;Program accepts two values and prints out their values, as well as the value of their multiplication
;Program parses both input values for zeros, as to prevent multiplying by zero.

.486
include \masm32\include\sasmacros.inc

.data
first dd ? ;the first number
second dd ? ; the second number
numChar dd 1
holder dd 0
ise db " equals ", 0
times db " times ", 0
zero db 'Anything multiplied by zero is zero', 0


.code
start:
  get_i first ;pull in the two values
  get_i second
  move numChar, second ;save second to loop control variable
  
 loop1:
  compare first, 0 ;if first = 0, jump to false: skip multiplication loop
  bez false
  
  compare second, 0 ;if second = 0, jump to false: skip multiplication loop
  bez false
  
  compare numChar, 0 ;if LCV is greater than 0, continue, if not, jump to true
  bez true 
  
  iadd holder, first ;add first to holder, so not to trash the value in first
  isub numChar, 1 ;subtract one from the LCV

  br loop1
  
true: ;Success: print out 'first times second = answer'
  put_i first
  put_str times
  put_i second
  put_str ise
  put_i holder
  
  br finished 
  
false: ;Failed: print 'Anything multiplied by zero equals zero'
  put_str zero 
  
  br finished
finished:
  exit
   
end start
