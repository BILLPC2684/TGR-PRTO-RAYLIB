#ifndef TGR_H
#define TGR_H

#define true  1
#define false 0

#define CPLength 0x5A0
#define PtrLenth 0x29

#define TGR_MEM_ROM_SIZE        0x0800000
#define TGR_MEM_ROM0            0x0000000
#define TGR_MEM_ROM1            0x0800000
#define TGR_MEM_SAV             0x1000000
#define TGR_MEM_WRAM            0x1800000
#define TGR_MEM_WRAM_SIZE       0x3FBFE00
#define TGR_MEM_STACK_SIZE      0x0020000
#define TGR_MEM_STACK0          0x57BFE00
#define TGR_MEM_STACK1          0x57DFE00
#define TGR_MEM_IO              0x57FFE00
#define TGR_MEM_IO_SIZE         0x0000200
#define TGR_MEM_SRAMEXT         0x5800000
#define TGR_MEM_SRAMEXT_SIZE    0x4000000
#define TGR_MEM_VRAM            0x9800000
#define TGR_MEM_VRAM_SIZE       0x1F80000
#define TGR_MEM_VSTACK0         0xB780000
#define TGR_MEM_VSTACK_SIZE     0x0020000
#define TGR_MEM_VSTACK1         0xB7A0000
#define TGR_MEM_VSTACK2         0xB7C0000
#define TGR_MEM_VSTACK3         0xB7E0000
#define TGR_MEM_VRAMEXT         0xB800000
#define TGR_MEM_VRAMEXT_SIZE    0x2000000
#define TGR_MEM_TOTAL           0xD800000

#define TGR_VMEM_VRAM           0x0000000
#define TGR_VMEM_VSTACK0        0x1F80000
#define TGR_VMEM_VSTACK1        0x1FA0000
#define TGR_VMEM_VSTACK2        0x1FC0000
#define TGR_VMEM_VSTACK3        0x1FE0000
#define TGR_VMEM_VRAMEXT        0x2000000
#define TGR_VMEM_TOTAL          0x4000000

#define TGR_MEM_WRAM_FULL TGR_MEM_WRAM_SIZE+TGR_MEM_STACK_SIZE *2+TGR_MEM_IO_SIZE+TGR_MEM_SRAMEXT_SIZE
#define TGR_MEM_VRAM_FULL TGR_MEM_VRAM_SIZE+TGR_MEM_VSTACK_SIZE*4+                TGR_MEM_VRAMEXT_SIZE

static const uint8_t* ErrorTexts[3] = {"Warning", "Error", "Fatal"};
static const Vector2 Vector2_ZERO = (Vector2){0,0};

static const Color VOID = {0};

#define min(x,y) ({__typeof__(x)_x=(x);__typeof__(y)_y=(y);_y>_x?_x:_y;})
#define max(x,y) ({__typeof__(x)_x=(x);__typeof__(y)_y=(y);_x>_y?_x:_y;})

#undef GREEN
#undef LIME
#define GREEN CLITERAL(Color){0,228,48,255}
#define LIME  CLITERAL(Color){0,158,47,255}

typedef struct {
 bool Debug,DebugTick[6],BreakDebug,Pause,skipBIOS,AsService,BlockDisp,ROMloaded,SilentRun,EXTSAV,KeepAspect,AnsiPrinting,StartOnLoad,TapePressent,TapeFramed,TapeFrame,ScreenReady,ClockSync,RapidDebug,Resetting;
 uint8_t MF, MB, CursorDepth, HeaderSize, *MEM,PageID[2],ROMBANK[33][TGR_MEM_ROM_SIZE],ErrorType,LED[3],Controller[2][32],ControllerType[2],Title[16],ControllerDevice[2],GUIOpacity,
        *REG, *Error, *BN, *RN, *SN, NETWORK_IP[256], BoarderThiccness;
 uint16_t MFT, FPS, SW,SH, HostWidth,HostHeight, ResizeDict[4],ControllerKey[2][32],NETWORK_PORT, IntroductionCutscene;
 uint32_t DebugPause[6], Clock, skip;
 uint64_t tmp[8];
 double IPS[2],MemUse,VMemUse;
  int8_t fade, MS;
 int16_t MX, MY, pMX, pMY;
 
 
 uint16_t Cutscene0Timer;
 uint8_t Cutscene0Speed, Cutscene0Fade0, Cutscene0Fade1, Cutscene0Fade2, Cutscene0Fade3, Cutscene0Position;
 Color   Cutscene0Background;
 
 uint16_t Cutscene1Timer;
 uint8_t Cutscene1transition0;
 
 Image Canvas,CanvasBuffer,UI;
 Color CursorColor;
 Rectangle DistRect;
 //TI:    Total Instructions
 //FN:    BIOS FileName
 //RN:    ROM  FileName
 //SN:    SAV  FileName
} System;
System sys;

