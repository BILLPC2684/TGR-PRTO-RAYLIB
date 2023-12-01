#include "taylor.asm"

header0

main:
 load a,0x7F
 load e,0x096F
 load f,0xFC00
 .start:
  load b,0x0180
  load c,0x0000
 
 .loop:
  wmem a,b,c
  rmem d,b,c
  cmpeq a,d,6
   addi c,1,c
   cmpeq c,0x0000,1
    addi b,1,b
   cmpeq b,e,2
    cmpeq c,f,1
     jmp .end
  jmp .loop
  
 .end:
  cmpeq a,0x7F,2
   load a,0xFF
   jmp .start
  disp a
  hlt 0
