#include "taylor_GPU.asm"
#ruledef TGR_logo_data {
 TGR_logo_data0 => 0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C
 TGR_logo_data1 => 0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC
 TGR_logo_data2 => 0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D
 TGR_logo_data3 => 0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62
 TGR_logo_data4 => 0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62
 TGR_logo_data5 => 0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00
}
LINES_G = ProgramAddr+512*7 ; 1 byte
LINES_B = LINES_G+1 ; 1 byte
LINES_GPU_X = LINES_B+1 ; 2 bytes; X
LINES_GPU_E = LINES_GPU_X+2 ; 4 bytes; E
TGR_LOGO_START_X = LINES_GPU_E+4 ; 2 bytes; X
TGR_LOGO_START_Y = TGR_LOGO_START_X+2 ; 2 bytes; Y
TGR_LOGO_DIRECTION = TGR_LOGO_START_Y+2 ; 1 bytes; E
NEXT = TGR_LOGO_DIRECTION+1

#addr ProgramAddr
main:
 GPU_resl 0 ;sets resolution to default (480x360)

 GPU_rmemi GPU_E,  CPLength+4   ;grabbing resolution width
 GPU_rmemi GPU_I,  CPLength+4+1
 GPU_bsli  GPU_E,  8,      GPU_E
 GPU_or    GPU_E,  GPU_I,  GPU_I
 GPU_mov   GPU_X2, GPU_I
 
 GPU_rmemi GPU_E,  CPLength+6   ;grabbing resolution height
 GPU_rmemi GPU_Y2, CPLength+6+1
 GPU_bsli  GPU_E,  8,      GPU_E
 GPU_or    GPU_E,  GPU_Y2, GPU_Y2
 GPU_divi  GPU_Y2, 2,      GPU_O
 GPU_subi  GPU_O,  44, GPU_O
 GPU_bsri  GPU_O,  8, GPU_U
 GPU_wmemi GPU_U,  TGR_LOGO_START_Y ; TGR LOGO START GPU_Y
 GPU_wmemi GPU_O,  TGR_LOGO_START_Y+1

 GPU_divi  GPU_I,  2,      GPU_O
 GPU_subi  GPU_O,  22, GPU_O
 GPU_bsri  GPU_O,  8, GPU_U
 GPU_wmemi GPU_U,  TGR_LOGO_START_X ; TGR LOGO START GPU_X
 GPU_wmemi GPU_O,  TGR_LOGO_START_X+1
 
 GPU_layer 0 ; setting drawing layer to 0
 GPU_setout  ; setted X3/4 and Y3/4 for tranfering the layer data over to layer 4 (for rendering) and for filling the screen
 
 GPU_load  GPU_X, 0x1F
 GPU_mov   GPU_R, GPU_X
 GPU_mov   GPU_G, GPU_X
 GPU_mov   GPU_B, GPU_X
 GPU_load  GPU_A, 0xFF
 GPU_load  GPU_X, 0x00
 GPU_frect ; filling the screen
 
 GPU_load  GPU_E, 0x60
 GPU_wmemi GPU_E, LINES_G
 GPU_load  GPU_E, 0x2F
 GPU_wmemi GPU_E, LINES_B
 .init_loop:
 GPU_load  GPU_A, 0xFF
 GPU_load  GPU_X, 0x00
 .loop:
  GPU_mod   GPU_X, GPU_O, GPU_R
  GPU_cmplt GPU_X, GPU_O, 2
   GPU_load GPU_X2, 0
   GPU_load GPU_IP, .ifcontinue0
  GPU_mov GPU_X2, GPU_I
  .ifcontinue0:
  GPU_rmemi GPU_G, LINES_G
  GPU_rmemi GPU_B, LINES_B
  GPU_line  ; drawing the line
  
  GPU_cmplti GPU_X, 0xFF*2, 6
   GPU_muli  GPU_E, 27, GPU_E ;jumbles E for next color value
   GPU_wmemi GPU_E, LINES_G ; stores E for in a safe spot from the active code
   GPU_muli  GPU_E, 27, GPU_E ;jumbles E for next color value
   GPU_wmemi GPU_E, LINES_B ; stores E for in a safe spot from the active code
   GPU_addi  GPU_X,  1, GPU_X
   GPU_load  GPU_IP, .loop
  
  GPU_led GPU_R, GPU_G, GPU_B
  GPU_mov GPU_X2, GPU_I
