//#include "taylor.h"
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
#include <unistd.h>
#if _WIN32
 #include <winsock2.h>
#else
 #include <sys/socket.h>
#endif

#define TAYLOR_GPU_DEBUG_TEST false //forced debug toggle
uint8_t TaylorPrintString[0xFFFF] = "";

// void dummyNetwork() {
//  sprintf(sys.NETWORK_IP,"localhost"); sys.NETWORK_PORT=1213;
//  if (netlib_init() == -1) { sprintf(sys.Error,"netlib_init: %s\n", netlib_get_error()); sys.ErrorType=2; TGR_printError(); exit(2); }
//  else {
//   ip_address ip;
//   tcp_socket sock;
//   uint32_t sent;
//   //netlib_check_socket_set(netlib_socket_set set, uint32_t timeout)
//   char message[1024];
//   if (netlib_resolve_host(&ip, sys.NETWORK_IP,sys.NETWORK_PORT) == -1) { sprintf(sys.Error,"netlib_resolve_host: %s (IP: %s:%i)\n", netlib_get_error(),sys.NETWORK_IP,sys.NETWORK_PORT); sys.ErrorType=0; TGR_printError(); }
//   else if (!(sock = netlib_tcp_open(&ip))) { sprintf(sys.Error,"netlib_tcp_open: %s (IP: %s:%i)\n", netlib_get_error(),sys.NETWORK_IP,sys.NETWORK_PORT); sys.ErrorType=0; TGR_printError(); }
//   else {
//    sprintf(MainPrintString,"%s%sConnected to server (IP: %s:%i)%s\n",COLOR_BOLD,COLOR_BLUE,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_RESET); TGR_FilterAnsi(MainPrintString);
//    netlib_byte_buf* buf = netlib_alloc_byte_buf(20);
//    netlib_write_uint32(buf,'t');
//    netlib_write_uint32(buf,'e');
//    netlib_write_uint32(buf,'s');
//    netlib_write_uint32(buf,'t');
//    netlib_write_uint32(buf,'1');
//    sent = netlib_tcp_send_buf(sock, buf);
//         //netlib_tcp_recv_buf
//    if (sent < buf->length) { sprintf(sys.Error, "netlib_tcp_send: %s\n", netlib_get_error()); sys.ErrorType=0; TGR_printError(); }
//    sprintf(MainPrintString,"%sSent %i bytes to (IP: %s:%i)\nData: \"%s",COLOR_GREEN,sent,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_MAGENTA); TGR_FilterAnsi(MainPrintString);
//    for (sent=0;sent<buf->length;sent++) { printf("%c", buf->data[sent]); }
//    sprintf(MainPrintString,"%s\"%s\n",COLOR_GREEN,COLOR_RESET); TGR_FilterAnsi(MainPrintString);
//    netlib_free_byte_buf(buf);
//    netlib_tcp_close(sock);
//    sprintf(MainPrintString,"%sClosed connection to server (IP: %s:%i)%s\n",COLOR_BLUE,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_RESET); TGR_FilterAnsi(MainPrintString);
//    netlib_quit();
//  }}
// }
#define TaylorNetwork_IsActive  0b10000000
#define TaylorNetwork_IsHost    0b01000000
#define TaylorNetwork_NetType   0b00100000
#define TaylorNetwork_Connected 0b00010000
#define TaylorNetwork_Operation 0b00001111
struct TaylorNetwork {

 uint8_t  oper;                                 //  +1
 //  0: IsActive  //0 Skip   / 1 Tick
 //  1: IsHost    //0 Client / 1 Server
 //  2: NetType   //0 TCP    / 1 UDP
 //  3: Connected //0 No     / 1 Yes
 //4-7: operation

 uint8_t  Address[256]; //String of IP          //  +1
 uint16_t Port;                                 //  +2
 uint32_t BufferPtr;                            //  +4
 uint16_t BufferSize;                           //  +2
 uint8_t  Error;                                //  +1
#if _WIN32
 SOCKET Sock;
 WSAPOLLFD FDarray;
#else
 //socket Sock;
#endif
} TaylorNetwork[256];                           //  =??

// ip_address Sockip;
// uint32_t sent;
// uint8_t connI=0;
// do {
//  if (TaylorNetwork[connI].oper & TaylorNetwork_IsActive) {
//   switch(TaylorNetwork[connI].oper & TaylorNetwork_Operation) {
//    case 0x00: //Nothing
//     break;
//    case 0x01: //Connect/Bind
//     if (netlib_resolve_host(&Sockip, TaylorNetwork[connI].IP,TaylorNetwork[connI].Port) == -1) { sprintf(sys.Error,"netlib_resolve_host: %s (IP: %s:%i)\n", netlib_get_error(), TaylorNetwork[connI].IP,TaylorNetwork[connI].Port); sys.ErrorType=0; TGR_printError(); TaylorNetwork[connI].Error=1; continue; }
//     if (TaylorNetwork[connI].oper & TaylorNetwork_IsHost) {
//      if (!(TaylorNetwork[connI].sock = netlib_tcp_open(&Sockip))) { sprintf(sys.Error,"netlib_tcp_open: %s (IP: %s:%i)\n", netlib_get_error(),sys.NETWORK_IP,sys.NETWORK_PORT); sys.ErrorType=0; TGR_printError(); TaylorNetwork[connI].Error=2; continue; }
//      TaylorNetwork[connI].oper |= TaylorNetwork_Connected;
     
//      netlib_resolve_host(&TaylorNetwork[connI].IP)
//      if (TaylorNetwork[connI].oper & TaylorNetwork_NetType) { //UDP
      

//      if (TaylorNetwork[connI].oper & TaylorNetwork_NetType) { //UDP
      
//       netlib_udp_bind()
//      } else { //TCP
//       netlib_tcp_open
//      }
//     }
//     break;
//    case 0x02: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//    case 0x: //
//     break;
//   }
//  }
// }while(++connI)

// I DON'T KNOW WHAT I'M DOING!!!! TLDR I'm stupid...
// void NetworkThread() {
//  #if _WIN32
//   TaylorNetwork[connI].FDarray = {0};
//   TaylorNetwork[connI].Sock = INVALID_SOCKET;
//   SOCKADDR_STORAGE addrLoopback = {0};
//   INT ret = 0;
//   ULONG uNonBlockingMode = 1;
//   CHAR buf[MAX_PATH] = {0};

//   if (INVALID_SOCKET == (TaylorNetwork[connI].Sock = socket(AF_INET6, SOCK_STREAM, 0))) { sprintf(sys.Error,"winsock2: Failed to Create Socket\n"); sys.ErrorType=1; TGR_printError(); TaylorNetwork[connI].Error=1; continue; } }
//   if (SOCKET_ERROR == ioctlsocket(TaylorNetwork[connI].Sock, FIONBIO, &uNonBlockingMode)) { sprintf(sys.Error,"winsock2: FIONBIO Error\n"); sys.ErrorType=1; TGR_printError(); TaylorNetwork[connI].Error=1; continue; }
  
//   addrLoopback.ss_family = AF_INET6;
//   INETADDR_SETLOOPBACK((SOCKADDR*)&addrLoopback);
//   SS_PORT((SOCKADDR*)&addrLoopback) = htons(TaylorNetwork[connI].Port);

//   if (SOCKET_ERROR == connect(TaylorNetwork[connI].Sock, (SOCKADDR*)&addrLoopback, sizeof(addrLoopback))) {
//    if (WSAEWOULDBLOCK != WSAGetLastError()) { ERR("connect"); }
//   }

//   //Call WSAPoll for writeability on connecting socket
//   TaylorNetwork[connI].FDarray.fd = TaylorNetwork[connI].Sock;
//   TaylorNetwork[connI].FDarray.events = POLLWRNORM;

//   if (SOCKET_ERROR == (ret = WSAPoll(&TaylorNetwork[connI].FDarray, 1, DEFAULT_WAIT))) { ERR("WSAPoll"); }
//   if (ret) {
//    if (TaylorNetwork[connI].FDarray.revents & POLLWRNORM) {
//     printf("ConnectThread: Established connection\n");
//     //Send data
//     if (SOCKET_ERROR == (ret = send(sock, TST_MSG, sizeof(TST_MSG), 0))) { ERR("send"); }
//     else printf("ConnectThread: sent %d bytes\n",ret);
//    }
//   }

//   //Call WSAPoll for readability on connected socket
//   TaylorNetwork[connI].FDarray.events = POLLRDNORM;

//   if (SOCKET_ERROR == (ret = WSAPoll(&TaylorNetwork[connI].FDarray, 1, DEFAULT_WAIT))) { ERR("WSAPoll"); }
//   if (ret) {
//    if (TaylorNetwork[connI].FDarray.revents & POLLRDNORM) {
//     if (SOCKET_ERROR == (ret = recv(sock, buf, sizeof(buf), 0))) { ERR("recv"); }
//     else printf("ConnectThread: recvd %d bytes\n",ret);
//    }
//   }

//   WaitForSingleObject(hCloseSignal,DEFAULT_WAIT);
//   CLOSESOCK(sock);
//  #else
//   #include <sys/socket.h>
//  #endif
// }

struct timespec start, end;
uint16_t TAYLOR_CARTINIT();
void*TAYLOR_Clock();
void*TAYLOR_MemCheck();
void*TAYLOR_GPU_Main();
void*TAYLOR_CPU_Core(bool ID);
void*TAYLOR_GPU_Core(uint8_t ID);
void TAYLOR_GPU_GraphicsCore();

void TAYLOR_GPU_ResetAll() { for(uint8_t i=0;i<4;i++) TAYLOR_GPU_Reset(i); }
void TAYLOR_GPU_Reset(uint8_t ThreadID) {
 GPU[ThreadID].X[0]=GPU[ThreadID].X[1]=GPU[ThreadID].Y[0]=GPU[ThreadID].Y[1]=GPU[ThreadID].IPS=GPUctl.frames=\
 GPU[ThreadID].R=GPU[ThreadID].G=GPU[ThreadID].B=GPU[ThreadID].A=GPU[ThreadID].Layer=GPUctl.Rez=GPUctl.NewRez=\
 GPU[ThreadID].E=GPU[ThreadID].I=GPU[ThreadID].O=GPU[ThreadID].U=GPU[ThreadID].sp=GPU[ThreadID].running=0;
 GPU[ThreadID].IP=CPLength+PtrLenth+13*0xFFFF; TAYLOR_GPU_ResetLayers();
 switch(ThreadID) {
  case 0:
   GPU[ThreadID].BP = TGR_VMEM_VSTACK0-TGR_MEM_VSTACK_SIZE,
   GPU[ThreadID].SP=GPU[ThreadID].MP=TGR_VMEM_VSTACK0;
   break;
  case 1:
   GPU[ThreadID].BP = TGR_VMEM_VSTACK1-TGR_MEM_VSTACK_SIZE,
   GPU[ThreadID].SP=GPU[ThreadID].MP=TGR_VMEM_VSTACK1;
   break;
  case 2:
   GPU[ThreadID].BP = TGR_VMEM_VSTACK2-TGR_MEM_VSTACK_SIZE,
   GPU[ThreadID].SP=GPU[ThreadID].MP=TGR_VMEM_VSTACK2;
   break;
  case 3:
   GPU[ThreadID].BP = TGR_VMEM_VSTACK3-TGR_MEM_VSTACK_SIZE,
   GPU[ThreadID].SP=GPU[ThreadID].MP=TGR_VMEM_VSTACK3;
   break;
  default:
   sprintf(sys.Error,"Unknown GPU ID(%d)\n",ThreadID); sys.ErrorType = 2; TGR_printError(); break;
 }
}
void TAYLOR_GPU_REGW(uint8_t ThreadID, uint8_t RegID, uint64_t Data) {
 switch(RegID) {
  case  0: GPU[ThreadID].X[0]=Data&0xFFFF; break;
  case  1: GPU[ThreadID].X[1]=Data&0xFFFF; break;
  case  2: GPU[ThreadID].Y[0]=Data&0xFFFF; break;
  case  3: GPU[ThreadID].Y[1]=Data&0xFFFF; break;
  case  4: GPU[ThreadID].IP = (Data-6)&0xFFFFFFF; break;
  case  5: sprintf(sys.Error,"GPU: StackPointer Can not be written to!\n"); sys.ErrorType = 1; TGR_printError(); break;
  case  6: GPU[ThreadID].sp = Data&0xFFFFFF; break;
  case  7: GPU[ThreadID].cp = Data&0xFFFFFF; break;
  case  8: GPU[ThreadID].R  = Data&0xFF; break;
  case  9: GPU[ThreadID].G  = Data&0xFF; break;
  case 10: GPU[ThreadID].B  = Data&0xFF; break;
  case 11: GPU[ThreadID].A  = Data&0xFF; break;
  case 12: GPU[ThreadID].E  = Data&0xFFFFFFF; break;
  case 13: GPU[ThreadID].I  = Data&0xFFFFFFF; break;
  case 14: GPU[ThreadID].O  = Data&0xFFFFFFF; break;
  case 15: GPU[ThreadID].U  = Data&0xFFFFFFF; break;
  default: sprintf(sys.Error,"GPU: Unknown Regster ID: %i\n",RegID); sys.ErrorType = 1; TGR_printError(); break;
}}
int32_t TAYLOR_GPU_REGR(uint8_t ThreadID, uint8_t RegID) {
 int32_t a[16] = {GPU[ThreadID].X[0],GPU[ThreadID].X[1],GPU[ThreadID].Y[0],GPU[ThreadID].Y[1],GPU[ThreadID].IP,GPU[ThreadID].SP,GPU[ThreadID].sp,GPU[ThreadID].cp,GPU[ThreadID].R,GPU[ThreadID].G,GPU[ThreadID].B,GPU[ThreadID].A,GPU[ThreadID].E,GPU[ThreadID].I,GPU[ThreadID].O,GPU[ThreadID].U};
 if(RegID > 15){sprintf(sys.Error,"GPU: Unknown Regster ID: %i\n",RegID);sys.ErrorType=1;TGR_printError();return 0;} else {return a[RegID];}
}
uint8_t TAYLOR_GPU_REGN[17][3] = {"X ","X2","Y ","Y2","IP","SP","sp","cp","R ","G ","B ","A ","E ","I ","O ","U ","__"};
uint8_t* TAYLOR_GPU_REG(uint8_t RegID) {
 if(RegID > 15){sprintf(sys.Error,"GPU: Unknown Regster ID: %i\n",RegID);sys.ErrorType=1;TGR_printError();return TAYLOR_GPU_REGN[16];} else {return TAYLOR_GPU_REGN[RegID];}
}

uint8_t *TAYLOR_ascii127 = "................................ !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~.......................................................................................................................................................";
void TAYLOR_dumpData(uint8_t *name, uint8_t *data, uint32_t size, uint32_t start, uint32_t end) {
 uint8_t bytes[16],msg[1024*1024]; int i,k,j=1,l=0,m=0;
 sprintf(msg,"%s._______._______________________________________________.________________.\n|%s",msg,name);
 for(i=0;i<7-strlen(name);i++) { sprintf(msg,"%s ",msg); }
 sprintf(msg,"%s|00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F|0123456789ABCDEF|\n|-------|-----------------------------------------------|----------------|\n|%07X|",msg,start);
 for (i=start;i<start+end;i++) {
  if (i >= start+size) { break; }
  if (j > 15) {
   bytes[j-1] = data[i];
   sprintf(msg,"%s%02X|",msg,data[i]);
   for (k=0; k < 16; k++) {
    sprintf(msg,"%s%c",msg,TAYLOR_ascii127[bytes[k]]);
   } l=0,j=0;
   sprintf(msg,"%s|\n|%07X|",msg,i+1);
  } else {
   sprintf(msg,"%s%02X ",msg,data[i]);
   bytes[j-1] = data[i];
  } j++; l++;
 }m=i;
 if (j > 0) {
  for (i=j; i < 16; i++) {
   sprintf(msg,"%s-- ",msg);
   bytes[j-1] = 0x00;
  } sprintf(msg,"%s--|",msg);
  for (i=0; i < l-1; i++) {
   sprintf(msg,"%s%c",msg,TAYLOR_ascii127[bytes[i]]);
  }
  if(m<16) { sprintf(msg,"%s%c",msg,TAYLOR_ascii127[bytes[m-1]]); }
  for (i=j; i < 16; i++) {
   sprintf(msg,"%s ",msg);
  } sprintf(msg,"%s |\n",msg);
 } sprintf(msg,"%s|_______|_______________________________________________|________________|\n\\Size: 0x%x/%d Bytes(",msg,size,size);
 if (size < 1024) { sprintf(msg,"%s%0.2f KB)\n",msg,size/1024.0f); } else { sprintf(msg,"%s%0.2f MB)\n",msg,(float)size/1024.0f/1024.0f); }
 TGR_FilterAnsi(msg);
}
void crop(uint8_t *dst, uint8_t *src, size_t mn, size_t mx) {
 const int len=mx-mn; src+=mn;
 for (int i=0; i<len; i++) { dst[i]=src[i]; }
 dst[len]='\0';
}