typedef struct CPU_INIT {
 uint16_t REGs[8];
 bool running,flag[8],ticked;
 uint32_t IP,SP,BP,MP,Clock;
 uint64_t IPS,TI,time;
 //IP:    InstuctionPointer
 //SP:    StackPointer
 //BP:    BasePoint
 //MP: Max Value of StackPointer
 //IPS:   InstructionsPerSecond
 //TI:    Total Instructions
} CPU_INIT;
CPU_INIT CPU[2];

typedef struct GPU_CORE {
 bool CoreReady[4],FrameRendering,FrameSeen,ForceRender;
 uint8_t Rez,NewRez;
 uint16_t frames,RenderDelta;
 Image Sprites[0x10000],Layers[5];
 Texture Canvas[4];
} GPU_INIT;
GPU_INIT GPUctl;
typedef struct {
 bool running,Pause;
 uint8_t R,G,B,A,Layer,CP[15][4];
 uint16_t X[4],Y[4];
 uint32_t IP,sp,cp,SP,BP,MP,IPS,E,I,O,U,Clock;
 uint64_t TI;
 // 0, 1, . . . X[2]:    16-bit X Position / X2/Width Position
 // 2, 3, . . . Y[2]:    16-bit Y Position / Y2/Height Position
 // 4 . . . . . IP:      28-bit Instuction Pointer
 // 5 . . . . . SP:      28-bit StackPointer (Read Only)
 // 6 . . . . . sp:      28-bit Sprite Pointer (Address From)
 // 7 . . . . . cp:      28-bit Canvas Pointer (Address  To )
 // 8, 9,10,11, R,G,B,A:  8-bit Red, Green, Blue, Alpha
 //12,13,14,15, E,I,O,U: 28-bit General Purpose Registers

 //   BP:  BasePoint  (Stack)
 //   MP:  MaxPointer (Stack)
 //   CP:  ColorPallet
} GPU_CORE;
GPU_CORE GPU[4];
static const uint16_t GPU_Resolutions[4][2] = {{480,360},{800,600},{852,480},{1280,720}};

typedef struct TapeFrame {
 bool FrameHasSaveState; // Does this frame contain a SaveState?
 uint8_t SaveState[TGR_MEM_TOTAL+1024]; // SaveState data
 Sound Audio; // 20 kHz; should contain for the whole frame
 Image Frame; // The Frame duh...
} TapeFrame;

typedef struct Tape {
 bool Loaded, JustLoaded; // Is the Tape Loaded or did it Just get Loaded?
 uint8_t FramesPerSaveState, // How many Frames is there per SaveState
         FrameData[335*576*2], // The Current Frame's raw binary
         Path[1024], // The Path of the Tape
         State; // Is it STOPPED, PLAYING, REWINDING, FAST-FORWARDING or EJECTING?
 Image Frame; // The Current Frame being recorded
 uint32_t Length,seek; // The Length and Seek Both Counted in Frames
 TapeFrame*FrameBuffer[255]; // 127 frame buffer for Rewind and Play/ FastF
} Tape; // max is 5 hours @ 24-FPS is 24*60*60*5
static const uint16_t Tape_Resolution[2] = {335,576};

enum TapeState {
 TAPE_STOP=0,
 TAPE_PLAY,
 TAPE_REWIND,
 TAPE_FASTFORWARD,
 TAPE_EJECT,
};

enum TGR_Controller_type {
 TGR_CONTROLTYPE_NONE=0,
 TGR_CONTROLTYPE_STANDARD, // . . 14 BUTTON, 0 JOT
 TGR_CONTROLTYPE_ARCADE, // . . . 8  BUTTON, 1 JOY
 TGR_CONTROLTYPE_STEERINGWHEEL,// 9  BUTTON, 1 JOY 
};

#endif