;;;;;;;;;;;;;;;;;
 ;WRITE LINE DATA
  GPU_bsri  GPU_X,  8, GPU_U
  GPU_wmemi GPU_U,  LINES_GPU_X ; 2 bytes; X
  GPU_wmemi GPU_X,  LINES_GPU_X+1

  GPU_bsri  GPU_E,  24, GPU_U
  GPU_wmemi GPU_U,  LINES_GPU_E ; 4 bytes; E
  GPU_bsri  GPU_U,  8, GPU_U
  GPU_wmemi GPU_U,  LINES_GPU_E+1
  GPU_bsri  GPU_U,  8, GPU_U
  GPU_wmemi GPU_U,  LINES_GPU_E+2
  GPU_wmemi GPU_E,  LINES_GPU_E+3

;;;;;;;;;;;;;;;;;
 ;READ LOGO DATA
  GPU_rmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; X
  GPU_bsli  GPU_U,  8, GPU_U
  GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
  GPU_or    GPU_X,  GPU_U,  GPU_X
  
  GPU_rmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; Y
  GPU_bsli  GPU_U,  8, GPU_U
  GPU_rmemi GPU_Y,  TGR_LOGO_START_Y+1
  GPU_or    GPU_Y,  GPU_U,  GPU_Y
  
;;;;;;;;;;;;;;;;;;  
;  TGR_LOGO_X    ; I
  GPU_load GPU_I, 0
;  TGR_LOGO_Y    ; O
  GPU_load GPU_O, 0
;  TGR_LOGO_ADDR ; U
  GPU_load GPU_U, TGR_Logo
  GPU_load GPU_X2, 2
  GPU_load GPU_Y2, 2
;Render TGR Logo
  .logo_loopY:
   GPU_cmpeqi GPU_I, 22, 1
    GPU_load GPU_IP, .logo_loop_exit
   .logo_loopX:
   GPU_rmem GPU_R, GPU_U
   GPU_addi GPU_U, 1, GPU_U
   GPU_rmem GPU_G, GPU_U
   GPU_addi GPU_U, 1, GPU_U
   GPU_rmem GPU_B, GPU_U
   GPU_addi GPU_U, 1, GPU_U
   GPU_rect
   GPU_addi GPU_X, 2, GPU_X
   GPU_addi GPU_O, 1, GPU_O
   GPU_cmpeqi GPU_O, 44, 8
    GPU_rmemi GPU_O,  TGR_LOGO_START_X ; 2 bytes; X
    GPU_bsli  GPU_O,  8, GPU_O
    GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
    GPU_or    GPU_X,  GPU_O,  GPU_X
    GPU_load  GPU_O, 0
    GPU_addi GPU_I, 1, GPU_I
    GPU_addi GPU_Y, 2, GPU_Y
    GPU_load GPU_IP, .logo_loopY
   GPU_load GPU_IP, .logo_loopX
