#!/bin/env python3
def hex2(x,l=2,j=False):x=hex(x)[2:][-l:];return("0x"*j)+("0"*(l-len(x)))+x.upper()
def strip(x): return x.rstrip(' ').replace('[','').replace(']','').replace('#','').replace('/','')
a,e,c=0,[
 [ 32*1024*1024-512*1024    ,"VRAM    "],
 [              128*1024    ,"VSTACK#0"],
 [              128*1024    ,"VSTACK#1"],
 [              128*1024    ,"VSTACK#2"],
 [              128*1024    ,"VSTACK#3"],
 [ 32*1024*1024             ,"VRAMEXT "],
],[
 [  8*1024*1024             ,"ROM[0]  "],
 [  8*1024*1024             ,"ROM[1]  "],
 [  8*1024*1024             ,"SAV     "],
 [ 64*1024*1024-256*1024-512,"WRAM    "],
 [              128*1024    ,"STACK#0 "],
 [              128*1024    ,"STACK#1 "],
 [                       512,"I/O     "],
 [ 64*1024*1024             ,"SRAMEXT "],
]; c=(e if input("Is this for the whole system? [Y/n]: ").lower()=="n"else c+e); print(f"\n####################################################\n## {'TGR VIDEO MEMORY MAP 'if'vram'==strip(c[0][1]).lower()else'TGR MEMORY MAP ######'}############################")
for i in range(len(c)):
 b,d = (c[i][0],"BY") if c[i][0]<1024 else (c[i][0]/1024,"KB") if c[i][0]<1024*1024 else (c[i][0]/1024/1024,"MB"); b = str(round(b*10)/10); b=b[:-2]if b.endswith(".0")else b
 print(f"# {c[i][1]} ${hex2(c[i][0],7)} [${hex2(a,7)} - ${hex2(a+c[i][0]-1,7)}] {' '*(3-(b.find('.')if'.'in b else len(b)))+b+' '*((b[::-1].find('.')if'.'in b else 3))}{d} #"); c[i].append([a,c[i][0]]); a+=c[i][0]
print(end='\n'+''.join([f"#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_{strip(i[1])}"+' '*(32-len(f"#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_{strip(i[1])}"))+hex2(i[2][0],7,1)+f"\n#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_{strip(i[1])}_SIZE"+' '*(32-len(f"#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_{strip(i[1])}_SIZE"))+hex2(i[2][1],7,1)+"\n" for i in c])+f"#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_TOTAL"+' '*(32-len(f"#define TGR_{'VMEM'if'vram'==strip(c[0][1]).lower()else'MEM'}_TOTAL"))+hex2(a,7,1)+"\n"if input(f"## {' '*(3-len(str(round(a/1024/1024*10000)//10000)))}{round(a/1024/1024*10000)//10000} MB [0x{hex2(a,7)}] ##############################\n####################################################\n#### ROM can be up to 16 MB split into 2 Banks! ####\n## exROM can be up to 128 MB split into 16 Banks! ##\n####################################################\n\nExport as C Defines? [y/N]: ").lower()=="y"else"")