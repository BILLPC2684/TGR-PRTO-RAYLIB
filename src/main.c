#if _WIN32
 #include <cJSON.h> // . . . . \.
#else                  //        https://github.com/DaveGasys.MBle/cJSON
 #include <cjson/cJSON.h> // . /
#endif
#include <raylib.h> // . . . . . https://github.com/raysan5/raylib
//#include "discord_game_sdk.h" // https://discord.com/developers/docs/game-sdk/sdk-starter-guide

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <signal.h>
#include <locale.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "netlib.h"
#include "color.h"
#include "TGR.h"

#define RLGL_ENABLE_OPENGL_DEBUG_CONTEXT 1
#define SUPPORT_TRACELOG_DEBUG 1

#if _WIN32
 #define _mkdir(path) mkdir(path)
#else
 #define _mkdir(path) mkdir(path, 0777)
#endif

static volatile bool MainRunning = 1;
static const uint16_t GPU_Resolutions[4][2];
static const uint16_t Tape_Resolution[2];

#define ScreenSise 2764800

#define version "v0.0.47e Nightly build 1"

uint8_t MainPrintString[0xFFFF] = "";
DIR* dir;

Tape CurrentTape;
Font font;
Color
 TGR_RED       = (Color){255,128,128,255},
 TGR_REDT      = (Color){255,128,128,128},
 TGR_DIM_RED   = (Color){255, 64, 64,255},
 TGR_DIM_REDT  = (Color){255, 64, 64,128},
 
 TGR_BLUE      = (Color){128,128,255,255},
 TGR_BLUET     = (Color){128,128,255,128},
 TGR_DIM_BLUE  = (Color){ 64, 64,255,255},
 TGR_DIM_BLUET = (Color){ 64, 64,255,128},
 BLUET         = (Color){  0,  0,255,128};

void DebugPauseExit() {
 for(uint8_t i=0; i<6; i++) sys.DebugTick[i] = true, sys.DebugPause[i] = 0;
 sys.Debug = sys.BreakDebug;
 sprintf(MainPrintString, "[[BREAKPOINT DEACTIVATED!]] Debug mode is %s\n",sys.Debug?"Still Enabled, sys.MY dear chap! (You're a feisty debugger aren't ya?)":"Disabled!");
 FilterAnsi(MainPrintString);
}

void intHandler(int dummy) {
 uint8_t l=0,i;
 for(i=0; i<6; i++) l+=sys.DebugPause[i]>0;
 if (l>0) { DebugPauseExit(); } else { MainRunning = false; }
}

void DebugPauseDetection() {
 uint8_t ch,l,i;
 while(true) {
  #if _WIN32
   ch = _getch();
   //printf("ch: \"%c\" (0x%02X)\n",ch,ch);
  #else
   ch = getchar();
  #endif
  for(l=0,i=0; i<6; i++) l+=sys.DebugPause[i]>0;
//  printf("l: %d\n",l);
  if (l>0) {
   if (ch == 0x03) { DebugPauseExit(); }
   if (ch == 0x0D || ch == 0x0A) { for(i=0; i<6; i++) { sys.DebugTick[i] = true; } }
 #if _WIN32
  } else {
   if (ch == 0x03) {
    //printf("93 ch: \"%c\" (0x%02X)\n",ch,ch);
    MainRunning = false;
   }
 #endif
}}}

void getAspectRatio(uint16_t out[4]) {
 uint16_t sx,sy;
 float scale_factor;
 if (sys.SW > sys.SH) {
  scale_factor = (sys.HostWidth-4)/(float)sys.SW; sy = scale_factor*sys.SH;
  if (sy > sys.HostHeight-4) {
   scale_factor = (sys.HostHeight-4)/(float)sys.SH; sx = scale_factor*sys.SW, sy = sys.HostHeight-4;
  } else { sx = sys.HostWidth-4; }
 } else {
  scale_factor = (sys.HostHeight-4)/(float)sys.SH; sx = scale_factor*sys.SW;
  if (sx > sys.HostWidth-4) {
   scale_factor = (sys.HostWidth-4)/(float)sys.SW; sx = sys.HostWidth-4, sy = scale_factor*sys.SH;
  } else { sy = sys.HostHeight-4; }
 } out[0]=sx,out[1]=sy,out[2]=(sys.HostWidth/2)-(sx/2),out[3]=(sys.HostHeight/2)-(sy/2);
}

