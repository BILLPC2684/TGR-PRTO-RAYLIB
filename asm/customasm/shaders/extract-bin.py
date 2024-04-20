#!/bin/env python3
import sys
CPLength, PtrLenth, OAMObjects = 0x5A0, 40, 11*0xFFFF
ProgramAddr = CPLength+PtrLenth+OAMObjects
def hex2(x,l=2,j=False):x=hex(x)[2:][-l:];return("0x"*j)+("0"*(l-len(x)))+x.upper()
if len(sys.argv)>1:
 with open(sys.argv[1].split('.')[0]+"-cropped.bin","wb") as outfile:
  infile = open(sys.argv[1],"rb").read()[ProgramAddr+1:]
  for i in infile: print(end="\\x"+hex2(i))
  print(f"\n{outfile.write(infile)}")
