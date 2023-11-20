#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <raylib.h>
#ifdef _WIN32
// #include<winsock2.h>
// #include<windows.h>
// void usleep(__int64 usec) {
//  HANDLE timer; LARGE_INTEGER ft; 
//  ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time
//  timer = CreateWaitableTimer(NULL, TRUE, NULL); 
//  SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
//  WaitForSingleObject(timer, INFINITE); 
//  CloseHandle(timer); 
// }
#else
 #include<unistd.h>
 #include<sys/un.h>
 #include<sys/socket.h>
#endif

void ResetCore(bool ID);
void CPUCore(bool ID);
void LoadPage(bool PID, uint8_t BID);

uint8_t* concat(const uint8_t *s1, const uint8_t *s2) {
 const size_t len[2] = {strlen(s1), strlen(s2)};
 uint8_t *result = malloc(len[0]+len[1]+1);//+1 for the null-terminator
 //in real code you would check for errors in malloc here
 memcpy(result, s1, len[0]);
 memcpy(result+len[0], s2, len[1]+1);//+1 to copy the null-terminator
 return result;
}

void bin_dump(uint64_t u) { uint8_t i=63; while (i-->0) { printf("%hhu",(u&(uint64_t)pow(2,i))?1:0); } printf("\n"); }

uint8_t *ascii127 = "................................ !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.......................................................................................................................................................";
void dumpData(uint8_t *name, uint8_t *data, uint32_t size, uint32_t start, uint32_t end) {
 uint8_t bytes[16]; int i,k,j=1,l=0,m=0;
 printf("._______._______________________________________________.________________.\n|%s",name);
 for(i=0;i<7-strlen(name);i++) { printf(" "); }
 printf("|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F|0123456789ABCDEF|\n|-------|-----------------------------------------------|----------------|\n|%07X|",start);
 for (i=start;i<start+end;i++) {
  if (i >= start+size) { break; }
  if (j > 15) {
   bytes[j-1] = data[i];
   printf("%02X|",data[i]);
   for (k=0; k < 16; k++) {
    printf("%c",ascii127[bytes[k]]);
   } l=0,j=0;
   printf("|\n|%07X|",i+1);
  } else {
   printf("%02X ",data[i]);
   bytes[j-1] = data[i];
  } j++; l++;
 }m=i;
 if (j > 0) {
  for (i=j; i < 16; i++) {
   printf("-- ");
   bytes[j-1] = 0x00;
  } printf("--|");
  for (i=0; i < l-1; i++) {
   printf("%c",ascii127[bytes[i]]);
  }
  if(m<16) { printf("%c",ascii127[bytes[m-1]]); }
  for (i=j; i < 16; i++) {
   printf(" ");
  } printf(" |\n");
 } printf("|_______|_______________________________________________|________________|\n\\Size: 0x%x/%d Bytes(",size,size);
 if (size < 1024) { printf("%0.2f KB)\n",size/1024.0f); } else { printf("%0.2f MB)\n",(float)size/1024.0f/1024.0f); }
}
void crop(uint8_t *dst, uint8_t *src, size_t mn, size_t mx) {
 const int len=mx-mn; src+=mn;
 for (int i=0; i<len; i++) { dst[i]=src[i]; }
 dst[len]='\0';
}

FILE *BIOSfp,*ROMfp,*SAVfp,Statefp;