FILE *TAYLOR_BIOSfp,*TAYLOR_ROMfp,*TAYLOR_SAVfp,TAYLOR_Statefp;

void TAYLOR_FlushSAV() {
 sprintf(TaylorPrintString,"TAYLOR_FlushSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n%s\n", (uint8_t*)((!sys.ROMloaded)?"True":"False"), (uint8_t*)(sys.EXTSAV?"True":"False"), strlen(sys.SN), (uint8_t*)((!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False"),sys.SN); TGR_FilterAnsi(TaylorPrintString);
 if (!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  TGR_FilterAnsi("TAYLOR_FlushSAV!!\n");
  TAYLOR_SAVfp = fopen(sys.SN,"wb"); fwrite(&sys.MEM[0x1000000], 1, TGR_MEM_ROM_SIZE, TAYLOR_SAVfp);
  fflush(TAYLOR_SAVfp); fclose(TAYLOR_SAVfp);
}}
void TAYLOR_WriteSAV(uint32_t Address, uint8_t Data) {
 sprintf(TaylorPrintString,"WriteSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n", (uint8_t*)((!sys.ROMloaded)?"True":"False"), (uint8_t*)(sys.EXTSAV?"True":"False"), strlen(sys.SN), (uint8_t*)((!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False")); TGR_FilterAnsi(TaylorPrintString);
 if (!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  TGR_FilterAnsi("WriteSAV!!\n");
  TAYLOR_SAVfp = fopen(sys.SN,"wb"); fseek(Address, TAYLOR_SAVfp, SEEK_SET);
  fwrite(Data, 1, 1, TAYLOR_SAVfp); fflush(TAYLOR_SAVfp); fclose(TAYLOR_SAVfp);
}}
void TAYLOR_LoadSAV() {
 sprintf(TaylorPrintString,"LoadSAV (LoadFailed: %s, EXTSAV: %s, strlen(SAVName): %li]: %s\n", (uint8_t*)((!sys.ROMloaded)?"True":"False"), (uint8_t*)(sys.EXTSAV?"True":"False"), strlen(sys.SN), (uint8_t*)((!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0))?"True":"False")); TGR_FilterAnsi(TaylorPrintString);
 if (!sys.ROMloaded && !(sys.EXTSAV && strlen(sys.SN)==0)) {
  TGR_FilterAnsi("LoadSAV!!\n");
  if ((TAYLOR_SAVfp = fopen(sys.SN,"rb")) != NULL) { fread(&sys.MEM[0x1000000], 1, TGR_MEM_ROM_SIZE, TAYLOR_SAVfp); fclose(TAYLOR_SAVfp); }
  TAYLOR_FlushSAV();
}}

int8_t TAYLOR_LoadCart() {
 sys.ROMloaded = false;
 if ((TAYLOR_ROMfp = fopen(sys.RN,"rb")) == NULL) { sprintf(sys.Error,"Failed to access ROM file\n"); sys.ErrorType = 1; TGR_printError(); return -1; }
 for(uint8_t i=0;i<32;i++){ if(feof(TAYLOR_ROMfp)){break;} fread(&sys.ROMBANK[i], TGR_MEM_ROM_SIZE, 1, TAYLOR_ROMfp); }
 if(!(sys.ROMBANK[0][1]=='T' && sys.ROMBANK[0][2]=='G' && sys.ROMBANK[0][3]=='R')) {
  sys.ErrorType = 1; sprintf(sys.Error,"Bad Header(\"%c%c%c\") in ROM file\n",TAYLOR_ascii127[sys.ROMBANK[0][1]],TAYLOR_ascii127[sys.ROMBANK[0][2]],TAYLOR_ascii127[sys.ROMBANK[0][3]]);
  for(uint8_t i=0;i<32;i++){ memset(sys.ROMBANK[i],0x7F,TGR_MEM_ROM_SIZE); } return -1;
 }
 sys.ROMloaded = true;
 fclose(TAYLOR_ROMfp);
 if (!sys.EXTSAV) {
  uint8_t i=0;
  //do{ if(sys.RN[strlen(sys.RN)-i] == '.') { break; } }while(++i);
  memset(sys.SN, 0, 1024);
  memcpy(sys.SN, sys.RN, strlen(sys.RN)-3); sys.SN[strlen(sys.SN)+1] = '\x00'; strcat(sys.SN, "sav");
  sprintf(TaylorPrintString,"%sSelected SAV file: %s%s\n",COLOR_YELLOW,sys.SN,COLOR_RESET); TGR_FilterAnsi(TaylorPrintString);
  TAYLOR_LoadSAV();
 } return 0;
}

void TAYLOR_PrintHeader() {
 printf("Header: \""); for(uint8_t i=0;i<5;i++){printf("%c",TAYLOR_ascii127[sys.MEM[i]]);}
 printf("\"\nTitle: \""); for(uint8_t i=0;i<16;i++){printf("%c",TAYLOR_ascii127[sys.MEM[0x05+i]]);}
 printf("\"\nversion: \""); for(uint8_t i=0;i<12;i++){printf("%c",TAYLOR_ascii127[sys.MEM[0x15+i]]);}
 if (sys.MEM[0]>0) { printf("\"\nAuthor: \""); for(uint8_t i=0;i<32;i++){printf("%c",TAYLOR_ascii127[sys.MEM[0x21+i]]);} }
 if (sys.MEM[0]>1) { printf("\"\nCheckSum: \""); for(uint8_t i=0;i<32;i++){printf("%c",TAYLOR_ascii127[sys.MEM[0x41+i]]);} }
 printf("\"\n");
}

int8_t TAYLOR_CPU_Init() { //############################################//
 sys.SilentRun = false;
 sprintf(TaylorPrintString,"Initalizing Taylor v0.32 Alpha Build\n"); TGR_FilterAnsi(TaylorPrintString);
 //sys.Debug = false; //debug mode
 //sys.BlockDisp = true; //block DISP instuction messages
 
 sprintf(TaylorPrintString,"\\Initialize Memory...\n"); TGR_FilterAnsi(TaylorPrintString);
 if((sys.MEM = malloc(0xD800000)) == NULL) { sprintf(sys.Error,"Memory allocation failed.\n"); sys.ErrorType = 2; TGR_printError(); return -1;}
 memset(sys.MEM, 0, 0xD800000);
 sys.Clock = sys.EXTSAV = sys.HeaderSize = sys.ROMloaded = 0;
 sys.REG = "ABCDEFGH________";
 sys.Error = malloc(1024);
 sys.BN = malloc(1024); sys.RN = malloc(1024); sys.SN = malloc(1024);
 for(uint8_t i=0;i<33;i++){ memset(sys.ROMBANK[i], 0x7F, TGR_MEM_ROM_SIZE); }
 pthread_t call_Core0; pthread_create(&call_Core0, NULL, &TAYLOR_CPU_Core, 0);
 pthread_t call_Core1; pthread_create(&call_Core1, NULL, &TAYLOR_CPU_Core, 1);
 pthread_t call_Clock; pthread_create(&call_Clock, NULL, &TAYLOR_Clock,   NULL);
 pthread_t call_MemCheck; pthread_create(&call_MemCheck, NULL, &TAYLOR_MemCheck,   NULL);
 pthread_t call_GPU;   pthread_create(&call_GPU,   NULL, &TAYLOR_GPU_Main, NULL);
 
 for(int i=TGR_MEM_VRAM;i<2+(0xFFFF*13);i++){sys.MEM[i]=0;}
 sprintf(TaylorPrintString,"|\\0x%07X\\%10d\tBytes(%10.2f MB)\tof RAM were allocated...\n"
        "|\\0x%07X\\%10d\tBytes(%10.2f MB)\tof VideoRAM was allocated...\n",
 TGR_MEM_WRAM_FULL, TGR_MEM_WRAM_FULL, TGR_MEM_WRAM_FULL/1024.0f/1024.0f,  TGR_MEM_VRAM_FULL, TGR_MEM_VRAM_FULL, TGR_MEM_VRAM_FULL/1024.0f/1024.0f);
 TGR_FilterAnsi(TaylorPrintString);
 sprintf(TaylorPrintString, "Initalization Finished!\n");
 TGR_FilterAnsi(TaylorPrintString);
}

void TAYLOR_CPU_Silent(bool silent) { sys.SilentRun = silent; }
void TAYLOR_CPU_ExtSAV(uint8_t filepath[]) {
 sys.SN = malloc(1024);
 strcpy(sys.SN, filepath); sprintf(TaylorPrintString,"\nEXTSAV Selected: %s\n",filepath); TGR_FilterAnsi(TaylorPrintString);
 sys.EXTSAV = true; TAYLOR_LoadSAV();
}
void TAYLOR_CPU_Load(uint8_t filepath[]) { TAYLOR_CPU_Stop();
 CPU[0].running=CPU[1].running=GPU[0].running=GPU[1].running=GPU[2].running=GPU[3].running=false; WaitTime(0.001);
 WaitTime(0.001); sys.RN = malloc(1024); sys.SN = malloc(1024);
 strcpy(sys.RN, filepath); sprintf(TaylorPrintString,"\nROM Selected: %s\n",filepath); TGR_FilterAnsi(TaylorPrintString); sys.EXTSAV = false;
 if(TAYLOR_LoadCart()<0) { sys.Title[0] = 0; sys.ROMloaded = 0; sys.ErrorType = 1; sprintf(sys.Error,"%sFailed to load ROM: \"%s\"...\n",sys.Error,sys.RN); TGR_printError(); }
 else { TAYLOR_CPU_LoadPage(0,0); TAYLOR_CPU_LoadPage(1,1); sprintf(sys.Title, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",sys.ROMBANK[0][5],sys.ROMBANK[0][6],sys.ROMBANK[0][7],sys.ROMBANK[0][8],sys.ROMBANK[0][9],sys.ROMBANK[0][10],sys.ROMBANK[0][11],sys.ROMBANK[0][12],sys.ROMBANK[0][13],sys.ROMBANK[0][14],sys.ROMBANK[0][15],sys.ROMBANK[0][16],sys.ROMBANK[0][17],sys.ROMBANK[0][18],sys.ROMBANK[0][19],sys.ROMBANK[0][20]); sys.ROMloaded = 1; sys.HeaderSize = TAYLOR_CARTINIT(); }
}
void TAYLOR_CPU_Start() {
 if (sys.ROMloaded && !CPU[0].running && !CPU[1].running) {
  if (sys.EXTSAV && strlen(sys.SN)==0) {
   sys.ErrorType = 1; sprintf(sys.Error,"External SAV File not given!!\n"); TGR_printError();
  } else {
   for(uint8_t i=0;i<1;i++) { TAYLOR_CPU_ResetCore(i); TAYLOR_CPU_LoadPage(i,i); } //TAYLOR_dumpData(i?"ROM#0":"ROM#1", &sys.MEM[TGR_MEM_ROM_SIZE*i], TGR_MEM_ROM_SIZE, 0, 256);
   CPU[0].running=true; TAYLOR_PrintHeader();
}} else { sprintf(sys.Error, "Cannot Start Emulation due to ROM not loaded or system is already running!\n"); sys.ErrorType=0; TGR_printError(); }
}
void TAYLOR_CPU_Reset(bool hard) {
 if (sys.ROMloaded && sys.Resetting == false) {
  sys.Resetting = true;
  TAYLOR_FlushSAV();
  sprintf(TaylorPrintString,"%sReset...",(uint8_t*)(hard>0?"":"Hard ")); TGR_FilterAnsi(TaylorPrintString);
  CPU[0].running = CPU[1].running = GPU[0].running = GPU[1].running = GPU[2].running = GPU[3].running = GPUctl.Rez = GPUctl.NewRez = false;  TAYLOR_GPU_ResetAll(); WaitTime(0.001);
  if (hard>0) { memset(sys.MEM, 0, 0xD800000); }
  TAYLOR_CPU_Start();
  //CPU_ResetCore(0); CPU_ResetCore(1); CPU_LoadPage(1,1); CPU[0].running=true;
  sys.Resetting = false;
}}
void TAYLOR_CPU_Stop() { if (sys.ROMloaded) { TAYLOR_FlushSAV(); }
 CPU[0].running = CPU[1].running = GPU[0].running = GPU[1].running = GPU[2].running = GPU[3].running = GPUctl.Rez = GPUctl.NewRez = false; memset(sys.MEM, 0, 0xD800000);
}
void TAYLOR_CPU_State(int type) { sprintf(TaylorPrintString,"%s SAVESTATE\nWIP!!!\n",(uint8_t*)(type==0?"Loading":"Saving")); TGR_FilterAnsi(TaylorPrintString); }
//void CPU_memdump(uint8_t recvbuf[], uint8_t* sendbuf[]) {  }

uint16_t TAYLOR_CARTINIT() {
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
}}

uint64_t zeroup(int64_t x);

void TAYLOR_CPU_ResetCore(bool ID) {
 for(uint8_t i=0;i<8;i++){CPU[ID].REGs[i]=0; CPU[ID].flag[i]=false;}
 CPU[ID].Clock = CPU[ID].IPS = CPU[ID].TI = CPU[ID].time =\
 CPU[ID].running = CPU[ID].ticked = sys.Pause = 0;
 CPU[ID].MP = CPU[ID].SP = (ID==0)?0x97FFDFF:0x97DFDFF;
 CPU[ID].BP = (ID==0)?0x97DFE00:0x97BFE00;
 CPU[ID].IP=sys.HeaderSize;
}

void TAYLOR_CPU_LoadPage(bool SlotID, uint8_t PageID) {
 sys.PageID[SlotID]=PageID&0x21;
 memcpy(&sys.MEM[SlotID*TGR_MEM_ROM_SIZE], &sys.ROMBANK[PageID&0x21], TGR_MEM_ROM_SIZE);
}

void*TAYLOR_Clock() {
 uint32_t i=0;
 while(true) {
  usleep(1);
  if ((i%1000)==0) sys.Clock++, sys.ClockSync = true;
  if (!sys.Pause) {
   CPU[0].running?CPU[0].Clock++:0, CPU[1].running?CPU[1].Clock++:0,
   GPU[0].running?GPU[0].Clock++:0, GPU[1].running?GPU[1].Clock++:0,
   GPU[2].running?GPU[2].Clock++:0, GPU[3].running?GPU[3].Clock++:0;
  } if((sys.Clock%41)==0 && (i%1000)==0) { sys.TapeFrame++, sys.TapeFramed = true; }
  if((sys.Clock%1000)==0 && (i%1000)==0 && sys.DiscordEnrichmentInited) { OnUserUpdated(&sys.DiscordApp); }
  i++;
}}
void*TAYLOR_MemCheck() {
 double MemUse=0; bool l=0;
 while(true) {
  while(!sys.ClockSync) usleep(1);
  if(l) {for(uint32_t i=0;i<TGR_MEM_WRAM_FULL;i++) { MemUse+=sys.MEM[TGR_MEM_WRAM+i]/255.0f; } sys.MemUse = MemUse; }
  else {
   //if((sys.Clock%5000)==0) GPUctl.NewRez=(GPUctl.NewRez+1)%4;
   //GPUctl.NewRez = 1;
   sys.IPS[0] = CPU[0].IPS, sys.IPS[1] = CPU[1].IPS;
   sys.FPS = GPUctl.frames; GPUctl.frames = 0;
//   sprintf(TaylorPrintString,"\nFPS: %d | GPU[ID].Running:%s\nInstuctionsPerSecond: %8ld|%8ld (%8ld) -> %.4f%%\n\\                     24000000|24000000 (48000000) -> 100.0000%%\n\\TotalRan: %ld|%ld (%ld)\n\n",sys.FPS,GPU[ID].running?"True":"False", CPU[0].IPS, CPU[1].IPS, CPU[0].IPS+CPU[1].IPS, (((sys.IPS[0]+sys.IPS[1])/(float)(CPU[0].running+CPU[1].running))/24000000.0f)*100, CPU[0].TI,CPU[1].TI,CPU[0].TI+CPU[1].TI);
//   TGR_FilterAnsi(TaylorPrintString);
   CPU[0].IPS = CPU[1].IPS = 0;
   CPU[0].ticked=1; CPU[1].ticked=1;
   for(uint32_t i=0;i<TGR_MEM_VRAM_FULL;i++) { MemUse+=sys.MEM[TGR_MEM_VRAM+i]/255.0f; } sys.VMemUse = MemUse;
  } MemUse = 0, l=!l;
}}

void TAYLOR_CPU_PrintArea(uint8_t msg[], uint32_t IMM) {
 if (IMM>=TGR_MEM_ROM0    && IMM<TGR_MEM_ROM1   ) { sprintf(msg,"%s%s%s(Area 0:ROM PAGE#0)",msg,COLOR_NORMAL,COLOR_GREEN); } else
 if (IMM>=TGR_MEM_ROM1    && IMM<TGR_MEM_SAV    ) { sprintf(msg,"%s%s%s(Area 1:ROM PAGE#1)",msg,COLOR_NORMAL,COLOR_GREEN); } else
 if (IMM>=TGR_MEM_SAV     && IMM<TGR_MEM_WRAM   ) { sprintf(msg,  "%s%s(Area 2:SAV data)",msg,COLOR_BOLD); } else
 if (IMM>=TGR_MEM_WRAM    && IMM<TGR_MEM_STACK0 ) { sprintf(msg,"%s%s%s(Area 3:Work RAM)",msg,COLOR_BOLD,COLOR_RED); } else
 if (IMM>=TGR_MEM_STACK0  && IMM<TGR_MEM_STACK1 ) { sprintf(msg,  "%s%s(Area 4:Stack#0 Memory)",msg,COLOR_BLUE); } else
 if (IMM>=TGR_MEM_STACK1  && IMM<TGR_MEM_IO     ) { sprintf(msg,  "%s%s(Area 5:Stack#1 Memory)",msg,COLOR_BLUE); } else
 if (IMM>=TGR_MEM_IO      && IMM<TGR_MEM_SRAMEXT) { sprintf(msg,"%s%s%s(Area 6:Static Memory)",msg,COLOR_BOLD,COLOR_YELLOW); } else
 if (IMM>=TGR_MEM_SRAMEXT && IMM<TGR_MEM_VRAM   ) { sprintf(msg,"%s%s%s(Area 7:Extended RAM)",msg,COLOR_BOLD,COLOR_RED); } else
 if (IMM>=TGR_MEM_VRAM    && IMM<TGR_MEM_VSTACK0) { sprintf(msg,"%s%s%s(Area 8:Video RAM)",msg,COLOR_BOLD,COLOR_MAGENTA); } else
 if (IMM>=TGR_MEM_VSTACK0 && IMM<TGR_MEM_VSTACK1) { sprintf(msg,  "%s%s(Area 9:Stack#0 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_MEM_VSTACK1 && IMM<TGR_MEM_VSTACK2) { sprintf(msg,  "%s%s(Area A:Stack#1 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_MEM_VSTACK2 && IMM<TGR_MEM_VSTACK3) { sprintf(msg,  "%s%s(Area B:Stack#2 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_MEM_VSTACK3 && IMM<TGR_MEM_VRAMEXT) { sprintf(msg,  "%s%s(Area C:Stack#3 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_MEM_VRAMEXT && IMM<TGR_MEM_TOTAL  ) { sprintf(msg,"%s%s%s(Area D:Ext. Video RAM)",msg,COLOR_BOLD,COLOR_MAGENTA); }
 else { sprintf(msg,"%s%s(Area ?:Invalid Address)",msg,COLOR_RED); }
}
void*TAYLOR_CPU_Core(bool ID) {
 uint8_t msg[2048]={0};
 uint32_t i=0,j=0;
 uint8_t CPUPrintString[0xFFFF] = "";
 sys.DebugTick[ID] = true;
 //printf("CPU Process #%d Started!\n",ID);
 while(true) {
  if(CPU[ID].running && !sys.Debug && sys.DebugPause[ID]>0) { sys.DebugTick[ID] = true, sys.DebugPause[ID] = 0; }
  if(CPU[ID].running && !sys.Pause && sys.DebugTick[ID] && sys.Cutscene0Timer > 31*30) {
   #ifdef _WIN32
    clock_gettime(CLOCK_MONOTONIC, &start);
   #else
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
   #endif
   for(j=0;j<50000;j++) { CPU[ID].IP=CPU[ID].IP%0xD800000;
    if(!CPU[ID].running || sys.Pause || !sys.DebugTick[ID]) break;
    if(CPU[ID].ticked) CPU[ID].IPS = CPU[ID].ticked = 0;
    uint8_t A   =      sys.MEM[CPU[ID].IP+1] >> 4 ;       //4 \.
    uint8_t B   =      sys.MEM[CPU[ID].IP+1] & 0xF;       //4 |-> A/B/C = 1.5 bytes
    uint8_t C   =      sys.MEM[CPU[ID].IP+2] >> 4 ;       //4 /'
    int32_t IMM =((((((sys.MEM[CPU[ID].IP+2] & 0xF) << 8) //4 \.
                |      sys.MEM[CPU[ID].IP+3]) << 8)       //8 |->  IMM  = 3.5 bytes
                |      sys.MEM[CPU[ID].IP+4]) << 8)       //8 |
                |      sys.MEM[CPU[ID].IP+5];             //8 /'
    if (sys.DebugPause[ID]>0 && sys.Debug) {
     sprintf(msg,"%s%s%s\nBreakPoint[Core#%i] Ends in %d instructions! [PRESS CTRL + C TO QUIT BREAKPOINT]",msg,COLOR_BOLD,COLOR_YELLOW,ID,--sys.DebugPause[ID]-1); sys.DebugTick[ID] = false;
    }
    if (sys.MEM[CPU[ID].IP] == 0x22) {
     sys.BreakDebug = sys.Debug, sys.Debug = true, sys.DebugPause[ID] = IMM>0?IMM+1:INT32_MAX, sys.DebugTick[ID] = false;
     sprintf(msg,"%s%s%s\n[[CPU#%i BREAKPOINT ACTIVATED!]] Ends in %d instructions! [PRESS CTRL + C TO QUIT BREAKPOINT]",msg,COLOR_BOLD,COLOR_YELLOW,ID,sys.DebugPause[ID]-1);
    }
    if (sys.Debug == true) {
     sprintf(msg,"%s%s%s\n[Core%s#%s%x] %sIC: %s0x%07X%s/%s%9i %s%s",msg,COLOR_BOLD,COLOR_GREEN,COLOR_RED,COLOR_GREEN,ID,COLOR_YELLOW,COLOR_CYAN,CPU[ID].IP,COLOR_YELLOW,COLOR_CYAN,CPU[ID].IP,COLOR_NORMAL,COLOR_GREEN);
     TAYLOR_CPU_PrintArea(msg,CPU[ID].IP);
     sprintf(msg,"%s %s| %sTotalRan: %s%ld %s(%ld)\n%s\\ %s>> %s[",msg,COLOR_BOLD,COLOR_YELLOW,COLOR_GREEN,CPU[ID].TI,COLOR_NORMAL,CPU[0].TI+CPU[1].TI,COLOR_BOLD,COLOR_YELLOW,COLOR_NORMAL);
     for (i=0; i < 6; i++) { sprintf(msg,"%s%s%s0x%02X%s%s",msg,COLOR_BOLD,COLOR_BLUE,sys.MEM[CPU[ID].IP+i],COLOR_NORMAL,COLOR_YELLOW); if (i < 5) { sprintf(msg,"%s, ",msg); } }
     sprintf(msg,"%s] %s| %s[%s%sA%s:%s%c%s%s, %s%sB%s:%s%c%s%s, %s%sC%s:%s%c%s%s, %s%sIMM%s:%s0x%07X%s%s]\n%s%s\\%sREGs: %s[",msg,COLOR_BOLD,COLOR_NORMAL,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,sys.REG[A],COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,sys.REG[B],COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,sys.REG[B],COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,IMM,COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_NORMAL);
     for (i=0; i < 8; i++) { sprintf(msg,"%s%s%s%c%s:%s0x%04X%s%s%s",msg,COLOR_BOLD,COLOR_GREEN,sys.REG[i],COLOR_YELLOW,COLOR_MAGENTA,CPU[ID].REGs[i],COLOR_NORMAL,COLOR_YELLOW,(uint8_t*)(i<7?", ":"")); }
     sprintf(msg,"%s]\n%s%s\\%sStackPointer: %s0x%x%s/%s%d %s| StackBase: 0x%x/%d\n\\\\StackData:[",msg,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_CYAN,CPU[ID].SP,COLOR_YELLOW,COLOR_CYAN,CPU[ID].SP,COLOR_GREEN,CPU[ID].BP,CPU[ID].BP);
     for (i = CPU[ID].SP+1; i <= CPU[ID].MP; ++i) {
      if(i%2==0) { sprintf(msg,"%s%s%s 0x",msg,COLOR_BLACK,COLOR_BG_YELLOW); }
      sprintf(msg,"%s%02X",msg,sys.MEM[i]);
      if(i%16==0 && i != 0) { sprintf(msg,"%s%s%s\n",msg,COLOR_RESET,COLOR_YELLOW); }
     } sprintf(msg,"%s%s%s]\n \\instruction: ",msg,COLOR_RESET,COLOR_YELLOW);
    }
    //Flags | WrittenREG, ReadREG, OverFlow, PointerOOB, ALUoperated, DivideBy0
    switch(sys.MEM[CPU[ID].IP]) {
     case 0x00:// LOAD   |
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (C > 0) {
       if (sys.Debug == true) { sprintf(msg,"%sMOV\n",msg); }
       CPU[ID].REGs[A] = CPU[ID].REGs[B]; CPU[ID].flag[1]=true;
      } else {
       if (sys.Debug == true) { sprintf(msg,"%sLOAD\n",msg); }
       CPU[ID].REGs[A] = IMM;
      } break;
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
      if (IMM >= 1) { CPU[ID].REGs[C] = CPU[ID].REGs[A]/max(IMM,1);             if(CPU[ID].REGs[A]%max(IMM,1)            >0){CPU[ID].flag[2]=false;}}
      else {          CPU[ID].REGs[C] = CPU[ID].REGs[A]/max(CPU[ID].REGs[B],1); if(CPU[ID].REGs[A]%max(CPU[ID].REGs[B],1)>0){CPU[ID].flag[2]=false;}} break;
     case 0x05:// MOD    |
      if (sys.Debug == true) { sprintf(msg,"%sMOD\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true; CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
      if (CPU[ID].REGs[A]==0) {CPU[ID].REGs[C] = 0; CPU[ID].flag[5]=true; break;}
      if (IMM >= 1) { CPU[ID].REGs[C] = CPU[ID].REGs[A]%max(IMM,1);             }
      else {          CPU[ID].REGs[C] = CPU[ID].REGs[A]%max(CPU[ID].REGs[B],1); } break;
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
      for(i=0;i<8;i++) {CPU[ID].REGs[A]+=pow(2,i)*CPU[ID].flag[i]; if(sys.Debug==true){printf("CPU[ID].flag[%d]: %s\n",i,(uint8_t*)(CPU[ID].flag[i]?"true":"false"));} CPU[ID].flag[i]=false;} CPU[ID].flag[0]=true; break;
     case 0x0D:// JMP    |
      if (sys.Debug == true) { sprintf(msg,"%sJUMP\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if (C >= 1) { CPU[ID].IP = (CPU[ID].REGs[A]<<16|CPU[ID].REGs[B])-6; CPU[ID].flag[1]=true; }else{ CPU[ID].IP = IMM-6; } break;
    // case 0x0E:// CMPEQ  |
    //  if (sys.Debug == true) { sprintf(msg,"%sCMP=\n",msg); }
    //  memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
    //  if (IMM>0) {  if (CPU[ID].REGs[A] != IMM) { CPU[ID].IP += ((C>0)?C:1)*6; }
    //  }else if(CPU[ID].REGs[A] != CPU[ID].REGs[B]) { CPU[ID].IP += ((C>0)?C:1)*6; } break;
    // case 0x0F:// CMPLT  |
    //  if (sys.Debug == true) { sprintf(msg,"%sCMP<\n",msg); }
    //  memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
    //  if (IMM>0) { if (!(CPU[ID].REGs[A] <  IMM)) { CPU[ID].IP += ((C>0)?C:1)*6; }
    //  }else if(!(CPU[ID].REGs[A] <  CPU[ID].REGs[B])) { CPU[ID].IP += ((C>0)?C:1)*6; } break;
    // case 0x10:// CMPGT  |
    //  if (sys.Debug == true) { sprintf(msg,"%sCMP>\n",msg); }
    //  memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; CPU[ID].flag[4]=true;
    //  if (IMM>0) {  if (!(CPU[ID].REGs[A] >  IMM)) { CPU[ID].IP += ((C>0)?C:1)*6; }
    //  }else if(!(CPU[ID].REGs[A] >  CPU[ID].REGs[B])) { CPU[ID].IP += ((C>0)?C:1)*6; } break;


     case 0x0E:// CMPEQ  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP=\n",msg); }
      if ((IMM>0)?(CPU[ID].REGs[A] == (IMM&0x7FFFFFF)):(CPU[ID].REGs[A] == CPU[ID].REGs[B])) {
       if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
      } CPU[ID].IP += max(C,1)*6;
      if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;
     case 0x0F:// CMPLT  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP<\n",msg); }
      if ((IMM>0)?(CPU[ID].REGs[A] < (IMM&0x7FFFFFF)):(CPU[ID].REGs[A] < CPU[ID].REGs[B])) {
       if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
      } CPU[ID].IP += max(C,1)*6;
      if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;
     case 0x10:// CMPGT  |
      if (sys.Debug == true) { sprintf(msg,"%sCMP>\n",msg); }
      if ((IMM>0)?(CPU[ID].REGs[A] > (IMM&0x7FFFFFF)):(CPU[ID].REGs[A] > CPU[ID].REGs[B])) {
       if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
      } CPU[ID].IP += max(C,1)*6;
      if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;

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
      if (IMM > 0xD7FFFFF) { IMM = CPU[ID].REGs[B]<<16|CPU[ID].REGs[C]; }
      if (IMM > 0xD7FFFFF) { sprintf(CPUPrintString,"0x%07x\n0xD7FFFFF\n",IMM); TGR_FilterAnsi(CPUPrintString); IMM = IMM-0xD800000; }
      if (sys.Debug == true) {
       sprintf(msg,"%s%s%sWMEM\n  %s\\%sWriting REG:%s%c %sto %s0x%07x ",msg,COLOR_BOLD,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_GREEN,sys.REG[A],COLOR_YELLOW,COLOR_CYAN,IMM);
       TAYLOR_CPU_PrintArea(msg,IMM); sprintf(msg,"%s%s%s\n",msg,COLOR_NORMAL,COLOR_GREEN);
      }
      if (IMM > 0x0FFFFFF) {
       sys.MEM[IMM]=CPU[ID].REGs[A]; if (IMM>=0x1000000 && IMM<=0x17FFFFF) { TAYLOR_WriteSAV(IMM-0x1000000, CPU[ID].REGs[A]&0xFF); }
      } else {
       sys.ErrorType = 0; sprintf(sys.Error,"CPU#%i: Invalid Instuction, You cannot write to ROM!\n",ID);
      } break;
     case 0x14:// RMEM   |
      if (IMM > 0xD7FFFFF) { IMM = CPU[ID].REGs[B]<<16|CPU[ID].REGs[C]; }
      if (IMM > 0xD7FFFFF) { sprintf(CPUPrintString,"0x%07x\n0xD7FFFFF\n",IMM); TGR_FilterAnsi(CPUPrintString); IMM = IMM-0xD800000; }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (sys.Debug == true) {
       sprintf(msg,"%s%s%sRMEM\n  %s\\%sReading %s0x%07x %sto REG:%s%c ",msg,COLOR_BOLD,COLOR_RED,COLOR_GREEN,COLOR_YELLOW,COLOR_CYAN,IMM,COLOR_YELLOW,COLOR_GREEN,sys.REG[A]);
       TAYLOR_CPU_PrintArea(msg,IMM); sprintf(msg,"%s%s%s\n",msg,COLOR_NORMAL,COLOR_GREEN);
      } CPU[ID].REGs[A]=sys.MEM[IMM]; break;
     
     case 0x15:// HALT   |
      if (sys.Debug == true) { sprintf(msg,"%sHALT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      //sys.ErrorType = 0;
      //sprintf(sys.Error,"HALT INSTUCTION NOT FINISHED!\n");
      switch(A%4) {
       case 0:
        CPU[ID].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,ID);
        break;
       case 1:
        for(i=0;i<2;i++) { CPU[i].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,i); }
        break;
       case 2:
        for(i=0;i<2;i++) { CPU[i].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,i); }
        for(i=0;i<4;i++) { GPU[i].running=false; sprintf(msg,"%sHALTING GPU#%i!\n",msg,i); }
        break;
       case 3:
        for(i=0;i<2;i++) { CPU[i].running=false; sprintf(msg,"%sHALTING CPU#%i!\n",msg,i); }
        for(i=0;i<4;i++) { GPU[i].running=false; sprintf(msg,"%sHALTING GPU#%i!\n",msg,i); }
        TAYLOR_CPU_Reset(true); TAYLOR_GPU_ResetAll();
        break;
      }
      if (sys.DebugPause[ID]>0) { sys.DebugTick[ID] = true, sys.DebugPause[ID] = 0, sys.Debug = sys.BreakDebug; TGR_FilterAnsi(msg); }
      break;
     case 0x16:// DISP   |
     if (sys.Debug == true) { sprintf(msg,"%sDISP%s\n",msg,(uint8_t*)(sys.BlockDisp?" [BLOCKED]":"")); }
     if (sys.BlockDisp) break;
      uint8_t DispMsg[3][16] = {0};
      switch(IMM%3) {
       case 2: sprintf(DispMsg[2],"%c: 0x%04X\t",sys.REG[C],CPU[ID].REGs[C]);
       case 1: sprintf(DispMsg[1],"%c: 0x%04X\t",sys.REG[B],CPU[ID].REGs[B]);
       case 0: sprintf(DispMsg[0],"%c: 0x%04X\t",sys.REG[A],CPU[ID].REGs[A]); break;
      } sprintf(sys.Debug?msg:CPUPrintString,"%s%s%s%s\n",sys.Debug?msg:CPUPrintString,DispMsg[0],DispMsg[1],DispMsg[2]);
      if (!sys.Debug) TGR_FilterAnsi(CPUPrintString);
      break;
     case 0x17:// IPOUT  |
      if (sys.Debug == true) { sprintf(msg,"%sIPOUT\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      CPU[ID].REGs[A]=CPU[ID].IP>>16; CPU[ID].REGs[B]=CPU[ID].IP&0xFFFF;
      break;
     case 0x18:// PAGE   |
      if (sys.Debug == true) { sprintf(msg,"%sPAGE\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      TAYLOR_CPU_LoadPage(A%2,IMM&0xFF&0x21);
      break;
     case 0x19:// CORE   |
      if (sys.Debug == true) { sprintf(msg,"%sCORE\n",msg); }
      A=A%6;
      //A = CoreID
      //B = State
      //IMM = Start Address
      if (A>1) {
       if (sys.DebugGPUstart && B%2)
        sys.BreakDebug = sys.Debug, sys.Debug = true, sys.DebugPause[A-2] = INT32_MAX, sys.DebugTick[A-2] = true;
       TAYLOR_GPU_Reset(A-2);
       GPU[A-2].IP = IMM;
       GPU[A-2].running = B%2;
       sprintf(msg,"%s%s GPU#%d...\n",msg,(B%2)?"Starting":"Stopping",A-2);
      } else {
       CPU[A].IP = IMM;
       CPU[A].running = B%2;
       sprintf(msg,"%s%s CPU#%d...\n",msg,(B%2)?"Starting":"Stopping",A-2);
      } break;
     case 0x1A:// PUSH   |
      if (sys.Debug == true) { sprintf(msg,"%sPUSH\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true;
      if (CPU[ID].SP-2 < CPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! STACK OVERFLOW!!\n",ID); CPU[ID].running=false; break;}
      else {sys.MEM[CPU[ID].SP--] = CPU[ID].REGs[A]&0xFF,sys.MEM[CPU[ID].SP--] = CPU[ID].REGs[A]>>8; } break;
     case 0x1B:// POP    |
      if (sys.Debug == true) { sprintf(msg,"%sPOP\n",msg); }
      memset(CPU[ID].flag, 0, 8); CPU[ID].flag[0]=true;
      if (CPU[ID].SP+2 > CPU[ID].MP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! stack empty...\n",ID); CPU[ID].running=false; break;}
      else {CPU[ID].REGs[A] = sys.MEM[++CPU[ID].SP]<<8|sys.MEM[++CPU[ID].SP]; } break;
     case 0x1C:// CALL   |
      if (sys.Debug == true) { sprintf(msg,"%sCALL\n",msg); } if(C>0){CPU[ID].flag[1]=true;}
      if (CPU[ID].SP-4 < CPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! STACK OVERFLOW!!\n",ID); CPU[ID].running=false; break;}
      else {sys.MEM[CPU[ID].SP--] = CPU[ID].IP,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>8,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>16,sys.MEM[CPU[ID].SP--] = CPU[ID].IP>>24,CPU[ID].IP = (IMM>0?IMM:(CPU[ID].REGs[A]<<16|CPU[ID].REGs[B])%0xD800000)-6;} break;
     case 0x1D:// RET    |
      if (sys.Debug == true) { sprintf(msg,"%sRET\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      if (CPU[ID].SP+4 > CPU[ID].MP) {sys.ErrorType = 3; sprintf(sys.Error,"CPU#%i: PANIC! stack empty...\n",ID); CPU[ID].running=false; break;}
       CPU[ID].IP = sys.MEM[++CPU[ID].SP]>>24|sys.MEM[++CPU[ID].SP]<<16|sys.MEM[++CPU[ID].SP]<<8|sys.MEM[++CPU[ID].SP]; break;
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
      if (IMM>0){ sys.LED[2] = IMM&0xFF; sys.LED[1] = (IMM>>8)&0xFF; sys.LED[0] = (IMM>>16)&0xFF; }
      else { sys.LED[0] = CPU[ID].REGs[A]&0xFF; sys.LED[1] = CPU[ID].REGs[B]&0xFF; sys.LED[2] = CPU[ID].REGs[C]&0xFF; }
      if (sys.Debug == true) { sprintf(msg,"%sLED\n  \\sys.LED is set to #%02X%02X%02X\n",msg,sys.LED[0],sys.LED[1],sys.LED[2]); }
      //sprintf(CPUPrintString,"sys.LED is set to #%02X%02X%02X\n",sys.LED[0],sys.LED[1],sys.LED[2]); TGR_FilterAnsi(CPUPrintString);
      break;
     case 0x20:// CLK    |
      if (sys.Debug == true) { sprintf(msg,"%sCLOCK\n",msg); }
      memset(CPU[ID].flag, 0, 8);
      CPU[ID].flag[1]=true; CPU[ID].REGs[A]=CPU[ID].Clock>>16,CPU[ID].REGs[B]=CPU[ID].Clock&0xFFFF;
      if (IMM>0) CPU[ID].Clock=0;
      break;
     case 0x21:// WAIT   |
      if (sys.Debug == true) {
       sprintf(msg,"%sWAIT | ", msg);
       if(IMM>0) { sprintf(msg,"%sIMM: %dus (%0.04f secs.)\n",msg, IMM, IMM/1000000.0f); }
       else { sprintf(msg,"%sREG[%c..%c]: %dus (%0.04f secs.)\n",msg, sys.REG[A],sys.REG[B], (CPU[ID].REGs[A]<<16)|CPU[ID].REGs[B], ((CPU[ID].REGs[A]<<16)|CPU[ID].REGs[B])/1000000.0f); }
      } if (!IMM>0) { memset(CPU[ID].flag, 0, 8); CPU[ID].flag[1]=true; }
      break;
     case 0x22:// BREAK |
      if (sys.Debug == true) { sprintf(msg,"%sBREAKPOINT\n",msg); }
      //operation happens before cycle//
      break;
     case 0xFF:// NOP    |
      if (sys.Debug == true) { sprintf(msg,"%sNOP\n",msg); }
      memset(CPU[ID].flag, 0, 8); break;
     default:
      if (sys.Debug == true) { sprintf(msg,"%sUNKNOWN\n",msg); }
      sys.ErrorType = 2; sprintf(sys.Error,"CPU#%i: Unknown Operation 0x%02X at 0x%07X\n",ID,sys.MEM[CPU[ID].IP],CPU[ID].IP);
      CPU[ID].running = 0; break;
    } CPU[ID].IP+=6; CPU[ID].IPS++; CPU[ID].TI++;
    if (sys.DebugPause[ID]==1) { sys.DebugTick[ID] = true, sys.DebugPause[ID] = 0, sys.Debug = false; sprintf(msg, "%s[[BREAKPOINT DEACTIVATED!]] Debug mode is Disabled!\n",msg); TGR_FilterAnsi(msg); }
    else if (sys.DebugPause[ID]>0) { sprintf(msg,"%s%s%s[  #######  PRESS ENTER  #######  ]\n",msg,COLOR_RESET,COLOR_YELLOW);  sys.DebugTick[ID] = false; }
    //else { sys.DebugTick[ID] = true, sys.DebugPause[ID] = 0, sys.Debug = false; }
    if (sys.Debug == true) { TGR_FilterAnsi(msg); } TGR_printError();
    sprintf(msg,"");  sprintf(CPUPrintString,"");
    if (sys.MEM[CPU[ID].IP] == 0x21) { usleep(IMM>0?IMM:((CPU[ID].REGs[A]<<16)|CPU[ID].REGs[B])); }
   }
   #ifdef _WIN32
    clock_gettime(CLOCK_MONOTONIC, &end);
   #else
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
   #endif
//   if (zeroup(1000-((end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000.0))/1000.0>0)
//    sprintf(CPUPrintString,"CPU[%i] delay: %f\n",ID,zeroup(1000-((end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000.0))/1000.0); TGR_FilterAnsi(CPUPrintString);
//    WaitTime(zeroup(1000-((end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000.0))/1000.0);
  // WaitTime(0.001);
  } else {
   usleep(1);
}} printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!  CPU Process #%d ENDED! !!\n!!! THIS SHOULDN'T HAPPEN !!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n",ID);
}

uint32_t TAYLOR_LEGACY_GPU_randi(uint32_t min, uint32_t max, uint32_t seed) { return (max*(((seed*2)%max)*100000)+min)%max; }
uint16_t TAYLOR_LEGACY_GPU_getx(uint32_t i) { return i%TGR_GPU_Resolutions[GPUctl.Rez][0]; }
uint16_t TAYLOR_LEGACY_GPU_gety(uint32_t i) { return (i-(i%TGR_GPU_Resolutions[GPUctl.Rez][0]))/TGR_GPU_Resolutions[GPUctl.Rez][0]; }
uint32_t TAYLOR_LEGACY_GPU_geti(uint16_t x,uint16_t y) { return ((y%TGR_GPU_Resolutions[GPUctl.Rez][1])*TGR_GPU_Resolutions[GPUctl.Rez][0])+(x%TGR_GPU_Resolutions[GPUctl.Rez][0]); }
/*
void GPU_makeCanvas(uint8_t ID, uint16_t Width,uint16_t Height) {
 uint32_t canvasAddr = TGR_MEM_VRAM+GPU[ID].cp;
// sprintf(TaylorPrintString,"Creating Canvas Buffer Address: 0x%07x: [Width: %i, Height: %i]\n",canvasAddr,Width,Height); TGR_FilterAnsi(TaylorPrintString);
 if (canvasAddr+4+Width*Height*4>0xD77FFFF) { sys.ErrorType = 0; sprintf(sys.Error,"GPU: cannot make canvas buffer (Video Memory OverFlow)!!\n"); TGR_printError(); return; }
 sys.MEM[canvasAddr++] =(Width>>8)&0xFF;
 sys.MEM[canvasAddr++] = Width    &0xFF;
 sys.MEM[canvasAddr++] =(Height>>8)&0xFF;
 sys.MEM[canvasAddr++] = Height    &0xFF;
// sprintf(TaylorPrintString,"canvasAddr: 0x%07x\n",canvasAddr); TGR_FilterAnsi(TaylorPrintString);
}
void GPU_plot(uint16_t x,uint16_t y, uint8_t r,uint8_t g,uint8_t b,uint8_t a) {
 uint32_t canvasAddr = TGR_MEM_VRAM+GPU[ID].cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 if(x<0|x>Width-1|y<0|y>Height-1){return;}
 canvasAddr+=GPU_geti(x,y)*4,
 sys.MEM[canvasAddr+0]=r,
 sys.MEM[canvasAddr+1]=g,
 sys.MEM[canvasAddr+2]=b,
 sys.MEM[canvasAddr+3]=a;
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
 
// for(uint16_t xi=(x<x2?x:x2);xi<=(x>x2?x:x2);xi++) { if(xi>Width-1|(((double)(y2-y)/(x2-x))*(xi-x)+y)>Height-1){continue;} GPU_plot(canvasAddr-TGR_MEM_VRAM+5, xi,((double)(y2-y)/(x2-x))*(xi-x)+y, r,g,b,a); }
// for(uint16_t yi=(y<y2?y:y2);yi<=(y>y2?y:y2);yi++) { if((((double)(x2-x)/(y2-y))*(yi-y)+x)>Width-1|yi>Height-1){continue;} GPU_plot(canvasAddr-TGR_MEM_VRAM+5, ((double)(x2-x)/(y2-y))*(yi-y)+x,yi, r,g,b,a); }
}


void LoadSurface() {
 UnloadImage(GPU[ID].Canvas);
 uint32_t canvasAddr = TGR_MEM_VRAM+GPU[ID].cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 GPU[ID].Canvas = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0, 0);
 memcpy((uint8_t*)GPU[ID].Canvas->pixels, &sys.MEM[canvasAddr], GPU[ID].Canvas->pitch*GPU[ID].Canvas->h);
 // Memory -> Canvas
}
void SaveSurface() {
 uint32_t canvasAddr = TGR_MEM_VRAM+GPU[ID].cp;
 uint16_t Width = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++],Height = sys.MEM[canvasAddr++]<<8|sys.MEM[canvasAddr++];
 memcpy(&sys.MEM[canvasAddr], (uint8_t*)GPU[ID].Canvas->pixels, GPU[ID].Canvas->pitch*GPU[ID].Canvas->h);
 SDL_FreeSurface(GPU[ID].Canvas);
 // Canvas -> Memory
}*/

void TAYLOR_LEGACY_HSV2RGB2(float h,float s,float v, int8_t*rx,int8_t*gx,int8_t*bx) {
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

void*TAYLOR_GPU_Main() {
 uint32_t i,j=0,k=0;
 uint8_t msg[2048]={0};
 uint32_t ptraddr;
 pthread_t call_GPUCore[4], call_GPUGraphicsCore;
 TAYLOR_GPU_ResetAll();
 TAYLOR_GPU_InitNodes();
 for(i=0;i<4;i++) {
  pthread_create(&call_GPUCore[i], NULL, &TAYLOR_GPU_Core, i); 
 }
 pthread_create(&call_GPUGraphicsCore, NULL, &TAYLOR_GPU_GraphicsCore, 0);
 #if TAYLOR_GPU_DEBUG_TEST
  uint32_t counter = 0;
  uint8_t text[1024] = "";
  ImageClearBackground(&GPUctl.Layers[1],(Color){0,0,0,0});
 #endif
 //GPUctl.FrameRendering == true;
 while(1) {
  #if TAYLOR_GPU_DEBUG_TEST
   if (GPUctl.FrameSeen = true) {
    //GPUctl.FrameRendering == true;
    GPUctl.FrameSeen = false;
    ImageClearBackground(&GPUctl.Layers[0],(Color){0x00,0,0x00,0xFF});
    ImageDrawLine(&GPUctl.Layers[0],0,0,TGR_GPU_Resolutions[GPUctl.Rez][0]-1,TGR_GPU_Resolutions[GPUctl.Rez][1]-1,(Color){0xFF,0x00,0xFF,0xFF});
    ImageDrawLine(&GPUctl.Layers[0],TGR_GPU_Resolutions[GPUctl.Rez][0]-1,0,0,TGR_GPU_Resolutions[GPUctl.Rez][1]-1,(Color){0xFF,0xFF,0x00,0xFF});
    for(i=0;i<32;i++) { ImageDrawPixel(&GPUctl.Layers[0], i*2,1, (counter>>i&1)?(Color){0xFF,0xFF,0xFF,0xFF}:(Color){0,0,0,0xFF}); }
    sprintf(text,"Hello World!\nCount: 0x%04X",counter++);
    getCharExt(&GPUctl.Layers[0], text, 2*8, 33*8, TGR_BLUE,true,1);
    ImageDrawLine(&GPUctl.Layers[0], 2*8, TGR_GPU_Resolutions[GPUctl.Rez][1]-8*8,3*8,  TGR_GPU_Resolutions[GPUctl.Rez][1]-8*8,(Color){0xFF,0x00,0x00,0xFF});
 
    uint8_t r,g,b,x=0,y=0; do {
     for(uint8_t y=0;y<32;y++){
      TAYLOR_LEGACY_HSV2RGB2(x/255.0, 1.0, 1.0, &r,&g,&b);
      ImageDrawPixel(&GPUctl.Layers[1],100+x,0+y,(Color){r,g,b,y/32.0*255});
    }}while(++x);
    ImageDraw(&GPUctl.Layers[0], GPUctl.Layers[1], (Rectangle){0,0,GPUctl.Layers[0].width,GPUctl.Layers[0].height}, (Rectangle){0,0,GPUctl.Layers[4].width,GPUctl.Layers[4].height}, WHITE);
    ImageDraw(&GPUctl.Layers[4], GPUctl.Layers[0], (Rectangle){0,0,GPUctl.Layers[0].width,GPUctl.Layers[0].height}, (Rectangle){0,0,GPUctl.Layers[4].width,GPUctl.Layers[4].height}, WHITE);
    GPUctl.FrameRendering = false;
    GPUctl.frames++;
//   ptraddr = sys.MEM[TGR_MEM_VRAM+CPLength+4*8+0]<<24|sys.MEM[TGR_MEM_VRAM+CPLength+4*8+1]<<16|sys.MEM[TGR_MEM_VRAM+CPLength+4*8+2]<<8|sys.MEM[TGR_MEM_VRAM+CPLength+4*8+3];
//   sys.MEM[ptraddr+1*4+1] = 0xFF;
  }
  #endif
  
  
  WaitTime(0.01); //60 UpdatesPerSecond target
}}

void TAYLOR_GPU_PrintArea(uint8_t msg[], uint32_t IMM) {
 if (IMM>=TGR_VMEM_VRAM    && IMM<TGR_VMEM_VSTACK0) { sprintf(msg,"%s%s%s(Area 8:Video RAM)",msg,COLOR_BOLD,COLOR_MAGENTA); } else
 if (IMM>=TGR_VMEM_VSTACK0 && IMM<TGR_VMEM_VSTACK1) { sprintf(msg,  "%s%s(Area 9:Stack#0 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_VMEM_VSTACK1 && IMM<TGR_VMEM_VSTACK2) { sprintf(msg,  "%s%s(Area A:Stack#1 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_VMEM_VSTACK2 && IMM<TGR_VMEM_VSTACK3) { sprintf(msg,  "%s%s(Area B:Stack#2 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_VMEM_VSTACK3 && IMM<TGR_VMEM_VRAMEXT) { sprintf(msg,  "%s%s(Area C:Stack#3 VMem)",msg,COLOR_MAGENTA); } else
 if (IMM>=TGR_VMEM_VRAMEXT && IMM<TGR_VMEM_TOTAL  ) { sprintf(msg,"%s%s%s(Area D:Ext. Video RAM)",msg,COLOR_BOLD,COLOR_MAGENTA); }
 else { sprintf(msg,"%s%s(Area ?:Invalid Address",msg,COLOR_RED); }
}

void TAYLOR_GPU_InitNodes() {
 for(uint16_t i=0; i<GPU_RENDER_NODE_LEN; i++) 
  for(uint8_t j=0; j<GPU_CORE_COUNT; j++) 
   GPU_RENDER_NODES[j][i].Oper = 0xFF;
}
int16_t TAYLOR_GPU_FindFreeNode(uint8_t ID) {
 for(uint16_t i=0; i<GPU_RENDER_NODE_LEN; i++) if (GPU_RENDER_NODES[ID][i].Oper == 0xFF) return i;
 return -1;
}

void TAYLOR_GPU_SpawnNode(uint8_t ID, uint16_t worker, uint8_t opcode, uint8_t A, uint8_t B, uint8_t C, uint32_t IMM) {
 if (worker > GPU_RENDER_NODE_LEN) return;
 GPU_RENDER_NODES[ID][worker].Oper = opcode,
 GPU_RENDER_NODES[ID][worker].R = GPU[ID].R,
 GPU_RENDER_NODES[ID][worker].G = GPU[ID].G,
 GPU_RENDER_NODES[ID][worker].B = GPU[ID].B,
 GPU_RENDER_NODES[ID][worker].A = GPU[ID].A,
 GPU_RENDER_NODES[ID][worker].Layer = GPU[ID].Layer,
 GPU_RENDER_NODES[ID][worker].sp = GPU[ID].sp,
 GPU_RENDER_NODES[ID][worker].OperA = A,
 GPU_RENDER_NODES[ID][worker].OperB = B,
 GPU_RENDER_NODES[ID][worker].OperC = C,
 GPU_RENDER_NODES[ID][worker].OperIMM = IMM;
 memcpy(GPU_RENDER_NODES[ID][worker].CP, GPU[ID].CP, 256*4);
 memcpy(GPU_RENDER_NODES[ID][worker].X,  GPU[ID].X,  2*4);
 memcpy(GPU_RENDER_NODES[ID][worker].Y,  GPU[ID].Y,  2*4);
}

void*TAYLOR_GPU_Core(uint8_t ID) {
 uint8_t msg[2048]={0}, GPUPrintString[0xFFFF] = "";
 sys.DebugTick[ID+2] = true;
 uint16_t worker = 0;
 bool frameflip = 0;
 
 uint32_t i,j=0,k=0,ptraddr,
  target_fps = 60,
  dat = 400000,
  max_loops_between_frames = dat/target_fps,
  loops_since_last_frame = 0;
 long sleep_time;
 
 //printf("GPU Process #%d Started!\n",ID);
 struct timespec start, end;
 clock_gettime(CLOCK_MONOTONIC, &start);
 bool useIMM;
 while(true) {
  useIMM = false;
  //printf("GPU[%d].running: %s, sys.Pause: %s, sys.DebugTick[%d]: %s, sys.Cutscene0Timer: %d, sys.ScreenReady: %s\n", ID, GPU[ID].running?"true":"false", sys.Pause?"true":"false", ID+2, sys.DebugTick[ID+2]?"true":"false", sys.Cutscene0Timer, sys.ScreenReady?"true":"false");
  if(GPU[ID].running && !sys.Debug && sys.DebugPause[ID+2]>0) { sys.DebugTick[ID+2] = true, sys.DebugPause[ID+2] = 0; }
  if(GPU[ID].running && !sys.Pause && sys.DebugTick[ID+2] && (sys.Cutscene0Timer > 31*30) && sys.ScreenReady == true) {
   
//   printf("TICK GPUCore(%d)!\n",ID);
   // X, X2, Y, Y2, InstructionPointer, StackPointer, SpritePointer, R,G,B,A, E,I,O,U
   //printf("TGR_MEM_VRAM+GPU[ID].IP+1: 0x%07X\n-------------------------: 0xD800000\n", TGR_MEM_VRAM+GPU[ID].IP+1);
   uint8_t A   =      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+1)%0xD800000] >> 4 ,       //4 \.
           B   =      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+1)%0xD800000] & 0xF,       //4 |-> A/B/C = 1.5 bytes
           C   =      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+2)%0xD800000] >> 4 ;       //4 /'
   int32_t IMM =((((((sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+2)%0xD800000] & 0xF) << 8) //4 \.
               |      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+3)%0xD800000]) << 8)       //8 |->  IMM  = 3.5 bytes
               |      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+4)%0xD800000]) << 8)       //8 |
               |      sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+5)%0xD800000];             //8 /'
   GPUctl.FrameRendering == true;
   if (sys.DebugPause[ID+2]>0 && sys.Debug) {
    sprintf(msg,"%s%s%s\nBreakPoint[GPU#%i] Ends in %d instructions! [PRESS CTRL + C TO QUIT BREAKPOINT]",msg,COLOR_BOLD,COLOR_YELLOW,ID,--sys.DebugPause[ID+2]-1); sys.DebugTick[ID+2] = false;
   }
   if (sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP)%0xD800000] == 0x1F) {
    sys.BreakDebug = sys.Debug, sys.Debug = true, sys.DebugPause[ID+2] = IMM>0?IMM+1:INT32_MAX, sys.DebugTick[ID+2] = false;
    sprintf(msg,"%s%s%s\n[[GPU#%i BREAKPOINT ACTIVATED!]] Ends in %d instructions! [PRESS CTRL + C TO QUIT BREAKPOINT]",msg,COLOR_BOLD,COLOR_YELLOW,ID,sys.DebugPause[ID+2]-1);
   }
   if (sys.Debug == true) {
    sprintf(msg,"%s\n[GPU%s#%s%d] IC: 0x%07X/%9i ",msg,COLOR_RED,COLOR_GREEN,ID,GPU[ID].IP,GPU[ID].IP);
    TAYLOR_GPU_PrintArea(msg,GPU[ID].IP); sprintf(msg,"%s\n\\ >> [",msg);
    for (i=0; i < 6; i++) { sprintf(msg,"%s%s%s0x%02X%s%s%s",msg,COLOR_BOLD,COLOR_BLUE,sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP+i)%0xD800000],COLOR_NORMAL,COLOR_YELLOW,(i<5)?", ":""); }
    sprintf(msg,"%s] %s| %s[%s%sA%s:%s%s%s%s, %s%sB%s:%s%s%s%s, %s%sC%s:%s%s%s%s, %s%sIMM%s:%s0x%07X%s%s]\n%s%s\\%sREGs: %s[",msg,COLOR_BOLD,COLOR_NORMAL,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,TAYLOR_GPU_REG(A),COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,TAYLOR_GPU_REG(B),COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,TAYLOR_GPU_REG(C),COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_BLUE,IMM,COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,COLOR_YELLOW,COLOR_NORMAL);
    // 0, 1, . . . X[2]    16-bit X Position / X2/Width Position
    // 2, 3, . . . Y[2]    16-bit Y Position / Y2/Height Position
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s%s%s%s:%s0x%04X%s%s%s",msg,COLOR_BOLD,COLOR_GREEN,TAYLOR_GPU_REG(i),COLOR_YELLOW,COLOR_MAGENTA,TAYLOR_GPU_REGR(ID, i),COLOR_NORMAL,COLOR_YELLOW,(i<7)?", ":""); }
    // 4 . . . . . IP      28-bit Instuction Pointer
    // 5 . . . . . SP      28-bit Stack Pointer
    // 6 . . . . . sp:     28-bit Sprite Pointer
    // 7 . . . . . cp:     28-bit Canvas Pointer
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s%s%s%s:%s0x%06X%s%s, ",msg,COLOR_BOLD,COLOR_GREEN,TAYLOR_GPU_REG(4+i),COLOR_YELLOW,COLOR_MAGENTA,TAYLOR_GPU_REGR(ID, 4+i),COLOR_NORMAL,COLOR_YELLOW); }
    // 8, 9,10,11, R,G,B,A  8-bit Red, Green, Blue, Alpha
    sprintf(msg,"%s\n \\",msg);
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s%s%s%s:%s0x%02X%s%s, ",msg,COLOR_BOLD,COLOR_GREEN,TAYLOR_GPU_REG(8+i),COLOR_YELLOW,COLOR_MAGENTA,TAYLOR_GPU_REGR(ID, 8+i),COLOR_NORMAL,COLOR_YELLOW); }
    //12,13,14,15, E,I,O,U 28-bit General Purpose Registers
    for (i=0; i < 4; i++) { sprintf(msg,"%s%s%s%s%s:%s0x%06X%s%s%s",msg,COLOR_BOLD,COLOR_GREEN,TAYLOR_GPU_REG(12+i),COLOR_YELLOW,COLOR_MAGENTA,TAYLOR_GPU_REGR(ID, 12+i),COLOR_NORMAL,COLOR_YELLOW,(i<3)?", ":""); }
 
    sprintf(msg,"%s,\n  \\%s%s%s%s:%s0x%06X%s%s, %s%s%s%s:%s0x%06X%s%s, ",msg,COLOR_BOLD,COLOR_GREEN,"X3",COLOR_YELLOW,COLOR_MAGENTA,GPU[ID].X[2],COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,"Y3",COLOR_YELLOW,COLOR_MAGENTA,GPU[ID].Y[2],COLOR_NORMAL,COLOR_YELLOW);
    sprintf(msg,       "%s%s%s%s%s:%s0x%06X%s%s, %s%s%s%s:%s0x%06X%s%s",  msg,COLOR_BOLD,COLOR_GREEN,"X4",COLOR_YELLOW,COLOR_MAGENTA,GPU[ID].X[3],COLOR_NORMAL,COLOR_YELLOW,COLOR_BOLD,COLOR_GREEN,"Y4",COLOR_YELLOW,COLOR_MAGENTA,GPU[ID].Y[3],COLOR_NORMAL,COLOR_YELLOW);
 //    sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[0],GPU[ID].REGs[0]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[1],GPU[ID].REGs[1]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[2],GPU[ID].REGs[2]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[3],GPU[ID].REGs[3]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[4],GPU[ID].REGs[4]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[5],GPU[ID].REGs[5]); sprintf(msg,"%s%c:0x%04X, ",msg,sys.REG[6],GPU[ID].REGs[6]); sprintf(msg,"%s%c:0x%04X"  ,msg,sys.REG[7],GPU[ID].REGs[7]);
    sprintf(msg,"%s] | TotalRan: %ld\n\\StackPointer: 0x%x/%d | StackBase: 0x%x/%d\n\\\\StackData:[",msg,GPU[ID].TI,GPU[ID].SP,GPU[ID].SP,GPU[ID].BP,GPU[ID].BP);
    for (i = TGR_MEM_VRAM+GPU[ID].SP+1; i <= TGR_MEM_VRAM+GPU[ID].MP; ++i) {
     if((i+1)%2==0) { sprintf(msg,"%s%s%s 0x",msg,COLOR_BLACK,COLOR_BG_YELLOW); }
     sprintf(msg,"%s%02X",msg,sys.MEM[i]);
     if(i%16==0 && i != 0) { sprintf(msg,"%s%s%s\n",msg,COLOR_RESET,COLOR_YELLOW); }
    } sprintf(msg,"%s%s%s]\n \\instruction: ",msg,COLOR_RESET,COLOR_YELLOW);
   }
   //if (sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP)%0xD800000] > 0x6F) {
    //if ((worker = GPUFindFreeNode()) < 0) { sprintf(sys.Error,"Could Not Find Free Node!! (Worker: %d)\n",worker); sys.ErrorType = 0; }
    //printf("Worker: %i\n",worker);
   //}
   switch(sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP)%0xD800000]) {
    case 0x00:
     if (sys.Debug == true) { sprintf(msg,"%sLOAD\n",msg); }
     TAYLOR_GPU_REGW(ID, A, IMM);
     break;
    case 0x01:
     if (sys.Debug == true) { sprintf(msg,"%sMOV\n",msg); }
     TAYLOR_GPU_REGW(ID, A, TAYLOR_GPU_REGR(ID,B));
     break;
    case 0x02:// ADD    |
     if (sys.Debug == true) { sprintf(msg,"%sADD\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)+IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)+TAYLOR_GPU_REGR(ID,B));} break;
    case 0x03:// SUB    |
     if (sys.Debug == true) { sprintf(msg,"%sSUB\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)-IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)-TAYLOR_GPU_REGR(ID,B));} break;
    case 0x04:// MUL    |
     if (sys.Debug == true) { sprintf(msg,"%sMUL\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)*IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)*TAYLOR_GPU_REGR(ID,B));} break;
    case 0x05:// DIV    |
     if (sys.Debug == true) { sprintf(msg,"%sDIV\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)/max(IMM,1));}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)/max(TAYLOR_GPU_REGR(ID,B),1));} break;
    case 0x06:// MOD    |
     if (sys.Debug == true) { sprintf(msg,"%sMOD\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)%max(IMM,1));}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)%max(TAYLOR_GPU_REGR(ID,B),1));} break;
    case 0x07:// AND    |
     if (sys.Debug == true) { sprintf(msg,"%sAND\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)&IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)&TAYLOR_GPU_REGR(ID,B));} break;
    case 0x08:// OR     |
     if (sys.Debug == true) { sprintf(msg,"%sOR\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)|IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)|TAYLOR_GPU_REGR(ID,B));} break;
    case 0x09:// XOR    |
     if (sys.Debug == true) { sprintf(msg,"%sXOR\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)^IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)^TAYLOR_GPU_REGR(ID,B));} break;
    case 0x0A:// BSL    |
     if (sys.Debug == true) { sprintf(msg,"%sBSL\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)<<IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)<<TAYLOR_GPU_REGR(ID,B));} break;
    case 0x0B:// BSR    |
     if (sys.Debug == true) { sprintf(msg,"%sBSR\n",msg); }
     if (IMM > 0) { TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)>>IMM);}
     else {         TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A)>>TAYLOR_GPU_REGR(ID,B));} break;
    case 0x0C:// NOT    |
     if (sys.Debug == true) { sprintf(msg,"%sNOT\n",msg); }
     TAYLOR_GPU_REGW(ID, A, ~TAYLOR_GPU_REGR(ID,A)); break;
    case 0x0D:// CMPEQ  |
     //printf("=IMM: %d\n",IMM&0x7FFFFFF);
     if(IMM>0x7FFFFFF) useIMM = true, IMM &= 0x7FFFFFF;
     if(IMM>0x3FFFFFF) IMM -= 0x8000000; //negitive
     //printf(">> %d\n",IMM);
     if (sys.Debug == true) { sprintf(msg,"%sCMP=\n",msg); }
     //printf("IMM>0: %s, %s/0x%07X==0x%07X: %d, %s/0x%07X==%s/0x%07X: %d\n", IMM>0?"left":"right", TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),IMM&0x7FFFFFF,(TAYLOR_GPU_REGR(ID,A) == (IMM&0x7FFFFFF)), TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),TAYLOR_GPU_REG(B),TAYLOR_GPU_REGR(ID,B),(TAYLOR_GPU_REGR(ID,A) == TAYLOR_GPU_REGR(ID,B)) );
     if (useIMM?(TAYLOR_GPU_REGR(ID,A) == IMM):(TAYLOR_GPU_REGR(ID,A) == TAYLOR_GPU_REGR(ID,B))) {
      if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
     }
     GPU[ID].IP += max(C,1)*6;
     if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;
    case 0x0E:// CMPLT  |
     //printf("<IMM: %d\n",IMM&0x7FFFFFF);
     if(IMM>0x7FFFFFF) useIMM = true, IMM &= 0x7FFFFFF;
     if(IMM>0x3FFFFFF) IMM -= 0x8000000; //negitive
     //printf(">> %d\n",IMM);
     if (sys.Debug == true) { sprintf(msg,"%sCMP<\n",msg); }
     //printf("IMM>0: %s, %s/0x%07X< 0x%07X: %d, %s/0x%07X< %s/0x%07X: %d\n", IMM>0?"left":"right", TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),IMM&0x7FFFFFF,(TAYLOR_GPU_REGR(ID,A) < (IMM&0x7FFFFFF)), TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),TAYLOR_GPU_REG(B),TAYLOR_GPU_REGR(ID,B),(TAYLOR_GPU_REGR(ID,A) < TAYLOR_GPU_REGR(ID,B)) );
     if (useIMM?(TAYLOR_GPU_REGR(ID,A) < IMM):(TAYLOR_GPU_REGR(ID,A) < TAYLOR_GPU_REGR(ID,B))) {
      if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
     }
     GPU[ID].IP += max(C,1)*6;
     if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;
    case 0x0F:// CMPGT  |
     //printf(">IMM: %d\n",IMM&0x7FFFFFF);
     if(IMM>0x7FFFFFF) useIMM = true, IMM &= 0x7FFFFFF;
     if(IMM>0x3FFFFFF) IMM -= 0x8000000; //negitive
     //printf(">> %d\n",IMM);
     if (sys.Debug == true) { sprintf(msg,"%sCMP>\n",msg); }
     //printf("IMM>0: %s, %s/0x%07X >0x%07X: %d, %s/0x%07X >%s/0x%07X: %d\n", IMM>0?"left":"right", TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),IMM&0x7FFFFFF,(TAYLOR_GPU_REGR(ID,A) > (IMM&0x7FFFFFF)), TAYLOR_GPU_REG(A),TAYLOR_GPU_REGR(ID,A),TAYLOR_GPU_REG(B),TAYLOR_GPU_REGR(ID,B),(TAYLOR_GPU_REGR(ID,A) > TAYLOR_GPU_REGR(ID,B)) );
     if (useIMM?(TAYLOR_GPU_REGR(ID,A) > IMM):(TAYLOR_GPU_REGR(ID,A) > TAYLOR_GPU_REGR(ID,B))) {
      if (sys.Debug == true) sprintf(msg,"%s  \\True\n",msg); break;
     }
     GPU[ID].IP += max(C,1)*6;
     if (sys.Debug == true) sprintf(msg,"%s  \\False\n",msg); break;
    case 0x10:// SPLIT  |
     if (sys.Debug == true) { sprintf(msg,"%sSPLIT\n",msg); }
     switch(IMM % 0x3) {
      case 0:
       TAYLOR_GPU_REGW(ID, B, TAYLOR_GPU_REGR(ID,A) & 0xFFFF); TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A) >> 16);
      case 1:
       TAYLOR_GPU_REGW(ID, B, TAYLOR_GPU_REGR(ID,A) & 0xFF); TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A) >> 8);
      case 2:
       TAYLOR_GPU_REGW(ID, B, TAYLOR_GPU_REGR(ID,A) & 0xF); TAYLOR_GPU_REGW(ID, C, TAYLOR_GPU_REGR(ID,A) >> 4);
     } break;
    case 0x11:// COMB   |
     if (sys.Debug == true) { sprintf(msg,"%sCOMBINE\n",msg); }
     switch(IMM % 0x3) {
      case 0:
       TAYLOR_GPU_REGW(ID, C, (TAYLOR_GPU_REGR(ID,A) << 16)&0xFFFF | (TAYLOR_GPU_REGR(ID,B) & 0xFFFF));
      case 1:
       TAYLOR_GPU_REGW(ID, C, (TAYLOR_GPU_REGR(ID,A) << 8)&0xFF | (TAYLOR_GPU_REGR(ID,B) & 0xFF));
      case 2:
       TAYLOR_GPU_REGW(ID, C, (TAYLOR_GPU_REGR(ID,A) << 4)&0xF | (TAYLOR_GPU_REGR(ID,B) & 0xF));
      } break;
    case 0x12:// WMEM   |
     if (IMM > 0x3FFFFFF) { IMM = TAYLOR_GPU_REGR(ID,B)&0x3FFFFFF; }
     if (sys.Debug == true) {
      sprintf(msg,"%sWMEM\n  \\Writing REG:%s to 0x%x ",msg,TAYLOR_GPU_REG(A),IMM); TAYLOR_GPU_PrintArea(msg,IMM);
     } sys.MEM[(TGR_MEM_VRAM+IMM)%0xD800000]=TAYLOR_GPU_REGR(ID,A); break;
    case 0x13:// RMEM   |
     if (IMM > 0x3FFFFFF) { IMM = TAYLOR_GPU_REGR(ID,B)&0x3FFFFFF; }
     if (sys.Debug == true) {
      sprintf(msg,"%sRMEM\n  \\Reading 0x%x to REG:%s ",msg,IMM,TAYLOR_GPU_REG(A)); TAYLOR_GPU_PrintArea(msg,IMM);
     } TAYLOR_GPU_REGW(ID, A, sys.MEM[(TGR_MEM_VRAM+IMM)%0xD800000]); break;
    
    case 0x14:// HALT   |
     if (sys.Debug == true) { sprintf(msg,"%sHALT\n",msg); }
     for(i=0;i<IMM==0?1:4;i++) { GPU[(ID+i)%4].running=false; sprintf(msg,"%sHALTING GPU#%i!\n",msg,(IMM+i)%2); }
     if (sys.DebugPause[ID+2]>0) { sys.DebugTick[ID+2] = true, sys.DebugPause[ID+2] = 0, sys.Debug = sys.BreakDebug; TGR_FilterAnsi(msg); }
     break;
    case 0x15:// DISP   |
     if (sys.Debug == true) { sprintf(msg,"%sDISP%s\n",msg,sys.BlockDisp?" [BLOCKED]":""); }
     if (sys.BlockDisp) break;
     uint8_t DispMsg[3][16] = {0}; //memset(DispMsg,0,16*3);
     switch(IMM%3) {
      case 2: sprintf(DispMsg[2],"%s:%s0x%07X\t",TAYLOR_GPU_REG(C),(TAYLOR_GPU_REGR(ID,C)<0)?"-":" ",abs(TAYLOR_GPU_REGR(ID,C)));
      case 1: sprintf(DispMsg[1],"%s:%s0x%07X\t",TAYLOR_GPU_REG(B),(TAYLOR_GPU_REGR(ID,B)<0)?"-":" ",abs(TAYLOR_GPU_REGR(ID,B)));
      case 0: sprintf(DispMsg[0],"%s:%s0x%07X\t",TAYLOR_GPU_REG(A),(TAYLOR_GPU_REGR(ID,A)<0)?"-":" ",abs(TAYLOR_GPU_REGR(ID,A))); break;
     } sprintf(sys.Debug?msg:GPUPrintString,"%s%s%s%s\n",sys.Debug?msg:GPUPrintString,DispMsg[0],DispMsg[1],DispMsg[2]);
     if (!sys.Debug) TGR_FilterAnsi(GPUPrintString);
     break;
    case 0x16:// CORE   |
     if (sys.Debug == true) { sprintf(msg,"%sCORE\n",msg); }
     //A = CoreID
     //B = State
     //IMM = Start Address
     TAYLOR_GPU_Reset(A%4);
     GPU[A%4].IP = IMM;
     GPU[A%4].running = B%2;
     break;
    case 0x17:// PUSH   |
     if (sys.Debug == true) { sprintf(msg,"%sPUSH\n",msg); }
     if (GPU[ID].SP-4 < GPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"GPU#%i: PANIC! STACK OVERFLOW!!\n",ID); GPU[ID].running=false; break; }
     else {
      sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = TAYLOR_GPU_REGR(ID,A)&0xFF,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = TAYLOR_GPU_REGR(ID,A)>>8,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = TAYLOR_GPU_REGR(ID,A)>>16,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = TAYLOR_GPU_REGR(ID,A)>>24;
      //printf("PUSH: %s -> 0x%X\n", TAYLOR_GPU_REG(A), TAYLOR_GPU_REGR(ID,A));
     } break;
    case 0x18:// POP    |
     if (sys.Debug == true) { sprintf(msg,"%sPOP\n",msg); }
     if (GPU[ID].SP+2 > GPU[ID].MP) { sys.ErrorType = 3; sprintf(sys.Error,"GPU#%i: PANIC! stack empty...\n",ID); GPU[ID].running=false; break; }
     else {
      uint32_t data = sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<24|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<16|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<8|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP];
      //uint32_t data = sys.MEM[TGR_MEM_VRAM+GPU[ID].SP++]|sys.MEM[TGR_MEM_VRAM+GPU[ID].SP++]<<8|sys.MEM[TGR_MEM_VRAM+GPU[ID].SP++]<<16|sys.MEM[TGR_MEM_VRAM+GPU[ID].SP++]<<24;
      //printf("POP: 0x%X -> %s\n", data, TAYLOR_GPU_REG(A));
      TAYLOR_GPU_REGW(ID,A, data);
     } break;
    case 0x19:// CALL   |
     if (sys.Debug == true) { sprintf(msg,"%sCALL\n",msg); }
     if (GPU[ID].SP-4 < GPU[ID].BP) { sys.ErrorType = 3; sprintf(sys.Error,"GPU#%i: PANIC! STACK OVERFLOW!!\n",ID); GPU[ID].running=false; break;}
     else {sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = GPU[ID].IP,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = GPU[ID].IP>>8,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = GPU[ID].IP>>16,sys.MEM[TGR_MEM_VRAM+GPU[ID].SP--] = GPU[ID].IP>>24, GPU[ID].IP = ((IMM>0?IMM:TAYLOR_GPU_REGR(ID, A))&0x3FFFFFF)-6; } break;
    case 0x1A:// RET    |
     if (sys.Debug == true) { sprintf(msg,"%sRET\n",msg); }
     if (GPU[ID].SP+4 > GPU[ID].MP) {sys.ErrorType = 3; sprintf(sys.Error,"GPU#%i: PANIC! stack empty...\n",ID); GPU[ID].running=false; break;}
     GPU[ID].IP = sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<24|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<16|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]<<8|sys.MEM[TGR_MEM_VRAM+ ++GPU[ID].SP]; break;
    case 0x1B:// SWAP   |
     if (sys.Debug == true) { sprintf(msg,"%sSWAP\n",msg); }
     if (!GPU[ID].SP+4 > GPU[ID].MP) {
      sys.tmp[0]=sys.MEM[GPU[ID].SP+3],sys.tmp[1]=sys.MEM[GPU[ID].SP+4];
      sys.MEM[GPU[ID].SP+3]=sys.MEM[GPU[ID].SP+1],sys.MEM[GPU[ID].SP+4]=sys.MEM[GPU[ID].SP+2];
      sys.MEM[GPU[ID].SP+1]=sys.tmp[0],sys.MEM[GPU[ID].SP+2]=sys.tmp[1];
     } break;
    case 0x1C:// LED    |
     memset(CPU[ID].flag, 0, 8); if(C>0){CPU[ID].flag[1]=true;}
     if (IMM>0){ sys.LED[2] = IMM&0xFF; sys.LED[1] = (IMM>>8)&0xFF; sys.LED[0] = (IMM>>16)&0xFF; }
     else { sys.LED[0] = TAYLOR_GPU_REGR(ID,A)&0xFF; sys.LED[1] = TAYLOR_GPU_REGR(ID,B)&0xFF; sys.LED[2] = TAYLOR_GPU_REGR(ID,C)&0xFF; }
     if (sys.Debug == true) { sprintf(msg,"%sLED\n  \\sys.LED is set to #%02X%02X%02X\n",msg,sys.LED[0],sys.LED[1],sys.LED[2]); }
     //sprintf(GPUPrintString,"sys.LED is set to #%02X%02X%02X\n",sys.LED[0],sys.LED[1],sys.LED[2]); TGR_FilterAnsi(GPUPrintString);
    case 0x1D:// CLK    |
     if (sys.Debug == true) { sprintf(msg,"%sCLOCK\n",msg); }
     TAYLOR_GPU_REGW(ID,A,GPU[ID].Clock);
     if (IMM>0) GPU[ID].Clock=0;
     break;
    case 0x1E:// WAIT   |
     if (sys.Debug == true) {
      sprintf(msg,"%sWAIT | ", msg);
      if(IMM>0) { sprintf(msg,"%sIMM: %dus (%0.04f secs.)\n",msg, IMM, IMM/1000000.0f); }
      else { sprintf(msg,"%sREG[%s]: %dus (%0.04f secs.)\n",msg, TAYLOR_GPU_REG(A), TAYLOR_GPU_REGR(ID, B), TAYLOR_GPU_REGR(ID, B)/1000000.0f); }
     } break;
    case 0x1F:// BREAK |
     if (sys.Debug == true) { sprintf(msg,"%sBREAKPOINT\n",msg); }
     //operation happens before cycle//
     break;
    case 0x20:// RGBA  |
     GPU[ID].R = IMM>>24&0x0F|C<<4,
     GPU[ID].G = IMM>>16&0xFF,
     GPU[ID].B = IMM>>8 &0xFF,
     GPU[ID].A = IMM    &0xFF;
     if (sys.Debug == true) { sprintf(msg,"%sRGBA: 0x%02X%02X%02X%02X\n",msg,GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A); }
     break;
    case 0x6E:// LAYER/SELECTLAYER   |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: SELECTLAYER\n",msg); }
     GPU[ID].Layer = A%5;
     break;
    case 0x6F:// RESL/RESOLUTION |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: RESOLUTION\n",msg); }
     sys.ScreenReady = false, GPUctl.Rez = -1, GPUctl.NewRez = A%5;
 //    GPUctl.Layers[0] = PtrBytes2ImageAlpha(sys.MEM+(0xD77FFFF-(TGR_GPU_Resolutions[GPUctl.Rez][0]*TGR_GPU_Resolutions[GPUctl.Rez][1]*4)),TGR_GPU_Resolutions[GPUctl.Rez][0],TGR_GPU_Resolutions[GPUctl.Rez][1]);
 //    ImageResizeCanvas(GPU[ID].Canvas, TGR_GPU_Resolutions[GPUctl.Rez][0],TGR_GPU_Resolutions[GPUctl.Rez][1], 0,0, (Color){0,0,0,0xFF});
     break;
    case 0x70:// PLOT   |
     //pthread_t call_GPU_Threads[Fin]; pthread_create(&call_Core0, NULL, &CPU_Core, 0);
     //GPU_PLOT
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: PLOT\n",msg); }
     sprintf(msg,"%sPlotted Pixel at GPU[%d].Layer: %d | x: %d, y: %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawPixel(&GPUctl.Layers[GPU[ID].Layer%5], GPU[ID].X[0],GPU[ID].Y[0], (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x00, A,B,C,IMM);
     break;
    case 0x71:// LINE   |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: LINE\n",msg); }
     sprintf(msg,"%sPlotted Line at GPU[%d].Layer: %d | x: %d, y: %d to x2: %d, y2: %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawLine(&GPUctl.Layers[GPU[ID].Layer%5], GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1], (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x01, A,B,C,IMM);
     break;
    case 0x72:// RECT   |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: RECT\n",msg); }
     sprintf(msg,"%sPlotted Rectable at GPU[%d].Layer: %d | x: %d, y: %d to x2: %d, y2: %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawRectangleLines(&GPUctl.Layers[GPU[ID].Layer%5], (Rectangle){GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1]}, 1, (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x02, A,B,C,IMM);
     break;
    case 0x73:// FRECT  |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: FILLRECT\n",msg); }
     sprintf(msg,"%sFilling Rectable at GPU[%d].Layer: %d | x: %d, y: %d to x2: %d, y2: %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawRectangle(&GPUctl.Layers[GPU[ID].Layer%5], GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1], (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x03, A,B,C,IMM);
     break;
    case 0x74:// CRCL  |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: CIRCLE\n",msg); }
     sprintf(msg,"%sPlotted Circle at GPU[%d].Layer: %d | x: %d, y: %d to Radius(x2): %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawCircleLines(&GPUctl.Layers[GPU[ID].Layer%5], GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1], (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x04, A,B,C,IMM);
     break;
    case 0x75:// FCRCL |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: FILLCIRCLE\n",msg); }
     sprintf(msg,"%sFilling Circle at GPU[%d].Layer: %d | x: %d, y: %d to Radius(x2): %d with RGBA: [0x%02X, 0x%02X, 0x%02X, 0x%02X] | GPU[ID].Layer: %d\n",msg,ID,GPU[ID].Layer%5,GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A,GPU[ID].Layer%5);
     //ImageDrawCircle(&GPUctl.Layers[GPU[ID].Layer%5], GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1], (Color){GPU[ID].R,GPU[ID].G,GPU[ID].B,GPU[ID].A});
     TAYLOR_GPU_SpawnNode(ID,worker++,0x05, A,B,C,IMM);
     break;
    case 0x76:// SETOUT | 
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: SETOUTERXY\n",msg); }
     GPU[ID].X[2]=GPU[ID].X[0],GPU[ID].X[3]=GPU[ID].X[1], GPU[ID].Y[2]=GPU[ID].Y[0],GPU[ID].Y[3]=GPU[ID].Y[1];
     break;
    case 0x77:// GETOUT |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: GETOUTERXY\n",msg); }
     GPU[ID].X[0]=GPU[ID].X[2],GPU[ID].X[1]=GPU[ID].X[3], GPU[ID].Y[0]=GPU[ID].Y[2],GPU[ID].Y[1]=GPU[ID].Y[3];
     break;
    case 0x78:// COPY   | /OUT/
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: COPY\n",msg); }
     sprintf(msg,"%sImageDraw A: %d, GPU[%d].Layer: %d\nFrom: [%d,%d,%d,%d] | To: [%d,%d,%d,%d] (strlen(sys.Error): %ld)\n",msg,A%5,ID,GPU[ID].Layer%5, GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1],GPU[ID].X[2],GPU[ID].Y[2],GPU[ID].X[3],GPU[ID].Y[3],strlen(sys.Error));
     TGR_printError(); sys.ErrorType = 2;
     if (GPU[ID].X[1]<GPU[ID].X[0] || (GPU[ID].X[1]|GPU[ID].X[0])==0) sprintf(sys.Error,  "GPU#%i: NULL RENDER X METHOD DETECTED: X2: 0x%04X/%d <= X : 0x%04X/%d at address: 0x%07X\n",           ID, GPU[ID].X[1],GPU[ID].X[1], GPU[ID].X[0],GPU[ID].X[0], TGR_MEM_VRAM+GPU[ID].IP);
     if (GPU[ID].X[3]<GPU[ID].X[2] || (GPU[ID].X[3]|GPU[ID].X[2])==0) sprintf(sys.Error,"%sGPU#%i: NULL RENDER X METHOD DETECTED: X4: 0x%04X/%d <= X3: 0x%04X/%d at address: 0x%07X\n",sys.Error, ID, GPU[ID].X[3],GPU[ID].X[3], GPU[ID].X[2],GPU[ID].X[2], TGR_MEM_VRAM+GPU[ID].IP);
     if (GPU[ID].Y[1]<GPU[ID].Y[0] || (GPU[ID].Y[1]|GPU[ID].Y[0])==0) sprintf(sys.Error,"%sGPU#%i: NULL RENDER Y METHOD DETECTED: Y2: 0Y%04X/%d <= Y : 0Y%04X/%d at address: 0Y%07X\n",sys.Error, ID, GPU[ID].Y[1],GPU[ID].Y[1], GPU[ID].Y[0],GPU[ID].Y[0], TGR_MEM_VRAM+GPU[ID].IP);
     if (GPU[ID].Y[3]<GPU[ID].Y[2] || (GPU[ID].Y[3]|GPU[ID].Y[2])==0) sprintf(sys.Error,"%sGPU#%i: NULL RENDER Y METHOD DETECTED: Y4: 0Y%04X/%d <= Y3: 0Y%04X/%d at address: 0Y%07X\n",sys.Error, ID, GPU[ID].Y[3],GPU[ID].Y[3], GPU[ID].Y[2],GPU[ID].Y[2], TGR_MEM_VRAM+GPU[ID].IP);
     if (strlen(sys.Error)>0) { GPU[ID].running = false; break; }
     //ImageDraw(&GPUctl.Layers[A%5],GPUctl.Layers[GPU[ID].Layer%5],(Rectangle){GPU[ID].X[0],GPU[ID].Y[0],GPU[ID].X[1],GPU[ID].Y[1]},(Rectangle){GPU[ID].X[2],GPU[ID].Y[2],GPU[ID].X[3],GPU[ID].Y[3]},WHITE);
     TAYLOR_GPU_SpawnNode(ID,worker++,0x06, A,B,C,IMM);
     /*do {
     do {
      i = ((((sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+0]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+1]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+2]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+3])+GPU[ID].X[0]+(GPU[ID].Y[0]*((sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+4]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].cp+5]));
      j = ((((sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+0]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+1]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+2]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+3])+GPU[ID].X[0]+(GPU[ID].Y[1]*((sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+4]<<8)|sys.MEM[TGR_MEM_VRAM+GPU[ID].sp+5]));
      for(uint8_t l=0;l<4;l++) { sys.MEM[i+l] = sys.MEM[j+l]; }
      } while(GPU[ID].X[0]++<GPU[ID].X[1]);
     } while(GPU[ID].Y[0]++<GPU[ID].Y[1]);
     i=j=0;*/ break;
    case 0x79:// 
    case 0x7A:// 
    case 0x7B://     
    case 0x7C:// ColorPalette
     if (sys.Debug == true) { sprintf(msg,"%s COLPAL |",msg); }
     if (IMM>255) IMM = TAYLOR_GPU_REGR(ID,B)&0xFF;
     switch(A%2) {
      case 0:
       if (sys.Debug == true) { sprintf(msg,"%s READ RGB to MEM(0x%07X)\n",msg,IMM); }
       GPU[ID].CP[IMM][0] = GPU[ID].R,
       GPU[ID].CP[IMM][1] = GPU[ID].G,
       GPU[ID].CP[IMM][2] = GPU[ID].B,
       GPU[ID].CP[IMM][3] = GPU[ID].A;
       break;
      case 1:
       if (sys.Debug == true) { sprintf(msg,"%s WRITE MEM(0x%07X) to RGB\n",msg,IMM); }
       GPU[ID].R = GPU[ID].CP[IMM][0],
       GPU[ID].G = GPU[ID].CP[IMM][1],
       GPU[ID].B = GPU[ID].CP[IMM][2],
       GPU[ID].A = GPU[ID].CP[IMM][3];
       break;
     } break;
    case 0x7D:// SPRITE / IMAGE 
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: SPRITE\n"); }
     TAYLOR_GPU_SpawnNode(ID,worker++,0x07, A,B,C,IMM);
     /*
     if (IMM==0) IMM = GPU[ID].sp;
     IMM|=TGR_MEM_VRAM;
     // A = ImageData Type [0:CP 4-bit, 1:CP 8-bit, 2:RGB, 3:RGBA]
     // sp = Sprite Pointer
     // 
     // X[0] = X (uint)
     // Y[0] = Y (uint)
     // X[1] = Width
     // Y[1] = Height
     //
     // X[2] = Rotation[1/2] 0xXXX.X----
     // Y[2] = Rotation[2/2] 0x---.-XXXX (probbly unused)
     // X[3] = Stretch/Resize Width  (Stretch/Resize happens)
     // Y[3] = Stretch/Resize Height (    Before Rotation   )
     // //perhaps will add scewing or leave that up to the dev to make...
     //
     uint8_t*ImageData;
     Image SpritePre,Sprite;
     uint16_t Xoffset = 0, Yoffset = 0;
     float Rotation;
     switch(A%4) {
      case 0:
       ImageData = malloc(512*512*4);
       TGR_CP2RGBA(ImageData, sys.MEM+IMM, ceil((GPU[ID].X[1]*GPU[ID].Y[1])/2.0), GPU[ID].CP);
       Sprite = RL_Bytes2ImageAlpha(ImageData, GPU[ID].X[1], GPU[ID].Y[1]);
       free(ImageData);
       break;
      case 1:
       ImageData = malloc(512*512*4);
       TGR_CP82RGBA(ImageData, sys.MEM+IMM, GPU[ID].X[1]*GPU[ID].Y[1], GPU[ID].CP);
       Sprite = RL_Bytes2ImageAlpha(ImageData, GPU[ID].X[1], GPU[ID].Y[1]);
       free(ImageData);
       break;
      case 2:
       Sprite = GenImageColor(GPU[ID].X[1], GPU[ID].Y[1], TGR_COLOR_VOID);
       SpritePre = RL_Bytes2Image(sys.MEM+IMM, GPU[ID].X[1], GPU[ID].Y[1]);
       ImageDraw(&Sprite, SpritePre, (Rectangle){0,0, SpritePre.width,SpritePre.height}, (Rectangle){0,0, Sprite.width,Sprite.height}, WHITE);
       UnloadImage(SpritePre);
       break;
      case 3:
       Sprite = RL_Bytes2ImageAlpha(sys.MEM+IMM, GPU[ID].X[1], GPU[ID].Y[1]);
       break;
     }
     if (min(Sprite.width,512) != min(GPU[ID].X[3],512) || min(Sprite.width,512) != min(GPU[ID].Y[3],512)) {
      ImageResizeNN(&Sprite, min(GPU[ID].X[3],512), min(GPU[ID].Y[3],512));
      //printf("Resized to %dx%d (was %dx%d)\n", Sprite.width, Sprite.height, min(GPU[ID].X[3],255), GPU[ID].Y[3]);
     }
     if ((Rotation = remainder(getDecimal(GPU[ID].X[2]<<16|GPU[ID].Y[2]),360)) != 0) {
      RL_ImageRotate2(&Sprite, Rotation);
      //printf("Rotated by %f\n", Rotation);
     }
     if (A%8 > 3) Xoffset = Sprite.width/2, Yoffset = Sprite.height/2;
    
     //printf("SPRITE: Drawing at %dx%d on Layer[%d], resized to %dx%d (was %dx%d), fixed float: [%d, %d] -> %f\n", GPU[ID].X[0], GPU[ID].Y[0],  GPU[ID].Layer, Sprite.width, Sprite.height, GPU[ID].X[3], GPU[ID].Y[3], GPU[ID].X[2], GPU[ID].Y[2], Rotation);
     ImageDraw(&GPUctl.Layers[GPU[ID].Layer], Sprite, (Rectangle){0,0, Sprite.width,Sprite.height}, (Rectangle){GPU[ID].X[0]-Xoffset,GPU[ID].Y[0]-Yoffset, Sprite.width,Sprite.height}, WHITE);
     UnloadImage(Sprite);*/
     break;
    
    case 0x7E:// LimitFPS
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: LimitFPS\n",msg); }
     target_fps = IMM;
     break;
    case 0x7F:// RENDER |
     if (sys.Debug == true) { sprintf(msg,"%s DRAW: RENDER\n",msg); }
     if (loops_since_last_frame >= max_loops_between_frames) {
      loops_since_last_frame = 0;
      TAYLOR_GPU_SpawnNode(ID,worker,0xFE, A,B,C,IMM);
      worker = 0;
      //ImageDraw(&sys.CanvasBuffer, GPUctl.Layers[4],(Rectangle){0,0,sys.SW,sys.SH}, (Rectangle){0,0,sys.SW,sys.SH},WHITE);
      GPUctl.FrameRendering = false;
      GPUctl.FrameSeen = false;
      GPUctl.frames++;
     }
     clock_gettime(CLOCK_MONOTONIC, &end);
     long elapsed_microseconds = (end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000;
     GPUctl.RenderDelta = elapsed_microseconds;
     // Calculate the remaining time to sleep to achieve the desired frame rate
     sleep_time = dat/target_fps-elapsed_microseconds;
     if (sleep_time > 0) { usleep(sleep_time); } //printf("sleep_time: %d\n",sleep_time); }
     //if (GPUctl.frames>target_fps) dat+=10;
     //if (GPUctl.frames<target_fps) dat-=10;
     max_loops_between_frames = dat/target_fps;
     clock_gettime(CLOCK_MONOTONIC, &start);
     break;
    case 0xFF:// NOP    |
     if (sys.Debug == true) { sprintf(msg,"%sNOP\n",msg); }
     break;
    default:
     if (sys.Debug == true) { sprintf(msg,"%sUNKNOWN\n",msg); }
     sys.ErrorType = 2; sprintf(sys.Error,"GPU#%i: Unknown Operation 0x%02X at 0x%07X\n",ID,sys.MEM[TGR_MEM_VRAM+GPU[ID].IP],TGR_MEM_VRAM+GPU[ID].IP);
     GPU[ID].running = 0; break;
   }GPU[ID].IP+=6; GPU[ID].IPS++; GPU[ID].TI++;
   if (GPU[ID].IP>0x3FFFFFF) { sys.ErrorType = 2; sprintf(sys.Error, "GPU#%i: Instuction Pointer is overflowed! (0x%07X)", ID, GPU[ID].IP); GPU[ID].running=false; }
   if (sys.DebugPause[ID+2]==1) { sys.DebugTick[ID+2] = true, sys.DebugPause[ID+2] = 00, sys.Debug = false; sprintf(msg, "%s[[BREAKPOINT DEACTIVATED!]] Debug mode is Disabled!\n",msg); TGR_FilterAnsi(msg); }
   else if (sys.DebugPause[ID+2]>0) { sprintf(msg,"%s%s%s[  #######  PRESS ENTER  #######  ]\n",msg,COLOR_RESET,COLOR_YELLOW); sys.DebugTick[ID+2] = false; }
   if (sys.Debug == true) { TGR_FilterAnsi(msg); } TGR_printError();
   sprintf(msg,"");  sprintf(GPUPrintString,"");
   if (sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP)%0xD800000] == 0x1E) { usleep((uint32_t)(IMM>0?IMM:TAYLOR_GPU_REGR(ID, A))); }
   loops_since_last_frame++;
   if (GPUctl.ForceRender && sys.MEM[(TGR_MEM_VRAM+GPU[ID].IP)&0x3FFFFFF]!=0x7F) {
     TAYLOR_GPU_SpawnNode(ID,worker,0xFE, A,B,C,IMM);
     worker = 0;
     //ImageDraw(&sys.CanvasBuffer, GPUctl.Layers[4],(Rectangle){0,0,sys.SW,sys.SH}, (Rectangle){0,0,sys.SW,sys.SH},WHITE);
     GPUctl.FrameRendering = false;
     GPUctl.FrameSeen = false;
     GPUctl.frames++;
     clock_gettime(CLOCK_MONOTONIC, &end);
     long elapsed_microseconds = (end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000;
     GPUctl.RenderDelta = elapsed_microseconds;
     // Calculate the remaining time to sleep to achieve the desired frame rate
     sleep_time = dat/target_fps-elapsed_microseconds;
     //if (sleep_time > 0) { usleep(sleep_time); }
     //if (GPUctl.frames>target_fps) dat+=10;
     //if (GPUctl.frames<target_fps) dat-=10;
     max_loops_between_frames = dat/target_fps;
     clock_gettime(CLOCK_MONOTONIC, &start);
   }
  } else usleep(1);
 } printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!  GPU Process #%d ENDED! !!\n!!! THIS SHOULDN'T HAPPEN !!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n",ID);
}

void TAYLOR_GPU_GraphicsCore() {
 uint32_t NodeID;
 uint8_t ID;
 while (true) {
  for(NodeID=0; NodeID<GPU_RENDER_NODE_LEN; NodeID++) {
   for(ID=0; ID<GPU_CORE_COUNT; ID++) {
   if (GPU_RENDER_NODES[ID][NodeID].Oper==0xFF) break;
/*   printf("""===========================\n\
    Oper: 0x%02X, Layer: %i\n\n\
    RGBA: 0x%02X%02X%02X%02X\n\n\
    CP[256][4]: Nah Too Lazy -3-\n\n\
    OperA:0x%01X/%s, OperB:0x%01X/%s, OperC:0x%01X/%s, OperIMM:0x%07X\n\n\
    X:{0x%04X, 0x%04X, 0x%04X, 0x%04X},Y:{0x%04X, 0x%04X, 0x%04X, 0x%04X}\n\n\
    sp:0x%07X, cp:0x%07X\n\n""",
    GPU_RENDER_NODES[ID][NodeID].Oper, GPU_RENDER_NODES[ID][NodeID].Layer,
    GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A,
    GPU_RENDER_NODES[ID][NodeID].OperA, TAYLOR_GPU_REG(GPU_RENDER_NODES[ID][NodeID].OperA), GPU_RENDER_NODES[ID][NodeID].OperB, TAYLOR_GPU_REG(GPU_RENDER_NODES[ID][NodeID].OperB), GPU_RENDER_NODES[ID][NodeID].OperC, TAYLOR_GPU_REG(GPU_RENDER_NODES[ID][NodeID].OperC), GPU_RENDER_NODES[ID][NodeID].OperIMM,
    GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].X[1],GPU_RENDER_NODES[ID][NodeID].X[2],GPU_RENDER_NODES[ID][NodeID].X[3],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].Y[1],GPU_RENDER_NODES[ID][NodeID].Y[2],GPU_RENDER_NODES[ID][NodeID].Y[3],
    GPU_RENDER_NODES[ID][NodeID].sp, GPU_RENDER_NODES[ID][NodeID].cp);*/
   switch(GPU_RENDER_NODES[ID][NodeID].Oper) {
    case 0x00:// PLOT   |
     ImageDrawPixel(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0], (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x01:// LINE   |
     ImageDrawLine(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1],GPU_RENDER_NODES[ID][NodeID].Y[1], (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x02:// RECT   |
     ImageDrawRectangleLines(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], (Rectangle){GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1],GPU_RENDER_NODES[ID][NodeID].Y[1]}, 1, (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x03:// FRECT  |
     ImageDrawRectangle(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1],GPU_RENDER_NODES[ID][NodeID].Y[1], (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x04:// CRCL  |
     ImageDrawCircleLines(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1], (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x05:// FCRCL |
     ImageDrawCircle(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5], GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1], (Color){GPU_RENDER_NODES[ID][NodeID].R,GPU_RENDER_NODES[ID][NodeID].G,GPU_RENDER_NODES[ID][NodeID].B,GPU_RENDER_NODES[ID][NodeID].A});
     break;
    case 0x06:// COPY   | /OUT/
     ImageDraw(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].OperA%5],GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer%5],(Rectangle){GPU_RENDER_NODES[ID][NodeID].X[0],GPU_RENDER_NODES[ID][NodeID].Y[0],GPU_RENDER_NODES[ID][NodeID].X[1],GPU_RENDER_NODES[ID][NodeID].Y[1]},(Rectangle){GPU_RENDER_NODES[ID][NodeID].X[2],GPU_RENDER_NODES[ID][NodeID].Y[2],GPU_RENDER_NODES[ID][NodeID].X[3],GPU_RENDER_NODES[ID][NodeID].Y[3]},WHITE);
     /*do {
      do {
       i = ((((sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+0]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+1]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+2]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+3])+GPU_RENDER_NODES[ID][NodeID].X[0]+(GPU_RENDER_NODES[ID][NodeID].Y[0]*((sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+4]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].CP+5]));
       j = ((((sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+0]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+1]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+2]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+3])+GPU_RENDER_NODES[ID][NodeID].X[0]+(GPU_RENDER_NODES[ID][NodeID].Y[1]*((sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+4]<<8)|sys.MEM[TGR_MEM_VRAM+GPU_RENDER_NODES[ID][NodeID].sp+5]));
       for(uint8_t l=0;l<4;l++) { sys.MEM[i+l] = sys.MEM[j+l]; }
       } while(GPU_RENDER_NODES[ID][NodeID].X[0]++<GPU_RENDER_NODES[ID][NodeID].X[1]);
     } while(GPU_RENDER_NODES[ID][NodeID].Y[0]++<GPU_RENDER_NODES[ID][NodeID].Y[1]);
     i=j=0;*/ break;
    case 0x07:// SPRITE / IMAGE 
     if (GPU_RENDER_NODES[ID][NodeID].OperIMM==0) GPU_RENDER_NODES[ID][NodeID].OperIMM = GPU_RENDER_NODES[ID][NodeID].sp;
     GPU_RENDER_NODES[ID][NodeID].OperIMM|=TGR_MEM_VRAM;
     // A = ImageData Type [0:CP 4-bit, 1:CP 8-bit, 2:RGB, 3:RGBA]
     // sp = Sprite Pointer
     // 
     // X[0] = X (uint)
     // Y[0] = Y (uint)
     // X[1] = Width
     // Y[1] = Height
     //
     // X[2] = Rotation[1/2] 0xXXX.X----
     // Y[2] = Rotation[2/2] 0x---.-XXXX (probbly unused)
     // X[3] = Stretch/Resize Width  (Stretch/Resize happens)
     // Y[3] = Stretch/Resize Height (    Before Rotation   )
     // //perhaps will add scewering or leave that up to a dev to make...
     //
     uint8_t*ImageData;
     Image SpritePre,Sprite;
     uint16_t Xoffset = 0, Yoffset = 0;
     float Rotation;
     switch(GPU_RENDER_NODES[ID][NodeID].OperA%4) {
      case 0:
       ImageData = malloc(512*512*4);
       TGR_CP2RGBA(ImageData, sys.MEM+GPU_RENDER_NODES[ID][NodeID].OperIMM, ceil((GPU_RENDER_NODES[ID][NodeID].X[1]*GPU_RENDER_NODES[ID][NodeID].Y[1])/2.0), GPU_RENDER_NODES[ID][NodeID].CP);
       Sprite = RL_Bytes2ImageAlpha(ImageData, GPU_RENDER_NODES[ID][NodeID].X[1], GPU_RENDER_NODES[ID][NodeID].Y[1]);
       free(ImageData);
       break;
      case 1:
       ImageData = malloc(512*512*4);
       TGR_CP82RGBA(ImageData, sys.MEM+GPU_RENDER_NODES[ID][NodeID].OperIMM, GPU_RENDER_NODES[ID][NodeID].X[1]*GPU_RENDER_NODES[ID][NodeID].Y[1], GPU_RENDER_NODES[ID][NodeID].CP);
       Sprite = RL_Bytes2ImageAlpha(ImageData, GPU_RENDER_NODES[ID][NodeID].X[1], GPU_RENDER_NODES[ID][NodeID].Y[1]);
       free(ImageData);
       break;
      case 2:
       Sprite = GenImageColor(GPU_RENDER_NODES[ID][NodeID].X[1], GPU_RENDER_NODES[ID][NodeID].Y[1], TGR_COLOR_VOID);
       SpritePre = RL_Bytes2Image(sys.MEM+GPU_RENDER_NODES[ID][NodeID].OperIMM, GPU_RENDER_NODES[ID][NodeID].X[1], GPU_RENDER_NODES[ID][NodeID].Y[1]);
       ImageDraw(&Sprite, SpritePre, (Rectangle){0,0, SpritePre.width,SpritePre.height}, (Rectangle){0,0, Sprite.width,Sprite.height}, WHITE);
       UnloadImage(SpritePre);
       break;
      case 3:
       Sprite = RL_Bytes2ImageAlpha(sys.MEM+GPU_RENDER_NODES[ID][NodeID].OperIMM, GPU_RENDER_NODES[ID][NodeID].X[1], GPU_RENDER_NODES[ID][NodeID].Y[1]);
       break;
     }
     if (min(Sprite.width,512) != min(GPU_RENDER_NODES[ID][NodeID].X[3],512) || min(Sprite.width,512) != min(GPU_RENDER_NODES[ID][NodeID].Y[3],512)) {
      ImageResizeNN(&Sprite, min(GPU_RENDER_NODES[ID][NodeID].X[3],512), min(GPU_RENDER_NODES[ID][NodeID].Y[3],512));
      //printf("Resized to %dx%d (was %dx%d)\n", Sprite.width, Sprite.height, min(GPU_RENDER_NODES[ID][NodeID].X[3],255), GPU_RENDER_NODES[ID][NodeID].Y[3]);
    }
    if ((Rotation = remainder(getDecimal(GPU_RENDER_NODES[ID][NodeID].X[2]<<16|GPU_RENDER_NODES[ID][NodeID].Y[2]),360)) != 0) {
      RL_ImageRotate2(&Sprite, Rotation);
      //printf("Rotated by %f\n", Rotation);
    }
    if (GPU_RENDER_NODES[ID][NodeID].OperA%8 > 3) Xoffset = Sprite.width/2, Yoffset = Sprite.height/2;
    
    //printf("SPRITE: Drawing at %dx%d on Layer[%d], resized to %dx%d (was %dx%d), fixed float: [%d, %d] -> %f\n", GPU_RENDER_NODES[ID][NodeID].X[0], GPU_RENDER_NODES[ID][NodeID].Y[0],  GPU_RENDER_NODES[ID][NodeID].Layer, Sprite.width, Sprite.height, GPU_RENDER_NODES[ID][NodeID].X[3], GPU_RENDER_NODES[ID][NodeID].Y[3], GPU_RENDER_NODES[ID][NodeID].X[2], GPU_RENDER_NODES[ID][NodeID].Y[2], Rotation);
    ImageDraw(&GPUctl.Layers[GPU_RENDER_NODES[ID][NodeID].Layer], Sprite, (Rectangle){0,0, Sprite.width,Sprite.height}, (Rectangle){GPU_RENDER_NODES[ID][NodeID].X[0]-Xoffset,GPU_RENDER_NODES[ID][NodeID].Y[0]-Yoffset, Sprite.width,Sprite.height}, WHITE);
    UnloadImage(Sprite);
    break;
    
    case 0xFE: // RENDER  |
     ImageDraw(&sys.CanvasBuffer, GPUctl.Layers[4],(Rectangle){0,0,sys.SW,sys.SH}, (Rectangle){0,0,sys.SW,sys.SH},WHITE);
     break;
    default:
     break;
   } GPU_RENDER_NODES[ID][NodeID].Oper = 0xFF;
 }}} usleep(1);
}
