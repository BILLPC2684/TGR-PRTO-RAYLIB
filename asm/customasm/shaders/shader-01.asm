#include "taylor_GPU.asm"
#ruledef TGR_logo_data {
 TGR_logo_data0 => 0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C
 TGR_logo_data1 => 0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC
 TGR_logo_data2 => 0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x8C@0x8C@0x8C@0xAC@0xAC@0xAC@0xCB@0xAE@0x0D
 TGR_logo_data3 => 0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0xAC@0xAC@0xAC@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xAC@0xAC@0xAC@0x8C@0x8C@0x8C@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62
 TGR_logo_data4 => 0xFF@0x62@0x62@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xF1@0xDC@0x69@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xFF@0xD8@0x00@0xFF@0xD8@0x00@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62
 TGR_logo_data5 => 0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0xFF@0x62@0x62@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xFF@0x00@0x00@0xCB@0xAE@0x0D@0xF1@0xDC@0x69@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xCB@0xAE@0x0D@0xCB@0xAE@0x0D@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00
}
#include "kofi_banner.asm"
LINES_G = ProgramAddr+512*7 ; 1 byte
LINES_B = LINES_G+1 ; 1 byte
LINES_E = LINES_B+1 ; 4 bytes; E
TGR_LOGO_START_X = LINES_E+4 ; 2 bytes; X
TGR_LOGO_START_Y = TGR_LOGO_START_X+2 ; 2 bytes; Y
TGR_LOGO_DIRECTION = TGR_LOGO_START_Y+2 ; 1 bytes; E
TGR_LOGO_SPIN = TGR_LOGO_DIRECTION+1 ; 2 bytes; X
NEXT = TGR_LOGO_SPIN+2

