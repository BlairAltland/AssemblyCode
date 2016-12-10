.486
include \masm32\include\sasmacros.inc

.data
l dd 10
w dd 10
two dd 2
area dd 0
numChar dd 1

.code
start:
  get_i l
  get_i w
    
  move area, l
  imult area, w
  put_i area
  
  iadd l, w
  imult two, l
  put_i two
 
 loop1:
  compare numChar, 0
  bez finished

  isub numChar, 1
  
  br loop1
finished:
  exit
   
end start