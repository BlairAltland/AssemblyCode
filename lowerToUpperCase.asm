.486
include \masm32\include\sasmacros.inc

.data
string db 'blank'
numChar dd 0
.code
start:
  get_str string
  ;put_str string
  isub string, 32
  put_str string
  
  
loop1:
  compare numChar, 0
  bez finished

  br loop1
finished:
  exit
end start