#addr ProgramAddr
main:
 GPU_resl 0 ;sets resolution to default (480x360)
 GPU_layer 0 ; setting drawing layer to 0
 
 GPU_load  GPU_O,  240;196
 GPU_bsri  GPU_O,  8,      GPU_U
 GPU_wmemi GPU_U,  TGR_LOGO_START_X ; TGR LOGO START GPU_X
 GPU_wmemi GPU_O,  TGR_LOGO_START_X+1
 
 GPU_load  GPU_O,  180;158
 GPU_bsri  GPU_O,  8, GPU_U
 GPU_wmemi GPU_U,  TGR_LOGO_START_Y ; TGR LOGO START GPU_Y
 GPU_wmemi GPU_O,  TGR_LOGO_START_Y+1
 
 GPU_load  GPU_O,  0
 GPU_wmemi GPU_O,  TGR_LOGO_SPIN
 GPU_wmemi GPU_O,  TGR_LOGO_SPIN+1

 GPU_load  GPU_E, 0x60
 GPU_wmemi GPU_E, LINES_G
 GPU_load  GPU_E, 0x2F
 GPU_wmemi GPU_E, LINES_B
 
 init_loop:
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 GPU_load GPU_X,   0
 GPU_load GPU_Y,   0
 ;
 GPU_rmemi  GPU_U,  CPLength+4   ;grabbing resolution width
 GPU_rmemi  GPU_X2, CPLength+4+1
 GPU_bsli   GPU_U,  8,      GPU_U
 GPU_or     GPU_U,  GPU_X2, GPU_X2
 ;
 GPU_rmemi  GPU_U,  CPLength+6    ;grabbing resolution height
 GPU_rmemi  GPU_Y2, CPLength+6+1
 GPU_bsli   GPU_U,  8,      GPU_U
 GPU_or     GPU_U,  GPU_Y2, GPU_Y2
 ;
 GPU_setout

 GPU_copy 4 ; coping data from layer 0 to layer 4
 GPU_render ; renders layer 4 to screen
 ;GPU_wait 1000000

 GPU_load GPU_R, 0x1F
 GPU_mov  GPU_G, GPU_R
 GPU_mov  GPU_B, GPU_R
 GPU_frect ; clears the drawing layer


 GPU_load GPU_X,     0 ;X[2] = Rotation[1/2]
 GPU_load GPU_Y,     0 ;Y[2] = Rotation[2/2]
 GPU_load GPU_X2,  360 ;X[3] = Resize Width  ;X[1] = Width
 GPU_load GPU_Y2,  180 ;Y[3] = Resize Height ;Y[1] = Height
 GPU_setout
 ;
 GPU_load   GPU_X,  60            ;X[0] = X 
 GPU_rmemi  GPU_U,  CPLength+6    ;grabbing resolution height
 GPU_rmemi  GPU_O,  CPLength+6+1
 GPU_bsli   GPU_U,    8,    GPU_U
 GPU_or     GPU_U,  GPU_O,  GPU_O
 GPU_subi   GPU_O,  180,    GPU_Y ;Y[0] = Y
 GPU_sprite SPRITE_RGBA, kofi_banner
 GPU_mov    GPU_Y2, GPU_O
 
 
 GPU_rmemi GPU_O,  CPLength+4   ;grabbing resolution width
 GPU_rmemi GPU_I,  CPLength+4+1
 GPU_bsli  GPU_O,  8,      GPU_O
 GPU_or    GPU_O,  GPU_I,  GPU_I
   
 GPU_load  GPU_X,  0
 GPU_load  GPU_Y,  0

 GPU_mov   GPU_X2, GPU_I
 GPU_mov   GPU_Y2, GPU_O
 GPU_divi  GPU_O,  2,      GPU_O
 GPU_setout  ; setted X3/4 and Y3/4 for tranfering the layer data over to layer 4 (for rendering) and for filling the screen
 ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

 GPU_rmemi GPU_O,  CPLength+4   ;grabbing resolution width
 GPU_rmemi GPU_X2, CPLength+4+1
 GPU_bsli  GPU_O,  8,      GPU_O
 GPU_or    GPU_O,  GPU_X2, GPU_X2

 GPU_divi  GPU_X2,  2,      GPU_O
 GPU_mov   GPU_X2,  GPU_I

 GPU_rmemi  GPU_U,  CPLength+6    ;grabbing resolution height
 GPU_rmemi  GPU_Y2, CPLength+6+1
 GPU_bsli   GPU_U,  8,      GPU_U
 GPU_or     GPU_U,  GPU_Y2, GPU_Y2
 
 GPU_rmemi GPU_U,  LINES_E ; 4 bytes; E
 GPU_bsli  GPU_U,  24, GPU_U
 GPU_or    GPU_E,  GPU_U,  GPU_E
 GPU_rmemi GPU_U,  LINES_E+1
 GPU_bsli  GPU_U,  16, GPU_U
 GPU_or    GPU_E,  GPU_U,  GPU_E
 GPU_rmemi GPU_U,  LINES_E+2
 GPU_bsli  GPU_U,  8,  GPU_U
 GPU_or    GPU_E,  GPU_U,  GPU_E
 GPU_rmemi GPU_U,  LINES_E+3
 GPU_or    GPU_E,  GPU_U,  GPU_E

 ;GPU_load GPU_X, 0
