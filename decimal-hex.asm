;Blair Altland
;CS220 FA16
;Accept input Decimal Number
;Convert input value to Hexadecimal

.486
include \masm32\include\sasmacros.inc

.data
convert dd "Input decimal integer to convert: ", 0
hexidecimal dd " in hexadecimal is: ", 0
convertAgain dd "Convert another integer? (Y/N)", 0
inputNumber dd 0
output dd ?
currentValue dd ?
counter dd 0
remainder dd 0
YNCounter dd 0

.code
start:

YNLoop: ;Ask if they want to go again, if yes, jump to begining

;get_i YNCounter
;compare YNCounter, 'yes'
;bez Convert

;br YNLoop

    ;Get decimal to convert
    get_i inputNumber
    move inputNumber, currentValue



Convert:
    compareb currentValue, 16 ;
    bez True

    move currentValue, output --> this is the key
    move counter, currentValue

    compare counter, 0
    bez HexCharacters

    br Convert

True:
    isub currentValue, 16
    iadd counter, 1

    br Convert

HexCharacters:


convert10:

    currentValue = 'A'
    bez

convert11:

    currentValue = 'B'
    bez

convert12:

    currentValue = 'C'
    bez

convert13:

    currentValue = 'D'
    bez

convert14:

    currentValue = 'E'
    bez

convert15:

    currentValue = 'F'
    bez


/////


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
