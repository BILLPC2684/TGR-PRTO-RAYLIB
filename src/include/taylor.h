#ifndef TAYLOR_H
#define TAYLOR_H

System sys;
CPU_INIT CPU[2];
GPU_INIT GPUctl;
GPU_CORE GPU[4];
static const uint16_t GPU_Resolutions[4][2];
void     GPU_ResetAll();
void     GPU_RESET(uint8_t ThreadID);
void     GPU_REGW(uint8_t ThreadID, uint8_t RegID, uint64_t Data);
int32_t  GPU_REGR(uint8_t ThreadID,uint8_t RegID);
uint8_t* GPU_REG(uint8_t RegID);
uint64_t zeroup(int64_t x);

void CPU_ResetCore(bool ID);
void CPU_LoadPage(bool SlotID, uint8_t PageID);
int8_t CPU_Init();
void CPU_Silent(bool silent);
void CPU_ExtSAV(uint8_t recvbuf[]);
void CPU_Load(uint8_t recvbuf[]);
void CPU_Start();
void CPU_Reset(bool hard);
void CPU_Stop();
void CPU_State(int type);
void CPU_memdump(uint8_t recvbuf[], uint8_t* sendbuf[]);

Image Bytes2Image(uint8_t data[], uint16_t width, uint16_t height);
Image PtrBytes2Image(uint8_t data[], uint16_t width, uint16_t height);
void getCharExt(Image *dest, uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S);
void printError();


#endif