;;;;;;;;;;;;;;;;;
  .logo_loop_exit_old:
  GPU_rmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; X
  GPU_bsli  GPU_U,  8, GPU_U
  GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
  GPU_or    GPU_X,  GPU_U,  GPU_X
  GPU_rmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; Y
  GPU_bsli  GPU_U,  8, GPU_U
  GPU_wmemi GPU_Y,  TGR_LOGO_START_Y+1
  GPU_or    GPU_Y,  GPU_U,  GPU_Y
  
  GPU_rmemi GPU_E,  TGR_LOGO_DIRECTION ; 1 bytes; E
  
  GPU_cmpeqi GPU_E, 0, 3 ;Down-Right
   GPU_addi GPU_Y, 1, GPU_Y
   GPU_addi GPU_X, 1, GPU_X
   GPU_load GPU_IP, .colision_detect
  GPU_cmpeqi GPU_E, 1, 3 ;Up-Right
   GPU_subi GPU_Y, 1, GPU_Y
   GPU_addi GPU_X, 1, GPU_X
   GPU_load GPU_IP, .colision_detect
  GPU_cmpeqi GPU_E, 2, 3 ;Down-Left
   GPU_addi GPU_Y, 1, GPU_Y
   GPU_subi GPU_X, 1, GPU_X
   GPU_load GPU_IP, .colision_detect
  GPU_cmpeqi GPU_E, 3, 3 ;Up-Left
   GPU_subi GPU_Y, 1, GPU_Y
   GPU_subi GPU_X, 1, GPU_X
   GPU_load GPU_IP, .colision_detect  
  
  .colision_detect:
  GPU_disp  GPU_E
  GPU_cmplti GPU_X, 1, 7 ;Left collision
   GPU_cmpeqi GPU_E, 2, 2 ;Down-Left
    GPU_load GPU_E, 0
    GPU_load GPU_IP, .colision_detect_exit

   GPU_cmpeqi GPU_E, 3, 2 ;Up-Left
    GPU_load GPU_E, 1
    GPU_load GPU_IP, .colision_detect_exit
   GPU_disp GPU_E, GPU_X


  GPU_cmplti GPU_Y, 1, 8 ;Top collision
   GPU_cmpeqi GPU_E, 3, 2 ;Up-Left
    GPU_load GPU_E, 2
    GPU_load GPU_IP, .colision_detect_exit

   GPU_cmpeqi GPU_E, 1, 2 ;Up-Right
    GPU_load GPU_E, 0
    GPU_load GPU_IP, .colision_detect_exit
   GPU_disp GPU_E, GPU_Y


  GPU_addi GPU_X, 88, GPU_X
  GPU_cmpgti GPU_X, GPU_X2, 7 ;Right collision
   GPU_cmpeqi GPU_E, 1, 2 ;Up-Right
    GPU_load GPU_E, 3
    GPU_load GPU_IP, .colision_detect_exit

   GPU_cmpeqi GPU_E, 0, 2 ;Down-Right
    GPU_load GPU_E, 2
    GPU_load GPU_IP, .colision_detect_exit
   GPU_disp GPU_E, GPU_X, GPU_X2


  GPU_addi GPU_Y, 44, GPU_Y
  GPU_cmpgti GPU_Y, GPU_Y2, 7 ;Bottom collision
   GPU_cmpeqi GPU_E, 2, 2 ;Down-Left
    GPU_load GPU_E, 3
    GPU_load GPU_IP, .colision_detect_exit

   GPU_cmpeqi GPU_E, 0, 3 ;Down-Right
    GPU_load GPU_E, 1
    GPU_load GPU_IP, .colision_detect_exit
   GPU_disp GPU_E, GPU_Y, GPU_Y2
  
  .colision_detect_exit:
  GPU_disp  GPU_E
  GPU_wmemi GPU_E,  TGR_LOGO_DIRECTION ; 1 bytes; E
  
  GPU_bsri  GPU_X,  8, GPU_U
  GPU_wmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; 
  GPU_wmemi GPU_X,  TGR_LOGO_START_X+1

  GPU_bsri  GPU_X,  8, GPU_U
  GPU_wmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; 
  GPU_wmemi GPU_X,  TGR_LOGO_START_Y+1
  .logo_loop_exit:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 ;RESTORE LINE DATA
  GPU_rmemi GPU_E,  CPLength+4   ;grabbing resolution width
  GPU_rmemi GPU_I,  CPLength+4+1
  GPU_bsli  GPU_E,  8,      GPU_E
  GPU_or    GPU_E,  GPU_I,  GPU_I
  GPU_mov   GPU_X2, GPU_I
  GPU_divi  GPU_I,  2,      GPU_O
  
  GPU_rmemi GPU_E,  CPLength+6   ;grabbing resolution height
  GPU_rmemi GPU_Y2, CPLength+6+1
  GPU_bsli  GPU_E,  8,      GPU_E
  GPU_or    GPU_E,  GPU_Y2, GPU_Y2
  
  GPU_rmemi GPU_U,  LINES_GPU_X ; 2 bytes; X
  GPU_bsli  GPU_U,  8, GPU_U
  GPU_wmemi GPU_X,  LINES_GPU_X+1
  GPU_or    GPU_X,  GPU_U,  GPU_X
  
  GPU_load GPU_Y, 0

  GPU_rmemi GPU_U,  LINES_GPU_E ; 4 bytes; E
  GPU_bsli  GPU_U,  24, GPU_U
  GPU_or    GPU_E,  GPU_U,  GPU_E
  GPU_rmemi GPU_U,  LINES_GPU_E+1
  GPU_bsli  GPU_U,  16, GPU_U
  GPU_or    GPU_E,  GPU_U,  GPU_E
  GPU_rmemi GPU_U,  LINES_GPU_E+2
  GPU_bsli  GPU_U,  8,  GPU_U
  GPU_or    GPU_E,  GPU_U,  GPU_E
  GPU_rmemi GPU_U,  LINES_GPU_E+3
  GPU_or    GPU_E,  GPU_U,  GPU_E
  
  ;
  GPU_load GPU_X, 0x1F
  GPU_mov  GPU_R, GPU_X
  GPU_mov  GPU_G, GPU_X
  GPU_mov  GPU_B, GPU_X

  GPU_load GPU_X, 0x00
  GPU_mov  GPU_Y, GPU_X
  GPU_mov  GPU_X2, GPU_I

  GPU_copy 4 ; coping data from layer 0 to layer 4
  GPU_render ; renders layer 4 to screen
  GPU_frect ; clears the drawing layer

  GPU_wait 1000000
  GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
  GPU_wmem GPU_E, LINES_G
  GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
  GPU_wmem GPU_E, LINES_B
  GPU_load GPU_X, 0
  GPU_load GPU_IP, .init_loop

#addr NEXT
TGR_Logo:
 TGR_logo_data0
 TGR_logo_data1
 TGR_logo_data2
 TGR_logo_data3
 TGR_logo_data4
 TGR_logo_data5