;;;;;;;;;;;;;;;;;;;;
 
 GPU_load  GPU_A, 0xFF
 GPU_load  GPU_X, 0x00
 line_loop:
  ;GPU_break 0
  GPU_mod   GPU_X, GPU_O, GPU_R
  GPU_cmplt GPU_X, GPU_O, 2
   GPU_load GPU_X2, 0
   GPU_load GPU_IP, .ifcontinue0
  GPU_mov GPU_X2, GPU_I
  .ifcontinue0:
  GPU_rmemi GPU_G, LINES_G
  GPU_rmemi GPU_B, LINES_B
  GPU_line  ; drawing the line
  
  GPU_cmplti GPU_X, 0x1DF, 6
   GPU_muli  GPU_E, 27, GPU_E ;jumbles E for next color value
   GPU_wmemi GPU_E, LINES_G ; stores E for in a safe spot from the active code
   GPU_muli  GPU_E, 27, GPU_E ;jumbles E for next color value
   GPU_wmemi GPU_E, LINES_B ; stores E for in a safe spot from the active code
   GPU_addi  GPU_X,  1, GPU_X
   GPU_load  GPU_IP, line_loop
  
 GPU_muli GPU_E, 27, GPU_R
 GPU_led GPU_R, GPU_G, GPU_B
 GPU_mov GPU_X2, GPU_I

 ;GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
 ;GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
 ;GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
 ;GPU_wmem GPU_E, LINES_B
 ;GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
 ;GPU_wmem GPU_E, LINES_G

 ;GPU_load GPU_IP, init_loop

 GPU_bsri  GPU_E,  24, GPU_U
 GPU_wmemi GPU_U,  LINES_E ; 4 bytes; E
 GPU_bsri  GPU_U,  8, GPU_U
 GPU_wmemi GPU_U,  LINES_E+1
 GPU_bsri  GPU_U,  8, GPU_U
 GPU_wmemi GPU_U,  LINES_E+2
 GPU_wmemi GPU_E,  LINES_E+3