Image Bytes2ImageAlpha(uint8_t data[], uint16_t width, uint16_t height) {
 Color *pixels = (Color *)RL_CALLOC(width*height, sizeof(Color));
 memcpy(pixels,data,width*height*4);
 return (Image){pixels,width,height,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
}
Image PtrBytes2ImageAlpha(uint8_t data[], uint16_t width, uint16_t height) {
 return (Image){data,width,height,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
}

Image Bytes2Image(uint8_t data[], uint16_t width, uint16_t height) {
 Color *pixels = (Color *)RL_CALLOC(width*height, sizeof(Color));
 memcpy(pixels,data,width*height*4);
 return (Image){pixels,width,height,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8};
}
Image PtrBytes2Image(uint8_t data[], uint16_t width, uint16_t height) {
 return (Image){data,width,height,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8};
}

void CP2RGBA(uint8_t out[], uint8_t data[], uint16_t length, uint8_t ColorPallet[15][3]) {
 uint32_t j=0,k;
 for(uint32_t i=0;i<length;i++) {
// sprintf(MainPrintString,"data[%i/%i]: %02X\n",i,length,data[i]);
// FilterAnsi(MainPrintString);
  if (((data[i])&0xF0)>>4 == 0) { j+=4; }
  else { for(k=0;k<3;k++) { out[j++] = ColorPallet[(((data[i])&0xF0)>>4)-1][k]; } out[j++] = 255; }
// sprintf(MainPrintString,"\\%X : \\x%02X\\x%02X\\x%02X\\x%02X\n",(data[i]&0xF0)>>4,out[j-0],out[j-1],out[j-2],out[j-3]);
// FilterAnsi(MainPrintString);
  if ((data[i]&0x0F) == 0) { j+=4; }
  else { for(k=0;k<3;k++) { out[j++] = ColorPallet[(data[i]&0x0F)-1][k]; } out[j++] = 255; }
// sprintf(MainPrintString,"\\ %X: \\x%02X\\x%02X\\x%02X\\x%02X\n",data[i]&0x0F,out[j-0],out[j-1],out[j-2],out[j-3]);
// FilterAnsi(MainPrintString);
 }
}

uint8_t* concat(const uint8_t *s1, const uint8_t *s2) {
 const size_t len[2] = {strlen(s1), strlen(s2)};
 uint8_t *result = malloc(len[0]+len[1]+1);//+1 for the null-terminator
 //in real code you would check for errors in malloc here
 memcpy(result, s1, len[0]);
 memcpy(result+len[0], s2, len[1]+1);//+1 to copy the null-terminator
 return result;
}

uint32_t utf16(uint8_t text[3]) {
 return (text[0] & 0b00001111) << 12
      | (text[1] & 0b00111111) << 6
      | (text[2] & 0b00111111);
}

// `ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-+_=[]{}\|;:'".,<>/?~abcdefghijklmnopqrstuvwxyz─│═║┌┬┐╔╦╗╓╥╖╒╤╕├┼┤╠╬╣╟╫╢╞╪╡└┴┘╚╩╝╙╨╜╘╧╛
#define ascii_size    95
#define unilist_size  92
#define fontraw_size unilist_size+ascii_size
Image TGR_fontImages[512];
uint16_t TGR_chars[ascii_size] = {' ','`','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','!','@','#','$','%','^','&','*','(',')','-','+','_','=','[',']','{','}','\\','|',';',':','\'','\"','.',',','<','>','/','?','~','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
uint8_t TGR_uni[unilist_size][3] = {"─","│","═","║","┌","┬","┐","╔","╦","╗","╓","╥","╖","╒","╤","╕","├","┼","┤","╠","╬","╣","╟","╫","╢","╞","╪","╡","└","┴","┘","╚","╩","╝","╙","╨","╜","╘","╧","╛","⢀","⢠","⢰","⢸","⡀","⣀","⣠","⣰","⣸","⡄","⣄","⣤","⣴","⣼","⡆","⣆","⣦","⣶","⣾","⡇","⣇","⣧","⣷","⣿","⡿","⡟","⡏","⡇","⢿","⠿","⠟","⠏","⠇","⢻","⠻","⠛","⠋","⠃","⢹","⠹","⠙","⠉","⠁","⢸","⠸","⠘","⠈","⏸","▶","⏹","⏪","⏩"},
    TGR_fontraw[fontraw_size][8] = {
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, //   00
 {0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111}, // `█01
 {0b00111100,0b01000010,0b01000010,0b01111110,0b01000010,0b01000010,0b01000010,0b00000000}, // A 02
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01000010,0b01000010,0b01111100,0b00000000}, // B 03
 {0b00111100,0b01000010,0b01000000,0b01000000,0b01000000,0b01000010,0b00111100,0b00000000}, // C 04
 {0b01111100,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01111100,0b00000000}, // D 05
 {0b01111110,0b01000000,0b01000000,0b01111100,0b01000000,0b01000000,0b01111110,0b00000000}, // E 06
 {0b01111110,0b01000000,0b01000000,0b01111100,0b01000000,0b01000000,0b01000000,0b00000000}, // F 07
 {0b00111100,0b01000010,0b01000000,0b01001110,0b01000010,0b01000010,0b00111100,0b00000000}, // G 08
 {0b01000010,0b01000010,0b01000010,0b01111110,0b01000010,0b01000010,0b01000010,0b00000000}, // H 09
 {0b01111110,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b01111110,0b00000000}, // I 10
 {0b01111110,0b00000100,0b00000100,0b00000100,0b00000100,0b01000100,0b00111000,0b00000000}, // J 11
 {0b01000100,0b01001000,0b01010000,0b01100000,0b01010000,0b01001000,0b01000100,0b00000000}, // K 12
 {0b01000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000}, // L 13
 {0b01000010,0b01100110,0b01100110,0b01011010,0b01011010,0b01000010,0b01000010,0b00000000}, // M 14
 {0b01000010,0b01100010,0b01010010,0b01001010,0b01000110,0b01000010,0b01000010,0b00000000}, // N 15
 {0b00111100,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b00111100,0b00000000}, // O 16
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01000000,0b01000000,0b01000000,0b00000000}, // P 17
 {0b00111100,0b01000010,0b01000010,0b01000010,0b01001010,0b01000110,0b00111110,0b00000000}, // Q 18
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01010000,0b01001000,0b01000100,0b00000000}, // R 19
 {0b00111100,0b01000010,0b00100000,0b00011000,0b00000100,0b01000010,0b00111100,0b00000000}, // S 20
 {0b01111110,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00000000}, // T 21
 {0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b00111100,0b00000000}, // U 22
 {0b01000010,0b01000010,0b01000010,0b01000010,0b00100100,0b00100100,0b00011000,0b00000000}, // V 23
 {0b01010100,0b01010100,0b01010100,0b01010100,0b01010100,0b01010100,0b00101000,0b00000000}, // W 24
 {0b01000010,0b01000010,0b00100100,0b00011000,0b00011000,0b00100100,0b01000010,0b00000000}, // X 25
 {0b01000010,0b01000010,0b00100100,0b00011000,0b00011000,0b00011000,0b00011000,0b00000000}, // Y 26
 {0b01111110,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b01111110,0b00000000}, // Z 27
 {0b00111100,0b01000010,0b01100010,0b01011010,0b01000110,0b01000010,0b00111100,0b00000000}, // 0 28
 {0b00001000,0b00011000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000}, // 1 29
 {0b00111100,0b01000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01111110,0b00000000}, // 2 30
 {0b00111100,0b01000010,0b00000010,0b00001100,0b00000010,0b01000010,0b00111100,0b00000000}, // 3 31
 {0b00000100,0b00001100,0b00010100,0b00100100,0b01111110,0b00000100,0b00000100,0b00000000}, // 4 32
 {0b01111110,0b01000000,0b01000000,0b01111100,0b00000010,0b01000010,0b00111100,0b00000000}, // 5 33
 {0b00111100,0b01000010,0b01000000,0b01111100,0b01000010,0b01000010,0b00111100,0b00000000}, // 6 34
 {0b01111110,0b00000010,0b00000100,0b00000100,0b00001000,0b00001000,0b00010000,0b00000000}, // 7 35
 {0b00111100,0b01000010,0b01000010,0b00111100,0b01000010,0b01000010,0b00111100,0b00000000}, // 8 36
 {0b00111100,0b01000010,0b01000010,0b00111110,0b00000010,0b00000010,0b00111100,0b00000000}, // 9 37
 {0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00000000,0b00001000,0b00000000}, // ! 38
 {0b00111100,0b01000010,0b01110010,0b01101010,0b01110010,0b01011100,0b00111110,0b00000000}, // @ 39
 {0b00000000,0b00100100,0b01111110,0b00100100,0b00100100,0b01111110,0b00100100,0b00000000}, // # 40
 {0b00011000,0b00111100,0b01011010,0b00111000,0b00011100,0b01011010,0b00111100,0b00011000}, // $ 41
 {0b01100001,0b10010010,0b10010100,0b01101000,0b00010110,0b00101001,0b01001001,0b10000110}, // % 42
 {0b00011000,0b00100100,0b01000010,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // ^ 43
 {0b00011000,0b00100100,0b00100100,0b00111010,0b01000100,0b01000100,0b00111010,0b00000000}, // & 44
 {0b00101010,0b00011100,0b00111110,0b00011100,0b00101010,0b00000000,0b00000000,0b00000000}, // * 45
 {0b00001100,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00001100,0b00000000}, // ( 46
 {0b00110000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00110000,0b00000000}, // ) 47
 {0b00000000,0b00000000,0b00000000,0b01111110,0b01111110,0b00000000,0b00000000,0b00000000}, // - 48
 {0b00000000,0b00011000,0b00011000,0b01111110,0b01111110,0b00011000,0b00011000,0b00000000}, // + 49
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b11111111}, // _ 50
 {0b00000000,0b00000000,0b01111110,0b00000000,0b00000000,0b01111110,0b00000000,0b00000000}, // = 51
 {0b00011100,0b00010000,0b00010000,0b00010000,0b00010000,0b00010000,0b00011100,0b00000000}, // [ 52
 {0b00111000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00111000,0b00000000}, // ] 53
 {0b00011100,0b00010000,0b00010000,0b00100000,0b00010000,0b00010000,0b00011100,0b00000000}, // { 54
 {0b00111000,0b00001000,0b00001000,0b00000100,0b00001000,0b00001000,0b00111000,0b00000000}, // } 55
 {0b10000000,0b01000000,0b00100000,0b00010000,0b00001000,0b00000100,0b00000010,0b00000001}, // \ 56 /
 {0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00000000}, // | 57
 {0b00000000,0b00000000,0b00001000,0b00000000,0b00000000,0b00001000,0b00010000,0b00000000}, // ; 58
 {0b00000000,0b00000000,0b00001000,0b00000000,0b00000000,0b00001000,0b00000000,0b00000000}, // : 59
 {0b00001000,0b00001000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // ' 60
 {0b00100100,0b00100100,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // " 61
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001000,0b00000000}, // . 62
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00001000,0b00010000}, // , 63
 {0b00000000,0b00000110,0b00011000,0b01100000,0b00011000,0b00000110,0b00000000,0b00000000}, // < 64
 {0b00000000,0b01100000,0b00011000,0b00000110,0b00011000,0b01100000,0b00000000,0b00000000}, // > 65
 {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000}, // / 66
 {0b00111100,0b01000010,0b01000010,0b00001100,0b00001000,0b00000000,0b00001000,0b00000000}, // ? 67
 {0b00000000,0b00000000,0b00000000,0b00110010,0b01001100,0b00000000,0b00000000,0b00000000}, // ~ 68
 {0b00111100,0b01000010,0b01000010,0b01111110,0b01000010,0b01000010,0b01000010,0b00000000}, // A 69
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01000010,0b01000010,0b01111100,0b00000000}, // B 70
 {0b00111100,0b01000010,0b01000000,0b01000000,0b01000000,0b01000010,0b00111100,0b00000000}, // C 71
 {0b01111100,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01111100,0b00000000}, // D 72
 {0b01111110,0b01000000,0b01000000,0b01111100,0b01000000,0b01000000,0b01111110,0b00000000}, // E 73
 {0b01111110,0b01000000,0b01000000,0b01111100,0b01000000,0b01000000,0b01000000,0b00000000}, // F 74
 {0b00111100,0b01000010,0b01000000,0b01001110,0b01000010,0b01000010,0b00111100,0b00000000}, // G 75
 {0b01000010,0b01000010,0b01000010,0b01111110,0b01000010,0b01000010,0b01000010,0b00000000}, // H 76
 {0b01111110,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b01111110,0b00000000}, // I 77
 {0b01111110,0b00000100,0b00000100,0b00000100,0b00000100,0b01000100,0b00111000,0b00000000}, // J 78
 {0b01000100,0b01001000,0b01010000,0b01100000,0b01010000,0b01001000,0b01000100,0b00000000}, // K 79
 {0b01000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01000000,0b01111110,0b00000000}, // L 80
 {0b01000010,0b01100110,0b01100110,0b01011010,0b01011010,0b01000010,0b01000010,0b00000000}, // M 81
 {0b01000010,0b01100010,0b01010010,0b01001010,0b01000110,0b01000010,0b01000010,0b00000000}, // N 82
 {0b00111100,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b00111100,0b00000000}, // O 83
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01000000,0b01000000,0b01000000,0b00000000}, // P 84
 {0b00111100,0b01000010,0b01000010,0b01000010,0b01001010,0b01000110,0b00111110,0b00000000}, // Q 85
 {0b01111100,0b01000010,0b01000010,0b01111100,0b01010000,0b01001000,0b01000100,0b00000000}, // R 86
 {0b00111100,0b01000010,0b00100000,0b00011000,0b00000100,0b01000010,0b00111100,0b00000000}, // S 87
 {0b01111110,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00000000}, // T 88
 {0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b00111100,0b00000000}, // U 89
 {0b00000000,0b01000010,0b01000010,0b01000010,0b00100100,0b00100100,0b00011000,0b00000000}, // V 90
 {0b01010100,0b01010100,0b01010100,0b01010100,0b01010100,0b01010100,0b00101000,0b00000000}, // W 91
 {0b01000010,0b01000010,0b00100100,0b00011000,0b00011000,0b00100100,0b01000010,0b00000000}, // X 92
 {0b01000010,0b01000010,0b00100100,0b00011000,0b00011000,0b00011000,0b00011000,0b00000000}, // Y 93
 {0b01111110,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b01111110,0b00000000}, // Z 94

 {0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00000000,0b00000000,0b00000000}, // ─ 95 \x7F\x00
 {0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000,0b00001000}, // │ 96 \x7F\x01
 {0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b00000000,0b00000000,0b00000000}, // ═ 97 \x7F\x02
 {0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000,0b00011000}, // ║ 98 \x7F\x03
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000111,0b00001100,0b00001000,0b00001000}, // ┌ 99 \x7F\x04
 {0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00011100,0b00001000,0b00001000}, // ┬ 100 \x7F\x05
 {0b00000000,0b00000000,0b00000000,0b00000000,0b11110000,0b00011000,0b00001000,0b00001000}, // ┐ 101 \x7F\x06
 {0b00000000,0b00000000,0b00000000,0b00001111,0b00011111,0b00011100,0b00011000,0b00011000}, // ╔ 102 \x7F\x07
 {0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b00111100,0b00011000,0b00011000}, // ╦ 103 \x7F\x08
 {0b00000000,0b00000000,0b00000000,0b11110000,0b11111000,0b00111000,0b00011000,0b00011000}, // ╗ 104 \x7F\x09
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00001111,0b00011100,0b00011000,0b00011000}, // ╓ 105 \x7F\x0A
 {0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00111100,0b00011000,0b00011000}, // ╥ 106 \x7F\x0B
 {0b00000000,0b00000000,0b00000000,0b00000000,0b11110000,0b00111000,0b00011000,0b00011000}, // ╖ 107 \x7F\x0C
 {0b00000000,0b00000000,0b00000000,0b00000111,0b00001111,0b00001100,0b00001000,0b00001000}, // ╒ 108 \x7F\x0D
 {0b00000000,0b00000000,0b00000000,0b11111111,0b11111111,0b00011100,0b00001000,0b00001000}, // ╤ 109 \x7F\x0E
 {0b00000000,0b00000000,0b00000000,0b11110000,0b11111000,0b00011000,0b00001000,0b00001000}, // ╕ 110 \x7F\x0F
 {0b00001000,0b00001000,0b00001000,0b00001100,0b00001111,0b00001100,0b00001000,0b00001000}, // ├ 111 \x7F\x10
 {0b00001000,0b00001000,0b00001000,0b00011100,0b11111111,0b00011100,0b00001000,0b00001000}, // ┼ 112 \x7F\x11
 {0b00001000,0b00001000,0b00001000,0b00011000,0b11111000,0b00011000,0b00001000,0b00001000}, // ┤ 113 \x7F\x12
 {0b00011000,0b00011000,0b00011100,0b00011111,0b00011111,0b00011100,0b00011000,0b00011000}, // ╠ 114 \x7F\x13
 {0b00011000,0b00011000,0b00111100,0b11111111,0b11111111,0b00111100,0b00011000,0b00011000}, // ╬ 115 \x7F\x14
 {0b00011000,0b00011000,0b00111000,0b11111000,0b11111000,0b00111000,0b00011000,0b00011000}, // ╣ 116 \x7F\x15
 {0b00011000,0b00011000,0b00011000,0b00011100,0b00011111,0b00011100,0b00011000,0b00011000}, // ╟ 117 \x7F\x16
 {0b00011000,0b00011000,0b00011000,0b00111100,0b11111111,0b00111100,0b00011000,0b00011000}, // ╫ 118 \x7F\x17
 {0b00011000,0b00011000,0b00011000,0b00111000,0b11111000,0b00111000,0b00011000,0b00011000}, // ╢ 119 \x7F\x18
 {0b00001000,0b00001000,0b00001100,0b00001111,0b00001111,0b00001100,0b00001000,0b00001000}, // ╞ 120 \x7F\x19
 {0b00001000,0b00001000,0b00011100,0b11111111,0b11111111,0b00011100,0b00001000,0b00001000}, // ╪ 121 \x7F\x1A
 {0b00001000,0b00001000,0b00011000,0b11111000,0b11111000,0b00011000,0b00001000,0b00001000}, // ╡ 122 \x7F\x1B
 {0b00001000,0b00001000,0b00001000,0b00001100,0b00000111,0b00000000,0b00000000,0b00000000}, // └ 123 \x7F\x1C
 {0b00001000,0b00001000,0b00001000,0b00011100,0b11111111,0b00000000,0b00000000,0b00000000}, // ┴ 124 \x7F\x1D
 {0b00001000,0b00001000,0b00001000,0b00011000,0b11110000,0b00000000,0b00000000,0b00000000}, // ┘ 125 \x7F\x1E
 {0b00011000,0b00011000,0b00011100,0b00011111,0b00001111,0b00000000,0b00000000,0b00000000}, // ╚ 126 \x7F\x1F
 {0b00011000,0b00011000,0b00111100,0b11111111,0b11111111,0b00000000,0b00000000,0b00000000}, // ╩ 127 \x7F\x20
 {0b00011000,0b00011000,0b00111000,0b11111000,0b11110000,0b00000000,0b00000000,0b00000000}, // ╝ 128 \x7F\x21
 {0b00011000,0b00011000,0b00011000,0b00011100,0b00001111,0b00000000,0b00000000,0b00000000}, // ╙ 129 \x7F\x22
 {0b00011000,0b00011000,0b00011000,0b00111100,0b11111111,0b00000000,0b00000000,0b00000000}, // ╨ 130 \x7F\x23
 {0b00011000,0b00011000,0b00011000,0b00111000,0b11110000,0b00000000,0b00000000,0b00000000}, // ╜ 131 \x7F\x24
 {0b00001000,0b00001000,0b00001100,0b00001111,0b00000111,0b00000000,0b00000000,0b00000000}, // ╘ 132 \x7F\x25
 {0b00001000,0b00001000,0b00011100,0b11111111,0b11111111,0b00000000,0b00000000,0b00000000}, // ╧ 133 \x7F\x26
 {0b00001000,0b00001000,0b00011000,0b11111000,0b11110000,0b00000000,0b00000000,0b00000000}, // ╛ 134 \x7F\x27
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000110,0b00000000}, // Breal 0 135 \x7F\x28 ⢀
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 1 136 \x7F\x29 ⢠
 {0b00000000,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 2 137 \x7F\x2A ⢰
 {0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 3 138 \x7F\x2B ⢸
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01100000,0b00000000}, // Breal 4 139 \x7F\x2C ⡀
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01100110,0b00000000}, // Breal 5 140 \x7F\x2D ⣀
 {0b00000000,0b00000000,0b00000000,0b00000000,0b00000110,0b00000000,0b01100110,0b00000000}, // Breal 6 141 \x7F\x2E ⣠
 {0b00000000,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b01100110,0b00000000}, // Breal 7 142 \x7F\x2F ⣰
 {0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b01100110,0b00000000}, // Breal 8 143 \x7F\x30 ⣸
 {0b00000000,0b00000000,0b00000000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 9 144 \x7F\x31 ⡄
 {0b00000000,0b00000000,0b00000000,0b00000000,0b01100000,0b00000000,0b01100110,0b00000000}, // Breal 10 145 \x7F\x32 ⣄
 {0b00000000,0b00000000,0b00000000,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 11 146 \x7F\x33 ⣤
 {0b00000000,0b00000000,0b00000110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 12 147 \x7F\x34 ⣴
 {0b00000110,0b00000000,0b00000110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 13 148 \x7F\x35 ⣼
 {0b00000000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 14 149 \x7F\x36 ⡆
 {0b00000000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100110,0b00000000}, // Breal 15 150 \x7F\x37 ⣆
 {0b00000000,0b00000000,0b01100000,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 16 151 \x7F\x38 ⣦
 {0b00000000,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 17 152 \x7F\x39 ⣶
 {0b00000110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 18 153 \x7F\x3A ⣾
 {0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 19 154 \x7F\x3B ⡇
 {0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100110,0b00000000}, // Breal 20 155 \x7F\x3C ⣇
 {0b01100000,0b00000000,0b01100000,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 21 156 \x7F\x3D ⣧
 {0b01100000,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 22 157 \x7F\x3E ⣷
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000}, // Breal 23 158 \x7F\x3F ⣿
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b01100000,0b00000000}, // Breal 24 159 \x7F\x40 ⡿
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 25 160 \x7F\x41 ⡟
 {0b01100110,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 26 161 \x7F\x42 ⡏
 {0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000}, // Breal 27 162 \x7F\x43 ⡇
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b00000110,0b00000000}, // Breal 28 163 \x7F\x44 ⢿
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100110,0b00000000,0b00000000,0b00000000}, // Breal 29 164 \x7F\x45 ⠿
 {0b01100110,0b00000000,0b01100110,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000}, // Breal 30 165 \x7F\x46 ⠟
 {0b01100110,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000}, // Breal 31 166 \x7F\x47 ⠏
 {0b01100000,0b00000000,0b01100000,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000}, // Breal 32 167 \x7F\x48 ⠇
 {0b01100110,0b00000000,0b01100110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 33 168 \x7F\x49 ⢻
 {0b01100110,0b00000000,0b01100110,0b00000000,0b00000110,0b00000000,0b00000000,0b00000000}, // Breal 34 169 \x7F\x4A ⠻
 {0b01100110,0b00000000,0b01100110,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 35 170 \x7F\x4B ⠛
 {0b01100110,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 36 171 \x7F\x4C ⠋
 {0b01100000,0b00000000,0b01100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 37 172 \x7F\x4D ⠃
 {0b01100110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 38 173 \x7F\x4E ⢹
 {0b01100110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000000,0b00000000}, // Breal 39 174 \x7F\x4F ⠹
 {0b01100110,0b00000000,0b00000110,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 40 175 \x7F\x50 ⠙
 {0b01100110,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 41 176 \x7F\x51 ⠉
 {0b01100000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 42 177 \x7F\x52 ⠁
 {0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000}, // Breal 43 178 \x7F\x53 ⢸
 {0b00000110,0b00000000,0b00000110,0b00000000,0b00000110,0b00000000,0b00000000,0b00000000}, // Breal 44 179 \x7F\x54 ⠸
 {0b00000110,0b00000000,0b00000110,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 45 180 \x7F\x55 ⠘
 {0b00000110,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000}, // Breal 46 181 \x7F\x56 ⠈

 {0b00000000,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b01100110,0b00000000}, // Pause  182 \x7F\x57 ⏸
 {0b00000000,0b01100000,0b01111000,0b01111110,0b01111110,0b01111000,0b01100000,0b00000000}, // Play   183 \x7F\x58 ▶
 {0b00000000,0b11111110,0b11111110,0b11111110,0b11111110,0b11111110,0b11111110,0b00000000}, // Play   184 \x7F\x59 ⏹
 {0b00000000,0b00100010,0b01100110,0b11101110,0b11101110,0b01100110,0b00100010,0b00000000}, // Rewind 185 \x7F\x5A ⏪
 {0b00000000,0b10001000,0b11001100,0b11101110,0b11101110,0b11001100,0b10001000,0b00000000}, // Fast-F 186 \x7F\x5B ⏩

 {0b01111110,0b11000011,0b10011001,0b11110011,0b11100111,0b11111111,0b11100111,0b01100110}, // <?> 187 \x7F\xFF
};
void getCharExt(Image *dest, uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S) {
 uint16_t i,j,x=0,y=0; Image chr;
 for(i=0;i<strlen(Letter);i++) { if (Letter[i] == '\n') { x=0,y+=8*S; continue; }
  if (Letter[i]==0x7F) j=ascii_size+Letter[++i];
  else for(j=0;j<fontraw_size;j++) if (Letter[i] == TGR_chars[j]) break;
  chr = ImageCopy(TGR_fontImages[j]); ImageResizeNN(&chr,S*8,S*8);
  if (depth > 0) ImageDraw(dest, chr, (Rectangle){0,0,S*8,S*8}, (Rectangle){X+x+depth,Y+y+depth,S*8,S*8}, (Color){0,0,0,sys.GUIOpacity/100.f*255});
  ImageDraw(dest, chr, (Rectangle){0,0,S*8,S*8}, (Rectangle){X+x,Y+y,S*8,S*8}, RGBA); x+=8*S; UnloadImage(chr);
}}


/*
void getCharExt(Image *dest, uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S) {
 Image str = ImageTextEx(font, Letter, S*8, 0, WHITE);
 if (depth > 0) ImageDraw(dest, str, (Rectangle){0,0,str.width,str.height}, (Rectangle){X+depth,Y+S*8+depth,str.width,str.height}, (Color){0,0,0,sys.GUIOpacity/100.f*255});
 ImageDraw(dest, str, (Rectangle){0,0,str.width,str.height}, (Rectangle){X,Y+S*8,str.width,str.height}, RGBA);
 UnloadImage(str);
}*/

/*
void getCharExt(Image *dest, uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S) {
 uint8_t string[1024] = {0}, k=0; Image chr;
 for (uint32_t i=0,j=0;i<=strlen(Letter);i++) {
  if (Letter[i] == '\n' || i == strlen(Letter)) { memcpy(string, &Letter[j], i-j); string[i-j]=0,j=i+1;
   chr = _ImageTextEx(font, string, S*8, 0, WHITE);
   if (depth > 0) ImageDraw(dest, chr, (Rectangle){0,0,chr.width,chr.height}, (Rectangle){X+depth,Y+k*S*8+depth,chr.width,chr.height}, (Color){0,0,0,sys.GUIOpacity/100.f*255});
   ImageDraw(dest, chr, (Rectangle){0,0,chr.width,chr.height}, (Rectangle){X,Y+k*S*8,chr.width,chr.height}, RGBA);
   UnloadImage(chr); k++;
}}}*/

/*
void getCharExt(Image *dest, uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S) {
 uint32_t OriginalLength = strlen(Letter)+10;j
 for (uint32_t i=0,k=0,j=0;i<=OriginalLength;i++) {
  if (Letter[i] == '\n' || i == OriginalLength) { if(i != OriginalLength) Letter[i] = 0;
   if (depth > 0) ImageDrawTextEx(dest, font, Letter+j, (Vector2){X+depth,Y+k*S*8+depth}, S*8, 0, (Color){0,0,0,sys.GUIOpacity/100.f*255});
   ImageDrawTextEx(dest, font, Letter+j, (Vector2){X,Y+k++*S*8}, S*8, 0, RGBA); j=++i;
}}}*/

void getChar(uint8_t Letter[], int16_t X,int16_t Y,Color RGBA, uint8_t depth, uint8_t S) { getCharExt(&sys.Canvas, Letter, X,Y,RGBA, depth, S); }

void printBits(uint8_t byte) { uint8_t b,j=7;
 while(j>0) { b = (byte>>j)&1;printf("%u", b); j--; }
}
void GenerateFont() {
 Color symbols[512][64] = {0};
 for(uint16_t i=0;i<256;i++) {
  for(uint8_t y=0;y<8;y++)
   for(uint8_t x=0;x<8;x++)
    if ((TGR_fontraw[(i<fontraw_size)?i:fontraw_size][y]&(128>>x))>0) symbols[i][y*8+x] = WHITE;
  TGR_fontImages[i] = (Image){symbols[i],8,8,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
 }
 sprintf(MainPrintString,"\\%s%sFont has been Generated!!%s\n\n",COLOR_BOLD,COLOR_GREEN,COLOR_BOTH_DEFAULT);
 FilterAnsi(MainPrintString);
}
/*
Font GenerateFont() {
 #define img_sz 128
 sprintf(MainPrintString,"\n%sGenerating TGR Font...\n",COLOR_MAGENTA);
 FilterAnsi(MainPrintString);
 Color *pixels = (Color *)RL_CALLOC(img_sz*img_sz, sizeof(Color));
 
 //ASSEMBLE GLYPHS
 int index = 0, i=0;
 int x = 0, y = 0;
 int yPosToRead = 0, xPosToRead = 0;
 for (index = 0; index < 256; index++) {
  while (yPosToRead < 8) {
   while (xPosToRead < 8) {
    if ((TGR_fontraw[(index<187)?index:187][yPosToRead]&(128>>xPosToRead))>0) pixels[(y+yPosToRead)*img_sz+(x+xPosToRead)] = WHITE;
    xPosToRead++;
   }yPosToRead++,xPosToRead=0;
  }x+=8,yPosToRead=0; if(x==img_sz) x=0,y+=8;// if(y>img_sz) break;
 }
 
 //GEN FONT
 Font font = GetFontDefault(); 
 x = 0, y = 0;
 
 int tempCharValues[256] = {0};
 Rectangle tempCharRecs[256] = {0};
 
 index = 0, yPosToRead = 0, xPosToRead = 0;
 
 // Parse image data to get rectangle sizes
 while (yPosToRead < img_sz) {
  while (xPosToRead < img_sz) {
   tempCharValues[index] = (index<187)?TGR_chars[index]:0xFFFD;
   tempCharRecs[index].x = (float)xPosToRead*8;
   tempCharRecs[index].y = (float)yPosToRead*8;
   tempCharRecs[index].height = 64.f;
   tempCharRecs[index].width = 64.f;
   index++,xPosToRead += 8;
  }yPosToRead+=8, xPosToRead = 0;
 }
 
 Image fontClear = {pixels,img_sz,img_sz,1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
 ImageResizeNN(&fontClear,fontClear.width*8,fontClear.height*8);
 font.texture = LoadTextureFromImage(fontClear);
 font.glyphCount = index;
 font.glyphPadding = 0; 
 font.glyphs = (GlyphInfo *)RL_MALLOC(font.glyphCount*sizeof(GlyphInfo));
 font.recs = (Rectangle *)RL_MALLOC(font.glyphCount*sizeof(Rectangle));
 
 for (i = 0; i < font.glyphCount; i++) {
  font.recs[i] = tempCharRecs[i];
  font.glyphs[i].value = tempCharValues[i];
  font.glyphs[i].offsetX = 0;
  font.glyphs[i].offsetY = 0;
  font.glyphs[i].advanceX = 0;
  font.glyphs[i].image = ImageFromImage(fontClear, tempCharRecs[i]);
 }font.baseSize = 8*8;
 
 UnloadImage(fontClear);
 sprintf(MainPrintString,"\\%s%sFont has been Generated!!%s\n\n",COLOR_BOLD,COLOR_GREEN,COLOR_BOTH_DEFAULT);
 FilterAnsi(MainPrintString);
 return font;
}*/

void UpdateColors() {
 TGR_RED       = (Color){255,128,128,255},
 TGR_REDT      = (Color){TGR_RED.r,TGR_RED.g,TGR_RED.b,sys.GUIOpacity/100.f*255},
 TGR_DIM_RED   = (Color){255, 64, 64,255},
 TGR_DIM_REDT  = (Color){TGR_DIM_RED.r,TGR_DIM_RED.g,TGR_DIM_RED.b,sys.GUIOpacity/100.f*255},
  
 TGR_BLUE      = (Color){128,128,255,255},
 TGR_BLUET     = (Color){TGR_BLUE.r,TGR_BLUE.g,TGR_BLUE.b,sys.GUIOpacity/100.f*255},
 TGR_DIM_BLUE  = (Color){ 64, 64,255,255},
 TGR_DIM_BLUET = (Color){TGR_DIM_BLUE.r,TGR_DIM_BLUE.g,TGR_DIM_BLUE.b,sys.GUIOpacity/100.f*255},
 BLUET         = (Color){  0,  0,255,sys.GUIOpacity/100.f*255};
// sprintf(MainPrintString,">>> %i, %i",sys.GUIOpacity,(int)(sys.GUIOpacity/100.f*255));
// FilterAnsi(MainPrintString);
}

void FilterAnsi(uint8_t*str) {
 if (sys.AnsiPrinting) {
  printf("%s",str);
 } else {
  uint8_t string[0xFFFF]="";
  uint16_t preptr=0,strptr=0;
  bool Catch = false;
  do {
   if (str[preptr] == 0) break;
   if (str[preptr] == '\e') Catch = true;
   if (!Catch) string[strptr++] = str[preptr];
   if (str[preptr] == 'm') Catch = false;
  } while(preptr++<0xFFFF);
  printf("%s",string);
}}

void printError() {
 if((strlen(sys.Error)>0) && (sys.ErrorType<3)) {
  uint8_t msg[1024] = {0};
  sprintf(msg,"%s%s%s[EMU %s] %s%s%s%s",COLOR_BG_DEFAULT,COLOR_BOLD,COLOR_YELLOW,ErrorTexts[sys.ErrorType],(sys.ErrorType<2?"":COLOR_NORMAL),(sys.ErrorType<1?"":COLOR_RED),sys.Error,COLOR_BOTH_DEFAULT); memset(sys.Error, 0, sizeof(sys.Error));
  FilterAnsi(msg); sys.ErrorType = 3;
}}
uint64_t zeroup(int64_t x) { return (x>=0)?x:0; }

char* toLower(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

void Init_GPUsprites() {
 uint32_t i=TGR_MEM_VRAM+CPLength+PtrLenth+2; uint16_t l=0;
 do {GPUctl.Sprites[l] = PtrBytes2ImageAlpha(sys.MEM+TGR_MEM_VRAM+((sys.MEM[i+l*11+3]&7)<<24|sys.MEM[i+l*11+2]<<16|sys.MEM[i+l*11+1]<<8|sys.MEM[i+l*11+0]),
 sys.MEM[i+l*11+5],sys.MEM[i+l*11+6]); } while(l++<(sys.MEM[i-2]<<8|sys.MEM[i-1]));
}

void reset_GPUlayers() {
 uint32_t i; uint16_t l=0; for(i=0;i<4;i++) GPU[i].Pause = true;
 Init_GPUsprites();
 i = TGR_MEM_VSTACK0; sys.MEM[i] = 0xFF;
 for (l=4;l!=65535;l--) {
  i-=GPU_Resolutions[GPUctl.Rez][0]*GPU_Resolutions[GPUctl.Rez][1]*4;
  //printf("l: %d | i: 0x%07X\n",l,i);
  sys.MEM[TGR_MEM_VRAM+CPLength+l*8+0] = (i>>24)&0xFF; sys.MEM[TGR_MEM_VRAM+CPLength+l*8+1] = (i>>16)&0xFF;
  sys.MEM[TGR_MEM_VRAM+CPLength+l*8+2] = (i>> 8)&0xFF; sys.MEM[TGR_MEM_VRAM+CPLength+l*8+3] =  i     &0xFF;
  sys.MEM[TGR_MEM_VRAM+CPLength+l*8+4] = (GPU_Resolutions[GPUctl.Rez][0]>>8)&0xFF; sys.MEM[TGR_MEM_VRAM+CPLength+l*8+5] = GPU_Resolutions[GPUctl.Rez][0]&0xFF;
  sys.MEM[TGR_MEM_VRAM+CPLength+l*8+6] = (GPU_Resolutions[GPUctl.Rez][1]>>8)&0xFF; sys.MEM[TGR_MEM_VRAM+CPLength+l*8+7] = GPU_Resolutions[GPUctl.Rez][1]&0xFF;
  GPUctl.Layers[l] = PtrBytes2ImageAlpha(&sys.MEM[i],GPU_Resolutions[GPUctl.Rez][0],GPU_Resolutions[GPUctl.Rez][1]);
  //printf("l: %d, i: 0x%08X | 0x%02X%02X%02X%02X, %dx%d] Ptr: 0x%X\n",l,i,sys.MEM[TGR_MEM_VRAM+CPLength+l*8+0],sys.MEM[TGR_MEM_VRAM+CPLength+l*8+1],sys.MEM[TGR_MEM_VRAM+CPLength+l*8+2],sys.MEM[TGR_MEM_VRAM+CPLength+l*8+3],(sys.MEM[TGR_MEM_VRAM+CPLength+l*8+4]<<8)|sys.MEM[TGR_MEM_VRAM+CPLength+l*8+5],(sys.MEM[TGR_MEM_VRAM+CPLength+l*8+6]<<8)|sys.MEM[TGR_MEM_VRAM+CPLength+l*8+7],GPUctl.Layers[l].data);
 } for(i=0;i<4;i++) GPU[i].Pause = false;
}

#include "taylor.c"
#include <errno.h>

void main(uint8_t argc, uint8_t*argv[]) {
 setlocale(LC_ALL, "");
 #if _WIN32
  #define CFGPATH concat(getenv("APPDATA"),"\\TheGameRazer\\")
  #define SEPERATOR "\\"
  #define linkuni "^"
  sys.AnsiPrinting = false;
 #else
  #define CFGPATH concat(getenv("HOME"),"/.config/TheGameRazer/")
  #define SEPERATOR "/"
  #define linkuni "🡕"
  signal(SIGINT, intHandler); //intHandler
  sys.AnsiPrinting = true;
 #endif
 printf(".");
 pthread_t call_DPD; pthread_create(&call_DPD, NULL, DebugPauseDetection, NULL);
 
 SetTraceLogLevel( LOG_WARNING); //LOG_WARNING
 
 sys.Error = malloc(1024); sys.ErrorType = 4;
 uint8_t NewROMPATH[1024]={0},ROMPATH[1024]={0},extSAV[1024]={0},BIOSPath[1024]={0};
 sprintf(BIOSPath,"%s%s%s%s",CFGPATH,"bin",SEPERATOR,"BIOS.bin");
 sys.StartOnLoad = sys.blockDisp = sys.keepAspect = sys.Debug = sys.skipBIOS = false, sys.GUIOpacity = 80;
 uint32_t i,j,k,l;
 for (i=0;i<unilist_size;i++) { TGR_chars[95+i] = utf16(TGR_uni[i]); }
 // open the file
 bool SystemHUD=false,ShowInput=false,ShowDump=false,HUDinfo=false,StartWithOverlay=false,INITFullscreen=false,FullscreenType=true,ForceSkipIntro=false,SkipIntro=false, UInput[2][32]={0};
 uint16_t DefaultKEYS[2][14] = {{KEY_Z,KEY_X,KEY_C,KEY_A,KEY_S,KEY_D,KEY_Q,KEY_W,KEY_ENTER,KEY_BACKSPACE,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT},{KEY_KP_1,KEY_KP_5,KEY_KP_3,KEY_KP_7,KEY_KP_DIVIDE,KEY_KP_9,KEY_KP_0,KEY_KP_DECIMAL,KEY_KP_ENTER,KEY_KP_ADD,KEY_KP_8,KEY_KP_2,KEY_KP_4,KEY_KP_6}};
 uint8_t hour_offset = 0, min_offset = 0; sys.Cutscene0Speed = 8, GPUctl.ForceRender = 0;
 Color FadeMask = (Color){0xFF,0xFF,0xFF,0x00},BoarderLED;
 
 for(j=0;j<2;j++) {
  sys.controllerDevice[j] = 0;
  sys.controllerType[j] = TGR_CONTROLTYPE_STANDARD;
  for(i=0;i<14;i++) {
   sys.controllerKey[j][i] = DefaultKEYS[j][i];
 }} printf(".");
 FILE *fp;
 dir = opendir(CFGPATH); if (!dir) { if (_mkdir(CFGPATH)<0) { sprintf(sys.Error, "Failed to create system's folder\n"); sys.ErrorType=1; printError(); } } closedir(dir);
 cJSON *json,*jsonItem,*jsonSubItem; uint8_t cfgdata[1024];
 if ((fp = fopen(concat(CFGPATH,"settings.cfg"), "r")) == NULL) { sprintf(sys.Error,"Unable to open Settings, Using Default Settings...\n"); sys.ErrorType=1; printError(); }
 else {
  int len = fread(cfgdata, 1, sizeof(cfgdata), fp); fclose(fp);
  if ((json = cJSON_Parse(cfgdata)) == NULL) { cJSON_Delete(json); }
  else {
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "StartOnLoad");
   if(cJSON_IsBool(jsonItem)) sys.StartOnLoad = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "AnsiPrinting");
   if(cJSON_IsBool(jsonItem)) sys.AnsiPrinting = cJSON_IsTrue(jsonItem); else {
    jsonItem = cJSON_GetObjectItemCaseSensitive(json, "FancyPrinting");
    if(cJSON_IsBool(jsonItem)) sys.AnsiPrinting = cJSON_IsTrue(jsonItem);     }
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "BlockDisp");
   if(cJSON_IsBool(jsonItem)) sys.blockDisp = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "ShowInput");
   if(cJSON_IsBool(jsonItem)) ShowInput = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "HUDinfo");
   if(cJSON_IsBool(jsonItem)) HUDinfo = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "StartWithOverlay");
   if(cJSON_IsBool(jsonItem)) SystemHUD = cJSON_IsTrue(jsonItem);

   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "KeepAspect");
   if(cJSON_IsBool(jsonItem)) sys.keepAspect = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "EnableFullscreen");
   if(cJSON_IsBool(jsonItem)) INITFullscreen =cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "BoarderlessWindow");
   if(cJSON_IsBool(jsonItem)) FullscreenType = cJSON_IsTrue(jsonItem);
   

   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "DebugMode");
   if(cJSON_IsBool(jsonItem)) sys.Debug = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "GUIOpacity");
   if(cJSON_IsNumber(jsonItem)) sys.GUIOpacity = jsonItem->valueint;

   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "SkipBIOS");
   if(cJSON_IsBool(jsonItem)) sys.skipBIOS = cJSON_IsTrue(jsonItem);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "BIOSPath");
   if(cJSON_IsString(jsonItem)) if(strlen(jsonItem->valuestring)>0) sprintf(BIOSPath,"%s",jsonItem->valuestring);
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "SkipIntro");
   if(cJSON_IsString(jsonItem)) ForceSkipIntro=SkipIntro = cJSON_IsTrue(jsonItem);

   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "hour_offset");
   if(cJSON_IsNumber(jsonItem)) hour_offset = jsonItem->valueint;
   jsonItem = cJSON_GetObjectItemCaseSensitive(json, "min_offset");
   if(cJSON_IsNumber(jsonItem)) min_offset = jsonItem->valueint;
   for(j=0;j<2;j++) {
    jsonItem = cJSON_GetObjectItemCaseSensitive(json, j==0?"Player0":"Player1");
    jsonSubItem = cJSON_GetObjectItemCaseSensitive(jsonItem, "device");
    if(cJSON_IsNumber(jsonSubItem)) sys.controllerDevice[j] = jsonSubItem->valueint;
    jsonSubItem = cJSON_GetObjectItemCaseSensitive(jsonItem, "type");
    if(cJSON_IsNumber(jsonSubItem)) sys.controllerType[j] = jsonSubItem->valueint;
    
    jsonSubItem = cJSON_GetObjectItemCaseSensitive(jsonItem, "keys");
    if(cJSON_IsArray(jsonSubItem)) {
     for(i=0;i<32;i++) {
      sys.controllerKey[j][i] = cJSON_GetArrayItem(jsonSubItem, i)->valueint;
   }}}
 }} printf(".\n");
 sprintf(MainPrintString,"Loading %s%sTGR-PRTO %s %sAlpha %sBuild...\n\\ %s%sTheGameRazer %s(C) %s2017-2024 Koranva-Forest%s\n \\ %s%sHelp us on Github%s: %s%s%shttps://github.com/BILLPC2684/TGR-PRTO-RAYLIB%s%s\n  \\ %s%sDonate at%s: %s%s%shttps://Ko-Fi.com/BILLPC2684%s%s\n",COLOR_BOLD,COLOR_YELLOW,version,COLOR_BLUE,COLOR_RESET,COLOR_BOLD,COLOR_RED,COLOR_YELLOW,COLOR_GREEN,COLOR_DEFAULT,COLOR_ITALIC,COLOR_GREEN,COLOR_RESET,COLOR_BOLD,COLOR_BLUE,COLOR_UNDERLINE,linkuni,COLOR_RESET,COLOR_ITALIC,COLOR_GREEN,COLOR_RESET,COLOR_BOLD,COLOR_BLUE,COLOR_UNDERLINE,linkuni,COLOR_RESET);
 FilterAnsi(MainPrintString);

 printf(">>> %i\n",argc);
 for (int i=1; i<argc; i++) {
  printf("got \"%s\": ",argv[i]);
  //printf("ARG[%d/%d]: %s\n",i,argc-1,argv[i]);
//  if (!strcmp(argv[i],"--slow"         ) | !strcmp(argv[i],"-s"   )) { i++; slowdown   = (int) strtol(argv[i], (char **)NULL, 10); } else
  if (!strcmp(argv[i],"--debug"        ) | !strcmp(argv[i],"-d"   )) { sys.Debug       = true; printf("true\n"); } else
  if (!strcmp(argv[i],"--nodebug"      ) | !strcmp(argv[i],"-nd"  )) { sys.Debug       = false; printf("false\n"); } else
  if (!strcmp(argv[i],"--pauseload"    ) | !strcmp(argv[i],"-pl"  )) { sys.Debug       = true, sys.DebugPause[0] = 1; printf("true\n"); } else
  if (!strcmp(argv[i],"--waitinput"    ) | !strcmp(argv[i],"-wi"  )) { sys.Debug       = true, sys.DebugPause[0] = INT32_MAX; printf("infinite\n"); } else
  if (!strcmp(argv[i],"--skip"         ) | !strcmp(argv[i],"-sk"  )) { sys.skip = (int) strtol(argv[++i], (char **)NULL, 10); sys.skipBIOS = true; printf("%d\n",argv[i]); } else
  if (!strcmp(argv[i],"--skipbios"     ) | !strcmp(argv[i],"-sb"  )) { sys.skipBIOS    = true; printf("true\n"); } else
  if (!strcmp(argv[i],"--allowbios"    ) | !strcmp(argv[i],"-ab"  )) { sys.skipBIOS    = false; printf("false\n"); } else
  if (!strcmp(argv[i],"--blockprint"   ) | !strcmp(argv[i],"-np"  )) { sys.blockDisp   = true; printf("true\n"); } else
  if (!strcmp(argv[i],"--blockdisp"    ) | !strcmp(argv[i],"-ap"  )) { sys.blockDisp   = false; printf("false\n"); } else
  if (!strcmp(argv[i],"--keepaspect"   ) | !strcmp(argv[i],"-ka"  )) { sys.keepAspect  = true; printf("true\n"); } else
  if (!strcmp(argv[i],"--loseaspect"   ) | !strcmp(argv[i],"-la"  )) { sys.keepAspect  = false; printf("false\n"); } else
//  if (!strcmp(argv[i],"--devinfo"      ) | !strcmp(argv[i],"-di"  )) { devInfo         = true; } else
  if (!strcmp(argv[i],"--forcerender"  ) | !strcmp(argv[i],"-fr"  )) { GPUctl.ForceRender = true; } else
//  if (!strcmp(argv[i],"--debugbios"    ) | !strcmp(argv[i],"-db"  )) { debugBIOS       = true; } else
//  if (!strcmp(argv[i],"--noDump"       ) | !strcmp(argv[i],"-nd"  )) { noDump          = true; } else
//  if (!strcmp(argv[i],"--hudinfo"      ) | !strcmp(argv[i],"-hi"  )) { HUDinfo         = true; } else
  if (!strcmp(argv[i],"--showinput"    ) | !strcmp(argv[i],"-si"  )) { ShowInput       = true; printf("true\n"); } else
  if (!strcmp(argv[i],"--cancelintro"  ) | !strcmp(argv[i],"-ci"  )) { SkipIntro       = true; printf("skipped\n"); } else
  if (!strcmp(argv[i],"--tape"         ) | !strcmp(argv[i],"-tp"  )) { CurrentTape.State = (!strcmp(argv[++i],"play")|!strcmp(argv[i],"1")); sprintf(CurrentTape.Path,"%s",argv[++i]); printf("\"%s\"\n",CurrentTape.Path); } else
  if (!strcmp(argv[i],"--hideinput"    ) | !strcmp(argv[i],"-hi"  )) { ShowInput       = false; printf("false\n"); } else
  if (!strcmp(argv[i],"--extSAV"       ) | !strcmp(argv[i],"-sav" )) { sprintf(extSAV,"%s",argv[++i]); printf("\"%s\"\n",extSAV); }
  else {
   printf("FILE\n");
   if (IsFileExtension(argv[i], ".tgr")) {
    sprintf(NewROMPATH,"%s",argv[i]);
   } else if (IsFileExtension(argv[i], ".sav")) {
    sprintf(extSAV,"%s",argv[i]);
    sprintf(sys.Error,"Unknown FileType Given!\n"); sys.ErrorType=1; printError();
   }
 
  }
 }
//### Can't get discord_game_sdk.so to work .w. ###///
// struct Application {
//  struct IDiscordCore* core;
//  struct IDiscordUsers* users;
// } app;
// // Don't forget to memset or otherwise initialize your classes!
// memset(&app, 0, sizeof(app));
// 
// IDiscordCoreEvents events;
// memset(&events, 0, sizeof(events));
// 
// struct DiscordCreateParams params;
// params.client_id = 1149758048399798292;
// params.flags = DiscordCreateFlags_Default;
// params.events = &events;
// params.event_data = &app;
// 
// DiscordCreate(DISCORD_VERSION, &params, &app.core);
 
 UpdateColors();
 sys.SW = GPU_Resolutions[GPUctl.Rez][0],sys.SH = GPU_Resolutions[GPUctl.Rez][1];
 sys.LED[0]=128,sys.LED[1]=0,sys.LED[2]=0;
 
 SetConfigFlags(FLAG_WINDOW_RESIZABLE);
 InitWindow(sys.SW+4, sys.SH+4, "TheGameRazer");
 SetWindowMinSize(sys.SW+4,sys.SH+4);
 SetTargetFPS(60);
 SetExitKey(KEY_NULL);
 //font = 
 GenerateFont();
 
 #include "images.h"
 #if !_WIN32
  Image Icon = Bytes2ImageAlpha(TGR_app_icon_data, 23,24);
  ImageResizeNN(&Icon,23*2,24*2);
  SetWindowIcon(Icon);
  UnloadImage(Icon);
  //b'\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf4\xf5\xf5\x00\x00\x00\x00\xff\x00\x00\x00\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xf4\xf5\xf5\x00\x00\x00\x00\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xf1\xdci\xff\xf1\xdci\xff\xac\xac\xac\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x8c\x8c\x8c\xff\xac\xac\xac\xff\xac\xac\xac\xff\xf1\xdci\xff\xf1\xdci\xff\xff\xd8\x00\xff\xff\xd8\x00\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\xff\xcb\xae\r\xff\xff\xd8\x00\xff\xff\xd8\x00\xff\xff\xd8\x00\xff\xcb\xae\r\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\xac\xac\xac\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xcb\xae\r\xff\xff\xd8\x00\xff\xf1\xdci\xff\xf1\xdci\xff\xf1\xdci\xff\xf1\xdci\xff\xcb\xae\r\xff\xac\xac\xac\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x8c\x8c\x8c\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xcb\xae\r\xff\xcb\xae\r\xff\xcb\xae\r\xff\xf1\xdci\xff\xf1\xdci\xff\xf1\xdci\xff\xac\xac\xac\xff\x00\x00\x00\xff\x00\x00\x00\xff\xac\xac\xac\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\xf1\xdci\xff\xf1\xdci\xff\xcb\xae\r\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xd8\x00\xff\xff\xd8\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xcb\xae\r\xff\xcb\xae\r\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\xcb\xae\r\xff\xf1\xdci\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
 #endif
 
 uint8_t text[1024] = {0}, TGR_full_logo_data[3872] = {0};
 Image TGR_logo = Bytes2ImageAlpha(TGR_logo_animation_data[33], 44, 22);
 ImageResizeNN(&TGR_logo,44*8,22*8);
 ImageColorReplace(&TGR_logo,(Color){0,0,0,0xFF},VOID);
 Image TGR_logo8x = ImageCopy(TGR_logo);

 Image KF_logo = Bytes2ImageAlpha(koranva_forest_splash_logo_data, 312, 93);
 //Image KF_logo = GenImageColor(8*8,8*8,RAYWHITE);
 //CP2RGBA(TGR_full_logo_data,TGR_full_logo_data_raw[0],484,TGR_full_logo_data_cp);
 //Image TGR_logo = PtrBytes2ImageAlpha(TGR_full_logo_data,44,22);
 //TGR_full_logo_data[10*4] = 0xFF; TGR_full_logo_data[10*4+3] = 0xFF;
 //ImageDrawPixel(&Logo_original,11,0,(Color){0,0xFF,0,0xFF});
 //printf("%d\n",TGR_full_logo_data[11*4+1]);
 
 Image RL_logo = Bytes2ImageAlpha(RL_logo_data, 64,64);
 ImageResizeNN(&RL_logo,128,128);
 
 uint8_t inDialog = 0;
 CPU_init();
 
 
// CPU_load("./ROMS/fib-endless.tgr");
 
// CPU_start();
// CPU_ResetCore(0); CPU_ResetCore(1);
// CPU[0].running = true;
// CPU[1].running = true;
 sprintf(sys.NETWORK_IP,"localhost"); sys.NETWORK_PORT=1213;
 if (netlib_init() == -1) { sprintf(sys.Error,"netlib_init: %s\n", netlib_get_error()); sys.ErrorType=2; printError(); exit(2); }
 else {
  ip_address ip;
  tcp_socket sock;
  uint32_t sent;
  char message[1024];
  if (netlib_resolve_host(&ip, sys.NETWORK_IP,sys.NETWORK_PORT) == -1) { sprintf(sys.Error,"netlib_resolve_host: %s (IP: %s:%i)\n", netlib_get_error(),sys.NETWORK_IP,sys.NETWORK_PORT); sys.ErrorType=0; printError(); }
  else if (!(sock = netlib_tcp_open(&ip))) { sprintf(sys.Error,"netlib_tcp_open: %s (IP: %s:%i)\n", netlib_get_error(),sys.NETWORK_IP,sys.NETWORK_PORT); sys.ErrorType=0; printError(); }
  else {
   sprintf(MainPrintString,"%s%sConnected to server (IP: %s:%i)%s\n",COLOR_BOLD,COLOR_BLUE,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_RESET); FilterAnsi(MainPrintString);
   netlib_byte_buf* buf = netlib_alloc_byte_buf(20);
   netlib_write_uint32(buf,'t');
   netlib_write_uint32(buf,'e');
   netlib_write_uint32(buf,'s');
   netlib_write_uint32(buf,'t');
   netlib_write_uint32(buf,'1');
   sent = netlib_tcp_send_buf(sock, buf);
   if (sent < buf->length) { sprintf(sys.Error, "netlib_tcp_send: %s\n", netlib_get_error()); sys.ErrorType=0; printError(); }
   sprintf(MainPrintString,"%sSent %i bytes to (IP: %s:%i)\nData: \"%s",COLOR_GREEN,sent,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_MAGENTA); FilterAnsi(MainPrintString);
   for (sent=0;sent<buf->length;sent++) { printf("%c", buf->data[sent]); }
   sprintf(MainPrintString,"%s\"%s\n",COLOR_GREEN,COLOR_RESET); FilterAnsi(MainPrintString);
   netlib_free_byte_buf(buf);
   netlib_tcp_close(sock);
   sprintf(MainPrintString,"%sClosed connection to server (IP: %s:%i)%s\n",COLOR_BLUE,sys.NETWORK_IP,sys.NETWORK_PORT,COLOR_RESET); FilterAnsi(MainPrintString);
   netlib_quit();
 }}

 uint8_t Data720p[GPU_Resolutions[3][0]*GPU_Resolutions[3][1]*3];
 Image OverlayUI        = GenImageColor(GPU_Resolutions[3][0],GPU_Resolutions[3][1],VOID);
 sys.UI                 = GenImageColor(GPU_Resolutions[3][0],GPU_Resolutions[3][1],VOID);
 sys.Canvas             = Bytes2Image(Data720p, GPU_Resolutions[3][0],GPU_Resolutions[3][1]);
 sys.CanvasBuffer       = Bytes2Image(Data720p, GPU_Resolutions[3][0],GPU_Resolutions[3][1]);
 Texture OverlayTexture = LoadTextureFromImage(OverlayUI);
 Texture CanvasTexture  = LoadTextureFromImage(sys.Canvas);
 Texture UITexture      = LoadTextureFromImage(sys.UI);
 //for(GPUctl.Rez=0;GPUctl.Rez<4;GPUctl.Rez++) { GPUctl.Canvas[GPUctl.Rez] = LoadTextureFromImage(GenImageColor(GPU_Resolutions[GPUctl.Rez][0],GPU_Resolutions[GPUctl.Rez][1],BLACK)); }
 for(GPUctl.Rez=0;GPUctl.Rez<4;GPUctl.Rez++) { GPUctl.Canvas[GPUctl.Rez] = LoadTextureFromImage((Image){NULL,GPU_Resolutions[GPUctl.Rez][0],GPU_Resolutions[GPUctl.Rez][1],1,PIXELFORMAT_UNCOMPRESSED_R8G8B8}); }

 uint8_t hexdump[1024*1024]={0},cursor=0;
 uint32_t hexdumpi=0;

 GPUctl.Rez = GPUctl.NewRez = 0; reset_GPUlayers();

 HideCursor(); sys.MF = sys.MFT = 1; //CURSOR SETUP
 Image MouseSymbol = GenImageColor(8,8,VOID);
 getCharExt(&MouseSymbol, "+",0,0, WHITE, 0, 1);

 Rectangle SrcRect = {0,0,sys.SW,sys.SH};
 sys.HostWidth = GetScreenWidth(), sys.HostHeight = GetScreenHeight(); getAspectRatio(sys.ResizeDict);
 sys.BoarderThiccness = ceil(max(GetScreenWidth()/(float)sys.SW, GetScreenHeight()/(float)sys.SH));
 sys.DistRect = (Rectangle){sys.ResizeDict[2],sys.ResizeDict[3], sys.ResizeDict[0],sys.ResizeDict[1]};
 
 time_t rawtime;
 struct tm*timeinfo;

 sys.Cutscene1Timer = -1;
 if (SkipIntro) sys.Cutscene0Timer = -1,sys.Cutscene0Fade3 = -1;

 if(INITFullscreen) {
  if(FullscreenType) { ToggleBorderlessWindowed(); } else { ToggleFullscreen(); }
  SetWindowMinSize(sys.HostWidth,sys.HostHeight);
 }
// uint8_t bytes0[12] = "\x00\x00\x00\x00\x00\x00\x0D\x00\x00\x00\x00\x00",
 //uint8_t bytes1[2048] = "\x6F\x00\x00\x00\x00\x00\x13\xC0\x00\x00\x05\xA4\x13\xD0\x00\x00\x05\xA5\x0A\xC0\xC0\x00\x00\x08\x08\xCD\xD0\x00\x00\x00\x01\x1D\x00\x00\x00\x00\x05\xD0\xE0\x00\x00\x02\x0B\xE0\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xCA\x12\xE0\x00\x0B\x07\xCB\x13\xC0\x00\x00\x05\xA6\x13\x30\x00\x00\x05\xA7\x0A\xC0\xC0\x00\x00\x08\x08\xC3\x30\x00\x00\x00\x0B\x30\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xCC\x12\x30\x00\x0B\x07\xCD\x6E\x00\x00\x00\x00\x00\x76\x00\x00\x00\x00\x00\x00\xB0\x00\x00\x00\xFF\x00\x00\x00\x00\x00\x00\x73\x00\x00\x00\x00\x00\x00\xC0\x00\x00\x00\x60\x12\xC0\x00\x0B\x07\xBE\x00\xC0\x00\x00\x00\x2F\x12\xC0\x00\x0B\x07\xBF\x0E\x0E\x20\x00\x00\x00\x00\x10\x00\x00\x00\x00\x00\x40\x00\x0B\x06\x72\x01\x1D\x00\x00\x00\x00\x06\x0E\x80\x00\x00\x00\x13\x90\x00\x0B\x07\xBE\x13\xA0\x00\x0B\x07\xBF\x71\x00\x00\x00\x00\x00\x0E\x00\x60\x00\x01\xFE\x04\xC0\xC0\x00\x00\x1B\x12\xC0\x00\x0B\x07\xBE\x04\xC0\xC0\x00\x00\x1B\x12\xC0\x00\x0B\x07\xBF\x02\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x06\x5A\x1F\x00\x00\x00\x00\x00\x1C\x89\xA0\x00\x00\x02\x01\x1D\x00\x00\x00\x00\x0B\x00\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xC0\x12\x00\x00\x0B\x07\xC1\x0B\xC0\xF0\x00\x00\x18\x12\xF0\x00\x0B\x07\xC2\x0B\xF0\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xC3\x0B\xF0\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xC4\x12\xC0\x00\x0B\x07\xC5\x0B\xD0\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xC6\x12\xD0\x00\x0B\x07\xC7\x0B\xE0\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xC8\x12\xE0\x00\x0B\x07\xC9\x13\xF0\x00\x0B\x07\xCA\x0A\xF0\xF0\x00\x00\x08\x12\x00\x00\x0B\x07\xCB\x08\x0F\x00\x00\x00\x00\x13\xF0\x00\x0B\x07\xCC\x0A\xF0\xF0\x00\x00\x08\x12\x20\x00\x0B\x07\xCD\x08\x2F\x20\x00\x00\x00\x00\xD0\x00\x00\x00\x00\x00\xE0\x00\x00\x00\x00\x00\xF0\x00\x0B\x0D\xA6\x0D\xD0\x10\x00\x00\x16\x00\x40\x00\x0B\x07\xEC\x13\x8F\x0D\x80\x00\x00\x02\xF0\xF0\x00\x00\x01\x13\x9F\x0D\x80\x00\x00\x02\xF0\xF0\x00\x00\x01\x13\xAF\x0D\x80\x00\x00\x02\xF0\xF0\x00\x00\x01\x70\x00\x00\x00\x00\x00\x02\xF0\xF0\x00\x00\x01\x0D\xE0\x80\x00\x00\x2C\x00\xE0\x00\x00\x00\x00\x13\xC0\x00\x0B\x07\xCA\x0A\xC0\xC0\x00\x00\x08\x12\x00\x00\x0B\x07\xCB\x08\x0C\x00\x00\x00\x00\x02\xD0\xD0\x00\x00\x01\x02\x20\x20\x00\x00\x01\x00\x40\x00\x0B\x07\x68\x02\xE0\xE0\x00\x00\x01\x02\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x07\x74\x13\xC0\x00\x0B\x07\xCE\x13\xF0\x00\x0B\x07\xCA\x0A\xF0\xF0\x00\x00\x08\x12\x00\x00\x0B\x07\xCB\x08\x0F\x00\x00\x00\x00\x13\xF0\x00\x0B\x07\xCC\x0A\xF0\xF0\x00\x00\x08\x12\x20\x00\x0B\x07\xCD\x08\x2F\x20\x00\x00\x00\x0D\xC0\x30\x00\x00\x00\x02\x20\x20\x00\x00\x01\x02\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x08\x82\x0D\xC0\x30\x00\x00\x01\x03\x20\x20\x00\x00\x01\x02\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x08\x82\x0D\xC0\x30\x00\x00\x02\x02\x20\x20\x00\x00\x01\x03\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x08\x82\x0D\xC0\x30\x00\x00\x03\x03\x20\x20\x00\x00\x01\x03\x00\x00\x00\x00\x01\x00\x40\x00\x0B\x08\x82\x0E\x00\x70\x00\x00\x01\x0D\xC0\x20\x00\x00\x02\x00\xC0\x00\x00\x00\x00\x00\x40\x00\x0B\x09\x4E\x0D\xC0\x20\x00\x00\x03\x00\xC0\x00\x00\x00\x01\x00\x40\x00\x0B\x09\x4E\x15\xC0\x00\x00\x00\x01\x0E\x20\x70\x00\x00\x01\x0D\xC0\x20\x00\x00\x03\x00\xC0\x00\x00\x00\x02\x00\x40\x00\x0B\x09\x4E\x0D\xC0\x20\x00\x00\x01\x00\xC0\x00\x00\x00\x00\x00\x40\x00\x0B\x09\x4E\x15\xC0\x00\x00\x00\x01\x02\x00\x00\x00\x00\x2C\x0F\x00\x70\x00\x00\x01\x0D\xC0\x20\x00\x00\x01\x00\xC0\x00\x00\x00\x03\x00\x40\x00\x0B\x09\x4E\x0D\xC0\x20\x00\x00\x00\x00\xC0\x00\x00\x00\x02\x00\x40\x00\x0B\x09\x4E\x15\xC0\x00\x00\x00\x01\x02\x20\x20\x00\x00\x16\x0F\x20\x70\x00\x00\x03\x0D\xC0\x20\x00\x00\x02\x00\xC0\x00\x00\x00\x03\x00\x40\x00\x0B\x09\x4E\x0D\xC0\x20\x00\x00\x00\x00\xC0\x00\x00\x00\x01\x00\x40\x00\x0B\x09\x4E\x15\xC0\x00\x00\x00\x01\x12\xC0\x00\x0B\x07\xCE\x0B\x00\xC0\x00\x00\x08\x12\xC0\x00\x0B\x07\xCA\x12\x00\x00\x0B\x07\xCB\x0B\x00\xF0\x00\x00\x08\x12\xF0\x00\x0B\x07\xCC\x12\x00\x00\x0B\x07\xCD\x13\xF0\x00\x0B\x07\xC0\x0A\xF0\xF0\x00\x00\x08\x12\x00\x00\x0B\x07\xC1\x08\x0F\x00\x00\x00\x00\x00\x20\x00\x00\x00\x00\x13\xF0\x00\x0B\x07\xC2\x0A\xF0\xF0\x00\x00\x18\x08\xCF\xC0\x00\x00\x00\x13\xF0\x00\x0B\x07\xC3\x0A\xF0\xF0\x00\x00\x10\x08\xCF\xC0\x00\x00\x00\x13\xF0\x00\x0B\x07\xC4\x0A\xF0\xF0\x00\x00\x08\x08\xCF\xC0\x00\x00\x00\x13\xF0\x00\x0B\x07\xC5\x08\xCF\xC0\x00\x00\x00\x13\xF0\x00\x0B\x07\xC7\x0A\xF0\xF0\x00\x00\x18\x12\xD0\x00\x0B\x07\xC7\x08\xDF\xD0\x00\x00\x00\x13\xF0\x00\x0B\x07\xC9\x0A\xF0\xF0\x00\x00\x18\x12\xE0\x00\x0B\x07\xC9\x08\xEF\xE0\x00\x00\x00\x00\x00\x00\x00\x00\x1F\x01\x80\x00\x00\x00\x00\x01\x90\x00\x00\x00\x00\x01\xA0\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x20\x00\x00\x00\x00\x01\x1D\x00\x00\x00\x00\x78\x40\x00\x00\x00\x00\x7F\x00\x00\x00\x00\x00\x73\x00\x00\x00\x00\x00\x1E\x10\x00\x00\x00\x00\x04\xC0\xC0\x00\x00\x1B\x12\xCE\x0D\x80\x00\x00\x04\xC0\xC0\x00\x00\x1B\x12\xCF\x0D\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x40\x00\x0B\x06\x5A\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFF\x00\x00\x00\x00\x00";
// for(i=0;i<12;i++) sys.MEM[i] = bytes0[i];
 //for(i=0;i<2048;i++) sys.MEM[TGR_MEM_VRAM+CPLength+PtrLenth+11*0xFFFF+i] = bytes1[i];
// printf("TGR_MEM_VRAM+CPLength+PtrLenth+11*0xFFFF: 0x%X\n",TGR_MEM_VRAM+CPLength+PtrLenth+11*0xFFFF);
 //sys.DebugPause[0] = -1;
 //sys.DebugPause[2] = -1;
 //sys.Debug = true;
// WaitTime(1);
 //GPU[0].running = true;
 bool External_Debug = false;
 Texture Layers_Texture;
 struct timespec start, end;
 uint16_t delta;
 while(MainRunning) {
  time(&rawtime);
  clock_gettime(CLOCK_MONOTONIC, &end);
  delta = (end.tv_sec-start.tv_sec)*1000000+(end.tv_nsec-start.tv_nsec)/1000;
  clock_gettime(CLOCK_MONOTONIC, &start);
  timeinfo = localtime(&rawtime);
  if (CurrentTape.JustLoaded) {
   // TO-DO //
   if (CurrentTape.Loaded) {
    CurrentTape.Frame = (Image){&CurrentTape.FrameData,Tape_Resolution[0],Tape_Resolution[1],1,PIXELFORMAT_UNCOMPRESSED_R5G6B5};
   }
   CurrentTape.JustLoaded = false;
  }
  if (sys.Cutscene0Timer < 32*30) {
   // Koranva Forest Logo: Fade in
   if (sys.Cutscene0Timer < 32*1) {
    sys.Cutscene0Fade3 = (sys.Cutscene0Fade3-sys.Cutscene0Speed>0)?sys.Cutscene0Fade3-sys.Cutscene0Speed:0;
   } else //does nothing
   if (sys.Cutscene0Timer < 32*2) {
    sys.Cutscene0Fade0 = (sys.Cutscene0Fade0+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Fade0+sys.Cutscene0Speed:0xFF;
   } else
   if (sys.Cutscene0Timer < 32*6) {} else //does nothing
   // Koranva Forest Logo: Fade Out
   if (sys.Cutscene0Timer < 32*7) {
    sys.Cutscene0Fade0 = (sys.Cutscene0Fade0-sys.Cutscene0Speed>0)?sys.Cutscene0Fade0-sys.Cutscene0Speed:0;
   } else
   if (sys.Cutscene0Timer < 32*8) {} else //does nothing
   // TGR Logo: Fade in
   if (sys.Cutscene0Timer < 32*17) {
    sys.Cutscene0Background = VOID;
    uint16_t localCSNum = (sys.Cutscene0Timer-32*8);
    if ((localCSNum>79 && localCSNum<88) || (localCSNum>119 && localCSNum<128) || (localCSNum>255 && localCSNum<264)) {
     sys.Cutscene0Background = (Color){0xCB,0xAE,0x0D,0xFF};
    } else
    if ((localCSNum>71 && localCSNum<88) || (localCSNum>111 && localCSNum<128) || (localCSNum>237 && localCSNum<264)) {
     sys.Cutscene0Background = (Color){0xFF,0xD8,0x00,0xFF};
    } else
    if ((localCSNum>63 && localCSNum<88) || (localCSNum>103 && localCSNum<128) || (localCSNum>239 && localCSNum<264)) {
     sys.Cutscene0Background = (Color){0xF1,0xDC,0x69,0xFF};
    }
    if (localCSNum%8==0) {
     UnloadImage(TGR_logo);
     printf("sys.Cutscene0Timer: %d | %d\n",sys.Cutscene0Timer,sys.Cutscene0Timer-32*8);
     TGR_logo = Bytes2ImageAlpha(TGR_logo_animation_data[(localCSNum/8<34)?localCSNum/8:33], 44, 22);
     ImageResizeNN(&TGR_logo,44*8,22*8);
     ImageColorReplace(&TGR_logo,(Color){0,0,0,0xFF},VOID);
    } sys.Cutscene0Fade1 = (sys.Cutscene0Fade1+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Fade1+sys.Cutscene0Speed:0xFF;
   } else
   // TGR Logo: Move up
   // raylib Logo: Fade in
   if (sys.Cutscene0Timer < 32*21) {
    sys.Cutscene0Position = (sys.Cutscene0Position+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Position+sys.Cutscene0Speed:0xFF;
    sys.Cutscene0Fade2 = (sys.Cutscene0Fade2+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Fade2+sys.Cutscene0Speed:0xFF;
   } else
   if (sys.Cutscene0Timer < 32*26) {} else //does nothing
   // TGR Logo: Fade out
   // raylib Logo: Fade out
   if (sys.Cutscene0Timer < 32*26+16) {
    sys.Cutscene0Fade1 = (sys.Cutscene0Fade1-sys.Cutscene0Speed>0)?sys.Cutscene0Fade1-sys.Cutscene0Speed:0;
    sys.Cutscene0Fade2 = (sys.Cutscene0Fade2-sys.Cutscene0Speed>0)?sys.Cutscene0Fade2-sys.Cutscene0Speed:0;
    sys.Cutscene0Fade3 = (sys.Cutscene0Fade3+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Fade3+sys.Cutscene0Speed:0xFF;
   } else
   if (sys.Cutscene0Timer < 32*27) {
    sys.Cutscene0Fade1 = (sys.Cutscene0Fade1-sys.Cutscene0Speed>0)?sys.Cutscene0Fade1-sys.Cutscene0Speed:0;
    sys.Cutscene0Fade2 = (sys.Cutscene0Fade2-sys.Cutscene0Speed>0)?sys.Cutscene0Fade2-sys.Cutscene0Speed:0;
    sys.Cutscene0Fade3 = (sys.Cutscene0Fade3+sys.Cutscene0Speed<0xFF)?sys.Cutscene0Fade3+sys.Cutscene0Speed:0xFF;
    if ((sys.Cutscene0Timer == 32*28)%31==0) {
     UnloadImage(TGR_logo);
     Image TGR_logo = Bytes2ImageAlpha(TGR_logo_animation_data[34], 44, 22);
     ImageResizeNN(&TGR_logo,44*8,22*8);
     ImageColorReplace(&TGR_logo,(Color){0,0,0,0xFF},VOID);
   } else
   if (sys.Cutscene0Timer == 32*29) {
     UnloadImage(TGR_logo);
     Image TGR_logo = Bytes2ImageAlpha(TGR_logo_animation_data[33], 44, 22);
     sys.Cutscene0Position = sys.Cutscene0Fade1 = sys.Cutscene0Fade2 = sys.Cutscene0Fade3 = 0;
   }} sys.Cutscene0Timer++;
  }
  if(IsKeyReleased(KEY_SPACE)) sys.Cutscene0Timer = 0;
  sys.pMX = sys.MX, sys.pMY = sys.MY, sys.CursorColor = GREEN,
  sys.MX = (GetMouseX()-sys.ResizeDict[2])*(sys.SW/(float)sys.ResizeDict[0]),
  sys.MY = (GetMouseY()-sys.ResizeDict[3])*(sys.SH/(float)sys.ResizeDict[1]);
  sys.MB = IsMouseButtonDown(MOUSE_BUTTON_LEFT),
  sys.MS = GetMouseWheelMove();
  
  if(sys.MX == sys.pMX && sys.MY == sys.pMY && sys.MB == 0 && sys.MS == 0) {
   if(sys.MFT == 0) {
    sys.MF=(sys.MF-8>1)?sys.MF-8:1;
   } else sys.MFT--;
  } else { sys.MFT = 160, sys.MF=(sys.MF+16<0xFF)?sys.MF+16:0xFF; }
  
  if(sys.MB) { sys.CursorColor = LIME; }
  if(!(CPU[0].running || CPU[1].running)) {
   sys.LED[0] = ((sys.fade<0)?-sys.fade++-1:sys.fade++)*2;
   if(sys.LED[1]>0) sys.LED[1]--;
   if(sys.LED[2]>0) sys.LED[2]--;
  } else
  if(sys.Pause) {
   sys.LED[0] = ((sys.fade<0)?sys.fade+++1:sys.fade++-1)*2;
   sys.LED[1] = ((sys.fade<0)?sys.fade+++1:sys.fade++-1)*2;
   if(sys.LED[2]>0) sys.LED[2]--;
  }
  if (GPUctl.Rez != GPUctl.NewRez) {
   sys.ScreenReady = false;
   GPUctl.Rez=GPUctl.NewRez=(GPUctl.NewRez%4);
   sys.SW = GPU_Resolutions[GPUctl.Rez][0],sys.SH = GPU_Resolutions[GPUctl.Rez][1];
   SetWindowMinSize(sys.SW+4,sys.SH+4);
   printf("%s%sNew Resolution: %s%dx%d%s\n",COLOR_BOLD,COLOR_YELLOW,COLOR_BLUE,sys.SW,sys.SH,COLOR_RESET);
   reset_GPUlayers(); SrcRect = (Rectangle){0,0,sys.SW,sys.SH};
  }
  if(IsWindowReady()) {
   if (IsFileDropped()) {
    FilePathList droppedFiles = LoadDroppedFiles();
    if (!strcmp(toLower(&droppedFiles.paths[0][strlen(droppedFiles.paths[0])-3]),"tgr")) {
     sprintf(extSAV,"");
     sprintf(NewROMPATH,"%s",droppedFiles.paths[0]);
    } else if (!strcmp(toLower(&droppedFiles.paths[0][strlen(droppedFiles.paths[0])-3]),"sav")) {
     sprintf(extSAV,"%s",droppedFiles.paths[0]);
    } else {
     sprintf(sys.Error,"Unknown FileType Given!\n"); sys.ErrorType=1; printError();
    }
    UnloadDroppedFiles(droppedFiles);
   }
   if (strcmp(NewROMPATH,ROMPATH)) {
    strcpy(ROMPATH,NewROMPATH);
    CPU_stop(); CPU_load(ROMPATH);
    if (strlen(extSAV)>0) {CPU_extsav(extSAV);}
    CPU_start();
   }
   sprintf(text,"TheGameRazer - [%s] - %i/%i FPS",(sys.ROMloaded)?((sys.title[0]==0)?"No Title":sys.title):"NO-ROM",sys.FPS,GetFPS());
   SetWindowTitle(text);
   
   if(IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL)) {
    if(IsKeyPressed(KEY_I)){ sprintf(MainPrintString,"HUDinfo\n"); FilterAnsi(MainPrintString); HUDinfo = 1-HUDinfo; }
    if(IsKeyPressed(KEY_U)){ sprintf(MainPrintString,"ShowInput\n"); FilterAnsi(MainPrintString); ShowInput = 1-ShowInput; }
    if(IsKeyPressed(KEY_G)){ sprintf(MainPrintString,"ShowDump\n"); FilterAnsi(MainPrintString); ShowDump = 1-ShowDump; }
    if(IsKeyPressed(KEY_O)){ sprintf(MainPrintString,"OPEN DA MENU!!\n"); FilterAnsi(MainPrintString); inDialog = 1; }
    if(IsKeyPressed(KEY_D)){ sys.Debug=1-sys.Debug; sprintf(MainPrintString,"Debug mode: %s\n",sys.Debug?"Enabled":"Disabled"); FilterAnsi(MainPrintString); inDialog = 1; }
    if(IsKeyPressed(KEY_Z)){ CPU_start(); }
   }if((IsKeyDown(KEY_LEFT_ALT)||IsKeyDown(KEY_RIGHT_ALT)) && IsKeyPressed(KEY_ENTER)){
    if(FullscreenType){ToggleBorderlessWindowed();}else{ToggleFullscreen();} INITFullscreen=!INITFullscreen;
    SetWindowMinSize((IsWindowFullscreen)?sys.SW+4:sys.HostWidth,(IsWindowFullscreen)?sys.SH+4:sys.HostHeight);
   }
   for(j=0;j<2;j++) {
    if (sys.controllerDevice[j] == 0) {
     for(i=0;i<32;i++)
      UInput[j][i] = IsKeyDown(sys.controllerKey[j][i]);
    } else if(IsGamepadAvailable(sys.controllerDevice[j]-1)) {
     for(i=0;i<32;i++)
      UInput[j][i] = IsGamepadButtonDown(sys.controllerDevice[j]-1, sys.controllerKey[j][i]);
    } else { sys.controllerType[j] = 0; }
   }


   if(!GPUctl.FrameSeen || GPUctl.ForceRender) { GPUctl.FrameSeen = true; }
   BeginDrawing();
    ClearBackground((Color){16,16,16,255});
    if(!(CPU[0].running||CPU[1].running||GPU[0].running||GPU[1].running||GPU[2].running||GPU[3].running)){
     ImageClearBackground(&sys.Canvas,(Color){0x16,0x51,0xED,0xFF});
     i = timeinfo->tm_hour+hour_offset, j = timeinfo->tm_min+min_offset;
     sprintf(text,"%s%d:%s%d",((i?12:i%13)<10)?" ":"",(i==0)?12:i%13,(j<10)?"0":"",j);
     getChar(text,  sys.SW-6*16,1*16,WHITE, 1, 2);
     getChar("CH3", sys.SW-5*16,2*16,WHITE, 1, 2);
     sprintf(text,"STOP\x7F\x59");
     getChar(text,         1*16,1*16,WHITE, 1, 2);
     if (CurrentTape.Loaded) {
       sprintf(text," SP  00:00:00\n\x7F\x59------------\x7F\x59");
      getChar(text,        1*16,sys.SH-4*16,WHITE, 1, 2);
     } else {
      getChar("[No Tape]", 1*16,sys.SH-2*16,WHITE, 1, 2);
    }} else {
     ImageDraw(&sys.Canvas,sys.CanvasBuffer,(Rectangle){0,0,sys.SW,sys.SH}, (Rectangle){0,0,sys.SW,sys.SH},WHITE);
    }
    ImageClearBackground(&sys.UI,VOID);
    ImageClearBackground(&OverlayUI,(sys.Cutscene0Timer < 32*30)?sys.Cutscene0Background:VOID);
 //   printf("System Canvas: 0x%02X\n",*(uint8_t*)&(sys.Canvas.data));
 //   printf("GPU Canvas: 0x%02X\n",*(uint8_t*)&(GPUctl.Canvas.data));
 //   ImageDraw(&sys.Canvas,GPUctl.Canvas[GPUctl.Rez], (Rectangle){0,0,sys.SW,sys.SH}, (Rectangle){0,0,sys.SW,sys.SH}, WHITE);
 //   printf("System Canvas: 0x%02X\n",*(uint8_t*)&(sys.Canvas.data));
    
    //sys.Canvas = GenImageColor(sys.SW,sys.SH,(Color){16,16,16,255});
 //   ImageClearBackground(&sys.Canvas,(Color){16,16,16,255});
 //   sprintf(text,"FPS: %2i|UPS: %2i[%.2fsys.MS]╧",sys.FPS,GetFPS(),GetFrameTime());
 //   DrawRectangle(12,sys.SH-32,1000,16,WHITE);
 //   DrawText(text, 12, sys.SH-32, 20, LIGHTGRAY);
 //   getChar(text, 12,sys.SH-32,TGR_RED, 0, 2);
    if (sys.Cutscene0Fade0>0) {
     ImageDraw(&OverlayUI,KF_logo,(Rectangle){0,0,KF_logo.width,KF_logo.height},(Rectangle){(((sys.SW/8)*8)/2)-((KF_logo.width/8)*8)/2, (((sys.SH/8)*8)/2)-((KF_logo.height/8)*8)/2-4*8, KF_logo.width,KF_logo.height},(Color){0xFF,0xFF,0xFF,sys.Cutscene0Fade0});
     getCharExt(&OverlayUI,"Presents...", (((sys.SW/8)*8)/2)-5*8, (((sys.SH/8)*8)/2)+4*8, (Color){TGR_BLUE.r,TGR_BLUE.g,TGR_BLUE.b,sys.Cutscene0Fade0}, 4, 2);
    }
    if (sys.Cutscene0Fade2>0) {
     ImageDrawText(&OverlayUI,"Powered By:", ((((sys.SW/8)*8)/2)-11*8)-4*8, (((sys.SH/8)*8)/2)+10*8, 20, (Color){245,245,245,sys.Cutscene0Fade2});
     ImageDraw(&OverlayUI,RL_logo,(Rectangle){0,0,RL_logo.width,RL_logo.height},(Rectangle){((((sys.SW/8)*8)/2)-64)+10*8, ((((sys.SH/8)*8)/2)-64)+12*8, 128,128},(Color){0xFF,0xFF,0xFF,sys.Cutscene0Fade2});
    }
    if (sys.Cutscene0Fade1>0)
     ImageDraw(&OverlayUI,TGR_logo,(Rectangle){0,0,TGR_logo.width,TGR_logo.height},(Rectangle){((((sys.SW/8)*8)/2)-((TGR_logo.width/8)*8)/2)-0*8, (((sys.SH/8)*8)/2)-((TGR_logo.height/8)*8)/2-(sys.Cutscene0Position/255.0)*(7*8), 44*8,22*8},(Color){0xFF,0xFF,0xFF,sys.Cutscene0Fade1});
    //DrawText("Powered By:", 120, 250, 20, RAYWHITE);
    //sprintf(text, "sys.MFT: %3d | sys.MF: %3d", sys.MFT,sys.MF);
    sprintf(text, "Draw Delta: %d\nRender Delta: %d", delta,GPUctl.RenderDelta);
    getChar(text,20*8,1*8,TGR_DIM_REDT,1,1);

//    sprintf(text,"` ABCDEFGHIJKLMN\nOPQRSTUVWXYZ0123\n456789!@#$%^&*()\n-+_=[]{}\\|;:'\".,\n<>/?~abcdefghijk\nlmnopqrstuvwxyz\n┌┬┐╔╦╗╓╥╖╒╤╕─│\n├┼┤╠╬╣╟╫╢╞╪╡═║\n└┴┘╚╩╝╙╨╜╘╧╛\n⢀ ⢠ ⢰ ⢸ ⡀ ⣀ ⣠ ⣰ ⣸ ⡄ ⣄ ⣤ ⣴ ⣼ ⡆ ⣆ ⣦ ⣶ ⣾ ⡇ ⣇ ⣧ ⣷ ⣿ a\n\n⡿ ⡟ ⡏ ⡇ ⢿ ⠿ ⠟ ⠏ ⠇ ⢻ ⠻ ⠛ ⠋ ⠃ ⢹ ⠹ ⠙ ⠉ ⠁ ⢸ ⠸ ⠘ ⠈ b");
//    getChar(text, 0*8, 0*8, LIGHTGRAY,true,1);
 //   getChar(text, 215,15, TGR_RED, 0, 2);
 //   getChar(text, 216,16, TGR_DIM_RED, 1, 2);
    
    if (HUDinfo == false) {
     sprintf(text,"FPS: %2i",sys.FPS);
     getChar(text, 2*8, sys.SH-(4*8), TGR_REDT,true,1);
    } else {
     //printf("2*8: %d, sys.SH-(7*8): %d\n",2*8, sys.SH-(17*8));
     sprintf(text,"Instruction Pointer: [0x%07X, 0x%07X]",CPU[0].IP,CPU[1].IP);
     getChar(text, 2*8, sys.SH-(7*8), TGR_BLUET,true,1);
     sprintf(text," RAM Usage: %9li/%9i bytes(%03.2f%%) full)",(uint64_t)sys.MemUse,0x8000000,(sys.MemUse/0x8000000)*100);
     getChar(text, 1*8, sys.SH-(6*8), TGR_REDT,true,1);
     sprintf(text,"VRAM Usage: %9li/%9i bytes(%03.2f%%) full)",(uint64_t)sys.VMemUse,0x4000000,(sys.VMemUse/0x4000000)*100);
     getChar(text,1*8, sys.SH-(5*8), TGR_REDT,true,1);
     sprintf(text,"FPS: %2i/%2i | IPS: %8i (%03.2f%%) TR: %ld",sys.FPS,GetFPS(),(int)(sys.IPS[0]+sys.IPS[1]),(sys.IPS[0]+sys.IPS[1])/24000000.0f*100,(uint64_t)(CPU[0].TI+CPU[1].TI));
     getChar(text, 2*8, sys.SH-(4*8), TGR_REDT,true,1);
 
    }
    if (ShowInput) {
     for(j=0;j<2;j++) {
      sprintf(text,"P%i:",j+1);
      getChar(text, 2*8, sys.SH-(3-j)*8, BLUET, true,1);
      switch(sys.controllerType[j]) {
       defult:
       case 0:
        getChar("DISCONNECTED", 6*8, sys.SH-(3-j)*8, TGR_DIM_REDT, true,1);
        break;
       case 1:
        getChar("[", 5*8, sys.SH-(3-j)*8, BLUET, true,1);
        if (UInput[j][ 0]) { getChar("A",       6*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 1]) { getChar("B",       8*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 2]) { getChar("C",      10*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 3]) { getChar("X",      12*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 4]) { getChar("Y",      14*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 5]) { getChar("Z",      16*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 6]) { getChar("L",      18*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 7]) { getChar("R",      20*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 8]) { getChar("START",  22*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][ 9]) { getChar("SELECT", 28*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][10]) { getChar("UP",     35*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][11]) { getChar("DOWN",   38*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][12]) { getChar("LEFT",   43*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        if (UInput[j][13]) { getChar("RIGHT",  48*8, sys.SH-(3-j)*8,  BLUET,true,1); }
        getChar("]", 53*8, sys.SH-(3-j)*8, BLUET, true,1);
        break;
       default:
        sprintf(text,"P%i: UNKNOWN CONTROLLER",j+1);
        getChar(text, 2*8, sys.SH-(3*8), BLUET, true,1);
    }}} else {
     sprintf(text,"SystemHUD: %s | SystemMenu: [%i, %i]",(SystemHUD)?"true":"false",0,0);
     getChar(text, 16,sys.SH-24, TGR_DIM_BLUET,  true,1);
     sprintf(text,"Mouse: [%i, %i, %i, %i] Click: %i | Scroll: %i",sys.MX,sys.MY,GetMouseX(),GetMouseY(),sys.MB,sys.MS);
     getChar(text, 16,sys.SH-16, TGR_DIM_BLUET,  true,1);
    }
    
    if (ShowDump) {
     uint32_t hexdump_addr = hexdumpi;
     uint16_t hexdump_x[2] = {sys.SW/2.0-29*8-4,sys.SW/2.0+29*8},
              hexdump_y[2] = {sys.SH/2.0-20*8-4,sys.SH/2.0+20*8};
     ImageDrawRectangle(&sys.UI,hexdump_x[0],hexdump_y[0],hexdump_x[1],hexdump_y[1],(Color){0,0xFF,0,0xFF});
     if((sys.MX>=hexdump_x[0] && sys.MX<hexdump_x[1]) && (sys.MY>=hexdump_y[0] && sys.MY<hexdump_y[1])) {
      sys.CursorColor = MAGENTA;
     } else SetMouseCursor(0);
     ImageDrawRectangle(&sys.UI, hexdump_x[0],hexdump_y[0],hexdump_x[1],hexdump_y[1],TGR_BLUET);
     sprintf(text,"._______.________________________________.________________.");
     getCharExt(&sys.UI,text,hexdump_x[0],hexdump_y[0],TGR_RED,1,1);
     sprintf(text, "|       |00  02  04  06  08  0A  0C  0E  |0 2 4 6 8 A C E |");
     getCharExt(&sys.UI,text,hexdump_x[0],hexdump_y[0]+1*8,TGR_RED,1,1);
     sprintf(text, "01  03  05  07  09  0B  0D  0F  1 3 5 7 9 B D F");
     getCharExt(&sys.UI,text,hexdump_x[0]+11*8,hexdump_y[0]+1*8,TGR_DIM_RED,1,1);
     if (hexdump_addr>=TGR_MEM_ROM0    && hexdump_addr<TGR_MEM_ROM1   ) { sprintf(text,"ROM PG0"); } else
     if (hexdump_addr>=TGR_MEM_ROM1    && hexdump_addr<TGR_MEM_SAV    ) { sprintf(text,"ROM PG1"); } else
     if (hexdump_addr>=TGR_MEM_SAV     && hexdump_addr<TGR_MEM_WRAM   ) { sprintf(text,"SAVdata"); } else
     if (hexdump_addr>=TGR_MEM_WRAM    && hexdump_addr<TGR_MEM_STACK0 ) { sprintf(text,"WRAM"); } else
     if (hexdump_addr>=TGR_MEM_STACK0  && hexdump_addr<TGR_MEM_STACK1 ) { sprintf(text,"Stack0"); } else
     if (hexdump_addr>=TGR_MEM_STACK1  && hexdump_addr<TGR_MEM_IO     ) { sprintf(text,"Stack1"); } else
     if (hexdump_addr>=TGR_MEM_IO      && hexdump_addr<TGR_MEM_SRAMEXT) { sprintf(text,"SRAM"); } else
     if (hexdump_addr>=TGR_MEM_SRAMEXT && hexdump_addr<TGR_MEM_VRAM   ) { sprintf(text,"Ext.RAM"); } else
     if (hexdump_addr>=TGR_MEM_VRAM    && hexdump_addr<TGR_MEM_VSTACK0) { sprintf(text,"VRAM"); } else
     if (hexdump_addr>=TGR_MEM_VSTACK0 && hexdump_addr<TGR_MEM_VSTACK1) { sprintf(text,"Stack0V"); } else
     if (hexdump_addr>=TGR_MEM_VSTACK1 && hexdump_addr<TGR_MEM_VSTACK2) { sprintf(text,"Stack1V"); } else
     if (hexdump_addr>=TGR_MEM_VSTACK2 && hexdump_addr<TGR_MEM_VSTACK3) { sprintf(text,"Stack2V"); } else
     if (hexdump_addr>=TGR_MEM_VSTACK3 && hexdump_addr<TGR_MEM_VRAMEXT) { sprintf(text,"Stack3V"); } else
     if (hexdump_addr>=TGR_MEM_VRAMEXT && hexdump_addr<TGR_MEM_TOTAL  ) { sprintf(text,"ExtVRAM"); }
     getCharExt(&sys.UI,text,hexdump_x[0]+1*8,hexdump_y[0]+1*8,TGR_DIM_RED,1,1);
     sprintf(text, "|-------|--------------------------------|----------------|");
     getCharExt(&sys.UI,text,hexdump_x[0]+0*8,hexdump_y[0]+2*8,TGR_RED,1,1);
     for(i=0;i<32;i++) {
      sprintf(text,"|       |                                |                |");
      getCharExt(&sys.UI,text,hexdump_x[0],hexdump_y[0]+(3+i)*8,TGR_RED,1,1);
      sprintf(text,"%02X  %02X  %02X  %02X  %02X  %02X  %02X  %02X   %c %c %c %c %c %c %c %c",sys.MEM[hexdump_addr],sys.MEM[hexdump_addr+2],sys.MEM[hexdump_addr+4],sys.MEM[hexdump_addr+6],sys.MEM[hexdump_addr+8],sys.MEM[hexdump_addr+10],sys.MEM[hexdump_addr+12],sys.MEM[hexdump_addr+14],ascii127[sys.MEM[hexdump_addr]],ascii127[sys.MEM[hexdump_addr+2]],ascii127[sys.MEM[hexdump_addr+4]],ascii127[sys.MEM[hexdump_addr+6]],ascii127[sys.MEM[hexdump_addr+8]],ascii127[sys.MEM[hexdump_addr+10]],ascii127[sys.MEM[hexdump_addr+12]],ascii127[sys.MEM[hexdump_addr+14]]);
      getCharExt(&sys.UI,text,hexdump_x[0]+9*8,hexdump_y[0]+(3+i)*8,(hexdump_addr%32==0)?TGR_DIM_RED:TGR_RED,1,1);
      sprintf(text,"%02X  %02X  %02X  %02X  %02X  %02X  %02X  %02X  %c %c %c %c %c %c %c %c",sys.MEM[hexdump_addr+1],sys.MEM[hexdump_addr+3],sys.MEM[hexdump_addr+5],sys.MEM[hexdump_addr+7],sys.MEM[hexdump_addr+9],sys.MEM[hexdump_addr+11],sys.MEM[hexdump_addr+13],sys.MEM[hexdump_addr+15],ascii127[sys.MEM[hexdump_addr+1]],ascii127[sys.MEM[hexdump_addr+3]],ascii127[sys.MEM[hexdump_addr+5]],ascii127[sys.MEM[hexdump_addr+7]],ascii127[sys.MEM[hexdump_addr+9]],ascii127[sys.MEM[hexdump_addr+11]],ascii127[sys.MEM[hexdump_addr+13]],ascii127[sys.MEM[hexdump_addr+15]]);
      getCharExt(&sys.UI,text,hexdump_x[0]+11*8,hexdump_y[0]+(3+i)*8,(hexdump_addr%32==0)?TGR_RED:TGR_DIM_RED,1,1);
      sprintf(text,"%07X",hexdump_addr);
      getCharExt(&sys.UI,text,hexdump_x[0]+1*8,hexdump_y[0]+(3+i)*8,(hexdump_addr%32==0)?TGR_RED:TGR_DIM_RED,1,1);
      hexdump_addr+=0x10;
     }
     if(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
      if(UInput[0][10]) hexdumpi=((int32_t)hexdumpi-0x100000)<=0?0:hexdumpi-0x100000;
      if(UInput[0][11]) hexdumpi=((int32_t)hexdumpi+0x100000)>=TGR_MEM_TOTAL?TGR_MEM_TOTAL:hexdumpi+0x100000;
     } else {
      if(UInput[0][10]) hexdumpi=((int32_t)hexdumpi-0x200)<=0?0:hexdumpi-0x200;
      if(UInput[0][11]) hexdumpi=((int32_t)hexdumpi+0x200)>=TGR_MEM_TOTAL?TGR_MEM_TOTAL:hexdumpi+0x200;
     }
    }
    
    //printf("2 | GPUctl.Rez: %d, &GPUctl.Layers[4]: 0x%X, \n",GPUctl.Rez,GPUctl.Layers[4].data);

//    getCharExt(&OverlayUI, "+",sys.MX-4,sys.MY-16, sys.CursorColor, sys.CursorDepth, 1);
    ImageDraw(&OverlayUI,MouseSymbol,(Rectangle){0,0,8,8},(Rectangle){sys.MX+sys.CursorDepth-4,sys.MY+sys.CursorDepth-4,8,8},(Color){sys.CursorColor.r,sys.CursorColor.g,sys.CursorColor.b,(float)((sys.MF>0)?256-sys.MF:sys.GUIOpacity/100.f)*sys.CursorColor.a});
    //ImageDraw(&OverlayUI,MouseSymbol,(Rectangle){0,0,8,8},(Rectangle){sys.MX-4,sys.MY-4,8,8},(Color){sys.CursorColor.r,sys.CursorColor.g,sys.CursorColor.b,(float)(256-sys.MF)*sys.CursorColor.a});
    UpdateTexture(CanvasTexture,sys.Canvas.data);
    UpdateTexture(UITexture,sys.UI.data);
    UpdateTexture(OverlayTexture, OverlayUI.data);
    FadeMask.a = sys.Cutscene0Fade3;
    BoarderLED = (Color){sys.LED[0],sys.LED[1],sys.LED[2],sys.Cutscene0Fade3};
    //printf("------------------\nsys.BoarderThiccness: %d [%f, %f]\nsys.DistRect: [%f, %f, %f, %f]\n",sys.BoarderThiccness,GetScreenWidth()/(float)sys.SW, GetScreenHeight()/(float)sys.SH,sys.DistRect.x,sys.DistRect.y,sys.DistRect.width,sys.DistRect.height);
    if (sys.keepAspect == true) { //############################################################################################################//
     //DrawTexturePro(GPUctl.Canvas[GPUctl.Rez], SrcRect, sys.DistRect, Vector2_ZERO, 0,FadeMask);
     DrawTexturePro(CanvasTexture , SrcRect, sys.DistRect, Vector2_ZERO, 0,FadeMask);
     DrawTexturePro(UITexture     , SrcRect, sys.DistRect, Vector2_ZERO, 0,FadeMask);
     DrawTexturePro(OverlayTexture, SrcRect, sys.DistRect, Vector2_ZERO, 0,WHITE);
     DrawRectangle(sys.ResizeDict[2]-sys.BoarderThiccness ,sys.ResizeDict[3]-sys.BoarderThiccness ,sys.BoarderThiccness                    ,sys.ResizeDict[1]+sys.BoarderThiccness*2,BoarderLED);
     DrawRectangle(sys.ResizeDict[2]-sys.BoarderThiccness ,sys.ResizeDict[3]-sys.BoarderThiccness ,sys.ResizeDict[0]+sys.BoarderThiccness*2,sys.BoarderThiccness                    ,BoarderLED);
     DrawRectangle(sys.ResizeDict[2]+sys.ResizeDict[0]    ,sys.ResizeDict[3]-sys.BoarderThiccness ,sys.BoarderThiccness                    ,sys.ResizeDict[1]+sys.BoarderThiccness*2,BoarderLED);
     DrawRectangle(sys.ResizeDict[2]-sys.BoarderThiccness ,sys.ResizeDict[3]+sys.ResizeDict[1]    ,sys.ResizeDict[0]+sys.BoarderThiccness*2,sys.BoarderThiccness                    ,BoarderLED);
    } else {
     //DrawTexturePro(GPUctl.Canvas[GPUctl.Rez], SrcRect, sys.DistRect, Vector2_ZERO,0,FadeMask);
     DrawTexturePro(CanvasTexture, SrcRect, sys.DistRect, Vector2_ZERO,0,FadeMask);
     DrawTexturePro(UITexture, SrcRect, sys.DistRect, Vector2_ZERO,0,FadeMask);
     DrawTexturePro(OverlayTexture, SrcRect, sys.DistRect, Vector2_ZERO, 0, WHITE);
     DrawRectangle(0,                                 0,                                  sys.BoarderThiccness,sys.HostHeight,      BoarderLED);
     DrawRectangle(0,                                 0,                                  sys.HostWidth,       sys.BoarderThiccness,BoarderLED);
     DrawRectangle(sys.HostWidth-sys.BoarderThiccness,0,                                  sys.BoarderThiccness,sys.HostHeight,      BoarderLED);
     DrawRectangle(0,                                 sys.HostHeight-sys.BoarderThiccness,sys.HostWidth,       sys.BoarderThiccness,BoarderLED);
    }
    //DrawRectangle(0   ,sys.SH-2,sys.SW,2 ,(Color){sys.LED[0],sys.LED[1],sys.LED[2],255});
    if (External_Debug) {
     if (sys.Cutscene1Timer < 32*5) {
      if (sys.Cutscene1Timer < 32*1) {
       if (sys.Cutscene1Timer == 0) {
        SetTargetFPS(120);
        SetWindowMinSize(1280*2+3, 720*2+3);
       }
      } else //init and does nothing
      if (sys.Cutscene1Timer < 32*5) {
       sys.Cutscene1transition0 = (sys.Cutscene1transition0+1<0xFF)?sys.Cutscene1transition0+1:0xFF;
      } else
      if (sys.Cutscene1Timer < 32*5) {} //does nothing
     }
    } else {
     if (sys.Cutscene1Timer < 32*5) {
      // Koranva Forest Logo: Fade in
      if (sys.Cutscene1Timer < 32*1) {} else //does nothing
      if (sys.Cutscene1Timer < 32*5) {
       sys.Cutscene1transition0 = (sys.Cutscene1transition0-1>0)?sys.Cutscene1transition0-1:0;
      } else
      if (sys.Cutscene1Timer == 32*5-1) {
       SetTargetFPS(120);
       SetWindowMinSize(1280*2+3, 720*2+3);
      } //deinit and does nothing
     }
    }
    if (External_Debug || (sys.Cutscene1Timer>0 && sys.Cutscene1Timer < 32*5)) {
     printf("TEST!!\n");
     SetWindowMinSize(sys.SW+4,sys.SH+4);
     Layers_Texture = LoadTextureFromImage(GPUctl.Layers[GPU[0].Layer]);
     UpdateTexture(Layers_Texture, GPUctl.Layers[GPU[0].Layer].data);
     DrawTexturePro((Texture) {0,GetScreenWidth(),GetScreenHeight(),1,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8}, (Rectangle){0,0, GetScreenWidth(),GetScreenHeight()},(Rectangle){(sys.Cutscene1transition0/255)*(GetScreenWidth()-(GetScreenWidth()/4)),(sys.Cutscene1transition0/255)*(GetScreenWidth()/2), sys.SW,sys.SH}, (Vector2){0,0}, 0, WHITE);
    }
   EndDrawing(); //UnloadImage(sys.Canvas); //UnloadTexture(CanvasTexture);
   if (WindowShouldClose()) { printf("BREAK!!!\n"); break; }
   if (IsWindowResized() || sys.ScreenReady == false) {
    sys.HostWidth = External_Debug?sys.SW:GetScreenWidth(), sys.HostHeight = External_Debug?sys.SH:GetScreenHeight(); getAspectRatio(sys.ResizeDict);
    sys.BoarderThiccness = External_Debug?1:ceil(max(GetScreenWidth()/(float)sys.SW, GetScreenHeight()/(float)sys.SH));
    sys.DistRect = (sys.keepAspect)?(Rectangle){sys.ResizeDict[2],sys.ResizeDict[3], sys.ResizeDict[0],sys.ResizeDict[1]}:(Rectangle){sys.BoarderThiccness,sys.BoarderThiccness, sys.SW*(((sys.HostWidth>>1<<1)-sys.BoarderThiccness)*128/sys.SW)/128,sys.SH*(((sys.HostHeight>>1<<1)-sys.BoarderThiccness)*128/sys.SH)/128};
    sys.ScreenReady = true;
  }}
 } CPU_stop(); sprintf(MainPrintString,"%s%s\n[EMU Notice] Shutting Down...%s\n",COLOR_BOLD,COLOR_BLUE,COLOR_RESET); FilterAnsi(MainPrintString);
 for(l=0,i=0; i<6; i++) l+=sys.DebugPause[0]>0;
 if (l>0) { sys.Debug = sys.BreakDebug; }

 dir = opendir(CFGPATH); if (!dir) { if (_mkdir(CFGPATH)<0) { sprintf(sys.Error, "Failed to create system's folder\n"); sys.ErrorType=1; printError(); } } closedir(dir);
 if ((fp = fopen(concat(CFGPATH,"settings.cfg"), "w")) == NULL) { sprintf(sys.Error,"Unable to modify the config file!\n"); sys.ErrorType=1; printError(); }
 else {
  cJSON *json2 = cJSON_CreateObject();
  cJSON_AddBoolToObject(json2,"StartOnLoad",sys.StartOnLoad);
  cJSON_AddBoolToObject(json2,"AnsiPrinting",sys.AnsiPrinting);
  cJSON_AddBoolToObject(json2,"BlockDisp",sys.blockDisp);
  cJSON_AddBoolToObject(json2,"StartWithOverlay",StartWithOverlay);
  cJSON_AddBoolToObject(json2,"ShowInput",ShowInput);
  cJSON_AddBoolToObject(json2,"HUDinfo",HUDinfo);
  cJSON_AddBoolToObject(json2,"KeepAspect",sys.keepAspect);
  cJSON_AddBoolToObject(json2,"EnableFullscreen", INITFullscreen);
  cJSON_AddBoolToObject(json2,"BoarderlessWindow",FullscreenType);
  cJSON_AddBoolToObject(json2,"DebugMode",sys.Debug);
  cJSON_AddBoolToObject(json2,"SkipIntro",ForceSkipIntro);
  cJSON_AddNumberToObject(json2, "GUIOpacity", sys.GUIOpacity);
  cJSON_AddBoolToObject(json2,"SkipBIOS",sys.skipBIOS);
  cJSON_AddStringToObject(json2, "BIOSPath", BIOSPath);
  cJSON_AddNumberToObject(json2, "hour_offset", hour_offset);
  cJSON_AddNumberToObject(json2, "min_offset", min_offset);
  cJSON *Player,*PlayerKeys;
  for(j=0;j<2;j++) {
   Player = cJSON_CreateObject();
   cJSON_AddNumberToObject(Player, "device", sys.controllerDevice[j]);
   cJSON_AddNumberToObject(Player, "type", sys.controllerType[j]);
   PlayerKeys = cJSON_CreateArray(); 
   for(i=0;i<32;i++) cJSON_AddItemToArray(PlayerKeys, cJSON_CreateNumber(sys.controllerKey[j][i]));
   cJSON_AddItemToObject(Player, "keys", PlayerKeys);
   cJSON_AddItemToObject(json2,j==0?"Player0":"Player1",Player);
  }
  uint8_t *json_str = cJSON_Print(json2);
  sprintf(MainPrintString,"%s%s%s\n", COLOR_GREEN,json_str,COLOR_RESET); FilterAnsi(MainPrintString);
  fputs(json_str, fp); fclose(fp);
  cJSON_free(json_str); cJSON_Delete(json2);
  cJSON_Delete(json);
 } printf("INITFullscreen: %s\n",(INITFullscreen)?"true":"false"); exit(0);
}