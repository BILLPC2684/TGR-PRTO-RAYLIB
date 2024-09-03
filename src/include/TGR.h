#ifndef TGR_H
#define TGR_H

#define true  1
#define false 0

#define CPLength 0x5A0
#define PtrLenth 0x29

#define GPU_RENDER_NODE_LEN 0xFFF
#define GPU_CORE_COUNT 4
#define GPU_LAYER_COUNT 5

#define TGR_MEM_ROM0                0x0000000
#define TGR_MEM_ROM1                0x0800000
#define TGR_MEM_SAV                 0x1000000
#define TGR_MEM_ROM_SIZE            0x0800000
#define TGR_MEM_WRAM                0x1800000
#define TGR_MEM_WRAM_SIZE           0x3FBFE00
#define TGR_MEM_STACK0              0x57BFE00
#define TGR_MEM_STACK1              0x57DFE00
#define TGR_MEM_STACK_SIZE          0x0020000
#define TGR_MEM_IO                  0x57FFE00
#define TGR_MEM_IO_SIZE             0x0000200
#define TGR_MEM_IO_NET_IP           0x57FFE00
#define TGR_MEM_IO_NET_IP_SIZE      0x0000004
#define TGR_MEM_IO_NET_PORT         0x57FFE04
#define TGR_MEM_IO_NET_PORT_SIZE    0x0000002
#define TGR_MEM_IO_NET_BUFFER       0x57FFE06
#define TGR_MEM_IO_NET_BUFFER_SIZE  0x0000002
#define TGR_MEM_IO_NET_SIZE         0x57FFE08
#define TGR_MEM_IO_NET_SIZE_SIZE    0x0000002
#define TGR_MEM_IO_NET_OPER         0x57FFE0A
#define TGR_MEM_IO_NET_OPER_SIZE    0x0000001
#define TGR_MEM_IO_NET_SOCKID       0x57FFE0B
#define TGR_MEM_IO_NET_SOCKID_SIZE  0x0000001
#define TGR_MEM_IO_NEXT             0x57FFE0C
#define TGR_MEM_IO_NEXT_SIZE        0x00001F4
#define TGR_MEM_SRAMEXT             0x5800000
#define TGR_MEM_SRAMEXT_SIZE        0x4000000
#define TGR_MEM_VRAM                0x9800000
#define TGR_MEM_VRAM_SIZE           0x1F80000
#define TGR_MEM_VSTACK0             0xB780000
#define TGR_MEM_VSTACK1             0xB7A0000
#define TGR_MEM_VSTACK2             0xB7C0000
#define TGR_MEM_VSTACK3             0xB7E0000
#define TGR_MEM_VSTACK_SIZE         0x0020000
#define TGR_MEM_VRAMEXT             0xB800000
#define TGR_MEM_VRAMEXT_SIZE        0x2000000
#define TGR_MEM_TOTAL               0xD800000

#define TGR_VMEM_VRAM               0x0000000
#define TGR_VMEM_VSTACK0            0x1F80000
#define TGR_VMEM_VSTACK1            0x1FA0000
#define TGR_VMEM_VSTACK2            0x1FC0000
#define TGR_VMEM_VSTACK3            0x1FE0000
#define TGR_VMEM_VRAMEXT            0x2000000
#define TGR_VMEM_TOTAL              0x4000000

static const uint32_t TGR_MEM_WRAM_FULL = TGR_MEM_WRAM_SIZE+TGR_MEM_STACK_SIZE *2+TGR_MEM_IO_SIZE+TGR_MEM_SRAMEXT_SIZE;
static const uint32_t TGR_MEM_VRAM_FULL = TGR_MEM_VRAM_SIZE+TGR_MEM_VSTACK_SIZE*4+                TGR_MEM_VRAMEXT_SIZE;