;;;;;;;;;;;;;;;;;

 GPU_load  GPU_R,  0x7F
 GPU_mov   GPU_G,  GPU_R
 GPU_mov   GPU_B,  GPU_R
 GPU_mov   GPU_A,  GPU_R
 GPU_rmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; X
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
 GPU_or    GPU_X,  GPU_U,  GPU_X
 
 GPU_rmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; Y
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_rmemi GPU_Y,  TGR_LOGO_START_Y+1
 GPU_or    GPU_Y,  GPU_U,  GPU_Y
 
 GPU_load  GPU_X2, 44 ;X[1] = Radius
 GPU_crcl
 GPU_load  GPU_A,  0xFF
 
 ;
 
 GPU_rmemi  GPU_O, TGR_LOGO_SPIN ;X[2] = Rotation[1/2]
 GPU_rmemi  GPU_X, TGR_LOGO_SPIN+1
 GPU_bsli   GPU_O, 8,     GPU_O
 GPU_or     GPU_O, GPU_X, GPU_X
 ;
 GPU_addi   GPU_X,      8, GPU_X
 GPU_modi   GPU_X, 0x1680, GPU_X
 GPU_divi   GPU_X,      8, GPU_E
 GPU_modi   GPU_E,      2, GPU_E
 ;GPU_disp   GPU_X
 ;
 GPU_bsri  GPU_X,   8,     GPU_O
 GPU_wmemi GPU_O,  TGR_LOGO_SPIN ; TGR LOGO START GPU_X
 GPU_wmemi GPU_X,  TGR_LOGO_SPIN+1
 ;GPU_bsli GPU_X,   4, GPU_X ;(15.0___* rotation)
 GPU_load GPU_Y,    0  ;Y[2] = Rotation[2/2]
                            ;(^^.^000* rotation)
 GPU_load GPU_X2,  88;X[3] = Resize Width
 GPU_load GPU_Y2,  44;Y[3] = Resize Height
 GPU_setout

 GPU_rmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; X
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
 GPU_or    GPU_X,  GPU_U,  GPU_X
 
 GPU_rmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; Y
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_rmemi GPU_Y,  TGR_LOGO_START_Y+1
 GPU_or    GPU_Y,  GPU_U,  GPU_Y
 
 GPU_load GPU_X2,  44;X[1] = Width
 GPU_load GPU_Y2,  22;Y[1] = Height
 GPU_sprite SPRITE_RGB_CENTER, TGR_Logo

 ;GPU_break 0
 GPU_cmpeqi GPU_E, 0, 1
  GPU_load GPU_IP, init_loop; ending the loop prematurely
 
 GPU_rmemi GPU_U,  TGR_LOGO_START_X ; 2 bytes; X
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_rmemi GPU_X,  TGR_LOGO_START_X+1
 GPU_or    GPU_X,  GPU_U,  GPU_X
 GPU_rmemi GPU_U,  TGR_LOGO_START_Y ; 2 bytes; Y
 GPU_bsli  GPU_U,  8, GPU_U
 GPU_wmemi GPU_Y,  TGR_LOGO_START_Y+1
 GPU_or    GPU_Y,  GPU_U,  GPU_Y
 
 GPU_rmemi  GPU_U,  CPLength+4   ;grabbing resolution width
 GPU_rmemi  GPU_X2, CPLength+4+1
 GPU_bsli   GPU_U,  8,      GPU_U
 GPU_or     GPU_U,  GPU_X2, GPU_X2
 ;
 GPU_rmemi  GPU_U,  CPLength+6    ;grabbing resolution height
 GPU_rmemi  GPU_Y2, CPLength+6+1
 GPU_bsli   GPU_U,  8,      GPU_U
 GPU_or     GPU_U,  GPU_Y2, GPU_Y2

 ;GPU_break 0
 GPU_rmemi GPU_E,  TGR_LOGO_DIRECTION ; 1 bytes; E
 
 GPU_cmpeqi GPU_E, 0, 3 ;Down-Right
  GPU_addi GPU_Y, 1, GPU_Y
  GPU_addi GPU_X, 1, GPU_X
  GPU_load GPU_IP, colision_detect
 GPU_cmpeqi GPU_E, 1, 3 ;Up-Right
  GPU_subi GPU_Y, 1, GPU_Y
  GPU_addi GPU_X, 1, GPU_X
  GPU_load GPU_IP, colision_detect
 GPU_cmpeqi GPU_E, 2, 3 ;Down-Left
  GPU_addi GPU_Y, 1, GPU_Y
  GPU_subi GPU_X, 1, GPU_X
  GPU_load GPU_IP, colision_detect
 GPU_cmpeqi GPU_E, 3, 3 ;Up-Left
  GPU_subi GPU_Y, 1, GPU_Y
  GPU_subi GPU_X, 1, GPU_X
  GPU_load GPU_IP, colision_detect  
 
 colision_detect:
  GPU_disp  GPU_E
  GPU_cmplti GPU_X, 44, 6 ;Left collision
   GPU_cmpeqi GPU_E, 2, 2 ;Down-Left
    GPU_load GPU_E, 0
    GPU_load GPU_IP, .colision_detect_exit
   
   GPU_cmpeqi GPU_E, 3, 2 ;Up-Left
    GPU_load GPU_E, 1
    GPU_load GPU_IP, .colision_detect_exit
   ;GPU_disp GPU_E, GPU_X
  
  
  GPU_cmplti GPU_Y, 44, 6 ;Top collision
   GPU_cmpeqi GPU_E, 3, 2 ;Up-Left
    GPU_load GPU_E, 2
    GPU_load GPU_IP, .colision_detect_exit
   
   GPU_cmpeqi GPU_E, 1, 2 ;Up-Right
    GPU_load GPU_E, 0
    GPU_load GPU_IP, .colision_detect_exit
   ;GPU_disp GPU_E, GPU_Y
  
  GPU_subi GPU_X2, 44, GPU_X2
  GPU_cmpgt GPU_X, GPU_X2, 6 ;Right collision
   GPU_cmpeqi GPU_E, 1, 2 ;Up-Right
    GPU_load GPU_E, 3
    GPU_load GPU_IP, .colision_detect_exit
   
   GPU_cmpeqi GPU_E, 0, 2 ;Down-Right
    GPU_load GPU_E, 2
    GPU_load GPU_IP, .colision_detect_exit
   ;GPU_disp GPU_E, GPU_X, GPU_X2
  
  
  GPU_subi GPU_Y2, 44, GPU_Y2
  GPU_cmpgt GPU_Y, GPU_Y2, 6 ;Bottom collision
   GPU_cmpeqi GPU_E, 2, 2 ;Down-Left
    GPU_load GPU_E, 3
    GPU_load GPU_IP, .colision_detect_exit
   
   GPU_cmpeqi GPU_E, 0, 3 ;Down-Right
    GPU_load GPU_E, 1
    GPU_load GPU_IP, .colision_detect_exit
   ;GPU_disp GPU_E, GPU_Y, GPU_Y2
  
  .colision_detect_exit:
  GPU_wmemi GPU_E,  TGR_LOGO_DIRECTION ; 1 bytes; E

  GPU_bsri  GPU_X,  8,      GPU_U
  GPU_wmemi GPU_U,  TGR_LOGO_START_X ; TGR LOGO START GPU_X
  GPU_wmemi GPU_X,  TGR_LOGO_START_X+1
  
  GPU_bsri  GPU_Y,  8, GPU_U
  GPU_wmemi GPU_U,  TGR_LOGO_START_Y ; TGR LOGO START GPU_Y
  GPU_wmemi GPU_Y,  TGR_LOGO_START_Y+1
  ;
  ;
  GPU_load GPU_IP, init_loop

