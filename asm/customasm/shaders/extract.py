#!/bin/env python3
import sys
CPLength, PtrLenth, OAMObjects, Str, l = 0x5A0, 40, 13*0xFFFF, [""], 0
ProgramAddr = CPLength+PtrLenth+OAMObjects
def hex2(x,l=2,j=False):x=hex(x)[2:][-l:];return("0x"*j)+("0"*(l-len(x)))+x.upper()
if len(sys.argv)>2:
 with open(sys.argv[2],"w") as outfile:
  infile, name = open(sys.argv[1],"rb").read()[ProgramAddr+1:], sys.argv[2].split('\\'if sys.platform=="nt"else"/")[-1].split(".")[0]
  for j,i in enumerate(infile):
   Str[-1]+="0x"+hex2(i)+"@"
   if j%513==512:
    Str[-1] = Str[-1][:-1]
    Str.append("")
  Str[-1] = Str[-1][:-1]
  outfile.write(''';##################################
;## Auto-generated by extract.py ##
;##################################
#include "taylor.asm"
#include "taylor_GPU.asm"
#ruledef GPU_payload {
'''+'\n'.join([f" payload_data{i} => {Str[i]}" for i in range(len(Str))])+'''
 MY_HEADER => 0`8 @ "TGR" @ 0`8 @ "'''+name+"\x00"*(16-len(name))+'''" @ "v00.00.00   "`96 @ 0xFF
}
MY_HEADER
init:
 lload A, B, payload
 lload C, D, 0x09800000+ProgramAddr ; VRAM
 lload F, G, 0 ;counter
 .payload_loop:
  rmem E, A, B
  wmem E, C, D
  cmpeqi F, 0xFFFF, 1
   addi G, 1, G
  addi F, 1, F
  cmpeqi B, 0xFFFF, 1
   addi A, 1, A
  addi B, 1, B
  cmpeqi D, 0xFFFF, 1
   addi C, 1, C
  addi D, 1, D
  cmpeqi F, '''+hex2(len(infile)&0xFFFF,4,True)+''', 3
   cmpeqi G, '''+hex2(len(infile)>>16,4,True)+''', 2
    core 2, 1, ProgramAddr ;start GPU
    jmp .while_true
  jmp .payload_loop
 .while_true:
  wait 1000000
  ;put your code here!
  halt 0
  jmp .while_true
payload:
'''+'\n'.join([f" payload_data{i}" for i in range(len(Str))]))
  print(f'File "{sys.argv[2]}" was written...')