static const uint16_t DefaultKEYS[2][14] = {{KEY_Z,KEY_X,KEY_C,KEY_A,KEY_S,KEY_D,KEY_Q,KEY_W,KEY_ENTER,KEY_BACKSPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT},{KEY_KP_1,KEY_KP_5,KEY_KP_3,KEY_KP_7,KEY_KP_DIVIDE,KEY_KP_9,KEY_KP_0,KEY_KP_DECIMAL,KEY_KP_ENTER,KEY_KP_ADD,KEY_KP_8,KEY_KP_2,KEY_KP_4,KEY_KP_6}};
static const uint8_t*ErrorTexts[3] = {"Warning", "Error", "Fatal"};
static const uint8_t*TypeHelpForHelp = "Use \"./TGR --help\" for help\n\n";
static const Vector2 Vector2_ZERO = (Vector2){0,0};
static const Color TGR_COLOR_VOID = {0};

#define min(x,y) ({__typeof__(x)_x=(x);__typeof__(y)_y=(y);_y>_x?_x:_y;})
#define max(x,y) ({__typeof__(x)_x=(x);__typeof__(y)_y=(y);_x>_y?_x:_y;})

#undef GREEN
#undef LIME
#define GREEN CLITERAL(Color){0,228,48,255}
#define LIME  CLITERAL(Color){0,158,47,255}

struct Application {
 int64_t epoch;
 struct IDiscordCore* core;
 struct IDiscordUserManager* users;
 struct IDiscordActivityManager* activities;
 struct IDiscordApplicationManager* application;
 struct IDiscordLobbyManager* lobbies;
 DiscordUserId user_id;
};

typedef struct {
 bool Debug, DebugTick[6], BreakDebug, Pause, skipBIOS, AsService, BlockDisp, ROMloaded, SilentRun, EXTSAV, KeepAspect, AnsiPrinting, StartOnLoad, TapePressent, TapeFramed, TapeFrame, ScreenReady, ClockSync, RapidDebug, Resetting, HelpOnError, ControllerScantype[2][32], DebugGPUstart, GPUoverDraw, SoloPlay, Online, DiscordEnrichment, DiscordEnrichmentInited;
 uint8_t MF, MB, CursorDepth, HeaderSize, *MEM, PageID[2], ROMBANK[33][TGR_MEM_ROM_SIZE], ErrorType, LED[3], Controller[2][32], ControllerType[2], Title[16], ControllerDevice[2], GUIOpacity,
        *REG, *Error, *BN, *RN, *SN, NETWORK_IP[256], BoarderThiccness;
 uint16_t MFT, FPS, SW,SH, HostWidth, HostHeight, ResizeDict[4], ControllerScancode[2][32], NETWORK_PORT, IntroductionCutscene, NumOfPlayers;
 uint32_t DebugPause[6], Clock, skip;
 uint64_t tmp[8];
 double IPS[2],MemUse,VMemUse;
  int8_t fade, MS;
 int16_t MX, MY, pMX, pMY;
 int64_t epoch;

 uint16_t Cutscene0Timer;
 uint8_t Cutscene0Speed, Cutscene0Fade0, Cutscene0Fade1, Cutscene0Fade2, Cutscene0Fade3, Cutscene0Position;
 Color   Cutscene0Background;
 
 uint16_t Cutscene1Timer;
 uint8_t Cutscene1transition0;
 
 Image Canvas,CanvasBuffer,UI;
 Color CursorColor;
 Rectangle DistRect;
 struct Application DiscordApp;
 //TI:    Total Instructions
 //FN:    BIOS FileName
 //RN:    ROM  FileName
 //SN:    SAV  FileName
} TGR_System;
TGR_System sys;

typedef struct {
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
} TGR_CPU_INIT;
TGR_CPU_INIT CPU[2];


/*
typedef struct GPU_Worker { 
 uint8_t GPUID, Layer;
 int16_t X[4],Y[4];
 uint8_t R,G,B,A,CP[256][4];
 uint32_t sp,cp;
} GPU_Worker;
*/
typedef struct {
 bool CoreReady[GPU_CORE_COUNT],FrameRendering,FrameSeen,ForceRender;
 uint8_t Rez,NewRez;
 uint16_t frames,RenderDelta;
 Image Sprites[0x10000],Layers[GPU_LAYER_COUNT];
 Texture Canvas[GPU_LAYER_COUNT];

// bool      Workers_InUsed[16];
// uint8_t   Workers_GPUID[16];
// pthread_t call_GPU_Workers[16];
} TGR_GPU_INIT;
TGR_GPU_INIT GPUctl;