#addr NEXT
TGR_Logo:
 TGR_logo_data0
 TGR_logo_data1
 TGR_logo_data2
 TGR_logo_data3
 TGR_logo_data4
 TGR_logo_data5
kofi_banner:
 kofi_banner_data0
 kofi_banner_data1
 kofi_banner_data2
 kofi_banner_data3
 kofi_banner_data4
 kofi_banner_data5
 kofi_banner_data6
 kofi_banner_data7
 kofi_banner_data8
 kofi_banner_data9
 kofi_banner_data10
 kofi_banner_data11
 kofi_banner_data12
 kofi_banner_data13
 kofi_banner_data14
 kofi_banner_data15
 kofi_banner_data16
 kofi_banner_data17
 kofi_banner_data18
 kofi_banner_data19
 kofi_banner_data20
 kofi_banner_data21
 kofi_banner_data22
 kofi_banner_data23
 kofi_banner_data24
 kofi_banner_data25
 kofi_banner_data26
 kofi_banner_data27
 kofi_banner_data28
 kofi_banner_data29
 kofi_banner_data30
 kofi_banner_data31
 kofi_banner_data32
 kofi_banner_data33
 kofi_banner_data34
 kofi_banner_data35
 kofi_banner_data36
 kofi_banner_data37
 kofi_banner_data38
 kofi_banner_data39
 kofi_banner_data40
 kofi_banner_data41
 kofi_banner_data42
 kofi_banner_data43
 kofi_banner_data44
 kofi_banner_data45
 kofi_banner_data46
 kofi_banner_data47
 kofi_banner_data48
 kofi_banner_data49
 kofi_banner_data50
 kofi_banner_data51
 kofi_banner_data52
 kofi_banner_data53
 kofi_banner_data54
 kofi_banner_data55
 kofi_banner_data56
 kofi_banner_data57
 kofi_banner_data58
 kofi_banner_data59
 kofi_banner_data60
 kofi_banner_data61
 kofi_banner_data62
 kofi_banner_data63
 kofi_banner_data64
 kofi_banner_data65
 kofi_banner_data66
 kofi_banner_data67
 kofi_banner_data68
 kofi_banner_data69
 kofi_banner_data70
 kofi_banner_data71
 kofi_banner_data72
 kofi_banner_data73
 kofi_banner_data74
 kofi_banner_data75
 kofi_banner_data76
 kofi_banner_data77
 kofi_banner_data78
 kofi_banner_data79
 kofi_banner_data80
 kofi_banner_data81
 kofi_banner_data82
 kofi_banner_data83
 kofi_banner_data84
 kofi_banner_data85
 kofi_banner_data86
 kofi_banner_data87
 kofi_banner_data88
 kofi_banner_data89
 kofi_banner_data90
 kofi_banner_data91
 kofi_banner_data92
 kofi_banner_data93
 kofi_banner_data94
 kofi_banner_data95
 kofi_banner_data96
 kofi_banner_data97
 kofi_banner_data98
 kofi_banner_data99
 kofi_banner_data100
 kofi_banner_data101
 kofi_banner_data102
 kofi_banner_data103
 kofi_banner_data104
 kofi_banner_data105
 kofi_banner_data106
 kofi_banner_data107
 kofi_banner_data108
 kofi_banner_data109
 kofi_banner_data110
 kofi_banner_data111
 kofi_banner_data112
 kofi_banner_data113
 kofi_banner_data114
 kofi_banner_data115
 kofi_banner_data116
 kofi_banner_data117
 kofi_banner_data118
 kofi_banner_data119
 kofi_banner_data120
 kofi_banner_data121
 kofi_banner_data122
 kofi_banner_data123
 kofi_banner_data124
 kofi_banner_data125
 kofi_banner_data126
 kofi_banner_data127
 kofi_banner_data128
 kofi_banner_data129
 kofi_banner_data130
 kofi_banner_data131
 kofi_banner_data132
 kofi_banner_data133
 kofi_banner_data134
 kofi_banner_data135
 kofi_banner_data136
 kofi_banner_data137
 kofi_banner_data138
 kofi_banner_data139
 kofi_banner_data140
 kofi_banner_data141
 kofi_banner_data142
 kofi_banner_data143
 kofi_banner_data144
 kofi_banner_data145
 kofi_banner_data146
 kofi_banner_data147
 kofi_banner_data148
 kofi_banner_data149
 kofi_banner_data150
 kofi_banner_data151
 kofi_banner_data152
 kofi_banner_data153
 kofi_banner_data154
 kofi_banner_data155
 kofi_banner_data156
 kofi_banner_data157
 kofi_banner_data158
 kofi_banner_data159
 kofi_banner_data160
 kofi_banner_data161
 kofi_banner_data162
 kofi_banner_data163
 kofi_banner_data164
 kofi_banner_data165
 kofi_banner_data166
 kofi_banner_data167
 kofi_banner_data168
 kofi_banner_data169
 kofi_banner_data170
 kofi_banner_data171
 kofi_banner_data172
 kofi_banner_data173
 kofi_banner_data174
 kofi_banner_data175
 kofi_banner_data176
 kofi_banner_data177
 kofi_banner_data178
 kofi_banner_data179
 kofi_banner_data180
 kofi_banner_data181
 kofi_banner_data182
 kofi_banner_data183
 kofi_banner_data184
 kofi_banner_data185
 kofi_banner_data186
 kofi_banner_data187
 kofi_banner_data188
 kofi_banner_data189
 kofi_banner_data190
 kofi_banner_data191
 kofi_banner_data192
 kofi_banner_data193
 kofi_banner_data194
 kofi_banner_data195
 kofi_banner_data196
 kofi_banner_data197
 kofi_banner_data198
 kofi_banner_data199
 kofi_banner_data200
 kofi_banner_data201
 kofi_banner_data202
 kofi_banner_data203
 kofi_banner_data204
 kofi_banner_data205
 kofi_banner_data206
 kofi_banner_data207
 kofi_banner_data208
 kofi_banner_data209
 kofi_banner_data210
 kofi_banner_data211
 kofi_banner_data212
 kofi_banner_data213
 kofi_banner_data214
 kofi_banner_data215
 kofi_banner_data216
 kofi_banner_data217
 kofi_banner_data218
 kofi_banner_data219
 kofi_banner_data220
 kofi_banner_data221
 kofi_banner_data222
 kofi_banner_data223
 kofi_banner_data224
 kofi_banner_data225
 kofi_banner_data226
 kofi_banner_data227
 kofi_banner_data228
 kofi_banner_data229
 kofi_banner_data230
 kofi_banner_data231
 kofi_banner_data232
 kofi_banner_data233
 kofi_banner_data234
 kofi_banner_data235
 kofi_banner_data236
 kofi_banner_data237
 kofi_banner_data238
 kofi_banner_data239
 kofi_banner_data240
 kofi_banner_data241
 kofi_banner_data242
 kofi_banner_data243
 kofi_banner_data244
 kofi_banner_data245
 kofi_banner_data246
 kofi_banner_data247
 kofi_banner_data248
 kofi_banner_data249
 kofi_banner_data250
 kofi_banner_data251
 kofi_banner_data252
 kofi_banner_data253
 kofi_banner_data254
 kofi_banner_data255
 kofi_banner_data256
 kofi_banner_data257
 kofi_banner_data258
 kofi_banner_data259
 kofi_banner_data260
 kofi_banner_data261
 kofi_banner_data262
 kofi_banner_data263
 kofi_banner_data264
 kofi_banner_data265
 kofi_banner_data266
 kofi_banner_data267
 kofi_banner_data268
 kofi_banner_data269
 kofi_banner_data270
 kofi_banner_data271
 kofi_banner_data272
 kofi_banner_data273
 kofi_banner_data274
 kofi_banner_data275
 kofi_banner_data276
 kofi_banner_data277
 kofi_banner_data278
 kofi_banner_data279
 kofi_banner_data280
 kofi_banner_data281
 kofi_banner_data282
 kofi_banner_data283
 kofi_banner_data284
 kofi_banner_data285
 kofi_banner_data286
 kofi_banner_data287
 kofi_banner_data288
 kofi_banner_data289
 kofi_banner_data290
 kofi_banner_data291
 kofi_banner_data292
 kofi_banner_data293
 kofi_banner_data294
 kofi_banner_data295
 kofi_banner_data296
 kofi_banner_data297
 kofi_banner_data298
 kofi_banner_data299
 kofi_banner_data300
 kofi_banner_data301
 kofi_banner_data302
 kofi_banner_data303
 kofi_banner_data304
 kofi_banner_data305
 kofi_banner_data306
 kofi_banner_data307
 kofi_banner_data308
 kofi_banner_data309
 kofi_banner_data310
 kofi_banner_data311
 kofi_banner_data312
 kofi_banner_data313
 kofi_banner_data314
 kofi_banner_data315
 kofi_banner_data316
 kofi_banner_data317
 kofi_banner_data318
 kofi_banner_data319
 kofi_banner_data320
 kofi_banner_data321
 kofi_banner_data322
 kofi_banner_data323
 kofi_banner_data324
 kofi_banner_data325
 kofi_banner_data326
 kofi_banner_data327
 kofi_banner_data328
 kofi_banner_data329
 kofi_banner_data330
 kofi_banner_data331
 kofi_banner_data332
 kofi_banner_data333
 kofi_banner_data334
 kofi_banner_data335
 kofi_banner_data336
 kofi_banner_data337
 kofi_banner_data338
 kofi_banner_data339
 kofi_banner_data340
 kofi_banner_data341
 kofi_banner_data342
 kofi_banner_data343
 kofi_banner_data344
 kofi_banner_data345
 kofi_banner_data346
 kofi_banner_data347
 kofi_banner_data348
 kofi_banner_data349
 kofi_banner_data350
 kofi_banner_data351
 kofi_banner_data352
 kofi_banner_data353
 kofi_banner_data354
 kofi_banner_data355
 kofi_banner_data356
 kofi_banner_data357
 kofi_banner_data358
 kofi_banner_data359
 kofi_banner_data360
 kofi_banner_data361
 kofi_banner_data362
 kofi_banner_data363
 kofi_banner_data364
 kofi_banner_data365
 kofi_banner_data366
 kofi_banner_data367
 kofi_banner_data368
 kofi_banner_data369
 kofi_banner_data370
 kofi_banner_data371
 kofi_banner_data372
 kofi_banner_data373
 kofi_banner_data374
 kofi_banner_data375
 kofi_banner_data376
 kofi_banner_data377
 kofi_banner_data378
 kofi_banner_data379
 kofi_banner_data380
 kofi_banner_data381
 kofi_banner_data382
 kofi_banner_data383
 kofi_banner_data384
 kofi_banner_data385
 kofi_banner_data386
 kofi_banner_data387
 kofi_banner_data388
 kofi_banner_data389
 kofi_banner_data390
 kofi_banner_data391
 kofi_banner_data392
 kofi_banner_data393
 kofi_banner_data394
 kofi_banner_data395
 kofi_banner_data396
 kofi_banner_data397
 kofi_banner_data398
 kofi_banner_data399
 kofi_banner_data400
 kofi_banner_data401
 kofi_banner_data402
 kofi_banner_data403
 kofi_banner_data404
 kofi_banner_data405
 kofi_banner_data406
 kofi_banner_data407
 kofi_banner_data408
 kofi_banner_data409
 kofi_banner_data410
 kofi_banner_data411
 kofi_banner_data412
 kofi_banner_data413
 kofi_banner_data414
 kofi_banner_data415
 kofi_banner_data416
 kofi_banner_data417
 kofi_banner_data418
 kofi_banner_data419
 kofi_banner_data420
 kofi_banner_data421
 kofi_banner_data422
 kofi_banner_data423
 kofi_banner_data424
 kofi_banner_data425
 kofi_banner_data426
 kofi_banner_data427
 kofi_banner_data428
 kofi_banner_data429
 kofi_banner_data430
 kofi_banner_data431
 kofi_banner_data432
 kofi_banner_data433
 kofi_banner_data434
 kofi_banner_data435
 kofi_banner_data436
 kofi_banner_data437
 kofi_banner_data438
 kofi_banner_data439
 kofi_banner_data440
 kofi_banner_data441
 kofi_banner_data442
 kofi_banner_data443
 kofi_banner_data444
 kofi_banner_data445
 kofi_banner_data446
 kofi_banner_data447
 kofi_banner_data448
 kofi_banner_data449
 kofi_banner_data450
 kofi_banner_data451
 kofi_banner_data452
 kofi_banner_data453
 kofi_banner_data454
 kofi_banner_data455
 kofi_banner_data456
 kofi_banner_data457
 kofi_banner_data458
 kofi_banner_data459
 kofi_banner_data460
 kofi_banner_data461
 kofi_banner_data462
 kofi_banner_data463
 kofi_banner_data464
 kofi_banner_data465
 kofi_banner_data466
 kofi_banner_data467
 kofi_banner_data468
 kofi_banner_data469
 kofi_banner_data470
 kofi_banner_data471
 kofi_banner_data472
 kofi_banner_data473
 kofi_banner_data474
 kofi_banner_data475
 kofi_banner_data476
 kofi_banner_data477
 kofi_banner_data478
 kofi_banner_data479
 kofi_banner_data480
 kofi_banner_data481
 kofi_banner_data482
 kofi_banner_data483
 kofi_banner_data484
 kofi_banner_data485
 kofi_banner_data486
 kofi_banner_data487
 kofi_banner_data488
 kofi_banner_data489
 kofi_banner_data490
 kofi_banner_data491
 kofi_banner_data492
 kofi_banner_data493
 kofi_banner_data494
 kofi_banner_data495
 kofi_banner_data496
 kofi_banner_data497
 kofi_banner_data498
 kofi_banner_data499
 kofi_banner_data500
 kofi_banner_data501
 kofi_banner_data502
 kofi_banner_data503
 kofi_banner_data504
 kofi_banner_data505