void FlushSAV() {
 printf("FlushSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n", sys.LoadFailed?"True":"False", sys.EXTSAV?"True":"False", strlen(sys.SN), (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False");
 if (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  printf("FlushSAV!!\n");
  SAVfp = fopen(sys.SN,"wb"); fwrite(&sys.MEM[0x1000000], 1, SIZ8MB, SAVfp);
  fflush(SAVfp); fclose(SAVfp);
}}
void WriteSAV(uint32_t Address, uint8_t Data) {
 printf("WriteSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n", sys.LoadFailed?"True":"False", sys.EXTSAV?"True":"False", strlen(sys.SN), (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False");
 if (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  printf("WriteSAV!!\n");
  SAVfp = fopen(sys.SN,"wb"); fseek(Address, SAVfp, SEEK_SET);
  fwrite(Data, 1, 1, SAVfp); fflush(SAVfp); fclose(SAVfp);
}}
void LoadSAV() {
 printf("LoadSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n", sys.LoadFailed?"True":"False", sys.EXTSAV?"True":"False", strlen(sys.SN), (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False");
 if (!sys.LoadFailed && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  printf("LoadSAV!!\n");
  if ((SAVfp = fopen(sys.SN,"rb")) != NULL) { fread(&sys.MEM[0x1000000], 1, SIZ8MB, SAVfp); fclose(SAVfp); }
  FlushSAV();
}}

int8_t LoadCart() {
 sys.LoadFailed = true;
 if ((ROMfp = fopen(sys.RN,"rb")) == NULL) { printf("[EMU Error] failed to access ROM file\n"); return -1; }
 for(uint8_t i=0;i<32;i++){ if(feof(ROMfp)){break;} fread(&sys.ROMBANK[i], SIZ8MB, 1, ROMfp); }
 if(!(sys.ROMBANK[0][1]=='T' && sys.ROMBANK[0][2]=='G' && sys.ROMBANK[0][3]=='R')) {
  sys.ErrorType = 1; sprintf(sys.Error,"Bad Header(\"%c%c%c\") in ROM file\n",ascii127[sys.ROMBANK[0][1]],ascii127[sys.ROMBANK[0][2]],ascii127[sys.ROMBANK[0][3]]);
  for(uint8_t i=0;i<32;i++){ memset(sys.ROMBANK[i],0x7F,SIZ8MB); } return -1;
 }
 fclose(ROMfp);
 sys.LoadFailed = false;
 if (!sys.EXTSAV) {
  uint8_t i=0;
  do{ if(sys.RN[strlen(sys.RN)-i] == '.') { break; } }while(++i);
  memcpy(sys.SN, sys.RN, strlen(sys.RN)-i+1); sys.SN[strlen(sys.RN)+1] = '\x00'; strcat(sys.SN, "sav");
  printf("Selected SAV file: %s\n",sys.SN);
  LoadSAV();
 } return 0;
}

void PrintError() {
 if((strlen(sys.Error)>0) && (sys.ErrorType<3)) {
  uint8_t msg[1024] = {0};
  for(int i=0;i<1024;i++) { errorbuf[i] = 0; }
  printf(msg,"[EMU %s] %s\n",ErrorTexts[sys.ErrorType],sys.Error);
  sys.ErrorType = 3;
}}

void PrintHeader() {
 printf("Header: \""); for(uint8_t i=0;i<5;i++){printf("%c",ascii127[sys.MEM[i]]);}
 printf("\"\nTitle: \""); for(uint8_t i=0;i<16;i++){printf("%c",ascii127[sys.MEM[0x05+i]]);}
 printf("\"\nversion: \""); for(uint8_t i=0;i<12;i++){printf("%c",ascii127[sys.MEM[0x15+i]]);}
 if (sys.MEM[0]>0) { printf("\"\nAuthor: \""); for(uint8_t i=0;i<32;i++){printf("%c",ascii127[sys.MEM[0x21+i]]);} }
 if (sys.MEM[0]>1) { printf("\"\nCheckSum: \""); for(uint8_t i=0;i<32;i++){printf("%c",ascii127[sys.MEM[0x41+i]]);} }
 printf("\"\n");
}

void Clock();
void GPUMain();
int CARTINIT();

void CPU_init() { //############################################//
 sys.SilentRun = false;
 printf("Initalizing Taylor v0.30 Alpha Build\n");
 sys.Debug = false; //debug mode
 sys.blockDisp = true; //block DISP instuction messages
 
 printf("\\Initialize Memory...\n");
 if((sys.MEM = malloc(0xD800000)) == NULL) { printf("[EMU Fatal] Memory allocation failed.\n"); return -1;}
 memset(sys.MEM, 0, 0xD800000);
 sys.Clock = 0;
 sys.EXTSAV = false;
 sys.HeaderSize = 0;
 sys.LoadFailed = true;
 sys.REG = "ABCDEFGH________";
 sys.Error = malloc(1024);
 sys.BN = malloc(1024); sys.RN = malloc(1024); sys.SN = malloc(1024);
 for(uint8_t i=0;i<33;i++){ memset(sys.ROMBANK[i], 0x7F, SIZ8MB); }
 pthread_t call_Core0; pthread_create(&call_Core0, NULL, CPUCore, 0);
 pthread_t call_Core1; pthread_create(&call_Core1, NULL, CPUCore, 1);
 pthread_t call_Clock; pthread_create(&call_Clock, NULL, Clock, NULL);
 pthread_t call_GPU;   pthread_create(&call_GPU,   NULL, GPUMain, NULL);
 
 for(int i=0x9800000;i<2+(0xFFFF*11);i++){sys.MEM[i]=0;}
 GPU_RESET();
 GPU.running=false;
 printf("|\\0x%07X\\%10d\tBytes(%10.2f MB)\tof RAM were allocated...\n"
        "|\\0x%07X\\%10d\tBytes(%10.2f MB)\tof VideoRAM was allocated...\n",
 RAMSIZ, RAMSIZ, RAMSIZ/1024.0f/1024.0f,  VRAMSIZ, VRAMSIZ, VRAMSIZ/1024.0f/1024.0f);
 printf("Initalization Finished!")
}

void CPU_silent(int silent) { sys.SilentRun = silent; }
void CPU_extsav(uint8_t recvbuf[]) {
 sys.SN = malloc(1024);
 strcpy(sys.SN, &recvbuf[6]); printf("\nEXTSAV Selected: %s\n",&recvbuf);
 sys.EXTSAV = true; LoadSAV();
}
void CPU_load(uint8_t recvbuf[]) {
 CPU[0].running=false; CPU[1].running=false; GPU.running=false; WaitTime(0.001);
 WaitTime(0.001); sys.RN = malloc(1024); sys.SN = malloc(1024);
 strcpy(sys.RN, &recvbuf[4]); printf("\nROM Selected: %s\n",&recvbuf); sys.EXTSAV = false;
 if(LoadCart()<0) { sys.ErrorType = 1; sprintf(sys.Error,"%sFailed to load ROM: \"%s\"...",sys.Error,sys.RN); PrintError(); }
 else { sys.HeaderSize = CARTINIT(); }
}
void CPU_start() {
 if (!sys.LoadFailed && !CPU[0].running && !CPU[1].running) {
  if (sys.EXTSAV && strlen(sys.SN)==0) {
   sys.ErrorType = 1; sprintf(sys.Error,"External SAV File not given!!"); PrintError();
  } else {
   ResetCore(0); ResetCore(1); LoadPage(0,0); LoadPage(1,1); CPU[0].running=true;
   dumpData("ROM#0", &sys.MEM[0x0000000], 0x0800000, 0, 256);
   dumpData("ROM#1", &sys.MEM[0x0800000], 0x0800000, 0, 256);
  }
 }
}
void CPU_reset(int hard) {
 if (!sys.LoadFailed) {
  printf("%sReset...",hard>0?"":"Hard ");
  CPU[0].running=false; CPU[1].running=false; GPU.running=false; WaitTime(0.001);
  if (hard>0) { memset(sys.MEM, 0, 0xD800000); }
  ResetCore(0); ResetCore(1); LoadPage(1,1); CPU[0].running=true;
 }
}
void CPU_stop() { FlushSAV(); CPU[0].running=false; CPU[1].running=false; GPU.running=false; memset(sys.MEM, 0, 0xD800000); }
void CPU_debug(int state) { sys.Debug=state; }
void CPU_pause(int state) { sys.Pause=state; }
void CPU_state(int type) { printf("%s SAVESTATE\nWIP!!!\n",type==0?"Loading":"Saving"); }
void CPU_memdump(uint8_t recvbuf[], uint8_t* sendbuf[]) {  }

int CARTINIT() { LoadPage(0,0);
 switch(sys.MEM[0]) {
  case 0x00:
   //TGRHeader[5]+Title[16]+version[12]
   return 5+16+12+1;
  case 0x01:
   //TGRHeader[5]+Title[16]+version[12]+Author[32]
   return 5+16+12+32+1;
  case 0x02:
   //TGRHeader[5]+Title[16]+version[12]+Author[32]+CheckSum[32]
   return 5+16+12+32+32+1;
 }
}

uint64_t zeroup(int64_t x) { return (x>=0)?x:0; }

void ResetCore(bool ID) {
 for(uint8_t i=0;i<8;i++){CPU[ID].REGs[i]=0; CPU[ID].flag[i]=false;}
 CPU[ID].running=false; CPU[ID].ticked=false;
 sys.Pause=false; CPU[ID].IP=sys.HeaderSize;
 CPU[ID].SP=(ID==0)?0x97FFDFF:0x97DFDFF;
 CPU[ID].BP=(ID==0)?0x97DFE00:0x97BFE00;
 CPU[ID].MP=CPU[ID].SP; CPU[ID].Clock = 0;
 CPU[ID].IPS=0; CPU[ID].TI=0; CPU[ID].time=0;
}

void LoadPage(bool PID, uint8_t BID) {
 sys.PageID[PID]=BID%0x21;
 memcpy(&sys.MEM[PID*SIZ8MB], &sys.ROMBANK[BID%0x21], SIZ8MB);
}

void Clock() {
 uint32_t i=0;
 sys.MemUse=0;
 while(true) {
  WaitTime(0.001);
  if(++i%1000){ //1000 McS = 1 MS
   sys.Clock++;
   if (!sys.Pause) { CPU[0].running?CPU[0].Clock++:0; CPU[1].running?CPU[1].Clock++:0; }
  }
  if((sys.Clock%1000)==0){
   sys.IPS[0] = CPU[0].IPS, sys.IPS[1] = CPU[1].IPS;
   sys.FPS = GPU.frames; GPU.frames = 0;
   printf("\nFPS: %d | GPU.Running:%s\nInstuctionsPerSecond: %8ld|%8ld (%8ld) -> %.4f%%\n\\                     24000000|24000000 (48000000) -> 100.0000%%\n\\TotalRan: %ld|%ld (%ld)\n\n",sys.FPS,GPU.running?"True":"False", CPU[0].IPS, CPU[1].IPS, CPU[0].IPS+CPU[1].IPS, (((sys.IPS[0]+sys.IPS[1])/(float)(CPU[0].running+CPU[1].running))/24000000.0f)*100, CPU[0].TI,CPU[1].TI,CPU[0].TI+CPU[1].TI);
   CPU[0].ticked=1; CPU[1].ticked=1;
   for(uint32_t i=0;i<0x8000000;i++) { sys.MemUse +=sys.MEM[0x1800000+i]/255.0f; }
   sys.MemUse = 99.95;
   memcpy(&membuf[sendptr_MemUse], (uint8_t*) (&sys.MemUse), 4); sys.MemUse=0;
   for(uint32_t i=0;i<0x4000000;i++) { sys.MemUse+=sys.MEM[0x9800000+i]/255.0f; }
   memcpy(&membuf[sendptr_VMemUse],(uint8_t*) (&sys.MemUse), 4); sys.MemUse=0;
}}}

void CPUCore(bool ID) {
 uint8_t msg[1024]={0};
 uint16_t dslp = 0;
 uint32_t i=0,j=0;
 while(true) {
  if(CPU[ID].running && !sys.Pause) {
   #ifdef _WIN32
    clock_gettime(CLOCK_MONOTONIC, &start);
   #else
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
   #endif
   for(j=0;j<23530;j++) { CPU[ID].IP=CPU[ID].IP%0xD800000;
    if(!CPU[ID].running) { break; }
    if(CPU[ID].ticked) { CPU[ID].IPS = 0; CPU[ID].ticked = 0; }
    uint8_t A   =      sys.MEM[CPU[ID].IP+1] >> 4 ;       //4 \.
    uint8_t B   =      sys.MEM[CPU[ID].IP+1] & 0xF;       //4 |-> A/B/C = 1.5 bytes
    uint8_t C   =      sys.MEM[CPU[ID].IP+2] >> 4 ;       //4 /'
    int32_t IMM =((((((sys.MEM[CPU[ID].IP+2] & 0xF) << 8) //4 \.
                |      sys.MEM[CPU[ID].IP+3]) << 8)       //8 |->  IMM  = 3.5 bytes
                |      sys.MEM[CPU[ID].IP+4]) << 8)       //8 |
                |      sys.MEM[CPU[ID].IP+5];             //8 /'
    if (sys.Debug == true) {
     sprintf(msg,"%s\n[Core#%x] IC: 0x%07X/%9i (Area ",msg,ID,CPU[ID].IP,CPU[ID].IP);
     if (CPU[ID].IP>=0x0000000 && CPU[ID].IP<=0x07FFFFF) { sprintf(msg,"%s0:ROM PAGE#0",msg); } else
     if (CPU[ID].IP>=0x0800000 && CPU[ID].IP<=0x0FFFFFF) { sprintf(msg,"%s1:ROM PAGE#1",msg); } else
     if (CPU[ID].IP>=0x1000000 && CPU[ID].IP<=0x17FFFFF) { sprintf(msg,"%s2:SAV data",msg); } else
     if (CPU[ID].IP>=0x1800000 && CPU[ID].IP<=0x96FFBFF) { sprintf(msg,"%s3:Work RAM",msg); } else
     if (CPU[ID].IP>=0x96FFC00 && CPU[ID].IP<=0x97FFBFF) { sprintf(msg,"%s4:Stack Memory",msg); } else
     if (CPU[ID].IP>=0x97FFC00 && CPU[ID].IP<=0x97FFFFF) { sprintf(msg,"%s5:Static Memory",msg); } else
     if (CPU[ID].IP>=0x9800000 && CPU[ID].IP<=0xD77FFFF) { sprintf(msg,"%s6:Video RAM",msg); } else
     if (CPU[ID].IP>=0xD780000 && CPU[ID].IP<=0xD7FFFFF) { sprintf(msg,"%s7:Stack VMem",msg); }
     else { sprintf(msg,"%s?:Invalid Address",msg); } sprintf(msg,"%s)\n\\ >> [",msg);
     for (i=0; i < 6; i++) { sprintf(msg,"%s0x%02X",msg,sys.MEM[CPU[ID].IP+i]); if (i < 5) { sprintf(msg,"%s, ",msg); } }
     sprintf(msg,"%s] | [A:%c, B:%c, C:%c, IMM:0x%07X]\n\\REGs: [",msg,sys.REG[A],sys.REG[B],sys.REG[C],IMM);
     for (i=0; i < 8; i++) { sprintf(msg,"%s%c:0x%04X%s",msg,sys.REG[i],CPU[ID].REGs[i],(i<7)?", ":""); }
//     sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[0],CPU[ID].REGs[0]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[1],CPU[ID].REGs[1]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[2],CPU[ID].REGs[2]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[3],CPU[ID].REGs[3]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[4],CPU[ID].REGs[4]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[5],CPU[ID].REGs[5]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[6],CPU[ID].REGs[6]); sprintf(msg,"%s%c:0x%04X"  ,msg,sys.REG[7],CPU[ID].REGs[7]);
     sprintf(msg,"%s] | TotalRan: %ld (%ld)\n\\StackPointer: 0x%x/%d | StackBase: 0x%x/%d\n\\\\StackData:[",msg,CPU[ID].TI,CPU[0].TI+CPU[1].TI,CPU[ID].SP,CPU[ID].SP,CPU[ID].BP,CPU[ID].BP);
     for (i = CPU[ID].SP+1; i <= CPU[ID].BP; ++i){
      if((i+1)%2==0) { sprintf(msg,"%s 0x",msg); }
      sprintf(msg,"%s%02X",msg,sys.MEM[i]);
      if(i%16==0 && i != 0) { sprintf(msg,"%s\n",msg); }
     } sprintf(msg,"%s]\n \\instruction: ",msg);
    }
    //Flags | WrittenREG, ReadREG, OverFlow, PointerOOB, ALUoperated, DivideBy0
//    printf("sys.MEM[CPU[ID].IP]: 0x%02X\n",sys.MEM[CPU[ID].IP]);
    switch(sys.MEM[CPU[ID].IP]) {
     case 0x00:// LOAD   |
      if (sys.Debug == true) { sprintf(msg,"%sMOV\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (C > 0) { CPU[ID].REGs[A] = CPU[ID].REGs[B]; CPU[ID].flag[1]=true; }
      else { CPU[ID].REGs[A] = IMM; } break;
     case 0x01:// ADD    |
      if (sys.Debug == true) { sprintf(msg,"%sADD\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]+IMM;             if(CPU[ID].REGs[A]+IMM            >0xFFFF){CPU[ID].flag[2]=true;}}
      else {         CPU[ID].REGs[C] = CPU[ID].REGs[A]+CPU[ID].REGs[B]; if(CPU[ID].REGs[A]+CPU[ID].REGs[B]>0xFFFF){CPU[ID].flag[2]=true;}} break;
     case 0x02:// SUB    |
      if (sys.Debug == true) { sprintf(msg,"%sSUB\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[2]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]-IMM;             if(CPU[ID].REGs[A]-IMM            <0){CPU[ID].flag[2]=false;}}
      else {         CPU[ID].REGs[C] = CPU[ID].REGs[A]-CPU[ID].REGs[B]; if(CPU[ID].REGs[A]-CPU[ID].REGs[B]<0){CPU[ID].flag[2]=false;}} break;
     case 0x03:// MUL    |
      if (sys.Debug == true) { sprintf(msg,"%sMUL\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]*IMM;             if(CPU[ID].REGs[A]*IMM            >0xFFFF){CPU[ID].flag[2]=true;}}
      else {         CPU[ID].REGs[C] = CPU[ID].REGs[A]*CPU[ID].REGs[B]; if(CPU[ID].REGs[A]*CPU[ID].REGs[B]>0xFFFF){CPU[ID].flag[2]=true;}} break;
     case 0x04:// DIV    |
      if (sys.Debug == true) { sprintf(msg,"%sDIV\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[2]=true; CPU[ID].flag[4]=true;
      if (CPU[ID].REGs[A]==0) {CPU[ID].REGs[C] = 0; CPU[ID].flag[5]=true; break;}
      if (IMM >= 1) { CPU[ID].REGs[C] = CPU[ID].REGs[A]/IMM;             if(CPU[ID].REGs[A]%IMM            >0){CPU[ID].flag[2]=false;}}
      else {          CPU[ID].REGs[C] = CPU[ID].REGs[A]/CPU[ID].REGs[B]; if(CPU[ID].REGs[A]%CPU[ID].REGs[B]>0){CPU[ID].flag[2]=false;}} break;
     case 0x05:// MOD    |
      if (sys.Debug == true) { sprintf(msg,"%sMOD\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (CPU[ID].REGs[A]==0) {CPU[ID].REGs[C] = 0; CPU[ID].flag[5]=true; break;}
      if (IMM >= 1) { CPU[ID].REGs[C] = CPU[ID].REGs[A]%IMM;             }
      else {          CPU[ID].REGs[C] = CPU[ID].REGs[A]%CPU[ID].REGs[B]; } break;
     case 0x06:// AND    |
      if (sys.Debug == true) { sprintf(msg,"%sAND\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]&IMM; }else{ CPU[ID].REGs[C] = CPU[ID].REGs[A]&CPU[ID].REGs[B]; } break;
     case 0x07:// OR     |
      if (sys.Debug == true) { sprintf(msg,"%sOR\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]|IMM; }else{ CPU[ID].REGs[C] = CPU[ID].REGs[A]|CPU[ID].REGs[B]; } break;
     case 0x08:// XOR    |
      if (sys.Debug == true) { sprintf(msg,"%sXOR\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]^IMM; }else{ CPU[ID].REGs[C] = CPU[ID].REGs[A]^CPU[ID].REGs[B]; } break;
     case 0x09:// BSL    |
      if (sys.Debug == true) { sprintf(msg,"%sBSL\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]<<IMM;             if(CPU[ID].REGs[A]<<IMM            >0xFFFF){CPU[ID].flag[2]=true;}}
      else {         CPU[ID].REGs[C] = CPU[ID].REGs[A]<<CPU[ID].REGs[B]; if(CPU[ID].REGs[A]<<CPU[ID].REGs[B]>0xFFFF){CPU[ID].flag[2]=true;}} break;
     case 0x0A:// BSR    |
      if (sys.Debug == true) { sprintf(msg,"%sBSR\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[2]=true; CPU[ID].flag[4]=true;
      if (IMM > 0) { CPU[ID].REGs[C] = CPU[ID].REGs[A]>>IMM;             if(CPU[ID].REGs[A]>>IMM            <0){CPU[ID].flag[2]=false;}}
      else {         CPU[ID].REGs[C] = CPU[ID].REGs[A]>>CPU[ID].REGs[B]; if(CPU[ID].REGs[A]>>CPU[ID].REGs[B]<0){CPU[ID].flag[2]=false;}} break;
     case 0x0B:// NOT    |
      if (sys.Debug == true) { sprintf(msg,"%sNOT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      CPU[ID].REGs[A] = ~CPU[ID].REGs[A]; break;
     case 0x0C:// flag  |
      if (sys.Debug == true) { sprintf(msg,"%sFLAG\n",msg); } CPU[ID].REGs[A] = 0;
      for(i=0;i<8;i++) {CPU[ID].REGs[A]+=pow(2,i)*CPU[ID].flag[i]; if(sys.Debug==true){printf("CPU[ID].flag[%d]: %s\n",i,(CPU[ID].flag[i])?"true":"false");} CPU[ID].flag[i]=false;} CPU[ID].flag[0]=true; break;
     case 0x0D:// JMP    |
      if (sys.Debug == true) { sprintf(msg,"%sJUMP\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if (C >= 1) { CPU[ID].IP = (CPU[ID].REGs[A]<<16|CPU[ID].REGs[B])-6; CPU[ID].flag[1]=true; }else{ CPU[ID].IP = IMM-6; } break;
     case 0x0E:// CMPEQ  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP=\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM>0) {  if (CPU[ID].REGs[A] != IMM) { CPU[ID].IP += ((C>0)?C:1)*6; }
      }else if(CPU[ID].REGs[A] != CPU[ID].REGs[B]) { CPU[ID].IP += ((C>0)?C:1)*6; } break;
     case 0x0F:// CMPLT  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP<\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM>0) { if (!(CPU[ID].REGs[A] <  IMM)) { CPU[ID].IP += ((C>0)?C:1)*6; }
      }else if(!(CPU[ID].REGs[A] <  CPU[ID].REGs[B])) { CPU[ID].IP += ((C>0)?C:1)*6; } break;
     case 0x10:// CMPGT  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP>\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (IMM>0) {  if (!(CPU[ID].REGs[A] >  IMM)) { CPU[ID].IP += ((C>0)?C:1)*6; }
      }else if(!(CPU[ID].REGs[A] >  CPU[ID].REGs[B])) { CPU[ID].IP += ((C>0)?C:1)*6; } break;
     case 0x11:// SPLIT  |
      if (sys.Debug == true) { sprintf(msg,"%sSPLIT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true;
      if ((IMM % 0x2) == 0) { CPU[ID].REGs[B] = CPU[ID].REGs[A] & 0xFF; CPU[ID].REGs[C] = CPU[ID].REGs[A] >> 8; } else { CPU[ID].REGs[B] = CPU[ID].REGs[A] & 0xF; CPU[ID].REGs[C] = CPU[ID].REGs[A] >> 4; } break;
     case 0x12:// COMB   |
      if (sys.Debug == true) { sprintf(msg,"%sCOMBINE\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true;
      if ((IMM % 0x2) == 0) { CPU[ID].REGs[C] = (CPU[ID].REGs[A] << 8) | (CPU[ID].REGs[B] & 0xFF); }else{ CPU[ID].REGs[C] = (CPU[ID].REGs[A] << 4) | (CPU[ID].REGs[B] & 0xF); } break;
     
     case 0x13:// WMEM   |
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      if (IMM > 0xD7FFFFF) { IMM = (CPU[ID].REGs[B]<<16|CPU[ID].REGs[C])%0xD7FFFFF; }
      if (IMM > 0x0FFFFFF) {
       if (sys.Debug == true) {
        sprintf(msg,"%sWMEM\n  \\Writing REG:%c to 0x%x  (Area ",msg,sys.REG[A],IMM);
        if (IMM>=0x0000000 && IMM<=0x07FFFFF) { sprintf(msg,"%s0:ROM PAGE#0)\n",msg); } else
        if (IMM>=0x0800000 && IMM<=0x0FFFFFF) { sprintf(msg,"%s1:ROM PAGE#1)\n",msg); } else
        if (IMM>=0x1000000 && IMM<=0x17FFFFF) { sprintf(msg,"%s2:SAV data)\n",msg); } else
        if (IMM>=0x1800000 && IMM<=0x96FFBFF) { sprintf(msg,"%s3:Work RAM)\n",msg); } else
        if (IMM>=0x96FFC00 && IMM<=0x97FFBFF) { sprintf(msg,"%s4:Stack Memory)\n",msg); } else
        if (IMM>=0x97FFC00 && IMM<=0x97FFFFF) { sprintf(msg,"%s5:Static Memory)\n",msg); } else
        if (IMM>=0x9800000 && IMM<=0xD77FFFF) { sprintf(msg,"%s6:Video RAM)\n",msg); } else
        if (IMM>=0xD780000 && IMM<=0xD7FFFFF) { sprintf(msg,"%s7:Stack VMem)\n",msg); }
        else { sprintf(msg,"%sInvalid Address)\n",msg); }
       } sys.MEM[IMM]=CPU[ID].REGs[A]; if (IMM>=0x1000000 && IMM<=0x17FFFFF) { WriteSAV(IMM-0x1000000, CPU[ID].REGs[A]&0xFF); }
      } else {
       sprintf(msg,"%s[EMU Warning] CPU#%i: Invalid Instuction, You cannot write to ROM!\n",msg,ID);
      } break;
     case 0x14:// RMEM   |
      if (IMM > 0xD7FFFFF) { IMM = (CPU[ID].REGs[B]<<16|CPU[ID].REGs[C])%0xD7FFFFF; }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (sys.Debug == true) {
       sprintf(msg,"%sRMEM\n  \\Reading 0x%x to REG:%c (Area ",msg,IMM,sys.REG[A]);
       if (IMM>=0x0000000 && IMM<=0x07FFFFF) { sprintf(msg,"%s0:ROM PAGE#0)\n",msg); } else
       if (IMM>=0x0800000 && IMM<=0x0FFFFFF) { sprintf(msg,"%s1:ROM PAGE#1)\n",msg); } else
       if (IMM>=0x1000000 && IMM<=0x17FFFFF) { sprintf(msg,"%s2:SAV data)\n",msg); } else
       if (IMM>=0x1800000 && IMM<=0x96FFBFF) { sprintf(msg,"%s3:Work RAM)\n",msg); } else
       if (IMM>=0x96FFC00 && IMM<=0x97FFBFF) { sprintf(msg,"%s4:Stack Memory)\n",msg); } else
       if (IMM>=0x97FFC00 && IMM<=0x97FFFFF) { sprintf(msg,"%s5:Static Memory)\n",msg); } else
       if (IMM>=0x9800000 && IMM<=0xD77FFFF) { sprintf(msg,"%s6:Video RAM)\n",msg); } else
       if (IMM>=0xD780000 && IMM<=0xD7FFFFF) { sprintf(msg,"%s7:Stack VMem)\n",msg); }
       else { sprintf(msg,"%sInvalid Address)\n",msg); }
      } CPU[ID].REGs[A]=sys.MEM[IMM]; break;
     
     case 0x15:// HALT   |
      if (sys.Debug == true) { sprintf(msg,"%sHALT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      sys.ErrorType = 0;
      sprintf(sys.Error,"HALT INSTUCTION NOT FINISHED!");
      for(i=0;i<2;i++) {CPU[i].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,i);}
      break;
     case 0x16:// DISP   |
      if (sys.Debug == true) { sprintf(msg,"%sDISP\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      if (!sys.blockDisp) {
       if((IMM%3)==0) { printf("%c: 0x%04X\n",sys.REG[A],CPU[ID].REGs[A]); } else
       if((IMM%3)==1) { printf("%c: 0x%04X\t%c: 0x%04X\t\n",sys.REG[A],CPU[ID].REGs[A],sys.REG[B],CPU[ID].REGs[B]); } else
       if((IMM%3)==2) { printf("%c: 0x%04X\t%c: 0x%04X\t%c: 0x%04X\t\n",sys.REG[A],CPU[ID].REGs[A],sys.REG[B],CPU[ID].REGs[B],sys.REG[C],CPU[ID].REGs[C]); }
      } break;
     case 0x17:// IPOUT  |
      if (sys.Debug == true) { sprintf(msg,"%sIPOUT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      CPU[ID].REGs[A]=CPU[ID].IP>>16; CPU[ID].REGs[B]=CPU[ID].IP&0xFFFF;
      break;
     case 0x18:// PAGE   |
      if (sys.Debug == true) { sprintf(msg,"%sPAGE\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      LoadPage(A%2,IMM&0xFF%0x21);
      break;
     case 0x19:// CORE   |
      if (sys.Debug == true) { sprintf(msg,"%sCORE\n",msg); }
      //A = CoreID
      //B = State
      //IMM = Start Address
      CPU[A%2].IP = IMM;
      CPU[A%2].running = B%2;
      break;
     case 0x1A:// PUSH   |
      if (sys.Debug == true) { sprintf(msg,"%sPUSH\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      if (CPU[ID].SP-2 < CPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! STACK OVERFLOW!!",ID); CPU[ID].running=false; break;}
      else {sys.MEM[CPU[ID].SP--] = CPU[ID].REGs[A]&0xFF,sys.MEM[CPU[ID].SP--] = CPU[ID].REGs[A]>>8; } break;
     case 0x1B:// POP    |
      if (sys.Debug == true) { sprintf(msg,"%sPOP\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (CPU[ID].SP+2 > CPU[ID].MP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! stack empty...",ID); CPU[ID].running=false; break;}
      else {CPU[ID].REGs[A] = sys.MEM[CPU[ID].SP++]|(sys.MEM[CPU[ID].SP++]<<8); } break;
     case 0x1C:// CALL   |
      if (sys.Debug == true) { sprintf(msg,"%sCALL\n",msg); } if(C>0){CPU[ID].flag[1]=true;}
      if (CPU[ID].SP-4 < CPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! STACK OVERFLOW!!",ID); CPU[ID].running=false; break;}
      else {sys.MEM[CPU[ID].SP--] = CPU[ID].IP,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>8,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>16,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>24,CPU[ID].IP = ((C==0)?IMM:(A<<16|B))&0xFFFFFFFFF;} break;
     case 0x1D:// RET    |
      if (sys.Debug == true) { sprintf(msg,"%sRET\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if (CPU[ID].SP+4 > CPU[ID].MP) {sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! stack empty...",ID); CPU[ID].running=false; break;}
       CPU[ID].IP = sys.MEM[CPU[ID].SP--]|sys.MEM[CPU[ID].SP--]<<8|sys.MEM[CPU[ID].SP--]<<16|sys.MEM[CPU[ID].SP--]<<24; break;
     case 0x1E:// SWAP   |
      if (sys.Debug == true) { sprintf(msg,"%sSWAP\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if (!CPU[ID].SP+4 > CPU[ID].MP) {
       sys.tmp[0]=sys.MEM[CPU[ID].SP+3],sys.tmp[1]=sys.MEM[CPU[ID].SP+4];
       sys.MEM[CPU[ID].SP+3]=sys.MEM[CPU[ID].SP+1],sys.MEM[CPU[ID].SP+4]=sys.MEM[CPU[ID].SP+2];
       sys.MEM[CPU[ID].SP+1]=sys.tmp[0],sys.MEM[CPU[ID].SP+2]=sys.tmp[1];
      } break;
     case 0x1F:// LED    |
      memset(CPU[ID].flag, 0, 8); if(C>0){CPU[ID].flag[1]=true;}
      if (IMM>0){ sys.LED[0] = IMM&0xFF; sys.LED[1] = (IMM>>8)&0xFF; sys.LED[2] = (IMM>>16)&0xFF; }
      else { sys.LED[0] = CPU[ID].REGs[A]&0xFF; sys.LED[1] = CPU[ID].REGs[B]&0xFF; sys.LED[2] = CPU[ID].REGs[C]&0xFF; }
      if (sys.Debug == true) { sprintf(msg,"%sLED\n  \\sys.LED is set to #%02X%02X%02X\n",msg,sys.LED[0],sys.LED[1],sys.LED[2]); }
//      printf("sys.LED is set to #%02X%02X%02X\n",sys.LED[0],sys.LED[1],sys.LED[2]);
      break;
     case 0x20:// CLK    |
      if (sys.Debug == true) { sprintf(msg,"%sCLOCK\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if(!(IMM>0)) { CPU[ID].flag[1]=true; CPU[ID].REGs[A]=CPU[ID].Clock; }
      else { CPU[ID].Clock=0; } break;
     case 0x21:// WAIT   |
      if (sys.Debug == true) { sprintf(msg,"%sWAIT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      dslp = CPU[ID].REGs[A];
      break;
     case 0xFF:// NOP    |
      if (sys.Debug == true) { sprintf(msg,"%sNOP\n",msg); }
      memset(CPU[ID].flag, 0, 8); break;
     default:
      if (sys.Debug == true) { sprintf(msg,"%sUNKNOWN\n",msg); }
      sys.ErrorType = 2; sprintf(sys.Error,"CPU#%i: Unknown Operation 0x%02X",ID,sys.MEM[CPU[ID].IP]);
      CPU[ID].running = 0; break;
    } CPU[ID].IP+=6; CPU[ID].IPS++; CPU[ID].TI++;
    if (sys.Debug == true) { printf("%s",msg); memset(msg,0,sizeof(msg)); }
    PrintError();
    if (sys.MEM[CPU[ID].IP] == 0x21) { WaitTime(dslp)); }
   }
   #ifdef _WIN32
    clock_gettime(CLOCK_MONOTONIC, &end);
   #else
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
   #endif
   WaitTime(zeroup(1000-((end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000))/1000);
  } else {
   WaitTime(0.001);
}}}

uint32_t randi(uint32_t min, uint32_t max, uint32_t seed) { return (max*(((seed*2)%max)*100000)+min)%max; }
uint16_t getx(uint32_t i) { return i%GPU_Resolutions[GPU.Rez][0]; }
uint16_t gety(uint32_t i) { return (i-(i%GPU_Resolutions[GPU.Rez][0]))/GPU_Resolutions[GPU.Rez][0]; }
uint32_t geti(uint16_t x,uint16_t y) { return ((y%GPU_Resolutions[GPU.Rez][1])*GPU_Resolutions[GPU.Rez][0])+(x%GPU_Resolutions[GPU.Rez][0]); }

void GPU_makeCanvas (uint16_t Width,uint16_t Height) {
 uint32_t canvasAddr = 0x9800000+GPU.cp;
// printf("Creating Canvas Buffer Address: 0x%07x: [Width: %i, Height: %i]\n",canvasAddr,Width,Height);
 if (canvasAddr+4+Width*Height*4>0xD77FFFF) { sys.ErrorType = 0; sprintf(sys.Error,"GPU: cannot make canvas buffer (Video Memory OverFlow)!!"); PrintError(); return; }
 sys.MEM[canvasAddr++] =(Width>>8)&0xFF;
 sys.MEM[canvasAddr++] = Width    &0xFF;
 sys.MEM[canvasAddr++] =(Height>>8)&0xFF;
 sys.MEM[canvasAddr++] = Height    &0xFF;
// printf("canvasAddr: 0x%07x\n",canvasAddr);
}
void GPU_plot(uint16_t x,uint16_t y, uint8_t r,uint8_t g,uint8_t b,uint8_t a) {
 uint32_t canvasAddr = 0x9800000+GPU.cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 if(x<0|x>Width-1|y<0|y>Height-1){return;}
 sys.MEM[canvasAddr+(geti(x,y)*4)+0]=r,
 sys.MEM[canvasAddr+(geti(x,y)*4)+1]=g,
 sys.MEM[canvasAddr+(geti(x,y)*4)+2]=b,
 sys.MEM[canvasAddr+(geti(x,y)*4)+3]=a;
}

void BlendPixel(uint8_t result[4], uint8_t fg[4], uint8_t bg[4]) {
// float alpha = (fg[3]+1)/256.0,
//       inv_alpha = 1.0 - fg[3]/256.0;
// result[0] = (uint8_t)((alpha * fg[0]/255.0 + inv_alpha * bg[0]/255.0)*255);
// result[1] = (uint8_t)((alpha * fg[1]/255.0 + inv_alpha * bg[1]/255.0)*255);
// result[2] = (uint8_t)((alpha * fg[2]/255.0 + inv_alpha * bg[2]/255.0)*255);
 float inv_alpha = (fg[3]/255.0)+(bg[3]/255.0)*(1.0-(fg[3]/256.0));
 result[0] = (((fg[0]/255.0)*(fg[3]/255.0) + (bg[0]/255.0)*(bg[3]/255.0)*(1.0-(fg[3]/256.0)))/inv_alpha)*255;
 result[1] = (((fg[1]/255.0)*(fg[3]/255.0) + (bg[1]/255.0)*(bg[3]/255.0)*(1.0-(fg[3]/256.0)))/inv_alpha)*255;
 result[2] = (((fg[2]/255.0)*(fg[3]/255.0) + (bg[2]/255.0)*(bg[3]/255.0)*(1.0-(fg[3]/256.0)))/inv_alpha)*255;
 result[3] = 0xff;
}

void GPU_circle(uint16_t x,uint16_t y, uint16_t radius, uint8_t r,uint8_t g,uint8_t b,uint8_t a) { double i; for(i=0; i<360; i+=0.1) { GPU_plot(x+radius*cos(i*PI/180),y+radius*sin(i*PI/180), r,g,b,a); } }
void GPU_circlef(uint16_t x,uint16_t y, uint16_t radius, uint8_t r,uint8_t g,uint8_t b,uint8_t a) { for(int rad=1;rad<radius;rad++) { GPU_circle(x,y,rad,r,g,b,a); } }

void GPU_line(uint32_t canvasAddr, uint16_t x,uint16_t y, uint16_t x2,uint16_t y2, uint8_t r,uint8_t g,uint8_t b,uint8_t a) {
 int16_t dx = abs(x2 - x), sx = x<x2?1:-1, dy = -abs(y2 - y), sy = y<y2?1:-1, error = dx + dy, e2;
 while(true) {
  GPU_plot(x,y, r,g,b,a);
  if(x == x2 && y == y2) {break;}
  e2 = 2 * error;
  if(e2 >= dy) {
   if(x == x2) {break;}
   error = error + dy;
   x = x + sx;
  }
  if(e2 <= dx) {
   if(y == y2) {break;}
   error = error + dx;
   y = y + sy;
  }
 }
 
// for(uint16_t xi=(x<x2?x:x2);xi<=(x>x2?x:x2);xi++) { if(xi>Width-1|(((double)(y2-y)/(x2-x))*(xi-x)+y)>Height-1){continue;} GPU_plot(canvasAddr-0x9800005, xi,((double)(y2-y)/(x2-x))*(xi-x)+y, r,g,b,a); }
// for(uint16_t yi=(y<y2?y:y2);yi<=(y>y2?y:y2);yi++) { if((((double)(x2-x)/(y2-y))*(yi-y)+x)>Width-1|yi>Height-1){continue;} GPU_plot(canvasAddr-0x9800005, ((double)(x2-x)/(y2-y))*(yi-y)+x,yi, r,g,b,a); }
}

void LoadSurface() {
 UnloadImage(GPU.Canvas);
 uint32_t canvasAddr = 0x9800000+GPU.cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 GPU.Canvas = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0, 0);
 memcpy((uint8_t*)GPU.Canvas->pixels, &sys.MEM[canvasAddr], GPU.Canvas->pitch*GPU.Canvas->h);
 // Memory -> Canvas
}
void SaveSurface() {
 uint32_t canvasAddr = 0x9800000+GPU.cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 memcpy(&sys.MEM[canvasAddr], (uint8_t*)GPU.Canvas->pixels, GPU.Canvas->pitch*GPU.Canvas->h);
 SDL_FreeSurface(GPU.Canvas);
 // Canvas -> Memory
}


void HSV2RGB2(float h,float s,float v, int8_t*rx,int8_t*gx,int8_t*bx) {
 float r,g,b,i=floor(h*6),f=h*6-i,p=v*(1-s),q=v*(1-f*s),t=v*(1-(1-f)*s);
 switch((int)i % 6) {
  case 0: r=v,g=t,b=p; break;
  case 1: r=q,g=v,b=p; break;
  case 2: r=p,g=v,b=t; break;
  case 3: r=p,g=q,b=v; break;
  case 4: r=t,g=p,b=v; break;
  case 5: r=v,g=p,b=q; break;
 } *rx=r*255, *gx=g*255, *bx=b*255;
}
void GPUCore(uint8_t ID);
void GPUMain() {
 uint32_t i=0,j=0;
 uint8_t msg[1024]={0};
 GPU.running = false;
 SDL_Init(SDL_INIT_VIDEO);
 SDL_Surface *ScreenSurf = SDL_CreateRGBSurface(0, GPU_Resolutions[GPU.Rez][0], GPU_Resolutions[GPU.Rez][1], 24, 0, 0, 0, 0);

 //memcpy(palette, pixels, rgbaImage->pitch*rgbaImage->h)

/*  GPU_circlef(Canvas, 100,100, 24, 0xFF, 0xFF, 0x00, 0xFF);
  GPU_line(Canvas, 200,200,200+(bin%200),250, 0xFF,0x00,0x00,0xFF);
  GPU_line(Canvas, 400,100,300,150+(bin%200), 0xFF,0xFF,0x00,0xFF);
  for(i=0;i<16;i++) {
   if ((bin>>i)&1) { GPU_circlef(Canvas,10+((16-i)*20),100, 10, 255,  0,  0, 255); }
   else { GPU_circlef(Canvas,10+((16-i)*20),100, 10, 128,128, 64, 255); }
  }
  bin++;*/
 uint32_t ptraddr;
 while(1) {
//  SDL_FillRect(ScreenSurf,(SDL_Rect[4]){0,0,ScreenSurf->w/2,ScreenSurf->h/2}, 0x7F0000FF);
//  SDL_Circle(ScreenSurf, 300,100, 25, 0x00,0xFF,0xFF,0xFF);
/*  uint8_t r,g,b,i=0;do {
   for(uint8_t y=0;y<32;y++){
    HSV2RGB2(i/255.0, 1.0, 1.0, &r,&g,&b);
    uint32_t ptraddr = 3*(y *ScreenSurf->w+ i);
    pixels[ptraddr+0]=r,pixels[ptraddr+1]=g,pixels[ptraddr+2]=b,pixels[ptraddr+3]=y/32.0*255;
    //SDL_plot(Canvas, i,y, r,g,b,y/32.0*255);
   } //printf("x: %i, RGB: 0x%02x%02x%02x\n",(int)round((i/255.0)*320),r,g,b);
   //GPU_line(Canvas, randi(0, GPU_Resolutions[GPU.Rez][0], sys.Clock),randi(0, GPU_Resolutions[GPU.Rez][1], sys.Clock*2), randi(0, GPU_Resolutions[GPU.Rez][0], sys.Clock*2),randi(0, GPU_Resolutions[GPU.Rez][1], sys.Clock*3), randi(0, 0xFF, sys.Clock*4), randi(0, 0xFF, sys.Clock*5),randi(0, 0xFF, sys.Clock*6),0xFF);
  }while(++i);*/
  if(GPU.running) {
  //void GPU_REGW(uint8_t ID, uint64_t Data)
  //int32_t GPU_REGR(uint8_t ID)
  // X, X2, Y, Y2, InstructionPointer, StackPointer, SpritePointer, R,G,B,A, E,I,O,U
   uint8_t A   =      sys.MEM[0x9800000+GPU.IP+1] >> 4 ;       //4 \.
   uint8_t B   =      sys.MEM[0x9800000+GPU.IP+1] & 0xF;       //4 |-> A/B/C = 1.5 bytes
   uint8_t C   =      sys.MEM[0x9800000+GPU.IP+2] >> 4 ;       //4 /'
   int32_t IMM =((((((sys.MEM[0x9800000+GPU.IP+2] & 0xF) << 8) //4 \.
               |      sys.MEM[0x9800000+GPU.IP+3]) << 8)       //8 |->  IMM  = 3.5 bytes
               |      sys.MEM[0x9800000+GPU.IP+4]) << 8)       //8 |
               |      sys.MEM[0x9800000+GPU.IP+5];             //8 /'
   if (sys.Debug == true) {
    sprintf(msg,"%s\n[GPU] IC: 0x%07X/%9i (Area ",msg,GPU.IP,GPU.IP);
    if (GPU.IP>=0x0000000 && GPU.IP<=0x3F7FFFF) { sprintf(msg,"%s6:Video RAM",msg); } else
    if (GPU.IP>=0x3F80000 && GPU.IP<=0x3FFFFFF) { sprintf(msg,"%s7:Stack VMem",msg); }
    else { sprintf(msg,"%s?:Invalid Address",msg); } sprintf(msg,"%s)\n\\ >> [",msg);
    for (i=0; i < 6; i++) { sprintf(msg,"%s0x%02X",msg,sys.MEM[0x9800000+GPU.IP+i]); if (i < 5) { sprintf(msg,"%s, ",msg); } }
    sprintf(msg,"%s] | [A:%s, B:%s, C:%s, IMM:0x%07X]\n\\REGs: [",msg,GPU_REG(A),GPU_REG(B),GPU_REG(C),IMM);
    // 0, 1, . . . X[2]    16-bit X Position / X2/Width Position // 2, 3, . . . Y[2]    16-bit Y Position / Y2/Height Position
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s:0x%04X, ",msg,GPU_REG(i),GPU_REGR(   i)); }
    // 4 . . . . . IP      28-bit Instuction Pointer // 5 . . . . . SP      28-bit Stack Pointer // 6 . . . . . sp:     28-bit Sprite Pointer // 7 . . . . . cp:     28-bit Canvas Pointer
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s:0x%06X, ",msg,GPU_REG(i),GPU_REGR( 4+i)); }
    // 8, 9,10,11, R,G,B,A  8-bit Red, Green, Blue, Alpha
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s:0x%02X, ",msg,GPU_REG(i),GPU_REGR( 8+i)); }
    //12,13,14,15, E,I,O,U 28-bit General Purpose Registers
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s:0x%06X%s",msg,GPU_REG(i),GPU_REGR(12+i),(i<7)?", ":""); }





//    sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[0],GPU.REGs[0]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[1],GPU.REGs[1]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[2],GPU.REGs[2]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[3],GPU.REGs[3]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[4],GPU.REGs[4]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[5],GPU.REGs[5]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[6],GPU.REGs[6]); sprintf(msg,"%s%c:0x%04X"  ,msg,sys.REG[7],GPU.REGs[7]);
    sprintf(msg,"%s] | TotalRan: %ld\n\\StackPointer: 0x%x/%d | StackBase: 0x%x/%d\n\\\\StackData:[",msg,GPU.TI,GPU.SP,GPU.SP,GPU.BP,GPU.BP);
    for (i = GPU.SP+1; i <= GPU.BP; ++i){
     if((i+1)%2==0) { sprintf(msg,"%s 0x",msg); }
     sprintf(msg,"%s%02X",msg,sys.MEM[i]);
     if(i%16==0 && i != 0) { sprintf(msg,"%s\n",msg); }
    } sprintf(msg,"%s]\n \\instruction: ",msg);
   }
   switch(sys.MEM[0x9800000+GPU.IP]) {
    case 0x00:
     GPU_REGW(A, IMM);
     break;
    case 0x01:
     GPU_REGW(A, GPU_REGR(B));
     break;
    case 0x02:// ADD    |
     if (sys.Debug == true) { sprintf(msg,"%sADD\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)+IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)+GPU_REGR(B));} break;
    case 0x03:// SUB    |
     if (sys.Debug == true) { sprintf(msg,"%sSUB\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)-IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)-GPU_REGR(B));} break;
    case 0x04:// MUL    |
     if (sys.Debug == true) { sprintf(msg,"%sMUL\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)*IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)*GPU_REGR(B));} break;
    case 0x05:// DIV    |
     if (sys.Debug == true) { sprintf(msg,"%sDIV\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)/IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)/GPU_REGR(B));} break;
    case 0x06:// MOD    |
     if (sys.Debug == true) { sprintf(msg,"%sMOD\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)%IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)%GPU_REGR(B));} break;
    case 0x07:// AND    |
     if (sys.Debug == true) { sprintf(msg,"%sAND\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)&IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)&GPU_REGR(B));} break;
    case 0x08:// OR     |
     if (sys.Debug == true) { sprintf(msg,"%sOR\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)|IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)|GPU_REGR(B));} break;
    case 0x09:// XOR    |
     if (sys.Debug == true) { sprintf(msg,"%sXOR\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)^IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)^GPU_REGR(B));} break;
    case 0x0A:// BSL    |
     if (sys.Debug == true) { sprintf(msg,"%sBSL\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)<<IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)<<GPU_REGR(B));} break;
    case 0x0B:// BSR    |
     if (sys.Debug == true) { sprintf(msg,"%sBSR\n",msg); }
     if (IMM > 0) { GPU_REGW(C, GPU_REGR(A)>>IMM);}
     else {         GPU_REGW(C, GPU_REGR(A)>>GPU_REGR(B));} break;
    case 0x0C:// NOT    |
     if (sys.Debug == true) { sprintf(msg,"%sNOT\n",msg); }
     GPU_REGW(A, ~GPU_REGR(A)); break;
    case 0x0D:// CMPEQ  |
     if (sys.Debug == true) { sprintf(msg,"%sCMP=\n",msg); }
     if (IMM>0) {  if (GPU_REGR(A) != IMM) { GPU.IP += ((C>0)?C:1)*6; }
     }else if(GPU_REGR(A) != GPU_REGR(B)) { GPU.IP += ((C>0)?C:1)*6; } break;
    case 0x0E:// CMPLT  |
     if (sys.Debug == true) { sprintf(msg,"%sCMP<\n",msg); }
     if (IMM>0) { if (!(GPU_REGR(A) <  IMM)) { GPU.IP += ((C>0)?C:1)*6; }
     }else if(!(GPU_REGR(A) <  GPU_REGR(B))) { GPU.IP += ((C>0)?C:1)*6; } break;
    case 0x0F:// CMPGT  |
     if (sys.Debug == true) { sprintf(msg,"%sCMP>\n",msg); }
     if (IMM>0) {  if (!(GPU_REGR(A) >  IMM)) { GPU.IP += ((C>0)?C:1)*6; }
     }else if(!(GPU_REGR(A) >  GPU_REGR(B))) { GPU.IP += ((C>0)?C:1)*6; } break;
    case 0x11:// SPLIT  |
     if (sys.Debug == true) { sprintf(msg,"%sSPLIT\n",msg); }
     if ((IMM % 0x2) == 0) { GPU_REGW(B, GPU_REGR(A) & 0xFF); GPU_REGW(C, GPU_REGR(A) >> 8); } else { GPU_REGW(B, GPU_REGR(A) & 0xF); GPU_REGW(C, GPU_REGR(A) >> 4); } break;
    case 0x12:// COMB   |
     if (sys.Debug == true) { sprintf(msg,"%sCOMBINE\n",msg); }
     if ((IMM % 0x2) == 0) { GPU_REGW(C, (GPU_REGR(A) << 8) | (GPU_REGR(B) & 0xFF)); }else{ GPU_REGW(C, (GPU_REGR(A) << 4) | (GPU_REGR(B) & 0xF)); } break;
    
    case 0x13:// WMEM   |
     if (IMM > 0x3FFFFFF) { IMM = GPU_REGR(A)%0x3FFFFFF; }
     if (sys.Debug == true) {
      sprintf(msg,"%sWMEM\n  \\Writing REG:%c to 0x%x  (Area ",msg,sys.REG[A],IMM);
      if (IMM>=0x0000000 && IMM<=0x3F7FFFF) { sprintf(msg,"%s6:Video RAM)\n",msg); } else
      if (IMM>=0x3F80000 && IMM<=0x3FFFFFF) { sprintf(msg,"%s7:Stack VMem)\n",msg); }
      else { sprintf(msg,"%sInvalid Address)\n",msg); }
     } sys.MEM[0x9800000+IMM]=GPU_REGR(A);
     break;
    case 0x14:// RMEM   |
     if (IMM > 0x3FFFFFF) { IMM = GPU_REGR(A)%0x3FFFFFF; }
     if (sys.Debug == true) {
      sprintf(msg,"%sRMEM\n  \\Reading 0x%x to REG:%c (Area ",msg,IMM,sys.REG[A]);
      if (IMM>=0x0000000 && IMM<=0x3F7FFFF) { sprintf(msg,"%s6:Video RAM)\n",msg); } else
      if (IMM>=0x3F80000 && IMM<=0x3FFFFFF) { sprintf(msg,"%s7:Stack VMem)\n",msg); }
      else { sprintf(msg,"%sInvalid Address)\n",msg); }
     } GPU_REGW(A, sys.MEM[0x9800000+IMM]); break;
    
    case 0x15:// HALT   |
     if (sys.Debug == true) { sprintf(msg,"%sHALT\n",msg); }
     sys.ErrorType = 0;
     sprintf(sys.Error,"HALT INSTUCTION NOT FINISHED!");
     for(i=0;i<2;i++) {CPU[i].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,i);}
     break;
    case 0x16:// DISP   |
     if (sys.Debug == true) { sprintf(msg,"%sDISP\n",msg); }
     if (!sys.blockDisp) {
      if((IMM%3)==0) { printf("%c: 0x%04X\n",GPU_REGR(A),GPU_REGR(A)); } else
      if((IMM%3)==2) { printf("%c: 0x%04X\t%c: 0x%04X\t%c: 0x%04X\t\n",GPU_REGR(A),GPU_REGR(A),GPU_REGR(B),GPU_REGR(B),GPU_REGR(C),GPU_REGR(C)); }
     } break;
    case 0x17:// RESOLUTION |
     GPU.Rez = GPU_REGR(A)&0x0F;
     SDL_FreeSurface(ScreenSurf);
     ScreenSurf = SDL_CreateRGBSurface(0, GPU_Resolutions[GPU.Rez][0], GPU_Resolutions[GPU.Rez][1], 24, 0, 0, 0, 0);
     break;
    case 0x18:// PLOT   |
     LoadSurface();

     uint8_t *pixels = (uint8_t*)ScreenSurf->pixels;
     ptraddr = 4*(GPU.Y[0] *ScreenSurf->w+ GPU.X[0]);
     pixels[ptraddr+0]=GPU.R,pixels[ptraddr+1]=GPU.G,pixels[ptraddr+2]=GPU.B,pixels[ptraddr+3]=GPU.A;
     break;



    case 0x1E:// COPY   |
     memcpy(GPU.screen, (uint8_t*)ScreenSurf->pixels, ScreenSurf->pitch*ScreenSurf->h);
     break;
    case 0x1F:// RENDER |
     memcpy(GPU.screen, (uint8_t*)ScreenSurf->pixels, ScreenSurf->pitch*ScreenSurf->h);
     GPU.frames++;
     break;
    
    
   }
  } WaitTime(0.001/60); //60 UpdatesPerSecond target
 }
// pthread_t call_GPUCore[16];
// for(uint8_t i=0;i<16;i++) { sys.MEM[0x98005A0+i*4+0]=0x03,sys.MEM[0x98005A0+i*4+1]=0xF7,sys.MEM[0x98005A0+i*4+2]=0xFF,sys.MEM[0x98005A0+i*4+3]=0xFA; pthread_create(&call_GPUCore[i], NULL, GPUCore, i); }
 
/* sys.MEM[0x98005A0]=0x03,sys.MEM[0x98005A1]=0xCD,sys.MEM[0x98005A2]=0xCF,sys.MEM[0x98005A3]=0xF5;
 sys.MEM[0x98005E0]=(GPU_Resolutions[GPU.Rez][0]>>8)&0xFF,sys.MEM[0x98005E1]=GPU_Resolutions[GPU.Rez][0]&0xFF,
 sys.MEM[0x98005E2]=(GPU_Resolutions[GPU.Rez][1]>>8)&0xFF,sys.MEM[0x98005E3]=GPU_Resolutions[GPU.Rez][1]&0xFF;
 while(true) {
  if (GPU.running) {
   for(uint8_t i=0;i<15;i++) {
    if(GPU.CoreReady[i]==true) {
     uint32_t Canvas1 = sys.MEM[0x98005A0+(15-i)*4+0]<<24|sys.MEM[0x98005A0+(15-i)*4+1]<<16|sys.MEM[0x98005A0+(15-i)*4+2]<<8|sys.MEM[0x98005A0+(15-i)*4+3],
              Canvas0 = sys.MEM[0x98005A0+(14-i)*4+0]<<24|sys.MEM[0x98005A0+(14-i)*4+1]<<16|sys.MEM[0x98005A0+(14-i)*4+2]<<8|sys.MEM[0x98005A0+(14-i)*4+3];
     GPU_copy(Canvas0,Canvas1, 0,0, 0,0,0,0, true);
     GPU.CoreReady[i]=false;
     if(i==14) { GPU_update(Canvas0); }
    }
   }
 usleep(1000.0/60); //60 UpdatesPerSecond target
 */
}
