.486
include \masm32\include\sasmacros.inc

.data
numXs dd 3 

.code
start:
main: compare numXs, 0
      bez done
      isub numXs,1
      put_ch 'X'
      br main
     
done:
    exit
end start