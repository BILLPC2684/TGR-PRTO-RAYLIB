#ifndef TAYLOR_H
#define TAYLOR_H

System sys;
GPU_INIT GPU;
uint16_t GPU_Resolutions[4][2];
void GPU_RESET();
void GPU_REGW(uint8_t ID, uint64_t Data);
int32_t GPU_REGR(uint8_t ID);
uint8_t* GPU_REG(uint8_t ID);
uint64_t zeroup(int64_t x);

typedef struct {
 uint16_t REGs[8],Clock;
 bool running,flag[8],ticked;
 uint32_t IP,SP,BP,MP;
 uint64_t IPS,TI,time;
 //IP:    InstuctionPointer
 //SP:    StackPointer
 //BP:    BasePoint
 //MP: Max Value of StackPointer
 //IPS:   InstructionsPerSecond
 //TI:    Total Instructions
} CPU_INIT;
CPU_INIT CPU[2];

void ResetCore(bool ID);
void LoadPage(bool PID, uint8_t BID);
void CPU_init();
void CPU_silent(int silent);
void CPU_extsav(uint8_t recvbuf[]);
void CPU_load(uint8_t recvbuf[]);
void CPU_start();


void CPU_load(uint8_t recvbuf[]);
void CPU_start();
void CPU_reset(int hard);
void CPU_stop();
void CPU_debug(int state);
void CPU_pause(int state);
void CPU_state(int type);
void CPU_memdump(uint8_t recvbuf[], uint8_t* sendbuf[]);
void GPU_makeCanvas (uint16_t Width,uint16_t Height);
void CPU_reset(int hard);
void CPU_stop();
void CPU_debug(int state);
void CPU_pause(int state);
void CPU_state(int type);
void CPU_memdump(uint8_t recvbuf[], uint8_t* sendbuf[]);
void printError();

#endif