typedef struct {
 uint8_t Oper,R,G,B,A,Layer,CP[256][4],OperA,OperB,OperC;
 int16_t X[4],Y[4];
 uint32_t sp,cp,OperIMM;
} TGR_GPU_RENDER_NODE;
TGR_GPU_RENDER_NODE GPU_RENDER_NODES[GPU_CORE_COUNT][GPU_RENDER_NODE_LEN];

typedef struct {
 bool running,Pause;
 uint8_t R,G,B,A,Layer,CP[256][4];
 int16_t X[4],Y[4];
 uint32_t IP,sp,cp,SP,BP,MP,IPS,E,I,O,U,Clock;
 uint64_t TI;
 // 0, 1, . . . X[2]:   s16-bit X Position / X2/Width Position
 // 2, 3, . . . Y[2]:   s16-bit Y Position / Y2/Height Position
 // 4 . . . . . IP:      28-bit Instuction Pointer
 // 5 . . . . . SP:      28-bit StackPointer (Read Only)
 // 6 . . . . . sp:      28-bit Sprite Pointer (Address From)
 // 7 . . . . . cp:      28-bit Canvas Pointer (Address  To )
 // 8, 9,10,11, R,G,B,A:  8-bit Red, Green, Blue, Alpha
 //12,13,14,15, E,I,O,U: 28-bit General Purpose Registers

 //   BP:  BasePoint  (Stack)
 //   MP:  MaxPointer (Stack)
 //   CP:  ColorPallet
} TGR_GPU_CORE;
TGR_GPU_CORE GPU[GPU_CORE_COUNT];
static const uint16_t TGR_GPU_Resolutions[4][2] = {{480,360},{800,600},{852,480},{1280,720}};

typedef struct TGR_TapeFrame {
 bool FrameHasSaveState; // Does this frame contain a SaveState?
 uint8_t SaveState[TGR_MEM_TOTAL+1024]; // SaveState data
 Sound Audio; // 20 kHz; should contain data from current frame to next frame (the whole frame)
 Image Frame; // The Frame duh...
 uint32_t seek; // the seek position for this frame
} TGR_TapeFrame;

typedef struct TGR_Tape {
 FILE *fp; // The Tape's File
 bool Loaded, JustLoaded; // Is the Tape Loaded or did it Just get Loaded?
 uint8_t FramesPerSaveState, // How many Frames is there per SaveState
         FrameData[335*576*2], // The Current Frame's raw binary
         Path[1024], // The Path of the Tape
         State; // Is it STOPPED, PLAYING, REWINDING, FAST-FORWARDING or EJECTING?
 Image Frame; // The Current Frame being recorded
 uint32_t Length,seek; // The Length and Seek Both Counted in Frames
 TGR_TapeFrame*FrameBuffer[255]; // 127 frame buffer for Rewind and Play/ FastF
} TGR_Tape; // max is 5 hours @ 24-FPS is 24*60*60*5
static const uint16_t TGR_Tape_Resolution[2] = {335,576};

enum TGR_TapeState {
 TGR_TAPE_STOP=0,
 TGR_TAPE_PLAY,
 TGR_TAPE_RECORD,
 TGR_TAPE_REWIND,
 TGR_TAPE_FASTFORWARD,
 TGR_TAPE_EJECT,
};

enum TGR_Controller_type {
 TGR_CONTROLTYPE_NONE=0,
 TGR_CONTROLTYPE_STANDARD, // . . 14 BUTTON, 0 JOT
 TGR_CONTROLTYPE_ARCADE, // . . . 10 BUTTON, 1 JOY
 TGR_CONTROLTYPE_STEERINGWHEEL,// 9  BUTTON, 1 JOY 
};

#endif