#include "taylor_GPU.asm"

#addr ProgramAddr
main:
 GPU_resl 0 ;sets resolution to default (480x360)
 
 GPU_rmemi GPU_E,  (32*15*3)+4   ;grabbing resolution width
 GPU_rmemi GPU_I,  (32*15*3)+4+1
 GPU_bsli GPU_E,  8,      GPU_E
 GPU_or   GPU_E,  GPU_I,  GPU_I
 GPU_mov  GPU_X2, GPU_I
 GPU_divi GPU_I,  2,      GPU_O
 
 GPU_rmemi GPU_E,  (32*15*3)+4+2 ;grabbing resolution height
 GPU_rmemi GPU_Y2, (32*15*3)+4+3
 GPU_bsli GPU_E,  8,      GPU_E
 GPU_or   GPU_E,  GPU_Y2, GPU_Y2
 
 GPU_layer 0 ; setting drawing layer to 0
 GPU_setout  ; setted X3/4 and Y3/4 for tranfering the layer data over to layer 4 (for rendering) and for filling the screen
 
 GPU_load GPU_A, 0xFF
 GPU_load GPU_X, 0x00
 GPU_frect ; filling the screen
 GPU_load GPU_E, 0x60
 GPU_wmemi GPU_E, ProgramAddr+512
 GPU_load GPU_E, 0x2F
 GPU_wmemi GPU_E, ProgramAddr+513
 .loop:
  GPU_cmplt GPU_X, GPU_O, 2
   GPU_load GPU_X2, 0
   GPU_load GPU_IP, .ifcontinue0
  GPU_mov GPU_X2, GPU_I
  .ifcontinue0:
  GPU_mod GPU_X, GPU_O, GPU_R
  GPU_rmemi GPU_G, ProgramAddr+512
  GPU_rmemi GPU_B, ProgramAddr+513
  GPU_line ; drawing the line
  
  GPU_cmplti GPU_X, 0xFF*2, 6
   GPU_muli GPU_E, 27, GPU_E       ;jumbles E for next color value
   GPU_wmemi GPU_E, ProgramAddr+512 ; stores E for in a safe spot from the active code
   GPU_muli GPU_E, 27, GPU_E       ;jumbles E for next color value
   GPU_wmemi GPU_E, ProgramAddr+513 ; stores E for in a safe spot from the active code
   GPU_addi GPU_X,  1, GPU_X
   GPU_load GPU_IP, .loop
  
  GPU_led GPU_R, GPU_G, GPU_B
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

  GPU_wait 1
  GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
  GPU_wmemi GPU_E, ProgramAddr+512
  GPU_muli GPU_E, 27, GPU_E ;jumbles E for next color value
  GPU_wmemi GPU_E, ProgramAddr+513
  GPU_load GPU_X, 0
  GPU_load GPU_IP, .loop
