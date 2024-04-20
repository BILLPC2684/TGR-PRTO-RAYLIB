#include "taylor_GPU.asm"
#include "cavestory_tileset.asm"
#include "cavestory_banner.asm" ; credit of "First Cave" to karzopla

#ruledef map_data {
 map0 => 0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xB1@0x00@0xD0@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xB1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xB1@0x00@0xB1@0x00@0xB1@0x00@0xB1@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xB1@0x00@0xD3@0x00@0x00@0x00@0xB4@0x00@0xB5@0x00@0xB1@0x00@0xB1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xB1@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xB1@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xB1@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xB1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE0@0x00@0xB2@0x00@0xB3@0x00@0x00@0x00@0x00@0x00@0xD6@0x00@0xD7@0x00@0xD8@0x00@0x00@0x00@0xD4@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD1@0x00@0xD0@0x00@0xD3@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xE6@0x00@0xE7@0x00@0xE8@0x00@0x00@0x00@0xE4@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xF0@0x00@0xF1@0x00@0xF0@0x00@0xD4@0x00@0xE1@0x00@0xE0@0x00@0xB2@0x00@0xB3@0x00@0x00@0x00@0xC1@0x00@0xC4@0x00@0xB1@0x00@0x00@0x00@0xB1@0x00@0xB1@0x00@0xB1@0x00@0x00@0x00@0xB1@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xF0@0x00@0xF1@0x00@0x00@0x00@0xC4@0x00@0xC5@0x00@0xD0@0x00@0xD1@0x00@0xB1@0x00@0x00@0x00@0x00
 map1 => 0x00@0x00@0x00@0x00@0x00@0x00@0x00@0xB1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xB7@0x00@0xC6@0x00@0xC7@0x00@0xC6@0x00@0xC7@0x00@0xB8@0x00@0xB9@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xB1@0x00@0xB6@0x00@0xB7@0x00@0xC6@0x00@0xC7@0x00@0xB8@0x00@0xE1@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xB1@0x00@0xB1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xD1@0x00@0xB1@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xD1@0x00@0xD0@0x00@0xB1@0x00@0xD0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0@0x00@0xE1@0x00@0xE0
}

cavestory_tileset = ProgramAddr+(512*12)-1 ; . . . . . . . . 12XXXXX bytes
cavestory_banner = cavestory_tileset+cavestory_tileset_len ; 345600 bytes
CameraX = cavestory_banner+cavestory_banner_len ; . . . . . . . . 2 bytes
CameraY = CameraX+2 ; . . . . . . . . . . . . . . . . . . . . . . 2 bytes
RenderMap = CameraY+2 ; . . . . . . . . . . . . . . . . . . . . 768 bytes
Var5 = RenderMap+768 ;. . . . . . . . . . . . . . . . . . . . . . 2 bytes
Var6 = Var5+2 ; . . . . . . . . . . . . . . . . . . . . . . . . . 2 bytes
NEXT = Var6+2 ; . . . . . . . . . . . . . . . . . . . . . . . . . ? bytes

Xoffset = 64
Yoffset = 44

#addr ProgramAddr
main:
 GPU_resl 0 ;sets resolution to default (480x360)
 GPU_layer 0 ; setting drawing layer to 0
 
 GPU_load  GPU_O,  0
 GPU_bsri  GPU_O,  8, GPU_U
 GPU_wmemi GPU_U,  CameraX
 GPU_wmemi GPU_O,  CameraX+1
 GPU_wmemi GPU_U,  CameraY
 GPU_wmemi GPU_O,  CameraY+1
 
 ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
 .main_loop:
 GPU_calli Set256ColorPalette0
 
 GPU_calli loop0_resetX
 
 GPU_load  GPU_Y, Yoffset
 GPU_rmemi GPU_U, CameraY
 GPU_rmemi GPU_O, CameraY+1
 GPU_bsli  GPU_U,     8, GPU_U
 GPU_or    GPU_U, GPU_O, GPU_O
 GPU_mod   GPU_O,    16, GPU_O
 GPU_sub   GPU_Y, GPU_O, GPU_Y
 
 ;GPU_rmemi GPU_U,  CPLength+4   ;grabbing resolution width
 ;GPU_rmemi GPU_X2, CPLength+4+1
 ;GPU_bsli  GPU_U,  8,      GPU_U
 ;GPU_or    GPU_U,  GPU_X2, GPU_X2
 
 ;GPU_rmemi GPU_U,  CPLength+6    ;grabbing resolution height
 ;GPU_rmemi GPU_Y2, CPLength+6+1
 ;GPU_bsli  GPU_U,  8,      GPU_U
 ;GPU_or    GPU_U,  GPU_Y2, GPU_Y2
 
 GPU_load  GPU_E,  RenderMap
 .loop0: ; while true
  GPU_cmpgti GPU_Y, 16*16+Yoffset, 1
   GPU_load GPU_IP, .loop0_end
  .loop1: ; for x in range(16)
   GPU_rmem GPU_U, GPU_E
   GPU_addi GPU_E, 1,     GPU_E
   GPU_rmem GPU_I, GPU_E
   GPU_bsli GPU_U, 8,     GPU_U
   GPU_or   GPU_U, GPU_I, GPU_I
   GPU_addi GPU_E, 1,     GPU_E
   ;
   GPU_load GPU_sp, cavestory_tileset
   GPU_muli GPU_I, 16*16, GPU_I
   GPU_add  GPU_sp, GPU_I, GPU_sp
   ;GPU_disp GPU_sp
   GPU_calli DrawTile16x
   ;
   ;GPU_modi   GPU_E, 24, GPU_I
   ;GPU_cmpeqi GPU_I, 0, 1
   GPU_cmpgti GPU_X,16*20+Xoffset, 3
    GPU_addi  GPU_Y, 16, GPU_Y
    GPU_calli loop0_resetX
    GPU_load GPU_IP, .loop0
   GPU_addi GPU_X, 16, GPU_X
   GPU_load GPU_IP, .loop1
  ;
 .loop0_end:
 GPU_calli Set256ColorPalette1
 ;
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
 GPU_sprite SPRITE_CP8, cavestory_banner ; uses SpritePointer instead of IMM
 ;
 GPU_copy 4 ; coping data from layer 0 to layer 4
 GPU_render ; renders layer 4 to screen
 ;
 GPU_load GPU_R, 0x1F
 GPU_mov  GPU_G, GPU_R
 GPU_mov  GPU_B, GPU_R
 GPU_frect ; clears the drawing layer
 
 GPU_load GPU_IP, .main_loop

loop0_resetX:
 GPU_load  GPU_X, Xoffset
 GPU_rmemi GPU_U, CameraX
 GPU_rmemi GPU_O, CameraX+1
 GPU_bsli  GPU_U,     8, GPU_U
 GPU_or    GPU_U, GPU_O, GPU_O
 GPU_mod   GPU_O,    16, GPU_O
 GPU_sub   GPU_X, GPU_O, GPU_X

DrawTile16x: ; requests SpritePointer, X and Y
 ;GPU_disp GPU_sp, GPU_X, GPU_Y
 GPU_push GPU_X2
 GPU_push GPU_Y2
 GPU_push GPU_X
 GPU_push GPU_Y
 GPU_load GPU_X,    0 ;X[2] = Rotation[1/2]
 GPU_load GPU_Y,    0 ;Y[2] = Rotation[2/2]
 GPU_load GPU_X2,  16 ;X[3] = Resize Width
 GPU_load GPU_Y2,  16 ;Y[3] = Resize Height
 GPU_setout
 ;
 GPU_pop GPU_Y        ;X[0] = X
 GPU_pop GPU_X        ;Y[0] = Y
 GPU_load GPU_X2,  16 ;X[1] = Width
 GPU_load GPU_Y2,  16 ;Y[1] = Height
 GPU_sprite SPRITE_CP8, NULL ; uses SpritePointer instead of IMM
 GPU_pop GPU_Y2
 GPU_pop GPU_X2
 GPU_ret

Set256ColorPalette0:
 GPU_rgba 0x000000FF
 GPU_palt PALETTE_WRITE, 0
 GPU_rgba 0xC7A7AFFF
 GPU_palt PALETTE_WRITE, 1
 GPU_rgba 0x9F8797FF
 GPU_palt PALETTE_WRITE, 2
 GPU_rgba 0x77677FFF
 GPU_palt PALETTE_WRITE, 3
 GPU_rgba 0x272F47FF
 GPU_palt PALETTE_WRITE, 4
 GPU_rgba 0x4F4F67FF
 GPU_palt PALETTE_WRITE, 5
 GPU_rgba 0x00172FFF
 GPU_palt PALETTE_WRITE, 6
 GPU_rgba 0xCFD7CFFF
 GPU_palt PALETTE_WRITE, 7
 GPU_rgba 0x5F779FFF
 GPU_palt PALETTE_WRITE, 8
 GPU_rgba 0x272F2FFF
 GPU_palt PALETTE_WRITE, 9
 GPU_rgba 0x00000FFF
 GPU_palt PALETTE_WRITE, 10
 GPU_rgba 0x0F376FFF
 GPU_palt PALETTE_WRITE, 11
 GPU_rgba 0x570000FF
 GPU_palt PALETTE_WRITE, 12
 GPU_rgba 0xFF0000FF
 GPU_palt PALETTE_WRITE, 13
 GPU_rgba 0x270F07FF
 GPU_palt PALETTE_WRITE, 14
 GPU_rgba 0x2F1F17FF
 GPU_palt PALETTE_WRITE, 15
 GPU_rgba 0x373727FF
 GPU_palt PALETTE_WRITE, 16
 GPU_rgba 0xB7AF87FF
 GPU_palt PALETTE_WRITE, 17
 GPU_rgba 0x8F8F6FFF
 GPU_palt PALETTE_WRITE, 18
 GPU_rgba 0x475747FF
 GPU_palt PALETTE_WRITE, 19
 GPU_rgba 0x001717FF
 GPU_palt PALETTE_WRITE, 20
 GPU_rgba 0x6F6F57FF
 GPU_palt PALETTE_WRITE, 21
 GPU_rgba 0x1F372FFF
 GPU_palt PALETTE_WRITE, 22
 GPU_rgba 0xFFF7DFFF
 GPU_palt PALETTE_WRITE, 23
 GPU_rgba 0x677F97FF
 GPU_palt PALETTE_WRITE, 24
 GPU_rgba 0x37475FFF
 GPU_palt PALETTE_WRITE, 25
 GPU_rgba 0x0F1727FF
 GPU_palt PALETTE_WRITE, 26
 GPU_rgba 0x272F3FFF
 GPU_palt PALETTE_WRITE, 27
 GPU_rgba 0x4F5F77FF
 GPU_palt PALETTE_WRITE, 28
 GPU_rgba 0x2F5FA7FF
 GPU_palt PALETTE_WRITE, 29
 GPU_rgba 0x001F97FF
 GPU_palt PALETTE_WRITE, 30
 GPU_rgba 0xBFCFDFFF
 GPU_palt PALETTE_WRITE, 31
 GPU_rgba 0x1F7747FF
 GPU_palt PALETTE_WRITE, 32
 GPU_rgba 0x000017FF
 GPU_palt PALETTE_WRITE, 33
 GPU_rgba 0x074F37FF
 GPU_palt PALETTE_WRITE, 34
 GPU_rgba 0xD7C77FFF
 GPU_palt PALETTE_WRITE, 35
 GPU_rgba 0xBFAF6FFF
 GPU_palt PALETTE_WRITE, 36
 GPU_rgba 0x877F57FF
 GPU_palt PALETTE_WRITE, 37
 GPU_rgba 0x6F6747FF
 GPU_palt PALETTE_WRITE, 38
 GPU_rgba 0x372F27FF
 GPU_palt PALETTE_WRITE, 39
 GPU_rgba 0x171717FF
 GPU_palt PALETTE_WRITE, 40
 GPU_rgba 0x9F9767FF
 GPU_palt PALETTE_WRITE, 41
 GPU_rgba 0x4F4737FF
 GPU_palt PALETTE_WRITE, 42
 GPU_rgba 0xB7BFBFFF
 GPU_palt PALETTE_WRITE, 43
 GPU_rgba 0x778F97FF
 GPU_palt PALETTE_WRITE, 44
 GPU_rgba 0x3F576FFF
 GPU_palt PALETTE_WRITE, 45
 GPU_rgba 0x001F3FFF
 GPU_palt PALETTE_WRITE, 46
 GPU_rgba 0x7F0000FF
 GPU_palt PALETTE_WRITE, 47
 GPU_rgba 0x8F9787FF
 GPU_palt PALETTE_WRITE, 48
 GPU_rgba 0xBFC7BFFF
 GPU_palt PALETTE_WRITE, 49
 GPU_rgba 0xDFE7DFFF
 GPU_palt PALETTE_WRITE, 50
 GPU_rgba 0xA7AFA7FF
 GPU_palt PALETTE_WRITE, 51
 GPU_rgba 0xAFA77FFF
 GPU_palt PALETTE_WRITE, 52
 GPU_rgba 0x4F4F37FF
 GPU_palt PALETTE_WRITE, 53
 GPU_rgba 0x776F57FF
 GPU_palt PALETTE_WRITE, 54
 GPU_rgba 0xDFD7B7FF
 GPU_palt PALETTE_WRITE, 55
 GPU_rgba 0xF7F7DFFF
 GPU_palt PALETTE_WRITE, 56
 GPU_rgba 0x6F7767FF
 GPU_palt PALETTE_WRITE, 57
 GPU_rgba 0x272727FF
 GPU_palt PALETTE_WRITE, 58
 GPU_rgba 0xFF3707FF
 GPU_palt PALETTE_WRITE, 59
 GPU_rgba 0x97377FFF
 GPU_palt PALETTE_WRITE, 60
 GPU_rgba 0xD7C787FF
 GPU_palt PALETTE_WRITE, 61
 GPU_rgba 0xAF9767FF
 GPU_palt PALETTE_WRITE, 62
 GPU_rgba 0x7F6F3FFF
 GPU_palt PALETTE_WRITE, 63
 GPU_rgba 0x271F0FFF
 GPU_palt PALETTE_WRITE, 64
 GPU_rgba 0x573F1FFF
 GPU_palt PALETTE_WRITE, 65
 GPU_rgba 0x77877FFF
 GPU_palt PALETTE_WRITE, 66
 GPU_rgba 0xB7C7BFFF
 GPU_palt PALETTE_WRITE, 67
 GPU_rgba 0xD7E7DFFF
 GPU_palt PALETTE_WRITE, 68
 GPU_rgba 0x97A79FFF
 GPU_palt PALETTE_WRITE, 69
 GPU_rgba 0x576F5FFF
 GPU_palt PALETTE_WRITE, 70
 GPU_rgba 0x2F4F3FFF
 GPU_palt PALETTE_WRITE, 71
 GPU_rgba 0xDFDFDFFF
 GPU_palt PALETTE_WRITE, 72
 GPU_rgba 0xA73700FF
 GPU_palt PALETTE_WRITE, 73
 GPU_rgba 0x676F67FF
 GPU_palt PALETTE_WRITE, 74
 GPU_rgba 0x87877FFF
 GPU_palt PALETTE_WRITE, 75
 GPU_rgba 0x4F4F57FF
 GPU_palt PALETTE_WRITE, 76
 GPU_rgba 0x2F373FFF
 GPU_palt PALETTE_WRITE, 77
 GPU_rgba 0x17172FFF
 GPU_palt PALETTE_WRITE, 78
 GPU_rgba 0xD7DFBFFF
 GPU_palt PALETTE_WRITE, 79
 GPU_rgba 0xB7BFA7FF
 GPU_palt PALETTE_WRITE, 80
 GPU_rgba 0x9FA797FF
 GPU_palt PALETTE_WRITE, 81
 GPU_rgba 0xEFF7CFFF
 GPU_palt PALETTE_WRITE, 82
 GPU_rgba 0x000F00FF
 GPU_palt PALETTE_WRITE, 83
 GPU_rgba 0xEFF7FFFF
 GPU_palt PALETTE_WRITE, 84
 GPU_rgba 0x5F6F2FFF
 GPU_palt PALETTE_WRITE, 85
 GPU_rgba 0x97C777FF
 GPU_palt PALETTE_WRITE, 86
 GPU_rgba 0x97C7AFFF
 GPU_palt PALETTE_WRITE, 87
 GPU_rgba 0xBFFFC7FF
 GPU_palt PALETTE_WRITE, 88
 GPU_rgba 0x678F97FF
 GPU_palt PALETTE_WRITE, 89
 GPU_rgba 0x4F6F87FF
 GPU_palt PALETTE_WRITE, 90
 GPU_rgba 0xA7D7AFFF
 GPU_palt PALETTE_WRITE, 91
 GPU_rgba 0x8FA77FFF
 GPU_palt PALETTE_WRITE, 92
 GPU_rgba 0x677F5FFF
 GPU_palt PALETTE_WRITE, 93
 GPU_rgba 0x474F47FF
 GPU_palt PALETTE_WRITE, 94
 GPU_rgba 0x1F2727FF
 GPU_palt PALETTE_WRITE, 95
 GPU_rgba 0xBF270FFF
 GPU_palt PALETTE_WRITE, 96
 GPU_rgba 0x470700FF
 GPU_palt PALETTE_WRITE, 97
 GPU_rgba 0x971F0FFF
 GPU_palt PALETTE_WRITE, 98
 GPU_rgba 0x001727FF
 GPU_palt PALETTE_WRITE, 99
 GPU_rgba 0x002700FF
 GPU_palt PALETTE_WRITE, 100
 GPU_rgba 0x006F00FF
 GPU_palt PALETTE_WRITE, 101
 GPU_rgba 0xFFBF4FFF
 GPU_palt PALETTE_WRITE, 102
 GPU_rgba 0xE7973FFF
 GPU_palt PALETTE_WRITE, 103
 GPU_rgba 0xCF772FFF
 GPU_palt PALETTE_WRITE, 104
 GPU_rgba 0x7F371FFF
 GPU_palt PALETTE_WRITE, 105
 GPU_rgba 0x471F17FF
 GPU_palt PALETTE_WRITE, 106
 GPU_rgba 0xBF4F27FF
 GPU_palt PALETTE_WRITE, 107
 GPU_rgba 0xA78767FF
 GPU_palt PALETTE_WRITE, 108
 GPU_rgba 0xCFA777FF
 GPU_palt PALETTE_WRITE, 109
 GPU_rgba 0x4F373FFF
 GPU_palt PALETTE_WRITE, 110
 GPU_rgba 0x77674FFF
 GPU_palt PALETTE_WRITE, 111
 GPU_rgba 0xFFC78FFF
 GPU_palt PALETTE_WRITE, 112
 GPU_rgba 0xFF1700FF
 GPU_palt PALETTE_WRITE, 113
 GPU_rgba 0x7F1F00FF
 GPU_palt PALETTE_WRITE, 114
 GPU_rgba 0xFFFFFFFF
 GPU_palt PALETTE_WRITE, 115
 GPU_rgba 0x274F6FFF
 GPU_palt PALETTE_WRITE, 116
 GPU_rgba 0x1F3F5FFF
 GPU_palt PALETTE_WRITE, 117
 GPU_rgba 0x172F4FFF
 GPU_palt PALETTE_WRITE, 118
 GPU_rgba 0x0F1F37FF
 GPU_palt PALETTE_WRITE, 119
 GPU_rgba 0x070F27FF
 GPU_palt PALETTE_WRITE, 120
 GPU_rgba 0x8F0000FF
 GPU_palt PALETTE_WRITE, 121
 GPU_rgba 0xB7AFBFFF
 GPU_palt PALETTE_WRITE, 122
 GPU_rgba 0x3F5767FF
 GPU_palt PALETTE_WRITE, 123
 GPU_rgba 0x77878FFF
 GPU_palt PALETTE_WRITE, 124
 GPU_rgba 0x002737FF
 GPU_palt PALETTE_WRITE, 125
 GPU_rgba 0x475F77FF
 GPU_palt PALETTE_WRITE, 126
 GPU_rgba 0x0F1F47FF
 GPU_palt PALETTE_WRITE, 127
 GPU_rgba 0x6797F7FF
 GPU_palt PALETTE_WRITE, 128
 GPU_rgba 0x677F87FF
 GPU_palt PALETTE_WRITE, 129
 GPU_rgba 0x2F3F5FFF
 GPU_palt PALETTE_WRITE, 130
 GPU_rgba 0x4F4F4FFF
 GPU_palt PALETTE_WRITE, 131
 GPU_rgba 0x6F6F77FF
 GPU_palt PALETTE_WRITE, 132
 GPU_rgba 0x97979FFF
 GPU_palt PALETTE_WRITE, 133
 GPU_rgba 0x7F7747FF
 GPU_palt PALETTE_WRITE, 134
 GPU_rgba 0x473F27FF
 GPU_palt PALETTE_WRITE, 135
 GPU_rgba 0x2F2717FF
 GPU_palt PALETTE_WRITE, 136
 GPU_rgba 0x675F37FF
 GPU_palt PALETTE_WRITE, 137
 GPU_rgba 0x4F3F2FFF
 GPU_palt PALETTE_WRITE, 138
 GPU_rgba 0x67572FFF
 GPU_palt PALETTE_WRITE, 139
 GPU_rgba 0x876F37FF
 GPU_palt PALETTE_WRITE, 140
 GPU_rgba 0xA78737FF
 GPU_palt PALETTE_WRITE, 141
 GPU_rgba 0x170F2FFF
 GPU_palt PALETTE_WRITE, 142
 GPU_rgba 0x372F37FF
 GPU_palt PALETTE_WRITE, 143
 GPU_rgba 0x3F97BFFF
 GPU_palt PALETTE_WRITE, 144
 GPU_rgba 0x0F4777FF
 GPU_palt PALETTE_WRITE, 145
 GPU_rgba 0xE7F7FFFF
 GPU_palt PALETTE_WRITE, 146
 GPU_rgba 0x770000FF
 GPU_palt PALETTE_WRITE, 147
 GPU_rgba 0x473F47FF
 GPU_palt PALETTE_WRITE, 148
 GPU_rgba 0x876F57FF
 GPU_palt PALETTE_WRITE, 149
 GPU_rgba 0xC7C77FFF
 GPU_palt PALETTE_WRITE, 150
 GPU_rgba 0x0F0F37FF
 GPU_palt PALETTE_WRITE, 151
 GPU_rgba 0xA79F67FF
 GPU_palt PALETTE_WRITE, 152
 GPU_rgba 0x4FA74FFF
 GPU_palt PALETTE_WRITE, 153
 GPU_rgba 0xEFEF97FF
 GPU_palt PALETTE_WRITE, 154
 GPU_rgba 0x001707FF
 GPU_palt PALETTE_WRITE, 155
 GPU_rgba 0x4F576FFF
 GPU_palt PALETTE_WRITE, 156
 GPU_rgba 0x373F4FFF
 GPU_palt PALETTE_WRITE, 157
 GPU_rgba 0x5F6F8FFF
 GPU_palt PALETTE_WRITE, 158
 GPU_rgba 0x6F87A7FF
 GPU_palt PALETTE_WRITE, 159
 GPU_rgba 0xE7E7DFFF
 GPU_palt PALETTE_WRITE, 160
 GPU_rgba 0x2F3747FF
 GPU_palt PALETTE_WRITE, 161
 GPU_rgba 0x4F575FFF
 GPU_palt PALETTE_WRITE, 162
 GPU_rgba 0x8F9F87FF
 GPU_palt PALETTE_WRITE, 163
 GPU_rgba 0x272737FF
 GPU_palt PALETTE_WRITE, 164
 GPU_rgba 0x6F776FFF
 GPU_palt PALETTE_WRITE, 165
 GPU_rgba 0x0F1717FF
 GPU_palt PALETTE_WRITE, 166
 GPU_rgba 0x773F67FF
 GPU_palt PALETTE_WRITE, 167
 GPU_rgba 0xAFBF9FFF
 GPU_palt PALETTE_WRITE, 168
 GPU_rgba 0x0F1F07FF
 GPU_palt PALETTE_WRITE, 169
 GPU_rgba 0x6F6F47FF
 GPU_palt PALETTE_WRITE, 170
 GPU_rgba 0x071700FF
 GPU_palt PALETTE_WRITE, 171
 GPU_rgba 0x3F473FFF
 GPU_palt PALETTE_WRITE, 172
 GPU_rgba 0x7F7F57FF
 GPU_palt PALETTE_WRITE, 173
 GPU_rgba 0x4F5FEFFF
 GPU_palt PALETTE_WRITE, 174
 GPU_rgba 0x172F0FFF
 GPU_palt PALETTE_WRITE, 175
 GPU_rgba 0x070007FF
 GPU_palt PALETTE_WRITE, 176
 GPU_rgba 0x9FBFBFFF
 GPU_palt PALETTE_WRITE, 177
 GPU_rgba 0xC7CFF7FF
 GPU_palt PALETTE_WRITE, 178
 GPU_rgba 0x8F97EFFF
 GPU_palt PALETTE_WRITE, 179
 GPU_rgba 0x4F471FFF
 GPU_palt PALETTE_WRITE, 180
 GPU_rgba 0x2F2F0FFF
 GPU_palt PALETTE_WRITE, 181
 GPU_rgba 0x1F1707FF
 GPU_palt PALETTE_WRITE, 182
 GPU_rgba 0x67877FFF
 GPU_palt PALETTE_WRITE, 183
 GPU_rgba 0x2F5F5FFF
 GPU_palt PALETTE_WRITE, 184
 GPU_rgba 0x0F1F1FFF
 GPU_palt PALETTE_WRITE, 185
 GPU_rgba 0x1F3F3FFF
 GPU_palt PALETTE_WRITE, 186
 GPU_rgba 0x3F8787FF
 GPU_palt PALETTE_WRITE, 187
 GPU_rgba 0xDFDFC7FF
 GPU_palt PALETTE_WRITE, 188
 GPU_rgba 0x979767FF
 GPU_palt PALETTE_WRITE, 189
 GPU_rgba 0x7F6F5FFF
 GPU_palt PALETTE_WRITE, 190
 GPU_rgba 0xEF1F57FF
 GPU_palt PALETTE_WRITE, 191
 GPU_rgba 0x0F2F4FFF
 GPU_palt PALETTE_WRITE, 192
 GPU_rgba 0x071737FF
 GPU_palt PALETTE_WRITE, 193
 GPU_rgba 0x000717FF
 GPU_palt PALETTE_WRITE, 194
 GPU_rgba 0x2F271FFF
 GPU_palt PALETTE_WRITE, 195
 GPU_rgba 0x574F3FFF
 GPU_palt PALETTE_WRITE, 196
 GPU_rgba 0x0F0000FF
 GPU_palt PALETTE_WRITE, 197
 GPU_rgba 0xDFDFA7FF
 GPU_palt PALETTE_WRITE, 198
 GPU_rgba 0xA7A787FF
 GPU_palt PALETTE_WRITE, 199
 GPU_rgba 0x000F27FF
 GPU_palt PALETTE_WRITE, 200
 GPU_rgba 0x374747FF
 GPU_palt PALETTE_WRITE, 201
 GPU_rgba 0xEFE7DFFF
 GPU_palt PALETTE_WRITE, 202
 GPU_rgba 0x7FA79FFF
 GPU_palt PALETTE_WRITE, 203
 GPU_rgba 0x4F6F67FF
 GPU_palt PALETTE_WRITE, 204
 GPU_rgba 0x374F47FF
 GPU_palt PALETTE_WRITE, 205
 GPU_rgba 0x00001FFF
 GPU_palt PALETTE_WRITE, 206
 GPU_rgba 0x072717FF
 GPU_palt PALETTE_WRITE, 207
 GPU_rgba 0x0F4F1FFF
 GPU_palt PALETTE_WRITE, 208
 GPU_rgba 0x578F27FF
 GPU_palt PALETTE_WRITE, 209
 GPU_rgba 0x276F37FF
 GPU_palt PALETTE_WRITE, 210
 GPU_rgba 0x1F3727FF
 GPU_palt PALETTE_WRITE, 211
 GPU_rgba 0x071707FF
 GPU_palt PALETTE_WRITE, 212
 GPU_rgba 0xD7DFDFFF
 GPU_palt PALETTE_WRITE, 213
 GPU_rgba 0xAFB7BFFF
 GPU_palt PALETTE_WRITE, 214
 GPU_rgba 0x87979FFF
 GPU_palt PALETTE_WRITE, 215
 GPU_rgba 0x2F475FFF
 GPU_palt PALETTE_WRITE, 216
 GPU_rgba 0x071F3FFF
 GPU_palt PALETTE_WRITE, 217
 GPU_rgba 0x5F6F7FFF
 GPU_palt PALETTE_WRITE, 218
 GPU_rgba 0xC7C787FF
 GPU_palt PALETTE_WRITE, 219
 GPU_rgba 0x373F3FFF
 GPU_palt PALETTE_WRITE, 220
 GPU_rgba 0x6F6F4FFF
 GPU_palt PALETTE_WRITE, 221
 GPU_rgba 0x2F7F47FF
 GPU_palt PALETTE_WRITE, 222
 GPU_rgba 0xEFEFA7FF
 GPU_palt PALETTE_WRITE, 223
 GPU_ret
Set256ColorPalette1:
 GPU_rgba 0x00000000
 GPU_palt PALETTE_WRITE, 0
 GPU_rgba 0x000F27FF
 GPU_palt PALETTE_WRITE, 1
 GPU_rgba 0x00274FFF
 GPU_palt PALETTE_WRITE, 2
 GPU_rgba 0xFF2F4FFF
 GPU_palt PALETTE_WRITE, 3
 GPU_rgba 0x000000FF
 GPU_palt PALETTE_WRITE, 4
 GPU_rgba 0x00071FFF
 GPU_palt PALETTE_WRITE, 5
 GPU_rgba 0x000F2FFF
 GPU_palt PALETTE_WRITE, 6
 GPU_rgba 0x071F4FFF
 GPU_palt PALETTE_WRITE, 7
 GPU_rgba 0x070000FF
 GPU_palt PALETTE_WRITE, 8
 GPU_rgba 0x7F2F57FF
 GPU_palt PALETTE_WRITE, 9
 GPU_rgba 0x3F070FFF
 GPU_palt PALETTE_WRITE, 10
 GPU_rgba 0x00070FFF
 GPU_palt PALETTE_WRITE, 11
 GPU_rgba 0xE72F4FFF
 GPU_palt PALETTE_WRITE, 12
 GPU_rgba 0x07274FFF
 GPU_palt PALETTE_WRITE, 13
 GPU_rgba 0x001F3FFF
 GPU_palt PALETTE_WRITE, 14
 GPU_rgba 0x071F37FF
 GPU_palt PALETTE_WRITE, 15
 GPU_rgba 0x173F67FF
 GPU_palt PALETTE_WRITE, 16
 GPU_rgba 0x00273FFF
 GPU_palt PALETTE_WRITE, 17
 GPU_rgba 0x00000FFF
 GPU_palt PALETTE_WRITE, 18
 GPU_rgba 0x000007FF
 GPU_palt PALETTE_WRITE, 19
 GPU_rgba 0x274F8FFF
 GPU_palt PALETTE_WRITE, 20
 GPU_rgba 0x001737FF
 GPU_palt PALETTE_WRITE, 21
 GPU_rgba 0x7FB7E7FF
 GPU_palt PALETTE_WRITE, 22
 GPU_rgba 0x003F67FF
 GPU_palt PALETTE_WRITE, 23
 GPU_rgba 0x00375FFF
 GPU_palt PALETTE_WRITE, 24
 GPU_rgba 0x00476FFF
 GPU_palt PALETTE_WRITE, 25
 GPU_rgba 0x175F9FFF
 GPU_palt PALETTE_WRITE, 26
 GPU_rgba 0x3F77B7FF
 GPU_palt PALETTE_WRITE, 27
 GPU_rgba 0x27070FFF
 GPU_palt PALETTE_WRITE, 28
 GPU_rgba 0xA72F4FFF
 GPU_palt PALETTE_WRITE, 29
 GPU_rgba 0x000717FF
 GPU_palt PALETTE_WRITE, 30
 GPU_rgba 0x2F274FFF
 GPU_palt PALETTE_WRITE, 31
 GPU_rgba 0xF72F4FFF
 GPU_palt PALETTE_WRITE, 32
 GPU_rgba 0x001F4FFF
 GPU_palt PALETTE_WRITE, 33
 GPU_rgba 0x00173FFF
 GPU_palt PALETTE_WRITE, 34
 GPU_rgba 0x0F0000FF
 GPU_palt PALETTE_WRITE, 35
 GPU_rgba 0x27274FFF
 GPU_palt PALETTE_WRITE, 36
 GPU_rgba 0xC72F4FFF
 GPU_palt PALETTE_WRITE, 37
 GPU_rgba 0x8F172FFF
 GPU_palt PALETTE_WRITE, 38
 GPU_rgba 0x0F2F57FF
 GPU_palt PALETTE_WRITE, 39
 GPU_rgba 0x006FD7FF
 GPU_palt PALETTE_WRITE, 40
 GPU_rgba 0x002747FF
 GPU_palt PALETTE_WRITE, 41
 GPU_rgba 0x4F87C7FF
 GPU_palt PALETTE_WRITE, 42
 GPU_rgba 0x003757FF
 GPU_palt PALETTE_WRITE, 43
 GPU_rgba 0x67274FFF
 GPU_palt PALETTE_WRITE, 44
 GPU_rgba 0x000F1FFF
 GPU_palt PALETTE_WRITE, 45
 GPU_rgba 0x3F274FFF
 GPU_palt PALETTE_WRITE, 46
 GPU_rgba 0x87274FFF
 GPU_palt PALETTE_WRITE, 47
 GPU_rgba 0xCF1F3FFF
 GPU_palt PALETTE_WRITE, 48
 GPU_rgba 0x000F37FF
 GPU_palt PALETTE_WRITE, 49
 GPU_rgba 0x1F4777FF
 GPU_palt PALETTE_WRITE, 50
 GPU_rgba 0x001F37FF
 GPU_palt PALETTE_WRITE, 51
 GPU_rgba 0x0067C7FF
 GPU_palt PALETTE_WRITE, 52
 GPU_rgba 0x2F5F8FFF
 GPU_palt PALETTE_WRITE, 53
 GPU_rgba 0x1F476FFF
 GPU_palt PALETTE_WRITE, 54
 GPU_rgba 0xB72F4FFF
 GPU_palt PALETTE_WRITE, 55
 GPU_rgba 0x57274FFF
 GPU_palt PALETTE_WRITE, 56
 GPU_rgba 0x4F274FFF
 GPU_palt PALETTE_WRITE, 57
 GPU_rgba 0x17274FFF
 GPU_palt PALETTE_WRITE, 58
 GPU_rgba 0x1F4F8FFF
 GPU_palt PALETTE_WRITE, 59
 GPU_rgba 0x075FAFFF
 GPU_palt PALETTE_WRITE, 60
 GPU_rgba 0x578FCFFF
 GPU_palt PALETTE_WRITE, 61
 GPU_rgba 0xC7273FFF
 GPU_palt PALETTE_WRITE, 62
 GPU_rgba 0xEF2F4FFF
 GPU_palt PALETTE_WRITE, 63
 GPU_rgba 0xBF273FFF
 GPU_palt PALETTE_WRITE, 64
 GPU_rgba 0x7F1727FF
 GPU_palt PALETTE_WRITE, 65
 GPU_rgba 0x170007FF
 GPU_palt PALETTE_WRITE, 66
 GPU_rgba 0xAF2F4FFF
 GPU_palt PALETTE_WRITE, 67
 GPU_rgba 0x00579FFF
 GPU_palt PALETTE_WRITE, 68
 GPU_rgba 0x17172FFF
 GPU_palt PALETTE_WRITE, 69
 GPU_rgba 0x37070FFF
 GPU_palt PALETTE_WRITE, 70
 GPU_rgba 0x00172FFF
 GPU_palt PALETTE_WRITE, 71
 GPU_rgba 0x00001FFF
 GPU_palt PALETTE_WRITE, 72
 GPU_rgba 0x275787FF
 GPU_palt PALETTE_WRITE, 73
 GPU_rgba 0x4F9FEFFF
 GPU_palt PALETTE_WRITE, 74
 GPU_rgba 0x070717FF
 GPU_palt PALETTE_WRITE, 75
 GPU_rgba 0x073F5FFF
 GPU_palt PALETTE_WRITE, 76
 GPU_rgba 0x0067BFFF
 GPU_palt PALETTE_WRITE, 77
 GPU_rgba 0x3F77A7FF
 GPU_palt PALETTE_WRITE, 78
 GPU_rgba 0x77274FFF
 GPU_palt PALETTE_WRITE, 79
 GPU_rgba 0x1F0707FF
 GPU_palt PALETTE_WRITE, 80
 GPU_rgba 0x0F3F67FF
 GPU_palt PALETTE_WRITE, 81
 GPU_rgba 0x004767FF
 GPU_palt PALETTE_WRITE, 82
 GPU_rgba 0x270707FF
 GPU_palt PALETTE_WRITE, 83
 GPU_rgba 0x170717FF
 GPU_palt PALETTE_WRITE, 84
 GPU_rgba 0x270F27FF
 GPU_palt PALETTE_WRITE, 85
 GPU_rgba 0x001F47FF
 GPU_palt PALETTE_WRITE, 86
 GPU_rgba 0x2F87DFFF
 GPU_palt PALETTE_WRITE, 87
 GPU_rgba 0x8F274FFF
 GPU_palt PALETTE_WRITE, 88
 GPU_rgba 0x17479FFF
 GPU_palt PALETTE_WRITE, 89
 GPU_rgba 0x000707FF
 GPU_palt PALETTE_WRITE, 90
 GPU_rgba 0x172F4FFF
 GPU_palt PALETTE_WRITE, 91
 GPU_rgba 0x1F274FFF
 GPU_palt PALETTE_WRITE, 92
 GPU_rgba 0xD72F4FFF
 GPU_palt PALETTE_WRITE, 93
 GPU_rgba 0x270F17FF
 GPU_palt PALETTE_WRITE, 94
 GPU_rgba 0x277FCFFF
 GPU_palt PALETTE_WRITE, 95
 GPU_rgba 0x001727FF
 GPU_palt PALETTE_WRITE, 96
 GPU_rgba 0x570F17FF
 GPU_palt PALETTE_WRITE, 97
 GPU_rgba 0x8F0F17FF
 GPU_palt PALETTE_WRITE, 98
 GPU_rgba 0xD72747FF
 GPU_palt PALETTE_WRITE, 99
 GPU_rgba 0xB72F47FF
 GPU_palt PALETTE_WRITE, 100
 GPU_rgba 0xFF374FFF
 GPU_palt PALETTE_WRITE, 101
 GPU_rgba 0x4F0F17FF
 GPU_palt PALETTE_WRITE, 102
 GPU_rgba 0x0F0F2FFF
 GPU_palt PALETTE_WRITE, 103
 GPU_rgba 0x972F4FFF
 GPU_palt PALETTE_WRITE, 104
 GPU_rgba 0x17070FFF
 GPU_palt PALETTE_WRITE, 105
 GPU_rgba 0x871727FF
 GPU_palt PALETTE_WRITE, 106
 GPU_rgba 0x376F9FFF
 GPU_palt PALETTE_WRITE, 107
 GPU_rgba 0x0F0717FF
 GPU_palt PALETTE_WRITE, 108
 GPU_rgba 0x004F7FFF
 GPU_palt PALETTE_WRITE, 109
 GPU_rgba 0x0057BFFF
 GPU_palt PALETTE_WRITE, 110
 GPU_rgba 0x2F5F9FFF
 GPU_palt PALETTE_WRITE, 111
 GPU_rgba 0x3F1F3FFF
 GPU_palt PALETTE_WRITE, 112
 GPU_rgba 0x9F2F4FFF
 GPU_palt PALETTE_WRITE, 113
 GPU_rgba 0x0F0007FF
 GPU_palt PALETTE_WRITE, 114
 GPU_rgba 0xF7EFE7FF
 GPU_palt PALETTE_WRITE, 115
 GPU_rgba 0x000727FF
 GPU_palt PALETTE_WRITE, 116
 GPU_rgba 0x07070FFF
 GPU_palt PALETTE_WRITE, 117
 GPU_rgba 0x27172FFF
 GPU_palt PALETTE_WRITE, 118
 GPU_rgba 0x072F67FF
 GPU_palt PALETTE_WRITE, 119
 GPU_rgba 0x37274FFF
 GPU_palt PALETTE_WRITE, 120
 GPU_rgba 0x002F67FF
 GPU_palt PALETTE_WRITE, 121
 GPU_rgba 0x0F070FFF
 GPU_palt PALETTE_WRITE, 122
 GPU_rgba 0xA71F37FF
 GPU_palt PALETTE_WRITE, 123
 GPU_rgba 0x17173FFF
 GPU_palt PALETTE_WRITE, 124
 GPU_rgba 0x170F27FF
 GPU_palt PALETTE_WRITE, 125
 GPU_rgba 0xF7273FFF
 GPU_palt PALETTE_WRITE, 126
 GPU_rgba 0xCF273FFF
 GPU_palt PALETTE_WRITE, 127
 GPU_rgba 0x9F273FFF
 GPU_palt PALETTE_WRITE, 128
 GPU_rgba 0x971F2FFF
 GPU_palt PALETTE_WRITE, 129
 GPU_rgba 0x4F070FFF
 GPU_palt PALETTE_WRITE, 130
 GPU_rgba 0xA71727FF
 GPU_palt PALETTE_WRITE, 131
 GPU_rgba 0x270F1FFF
 GPU_palt PALETTE_WRITE, 132
 GPU_rgba 0x3F0F1FFF
 GPU_palt PALETTE_WRITE, 133
 GPU_rgba 0x67172FFF
 GPU_palt PALETTE_WRITE, 134
 GPU_rgba 0x1F0F27FF
 GPU_palt PALETTE_WRITE, 135
 GPU_rgba 0x6F171FFF
 GPU_palt PALETTE_WRITE, 136
 GPU_rgba 0x670F1FFF
 GPU_palt PALETTE_WRITE, 137
 GPU_rgba 0x07071FFF
 GPU_palt PALETTE_WRITE, 138
 GPU_rgba 0xCF2F4FFF
 GPU_palt PALETTE_WRITE, 139
 GPU_rgba 0x771F2FFF
 GPU_palt PALETTE_WRITE, 140
 GPU_rgba 0x770717FF
 GPU_palt PALETTE_WRITE, 141
 GPU_rgba 0x471737FF
 GPU_palt PALETTE_WRITE, 142
 GPU_rgba 0xDF273FFF
 GPU_palt PALETTE_WRITE, 143
 GPU_rgba 0x9F0F1FFF
 GPU_palt PALETTE_WRITE, 144
 GPU_rgba 0x07275FFF
 GPU_palt PALETTE_WRITE, 145
 GPU_rgba 0x370F27FF
 GPU_palt PALETTE_WRITE, 146
 GPU_rgba 0xBF172FFF
 GPU_palt PALETTE_WRITE, 147
 GPU_rgba 0x0F0F27FF
 GPU_palt PALETTE_WRITE, 148
 GPU_rgba 0xC7274FFF
 GPU_palt PALETTE_WRITE, 149
 GPU_rgba 0x5F1727FF
 GPU_palt PALETTE_WRITE, 150
 GPU_rgba 0x2F0F2FFF
 GPU_palt PALETTE_WRITE, 151
 GPU_rgba 0xF71F2FFF
 GPU_palt PALETTE_WRITE, 152
 GPU_rgba 0xF71F37FF
 GPU_palt PALETTE_WRITE, 153
 GPU_rgba 0xAF1717FF
 GPU_palt PALETTE_WRITE, 154
 GPU_rgba 0x97172FFF
 GPU_palt PALETTE_WRITE, 155
 GPU_rgba 0xC71727FF
 GPU_palt PALETTE_WRITE, 156
 GPU_rgba 0x2F0F17FF
 GPU_palt PALETTE_WRITE, 157
 GPU_rgba 0xF71F27FF
 GPU_palt PALETTE_WRITE, 158
 GPU_rgba 0x670F17FF
 GPU_palt PALETTE_WRITE, 159
 GPU_rgba 0x002757FF
 GPU_palt PALETTE_WRITE, 160
 GPU_rgba 0x002F5FFF
 GPU_palt PALETTE_WRITE, 161
 GPU_rgba 0x473767FF
 GPU_palt PALETTE_WRITE, 162
 GPU_rgba 0x172F67FF
 GPU_palt PALETTE_WRITE, 163
 GPU_rgba 0xD73F67FF
 GPU_palt PALETTE_WRITE, 164
 GPU_rgba 0x9F3767FF
 GPU_palt PALETTE_WRITE, 165
 GPU_rgba 0xFF3F67FF
 GPU_palt PALETTE_WRITE, 166
 GPU_rgba 0xF73F67FF
 GPU_palt PALETTE_WRITE, 167
 GPU_rgba 0x6F3767FF
 GPU_palt PALETTE_WRITE, 168
 GPU_rgba 0x673767FF
 GPU_palt PALETTE_WRITE, 169
 GPU_rgba 0xCF3F67FF
 GPU_palt PALETTE_WRITE, 170
 GPU_rgba 0xF73767FF
 GPU_palt PALETTE_WRITE, 171
 GPU_rgba 0x373767FF
 GPU_palt PALETTE_WRITE, 172
 GPU_rgba 0xC73F67FF
 GPU_palt PALETTE_WRITE, 173
 GPU_rgba 0xDF3767FF
 GPU_palt PALETTE_WRITE, 174
 GPU_rgba 0xBF3767FF
 GPU_palt PALETTE_WRITE, 175
 GPU_rgba 0xEF3F67FF
 GPU_palt PALETTE_WRITE, 176
 GPU_rgba 0x8F3767FF
 GPU_palt PALETTE_WRITE, 177
 GPU_rgba 0xE73767FF
 GPU_palt PALETTE_WRITE, 178
 GPU_rgba 0xA73767FF
 GPU_palt PALETTE_WRITE, 179
 GPU_rgba 0xAF3767FF
 GPU_palt PALETTE_WRITE, 180
 GPU_rgba 0x573767FF
 GPU_palt PALETTE_WRITE, 181
 GPU_rgba 0x7F3767FF
 GPU_palt PALETTE_WRITE, 182
 GPU_rgba 0x2F2F67FF
 GPU_palt PALETTE_WRITE, 183
 GPU_rgba 0x373737FF
 GPU_palt PALETTE_WRITE, 184
 GPU_rgba 0xBFBFBFFF
 GPU_palt PALETTE_WRITE, 185
 GPU_rgba 0x9F9F9FFF
 GPU_palt PALETTE_WRITE, 186
 GPU_rgba 0x474747FF
 GPU_palt PALETTE_WRITE, 187
 GPU_rgba 0xF7772FFF
 GPU_palt PALETTE_WRITE, 188
 GPU_rgba 0x976F2FFF
 GPU_palt PALETTE_WRITE, 189
 GPU_rgba 0xF76F2FFF
 GPU_palt PALETTE_WRITE, 190
 GPU_rgba 0x006F2FFF
 GPU_palt PALETTE_WRITE, 191
 GPU_rgba 0x005F27FF
 GPU_palt PALETTE_WRITE, 192
 GPU_rgba 0x97471FFF
 GPU_palt PALETTE_WRITE, 193
 GPU_rgba 0x000F07FF
 GPU_palt PALETTE_WRITE, 194
 GPU_rgba 0xF71F0FFF
 GPU_palt PALETTE_WRITE, 195
 GPU_rgba 0xF71717FF
 GPU_palt PALETTE_WRITE, 196
 GPU_rgba 0xE73F67FF
 GPU_palt PALETTE_WRITE, 197
 GPU_rgba 0x171717FF
 GPU_palt PALETTE_WRITE, 198
 GPU_rgba 0x3F6F2FFF
 GPU_palt PALETTE_WRITE, 199
 GPU_rgba 0xC75F27FF
 GPU_palt PALETTE_WRITE, 200
 GPU_rgba 0x672F0FFF
 GPU_palt PALETTE_WRITE, 201
 GPU_rgba 0xDF772FFF
 GPU_palt PALETTE_WRITE, 202
 GPU_rgba 0x001F0FFF
 GPU_palt PALETTE_WRITE, 203
 GPU_rgba 0x004F1FFF
 GPU_palt PALETTE_WRITE, 204
 GPU_rgba 0xFF3767FF
 GPU_palt PALETTE_WRITE, 205
 GPU_rgba 0x1F2F67FF
 GPU_palt PALETTE_WRITE, 206
 GPU_rgba 0x4F270FFF
 GPU_palt PALETTE_WRITE, 207
 GPU_rgba 0x5F3767FF
 GPU_palt PALETTE_WRITE, 208
 GPU_rgba 0x777F77FF
 GPU_palt PALETTE_WRITE, 209
 GPU_rgba 0x000F00FF
 GPU_palt PALETTE_WRITE, 210
 GPU_rgba 0x005727FF
 GPU_palt PALETTE_WRITE, 211
 GPU_rgba 0x002F0FFF
 GPU_palt PALETTE_WRITE, 212
 GPU_rgba 0x170700FF
 GPU_palt PALETTE_WRITE, 213
 GPU_rgba 0x371F0FFF
 GPU_palt PALETTE_WRITE, 214
 GPU_rgba 0x776F2FFF
 GPU_palt PALETTE_WRITE, 215
 GPU_rgba 0xBF772FFF
 GPU_palt PALETTE_WRITE, 216
 GPU_rgba 0x8F571FFF
 GPU_palt PALETTE_WRITE, 217
 GPU_rgba 0xF72F67FF
 GPU_palt PALETTE_WRITE, 218
 GPU_ret

#addr cavestory_tileset
 cavestory_tileset_data0
 cavestory_tileset_data1
 cavestory_tileset_data2
 cavestory_tileset_data3
 cavestory_tileset_data4
 cavestory_tileset_data5
 cavestory_tileset_data6
 cavestory_tileset_data7
 cavestory_tileset_data8
 cavestory_tileset_data9
 cavestory_tileset_data10
 cavestory_tileset_data11
 cavestory_tileset_data12
 cavestory_tileset_data13
 cavestory_tileset_data14
 cavestory_tileset_data15
 cavestory_tileset_data16
 cavestory_tileset_data17
 cavestory_tileset_data18
 cavestory_tileset_data19
 cavestory_tileset_data20
 cavestory_tileset_data21
 cavestory_tileset_data22
 cavestory_tileset_data23
 cavestory_tileset_data24
 cavestory_tileset_data25
 cavestory_tileset_data26
 cavestory_tileset_data27
 cavestory_tileset_data28
 cavestory_tileset_data29
 cavestory_tileset_data30
 cavestory_tileset_data31
 cavestory_tileset_data32
 cavestory_tileset_data33
 cavestory_tileset_data34
 cavestory_tileset_data35
 cavestory_tileset_data36
 cavestory_tileset_data37
 cavestory_tileset_data38
 cavestory_tileset_data39
 cavestory_tileset_data40
 cavestory_tileset_data41
 cavestory_tileset_data42
 cavestory_tileset_data43
 cavestory_tileset_data44
 cavestory_tileset_data45
 cavestory_tileset_data46
 cavestory_tileset_data47
 cavestory_tileset_data48
 cavestory_tileset_data49
 cavestory_tileset_data50
 cavestory_tileset_data51
 cavestory_tileset_data52
 cavestory_tileset_data53
 cavestory_tileset_data54
 cavestory_tileset_data55
 cavestory_tileset_data56
 cavestory_tileset_data57
 cavestory_tileset_data58
 cavestory_tileset_data59
 cavestory_tileset_data60
 cavestory_tileset_data61
 cavestory_tileset_data62
 cavestory_tileset_data63
 cavestory_tileset_data64
 cavestory_tileset_data65
 cavestory_tileset_data66
 cavestory_tileset_data67
 cavestory_tileset_data68
 cavestory_tileset_data69
 cavestory_tileset_data70
 cavestory_tileset_data71
 cavestory_tileset_data72
 cavestory_tileset_data73
 cavestory_tileset_data74
 cavestory_tileset_data75
 cavestory_tileset_data76
 cavestory_tileset_data77
 cavestory_tileset_data78
 cavestory_tileset_data79
 cavestory_tileset_data80
 cavestory_tileset_data81
 cavestory_tileset_data82
 cavestory_tileset_data83
 cavestory_tileset_data84
 cavestory_tileset_data85
 cavestory_tileset_data86
 cavestory_tileset_data87
 cavestory_tileset_data88
 cavestory_tileset_data89
 cavestory_tileset_data90
 cavestory_tileset_data91
 cavestory_tileset_data92
 cavestory_tileset_data93
 cavestory_tileset_data94
 cavestory_tileset_data95
 cavestory_tileset_data96
 cavestory_tileset_data97
 cavestory_tileset_data98
 cavestory_tileset_data99
 cavestory_tileset_data100
 cavestory_tileset_data101
 cavestory_tileset_data102
 cavestory_tileset_data103
 cavestory_tileset_data104
 cavestory_tileset_data105
 cavestory_tileset_data106
 cavestory_tileset_data107
 cavestory_tileset_data108
 cavestory_tileset_data109
 cavestory_tileset_data110
 cavestory_tileset_data111
 cavestory_tileset_data112
 cavestory_tileset_data113
 cavestory_tileset_data114
 cavestory_tileset_data115
 cavestory_tileset_data116
 cavestory_tileset_data117
 cavestory_tileset_data118
 cavestory_tileset_data119
 cavestory_tileset_data120
 cavestory_tileset_data121
 cavestory_tileset_data122
 cavestory_tileset_data123
 cavestory_tileset_data124
 cavestory_tileset_data125
 cavestory_tileset_data126
 cavestory_tileset_data127
 cavestory_tileset_data128
 cavestory_tileset_data129
 cavestory_tileset_data130
 cavestory_tileset_data131
 cavestory_tileset_data132
 cavestory_tileset_data133
 cavestory_tileset_data134
 cavestory_tileset_data135
 cavestory_tileset_data136
 cavestory_tileset_data137
 cavestory_tileset_data138
 cavestory_tileset_data139
 cavestory_tileset_data140
 cavestory_tileset_data141
 cavestory_tileset_data142
 cavestory_tileset_data143
 cavestory_tileset_data144
 cavestory_tileset_data145
 cavestory_tileset_data146
 cavestory_tileset_data147
 cavestory_tileset_data148
 cavestory_tileset_data149
 cavestory_tileset_data150
 cavestory_tileset_data151
 cavestory_tileset_data152
 cavestory_tileset_data153
 cavestory_tileset_data154
 cavestory_tileset_data155
 cavestory_tileset_data156
 cavestory_tileset_data157
 cavestory_tileset_data158
 cavestory_tileset_data159
 cavestory_tileset_data160
 cavestory_tileset_data161
 cavestory_tileset_data162
 cavestory_tileset_data163
 cavestory_tileset_data164
 cavestory_tileset_data165
 cavestory_tileset_data166
 cavestory_tileset_data167
 cavestory_tileset_data168
 cavestory_tileset_data169
 cavestory_tileset_data170
 cavestory_tileset_data171
 cavestory_tileset_data172
 cavestory_tileset_data173
 cavestory_tileset_data174
 cavestory_tileset_data175
 cavestory_tileset_data176
 cavestory_tileset_data177
 cavestory_tileset_data178
 cavestory_tileset_data179
 cavestory_tileset_data180
 cavestory_tileset_data181
 cavestory_tileset_data182
 cavestory_tileset_data183
 cavestory_tileset_data184
 cavestory_tileset_data185
 cavestory_tileset_data186
 cavestory_tileset_data187
 cavestory_tileset_data188
 cavestory_tileset_data189
 cavestory_tileset_data190
 cavestory_tileset_data191
 cavestory_tileset_data192
 cavestory_tileset_data193
 cavestory_tileset_data194
 cavestory_tileset_data195
 cavestory_tileset_data196
 cavestory_tileset_data197
 cavestory_tileset_data198
 cavestory_tileset_data199
 cavestory_tileset_data200
 cavestory_tileset_data201
 cavestory_tileset_data202
 cavestory_tileset_data203
 cavestory_tileset_data204
 cavestory_tileset_data205
 cavestory_tileset_data206
 cavestory_tileset_data207
 cavestory_tileset_data208
 cavestory_tileset_data209
 cavestory_tileset_data210
 cavestory_tileset_data211
 cavestory_tileset_data212
 cavestory_tileset_data213
 cavestory_tileset_data214
 cavestory_tileset_data215
 cavestory_tileset_data216
 cavestory_tileset_data217
 cavestory_tileset_data218
 cavestory_tileset_data219
 cavestory_tileset_data220
 cavestory_tileset_data221
 cavestory_tileset_data222
 cavestory_tileset_data223
 cavestory_tileset_data224
 cavestory_tileset_data225
 cavestory_tileset_data226
 cavestory_tileset_data227
 cavestory_tileset_data228
 cavestory_tileset_data229
 cavestory_tileset_data230
 cavestory_tileset_data231
 cavestory_tileset_data232
 cavestory_tileset_data233
 cavestory_tileset_data234
 cavestory_tileset_data235
 cavestory_tileset_data236
 cavestory_tileset_data237
 cavestory_tileset_data238
 cavestory_tileset_data239
 cavestory_tileset_data240
 cavestory_tileset_data241
 cavestory_tileset_data242
 cavestory_tileset_data243
 cavestory_tileset_data244
 cavestory_tileset_data245
 cavestory_tileset_data246
 cavestory_tileset_data247
 cavestory_tileset_data248
 cavestory_tileset_data249
 cavestory_tileset_data250
 cavestory_tileset_data251
 cavestory_tileset_data252
 cavestory_tileset_data253
 cavestory_tileset_data254
 cavestory_tileset_data255
 cavestory_tileset_data256
 cavestory_tileset_data257
 cavestory_tileset_data258
 cavestory_tileset_data259
 cavestory_tileset_data260
 cavestory_tileset_data261
 cavestory_tileset_data262
 cavestory_tileset_data263
 cavestory_tileset_data264
 cavestory_tileset_data265
 cavestory_tileset_data266
 cavestory_tileset_data267
 cavestory_tileset_data268
 cavestory_tileset_data269
 cavestory_tileset_data270
 cavestory_tileset_data271
 cavestory_tileset_data272
 cavestory_tileset_data273
 cavestory_tileset_data274
 cavestory_tileset_data275
 cavestory_tileset_data276
 cavestory_tileset_data277
 cavestory_tileset_data278
 cavestory_tileset_data279
 cavestory_tileset_data280
 cavestory_tileset_data281
 cavestory_tileset_data282
 cavestory_tileset_data283
 cavestory_tileset_data284
 cavestory_tileset_data285
 cavestory_tileset_data286
 cavestory_tileset_data287
 cavestory_tileset_data288
 cavestory_tileset_data289
 cavestory_tileset_data290
 cavestory_tileset_data291
 cavestory_tileset_data292
 cavestory_tileset_data293
 cavestory_tileset_data294
 cavestory_tileset_data295
 cavestory_tileset_data296
 cavestory_tileset_data297
 cavestory_tileset_data298
 cavestory_tileset_data299
 cavestory_tileset_data300
 cavestory_tileset_data301
 cavestory_tileset_data302
 cavestory_tileset_data303
 cavestory_tileset_data304
 cavestory_tileset_data305
 cavestory_tileset_data306
 cavestory_tileset_data307
 cavestory_tileset_data308
 cavestory_tileset_data309
 cavestory_tileset_data310
 cavestory_tileset_data311
 cavestory_tileset_data312
 cavestory_tileset_data313
 cavestory_tileset_data314
 cavestory_tileset_data315
 cavestory_tileset_data316
 cavestory_tileset_data317
 cavestory_tileset_data318
 cavestory_tileset_data319
 cavestory_tileset_data320
 cavestory_tileset_data321
 cavestory_tileset_data322
 cavestory_tileset_data323
 cavestory_tileset_data324
 cavestory_tileset_data325
 cavestory_tileset_data326
 cavestory_tileset_data327
 cavestory_tileset_data328
 cavestory_tileset_data329
 cavestory_tileset_data330
 cavestory_tileset_data331
 cavestory_tileset_data332
 cavestory_tileset_data333
 cavestory_tileset_data334
 cavestory_tileset_data335
 cavestory_tileset_data336
 cavestory_tileset_data337
 cavestory_tileset_data338
 cavestory_tileset_data339
 cavestory_tileset_data340
 cavestory_tileset_data341
 cavestory_tileset_data342
 cavestory_tileset_data343
 cavestory_tileset_data344
 cavestory_tileset_data345
 cavestory_tileset_data346
 cavestory_tileset_data347
 cavestory_tileset_data348
 cavestory_tileset_data349
 cavestory_tileset_data350
 cavestory_tileset_data351
 cavestory_tileset_data352
 cavestory_tileset_data353
 cavestory_tileset_data354
 cavestory_tileset_data355
 cavestory_tileset_data356
 cavestory_tileset_data357
 cavestory_tileset_data358
 cavestory_tileset_data359
 cavestory_tileset_data360
 cavestory_tileset_data361
 cavestory_tileset_data362
 cavestory_tileset_data363
 cavestory_tileset_data364
 cavestory_tileset_data365
 cavestory_tileset_data366
 cavestory_tileset_data367
 cavestory_tileset_data368
 cavestory_tileset_data369
 cavestory_tileset_data370
 cavestory_tileset_data371
 cavestory_tileset_data372
 cavestory_tileset_data373
 cavestory_tileset_data374
 cavestory_tileset_data375
 cavestory_tileset_data376
 cavestory_tileset_data377
 cavestory_tileset_data378
 cavestory_tileset_data379
 cavestory_tileset_data380
 cavestory_tileset_data381
 cavestory_tileset_data382
 cavestory_tileset_data383
 cavestory_tileset_data384
 cavestory_tileset_data385
 cavestory_tileset_data386
 cavestory_tileset_data387
 cavestory_tileset_data388
 cavestory_tileset_data389
 cavestory_tileset_data390
 cavestory_tileset_data391
 cavestory_tileset_data392
 cavestory_tileset_data393
 cavestory_tileset_data394
 cavestory_tileset_data395
 cavestory_tileset_data396
 cavestory_tileset_data397
 cavestory_tileset_data398
 cavestory_tileset_data399
 cavestory_tileset_data400
 cavestory_tileset_data401
 cavestory_tileset_data402
 cavestory_tileset_data403
 cavestory_tileset_data404
 cavestory_tileset_data405
 cavestory_tileset_data406
 cavestory_tileset_data407
 cavestory_tileset_data408
 cavestory_tileset_data409
 cavestory_tileset_data410
 cavestory_tileset_data411
 cavestory_tileset_data412
 cavestory_tileset_data413
 cavestory_tileset_data414
 cavestory_tileset_data415
 cavestory_tileset_data416
 cavestory_tileset_data417
 cavestory_tileset_data418
 cavestory_tileset_data419
 cavestory_tileset_data420
 cavestory_tileset_data421
 cavestory_tileset_data422
 cavestory_tileset_data423
 cavestory_tileset_data424
 cavestory_tileset_data425
 cavestory_tileset_data426
 cavestory_tileset_data427
 cavestory_tileset_data428
 cavestory_tileset_data429
 cavestory_tileset_data430
 cavestory_tileset_data431
 cavestory_tileset_data432
 cavestory_tileset_data433
 cavestory_tileset_data434
 cavestory_tileset_data435
 cavestory_tileset_data436
 cavestory_tileset_data437
 cavestory_tileset_data438
 cavestory_tileset_data439
 cavestory_tileset_data440
 cavestory_tileset_data441
 cavestory_tileset_data442
 cavestory_tileset_data443
 cavestory_tileset_data444
 cavestory_tileset_data445
 cavestory_tileset_data446
 cavestory_tileset_data447
 cavestory_tileset_data448
 cavestory_tileset_data449
 cavestory_tileset_data450
 cavestory_tileset_data451
 cavestory_tileset_data452
 cavestory_tileset_data453
 cavestory_tileset_data454
 cavestory_tileset_data455
 cavestory_tileset_data456
 cavestory_tileset_data457
 cavestory_tileset_data458
 cavestory_tileset_data459
 cavestory_tileset_data460
 cavestory_tileset_data461
 cavestory_tileset_data462
 cavestory_tileset_data463
 cavestory_tileset_data464
 cavestory_tileset_data465
 cavestory_tileset_data466
 cavestory_tileset_data467
 cavestory_tileset_data468
 cavestory_tileset_data469
 cavestory_tileset_data470
 cavestory_tileset_data471
 cavestory_tileset_data472
 cavestory_tileset_data473
 cavestory_tileset_data474
 cavestory_tileset_data475
 cavestory_tileset_data476
 cavestory_tileset_data477
 cavestory_tileset_data478
 cavestory_tileset_data479
 cavestory_tileset_data480
 cavestory_tileset_data481
 cavestory_tileset_data482
 cavestory_tileset_data483
 cavestory_tileset_data484
 cavestory_tileset_data485
 cavestory_tileset_data486
 cavestory_tileset_data487
 cavestory_tileset_data488
 cavestory_tileset_data489
 cavestory_tileset_data490
 cavestory_tileset_data491
 cavestory_tileset_data492
 cavestory_tileset_data493
 cavestory_tileset_data494
 cavestory_tileset_data495
 cavestory_tileset_data496
 cavestory_tileset_data497
 cavestory_tileset_data498
 cavestory_tileset_data499
 cavestory_tileset_data500
 cavestory_tileset_data501
 cavestory_tileset_data502
 cavestory_tileset_data503
 cavestory_tileset_data504
 cavestory_tileset_data505
 cavestory_tileset_data506
 cavestory_tileset_data507
 cavestory_tileset_data508
 cavestory_tileset_data509
 cavestory_tileset_data510
 cavestory_tileset_data511
 cavestory_tileset_data512
 cavestory_tileset_data513
 cavestory_tileset_data514
 cavestory_tileset_data515
 cavestory_tileset_data516
 cavestory_tileset_data517
 cavestory_tileset_data518
 cavestory_tileset_data519
 cavestory_tileset_data520
 cavestory_tileset_data521
 cavestory_tileset_data522
 cavestory_tileset_data523
 cavestory_tileset_data524
 cavestory_tileset_data525
 cavestory_tileset_data526
 cavestory_tileset_data527
 cavestory_tileset_data528
 cavestory_tileset_data529
 cavestory_tileset_data530
 cavestory_tileset_data531
 cavestory_tileset_data532
 cavestory_tileset_data533
 cavestory_tileset_data534
 cavestory_tileset_data535
 cavestory_tileset_data536
 cavestory_tileset_data537
 cavestory_tileset_data538
 cavestory_tileset_data539
 cavestory_tileset_data540
 cavestory_tileset_data541
 cavestory_tileset_data542
 cavestory_tileset_data543
 cavestory_tileset_data544
 cavestory_tileset_data545
 cavestory_tileset_data546
 cavestory_tileset_data547
 cavestory_tileset_data548
 cavestory_tileset_data549
 cavestory_tileset_data550
 cavestory_tileset_data551
 cavestory_tileset_data552
 cavestory_tileset_data553
 cavestory_tileset_data554
 cavestory_tileset_data555
 cavestory_tileset_data556
 cavestory_tileset_data557
 cavestory_tileset_data558
 cavestory_tileset_data559
 cavestory_tileset_data560
 cavestory_tileset_data561
 cavestory_tileset_data562
 cavestory_tileset_data563
 cavestory_tileset_data564
 cavestory_tileset_data565
 cavestory_tileset_data566
 cavestory_tileset_data567
 cavestory_tileset_data568
 cavestory_tileset_data569
 cavestory_tileset_data570
 cavestory_tileset_data571
 cavestory_tileset_data572
 cavestory_tileset_data573
 cavestory_tileset_data574
 cavestory_tileset_data575
 cavestory_tileset_data576
 cavestory_tileset_data577
 cavestory_tileset_data578
 cavestory_tileset_data579
 cavestory_tileset_data580
 cavestory_tileset_data581
 cavestory_tileset_data582
 cavestory_tileset_data583
 cavestory_tileset_data584
 cavestory_tileset_data585
 cavestory_tileset_data586
 cavestory_tileset_data587
 cavestory_tileset_data588
 cavestory_tileset_data589
 cavestory_tileset_data590
 cavestory_tileset_data591
 cavestory_tileset_data592
 cavestory_tileset_data593
 cavestory_tileset_data594
 cavestory_tileset_data595
 cavestory_tileset_data596
 cavestory_tileset_data597
 cavestory_tileset_data598
 cavestory_tileset_data599
 cavestory_tileset_data600
 cavestory_tileset_data601
 cavestory_tileset_data602
 cavestory_tileset_data603
 cavestory_tileset_data604
 cavestory_tileset_data605
 cavestory_tileset_data606
 cavestory_tileset_data607
 cavestory_tileset_data608
 cavestory_tileset_data609
 cavestory_tileset_data610
 cavestory_tileset_data611
 cavestory_tileset_data612
 cavestory_tileset_data613
 cavestory_tileset_data614
 cavestory_tileset_data615
 cavestory_tileset_data616
 cavestory_tileset_data617
 cavestory_tileset_data618
 cavestory_tileset_data619
 cavestory_tileset_data620
 cavestory_tileset_data621
 cavestory_tileset_data622
 cavestory_tileset_data623
 cavestory_tileset_data624
 cavestory_tileset_data625
 cavestory_tileset_data626
 cavestory_tileset_data627
 cavestory_tileset_data628
 cavestory_tileset_data629
 cavestory_tileset_data630
 cavestory_tileset_data631
 cavestory_tileset_data632
 cavestory_tileset_data633
 cavestory_tileset_data634
 cavestory_tileset_data635
 cavestory_tileset_data636
 cavestory_tileset_data637
 cavestory_tileset_data638
 cavestory_tileset_data639
 cavestory_tileset_data640
 cavestory_tileset_data641
 cavestory_tileset_data642
 cavestory_tileset_data643
 cavestory_tileset_data644
 cavestory_tileset_data645
 cavestory_tileset_data646
 cavestory_tileset_data647
 cavestory_tileset_data648
 cavestory_tileset_data649
 cavestory_tileset_data650
 cavestory_tileset_data651
 cavestory_tileset_data652
 cavestory_tileset_data653
 cavestory_tileset_data654
 cavestory_tileset_data655
 cavestory_tileset_data656
 cavestory_tileset_data657
 cavestory_tileset_data658
 cavestory_tileset_data659
 cavestory_tileset_data660
 cavestory_tileset_data661
 cavestory_tileset_data662
 cavestory_tileset_data663
 cavestory_tileset_data664
 cavestory_tileset_data665
 cavestory_tileset_data666
 cavestory_tileset_data667
 cavestory_tileset_data668
 cavestory_tileset_data669
 cavestory_tileset_data670
 cavestory_tileset_data671
 cavestory_tileset_data672
 cavestory_tileset_data673
 cavestory_tileset_data674
 cavestory_tileset_data675
 cavestory_tileset_data676
 cavestory_tileset_data677
 cavestory_tileset_data678
 cavestory_tileset_data679
 cavestory_tileset_data680
 cavestory_tileset_data681
 cavestory_tileset_data682
 cavestory_tileset_data683
 cavestory_tileset_data684
 cavestory_tileset_data685
 cavestory_tileset_data686
 cavestory_tileset_data687
 cavestory_tileset_data688
 cavestory_tileset_data689
 cavestory_tileset_data690
 cavestory_tileset_data691
 cavestory_tileset_data692
 cavestory_tileset_data693
 cavestory_tileset_data694
 cavestory_tileset_data695
 cavestory_tileset_data696
 cavestory_tileset_data697
 cavestory_tileset_data698
 cavestory_tileset_data699
 cavestory_tileset_data700
 cavestory_tileset_data701
 cavestory_tileset_data702
 cavestory_tileset_data703
 cavestory_tileset_data704
 cavestory_tileset_data705
 cavestory_tileset_data706
 cavestory_tileset_data707
 cavestory_tileset_data708
 cavestory_tileset_data709
 cavestory_tileset_data710
 cavestory_tileset_data711
 cavestory_tileset_data712
 cavestory_tileset_data713
 cavestory_tileset_data714
 cavestory_tileset_data715
 cavestory_tileset_data716
 cavestory_tileset_data717
 cavestory_tileset_data718
 cavestory_tileset_data719
 cavestory_tileset_data720
 cavestory_tileset_data721
 cavestory_tileset_data722
 cavestory_tileset_data723
 cavestory_tileset_data724
 cavestory_tileset_data725
 cavestory_tileset_data726
 cavestory_tileset_data727
 cavestory_tileset_data728
 cavestory_tileset_data729
 cavestory_tileset_data730
 cavestory_tileset_data731
 cavestory_tileset_data732
 cavestory_tileset_data733
 cavestory_tileset_data734
 cavestory_tileset_data735
 cavestory_tileset_data736
 cavestory_tileset_data737
 cavestory_tileset_data738
 cavestory_tileset_data739
 cavestory_tileset_data740
 cavestory_tileset_data741
 cavestory_tileset_data742
 cavestory_tileset_data743
 cavestory_tileset_data744
 cavestory_tileset_data745
 cavestory_tileset_data746
 cavestory_tileset_data747
 cavestory_tileset_data748
 cavestory_tileset_data749
 cavestory_tileset_data750
 cavestory_tileset_data751
 cavestory_tileset_data752
 cavestory_tileset_data753
 cavestory_tileset_data754
 cavestory_tileset_data755
 cavestory_tileset_data756
 cavestory_tileset_data757
 cavestory_tileset_data758
 cavestory_tileset_data759
 cavestory_tileset_data760
 cavestory_tileset_data761
 cavestory_tileset_data762
 cavestory_tileset_data763
 cavestory_tileset_data764
 cavestory_tileset_data765
 cavestory_tileset_data766
 cavestory_tileset_data767
 cavestory_tileset_data768
 cavestory_tileset_data769
 cavestory_tileset_data770
 cavestory_tileset_data771
 cavestory_tileset_data772
 cavestory_tileset_data773
 cavestory_tileset_data774
 cavestory_tileset_data775
 cavestory_tileset_data776
 cavestory_tileset_data777
 cavestory_tileset_data778
 cavestory_tileset_data779
 cavestory_tileset_data780
 cavestory_tileset_data781
 cavestory_tileset_data782
 cavestory_tileset_data783
 cavestory_tileset_data784
 cavestory_tileset_data785
 cavestory_tileset_data786
 cavestory_tileset_data787
 cavestory_tileset_data788
 cavestory_tileset_data789
 cavestory_tileset_data790
 cavestory_tileset_data791
 cavestory_tileset_data792
 cavestory_tileset_data793
 cavestory_tileset_data794
 cavestory_tileset_data795
 cavestory_tileset_data796
 cavestory_tileset_data797
 cavestory_tileset_data798
 cavestory_tileset_data799
 cavestory_tileset_data800
 cavestory_tileset_data801
 cavestory_tileset_data802
 cavestory_tileset_data803
 cavestory_tileset_data804
 cavestory_tileset_data805
 cavestory_tileset_data806
 cavestory_tileset_data807
 cavestory_tileset_data808
 cavestory_tileset_data809
 cavestory_tileset_data810
 cavestory_tileset_data811
 cavestory_tileset_data812
 cavestory_tileset_data813
 cavestory_tileset_data814
 cavestory_tileset_data815
 cavestory_tileset_data816
 cavestory_tileset_data817
 cavestory_tileset_data818
 cavestory_tileset_data819
 cavestory_tileset_data820
 cavestory_tileset_data821
 cavestory_tileset_data822
 cavestory_tileset_data823
 cavestory_tileset_data824
 cavestory_tileset_data825
 cavestory_tileset_data826
 cavestory_tileset_data827
 cavestory_tileset_data828
 cavestory_tileset_data829
 cavestory_tileset_data830
 cavestory_tileset_data831
 cavestory_tileset_data832
 cavestory_tileset_data833
 cavestory_tileset_data834
 cavestory_tileset_data835
 cavestory_tileset_data836
 cavestory_tileset_data837
 cavestory_tileset_data838
 cavestory_tileset_data839
 cavestory_tileset_data840
 cavestory_tileset_data841
 cavestory_tileset_data842
 cavestory_tileset_data843
 cavestory_tileset_data844
 cavestory_tileset_data845
 cavestory_tileset_data846
 cavestory_tileset_data847
 cavestory_tileset_data848
 cavestory_tileset_data849
 cavestory_tileset_data850
 cavestory_tileset_data851
 cavestory_tileset_data852
 cavestory_tileset_data853
 cavestory_tileset_data854
 cavestory_tileset_data855
 cavestory_tileset_data856
 cavestory_tileset_data857
 cavestory_tileset_data858
 cavestory_tileset_data859
 cavestory_tileset_data860
 cavestory_tileset_data861
 cavestory_tileset_data862
 cavestory_tileset_data863
 cavestory_tileset_data864
 cavestory_tileset_data865
 cavestory_tileset_data866
 cavestory_tileset_data867
 cavestory_tileset_data868
 cavestory_tileset_data869
 cavestory_tileset_data870
 cavestory_tileset_data871
 cavestory_tileset_data872
 cavestory_tileset_data873
 cavestory_tileset_data874
 cavestory_tileset_data875
 cavestory_tileset_data876
 cavestory_tileset_data877
 cavestory_tileset_data878
 cavestory_tileset_data879
 cavestory_tileset_data880
 cavestory_tileset_data881
 cavestory_tileset_data882
 cavestory_tileset_data883
 cavestory_tileset_data884
 cavestory_tileset_data885
 cavestory_tileset_data886
 cavestory_tileset_data887
 cavestory_tileset_data888
 cavestory_tileset_data889
 cavestory_tileset_data890
 cavestory_tileset_data891
 cavestory_tileset_data892
 cavestory_tileset_data893
 cavestory_tileset_data894
 cavestory_tileset_data895
 cavestory_tileset_data896
 cavestory_tileset_data897
 cavestory_tileset_data898
 cavestory_tileset_data899
 cavestory_tileset_data900
 cavestory_tileset_data901
 cavestory_tileset_data902
 cavestory_tileset_data903
 cavestory_tileset_data904
 cavestory_tileset_data905
 cavestory_tileset_data906
 cavestory_tileset_data907
 cavestory_tileset_data908
 cavestory_tileset_data909
 cavestory_tileset_data910
 cavestory_tileset_data911
 cavestory_tileset_data912
 cavestory_tileset_data913
 cavestory_tileset_data914
 cavestory_tileset_data915
 cavestory_tileset_data916
 cavestory_tileset_data917
 cavestory_tileset_data918
 cavestory_tileset_data919
 cavestory_tileset_data920
 cavestory_tileset_data921
 cavestory_tileset_data922
 cavestory_tileset_data923
 cavestory_tileset_data924
 cavestory_tileset_data925
 cavestory_tileset_data926
 cavestory_tileset_data927
 cavestory_tileset_data928
 cavestory_tileset_data929
 cavestory_tileset_data930
 cavestory_tileset_data931
 cavestory_tileset_data932
 cavestory_tileset_data933
 cavestory_tileset_data934
 cavestory_tileset_data935
 cavestory_tileset_data936
 cavestory_tileset_data937
 cavestory_tileset_data938
 cavestory_tileset_data939
 cavestory_tileset_data940
 cavestory_tileset_data941
 cavestory_tileset_data942
 cavestory_tileset_data943
 cavestory_tileset_data944
 cavestory_tileset_data945
 cavestory_tileset_data946
 cavestory_tileset_data947
 cavestory_tileset_data948
 cavestory_tileset_data949
 cavestory_tileset_data950
 cavestory_tileset_data951
 cavestory_tileset_data952
 cavestory_tileset_data953
 cavestory_tileset_data954
 cavestory_tileset_data955
 cavestory_tileset_data956
 cavestory_tileset_data957
 cavestory_tileset_data958
 cavestory_tileset_data959
 cavestory_tileset_data960
 cavestory_tileset_data961
 cavestory_tileset_data962
 cavestory_tileset_data963
 cavestory_tileset_data964
 cavestory_tileset_data965
 cavestory_tileset_data966
 cavestory_tileset_data967
 cavestory_tileset_data968
 cavestory_tileset_data969
 cavestory_tileset_data970
 cavestory_tileset_data971
 cavestory_tileset_data972
 cavestory_tileset_data973
 cavestory_tileset_data974
 cavestory_tileset_data975
 cavestory_tileset_data976
 cavestory_tileset_data977
 cavestory_tileset_data978
 cavestory_tileset_data979
 cavestory_tileset_data980
 cavestory_tileset_data981
 cavestory_tileset_data982
 cavestory_tileset_data983
 cavestory_tileset_data984
 cavestory_tileset_data985
 cavestory_tileset_data986
 cavestory_tileset_data987
 cavestory_tileset_data988
 cavestory_tileset_data989
 cavestory_tileset_data990
 cavestory_tileset_data991
 cavestory_tileset_data992
 cavestory_tileset_data993
 cavestory_tileset_data994
 cavestory_tileset_data995
 cavestory_tileset_data996
 cavestory_tileset_data997
 cavestory_tileset_data998
 cavestory_tileset_data999
 cavestory_tileset_data1000
 cavestory_tileset_data1001
 cavestory_tileset_data1002
 cavestory_tileset_data1003
 cavestory_tileset_data1004
 cavestory_tileset_data1005
 cavestory_tileset_data1006
 cavestory_tileset_data1007
 cavestory_tileset_data1008
 cavestory_tileset_data1009
 cavestory_tileset_data1010
 cavestory_tileset_data1011
 cavestory_tileset_data1012
 cavestory_tileset_data1013
 cavestory_tileset_data1014
 cavestory_tileset_data1015
 cavestory_tileset_data1016
 cavestory_tileset_data1017
 cavestory_tileset_data1018
 cavestory_tileset_data1019
 cavestory_tileset_data1020
 cavestory_tileset_data1021
 cavestory_tileset_data1022
 cavestory_tileset_data1023
 cavestory_tileset_data1024
 cavestory_tileset_data1025
 cavestory_tileset_data1026
 cavestory_tileset_data1027
 cavestory_tileset_data1028
 cavestory_tileset_data1029
 cavestory_tileset_data1030
 cavestory_tileset_data1031
 cavestory_tileset_data1032
 cavestory_tileset_data1033
 cavestory_tileset_data1034
 cavestory_tileset_data1035
 cavestory_tileset_data1036
 cavestory_tileset_data1037
 cavestory_tileset_data1038
 cavestory_tileset_data1039
 cavestory_tileset_data1040
 cavestory_tileset_data1041
 cavestory_tileset_data1042
 cavestory_tileset_data1043
 cavestory_tileset_data1044
 cavestory_tileset_data1045
 cavestory_tileset_data1046
 cavestory_tileset_data1047
 cavestory_tileset_data1048
 cavestory_tileset_data1049
 cavestory_tileset_data1050
 cavestory_tileset_data1051
 cavestory_tileset_data1052
 cavestory_tileset_data1053
 cavestory_tileset_data1054
 cavestory_tileset_data1055
 cavestory_tileset_data1056
 cavestory_tileset_data1057
 cavestory_tileset_data1058
 cavestory_tileset_data1059
 cavestory_tileset_data1060
 cavestory_tileset_data1061
 cavestory_tileset_data1062
 cavestory_tileset_data1063
 cavestory_tileset_data1064
 cavestory_tileset_data1065
 cavestory_tileset_data1066
 cavestory_tileset_data1067
 cavestory_tileset_data1068
 cavestory_tileset_data1069
 cavestory_tileset_data1070
 cavestory_tileset_data1071
 cavestory_tileset_data1072
 cavestory_tileset_data1073
 cavestory_tileset_data1074
 cavestory_tileset_data1075
 cavestory_tileset_data1076
 cavestory_tileset_data1077
 cavestory_tileset_data1078
 cavestory_tileset_data1079
 cavestory_tileset_data1080
 cavestory_tileset_data1081
 cavestory_tileset_data1082
 cavestory_tileset_data1083
 cavestory_tileset_data1084
 cavestory_tileset_data1085
 cavestory_tileset_data1086
 cavestory_tileset_data1087
 cavestory_tileset_data1088
 cavestory_tileset_data1089
 cavestory_tileset_data1090
 cavestory_tileset_data1091
 cavestory_tileset_data1092
 cavestory_tileset_data1093
 cavestory_tileset_data1094
 cavestory_tileset_data1095
 cavestory_tileset_data1096
 cavestory_tileset_data1097
 cavestory_tileset_data1098
 cavestory_tileset_data1099
 cavestory_tileset_data1100
 cavestory_tileset_data1101
 cavestory_tileset_data1102
 cavestory_tileset_data1103
 cavestory_tileset_data1104
 cavestory_tileset_data1105
 cavestory_tileset_data1106
 cavestory_tileset_data1107
 cavestory_tileset_data1108
 cavestory_tileset_data1109
 cavestory_tileset_data1110
 cavestory_tileset_data1111
 cavestory_tileset_data1112
 cavestory_tileset_data1113
 cavestory_tileset_data1114
 cavestory_tileset_data1115
 cavestory_tileset_data1116
 cavestory_tileset_data1117
 cavestory_tileset_data1118
 cavestory_tileset_data1119
 cavestory_tileset_data1120
 cavestory_tileset_data1121
 cavestory_tileset_data1122
 cavestory_tileset_data1123
 cavestory_tileset_data1124
 cavestory_tileset_data1125
 cavestory_tileset_data1126
 cavestory_tileset_data1127
 cavestory_tileset_data1128
 cavestory_tileset_data1129
 cavestory_tileset_data1130
 cavestory_tileset_data1131
 cavestory_tileset_data1132
 cavestory_tileset_data1133
 cavestory_tileset_data1134
 cavestory_tileset_data1135
 cavestory_tileset_data1136
 cavestory_tileset_data1137
 cavestory_tileset_data1138
 cavestory_tileset_data1139
 cavestory_tileset_data1140
 cavestory_tileset_data1141
 cavestory_tileset_data1142
 cavestory_tileset_data1143
 cavestory_tileset_data1144
 cavestory_tileset_data1145
 cavestory_tileset_data1146
 cavestory_tileset_data1147
 cavestory_tileset_data1148
 cavestory_tileset_data1149
 cavestory_tileset_data1150
 cavestory_tileset_data1151
 cavestory_tileset_data1152
 cavestory_tileset_data1153
 cavestory_tileset_data1154
 cavestory_tileset_data1155
 cavestory_tileset_data1156
 cavestory_tileset_data1157
 cavestory_tileset_data1158
 cavestory_tileset_data1159
 cavestory_tileset_data1160
 cavestory_tileset_data1161
 cavestory_tileset_data1162
 cavestory_tileset_data1163
 cavestory_tileset_data1164
 cavestory_tileset_data1165
 cavestory_tileset_data1166
 cavestory_tileset_data1167
 cavestory_tileset_data1168
 cavestory_tileset_data1169
 cavestory_tileset_data1170
 cavestory_tileset_data1171
 cavestory_tileset_data1172
 cavestory_tileset_data1173
 cavestory_tileset_data1174
 cavestory_tileset_data1175
 cavestory_tileset_data1176
 cavestory_tileset_data1177
 cavestory_tileset_data1178
 cavestory_tileset_data1179
 cavestory_tileset_data1180
 cavestory_tileset_data1181
 cavestory_tileset_data1182
 cavestory_tileset_data1183
 cavestory_tileset_data1184
 cavestory_tileset_data1185
 cavestory_tileset_data1186
 cavestory_tileset_data1187
 cavestory_tileset_data1188
 cavestory_tileset_data1189
 cavestory_tileset_data1190
 cavestory_tileset_data1191
 cavestory_tileset_data1192
 cavestory_tileset_data1193
 cavestory_tileset_data1194
 cavestory_tileset_data1195
 cavestory_tileset_data1196
 cavestory_tileset_data1197
 cavestory_tileset_data1198
 cavestory_tileset_data1199
 cavestory_tileset_data1200
 cavestory_tileset_data1201
 cavestory_tileset_data1202
 cavestory_tileset_data1203
 cavestory_tileset_data1204
 cavestory_tileset_data1205
 cavestory_tileset_data1206
 cavestory_tileset_data1207
 cavestory_tileset_data1208
 cavestory_tileset_data1209
 cavestory_tileset_data1210
 cavestory_tileset_data1211
 cavestory_tileset_data1212
 cavestory_tileset_data1213

#addr cavestory_banner
 cavestory_banner_data0
 cavestory_banner_data1
 cavestory_banner_data2
 cavestory_banner_data3
 cavestory_banner_data4
 cavestory_banner_data5
 cavestory_banner_data6
 cavestory_banner_data7
 cavestory_banner_data8
 cavestory_banner_data9
 cavestory_banner_data10
 cavestory_banner_data11
 cavestory_banner_data12
 cavestory_banner_data13
 cavestory_banner_data14
 cavestory_banner_data15
 cavestory_banner_data16
 cavestory_banner_data17
 cavestory_banner_data18
 cavestory_banner_data19
 cavestory_banner_data20
 cavestory_banner_data21
 cavestory_banner_data22
 cavestory_banner_data23
 cavestory_banner_data24
 cavestory_banner_data25
 cavestory_banner_data26
 cavestory_banner_data27
 cavestory_banner_data28
 cavestory_banner_data29
 cavestory_banner_data30
 cavestory_banner_data31
 cavestory_banner_data32
 cavestory_banner_data33
 cavestory_banner_data34
 cavestory_banner_data35
 cavestory_banner_data36
 cavestory_banner_data37
 cavestory_banner_data38
 cavestory_banner_data39
 cavestory_banner_data40
 cavestory_banner_data41
 cavestory_banner_data42
 cavestory_banner_data43
 cavestory_banner_data44
 cavestory_banner_data45
 cavestory_banner_data46
 cavestory_banner_data47
 cavestory_banner_data48
 cavestory_banner_data49
 cavestory_banner_data50
 cavestory_banner_data51
 cavestory_banner_data52
 cavestory_banner_data53
 cavestory_banner_data54
 cavestory_banner_data55
 cavestory_banner_data56
 cavestory_banner_data57
 cavestory_banner_data58
 cavestory_banner_data59
 cavestory_banner_data60
 cavestory_banner_data61
 cavestory_banner_data62
 cavestory_banner_data63
 cavestory_banner_data64
 cavestory_banner_data65
 cavestory_banner_data66
 cavestory_banner_data67
 cavestory_banner_data68
 cavestory_banner_data69
 cavestory_banner_data70
 cavestory_banner_data71
 cavestory_banner_data72
 cavestory_banner_data73
 cavestory_banner_data74
 cavestory_banner_data75
 cavestory_banner_data76
 cavestory_banner_data77
 cavestory_banner_data78
 cavestory_banner_data79
 cavestory_banner_data80
 cavestory_banner_data81
 cavestory_banner_data82
 cavestory_banner_data83
 cavestory_banner_data84
 cavestory_banner_data85
 cavestory_banner_data86
 cavestory_banner_data87
 cavestory_banner_data88
 cavestory_banner_data89
 cavestory_banner_data90
 cavestory_banner_data91
 cavestory_banner_data92
 cavestory_banner_data93
 cavestory_banner_data94
 cavestory_banner_data95
 cavestory_banner_data96
 cavestory_banner_data97
 cavestory_banner_data98
 cavestory_banner_data99
 cavestory_banner_data100
 cavestory_banner_data101
 cavestory_banner_data102
 cavestory_banner_data103
 cavestory_banner_data104
 cavestory_banner_data105
 cavestory_banner_data106
 cavestory_banner_data107
 cavestory_banner_data108
 cavestory_banner_data109
 cavestory_banner_data110
 cavestory_banner_data111
 cavestory_banner_data112
 cavestory_banner_data113
 cavestory_banner_data114
 cavestory_banner_data115
 cavestory_banner_data116
 cavestory_banner_data117
 cavestory_banner_data118
 cavestory_banner_data119
 cavestory_banner_data120
 cavestory_banner_data121
 cavestory_banner_data122
 cavestory_banner_data123
 cavestory_banner_data124
 cavestory_banner_data125
 cavestory_banner_data126
 cavestory_banner_data127
 cavestory_banner_data128
 cavestory_banner_data129
 cavestory_banner_data130
 cavestory_banner_data131
 cavestory_banner_data132
 cavestory_banner_data133
 cavestory_banner_data134
 cavestory_banner_data135
 cavestory_banner_data136
 cavestory_banner_data137
 cavestory_banner_data138
 cavestory_banner_data139
 cavestory_banner_data140
 cavestory_banner_data141
 cavestory_banner_data142
 cavestory_banner_data143
 cavestory_banner_data144
 cavestory_banner_data145
 cavestory_banner_data146
 cavestory_banner_data147
 cavestory_banner_data148
 cavestory_banner_data149
 cavestory_banner_data150
 cavestory_banner_data151
 cavestory_banner_data152
 cavestory_banner_data153
 cavestory_banner_data154
 cavestory_banner_data155
 cavestory_banner_data156
 cavestory_banner_data157
 cavestory_banner_data158
 cavestory_banner_data159
 cavestory_banner_data160
 cavestory_banner_data161
 cavestory_banner_data162
 cavestory_banner_data163
 cavestory_banner_data164
 cavestory_banner_data165
 cavestory_banner_data166
 cavestory_banner_data167
 cavestory_banner_data168
 cavestory_banner_data169
 cavestory_banner_data170
 cavestory_banner_data171
 cavestory_banner_data172
 cavestory_banner_data173
 cavestory_banner_data174
 cavestory_banner_data175
 cavestory_banner_data176
 cavestory_banner_data177
 cavestory_banner_data178
 cavestory_banner_data179
 cavestory_banner_data180
 cavestory_banner_data181
 cavestory_banner_data182
 cavestory_banner_data183
 cavestory_banner_data184
 cavestory_banner_data185
 cavestory_banner_data186
 cavestory_banner_data187
 cavestory_banner_data188
 cavestory_banner_data189
 cavestory_banner_data190
 cavestory_banner_data191
 cavestory_banner_data192
 cavestory_banner_data193
 cavestory_banner_data194
 cavestory_banner_data195
 cavestory_banner_data196
 cavestory_banner_data197
 cavestory_banner_data198
 cavestory_banner_data199
 cavestory_banner_data200
 cavestory_banner_data201
 cavestory_banner_data202
 cavestory_banner_data203
 cavestory_banner_data204
 cavestory_banner_data205
 cavestory_banner_data206
 cavestory_banner_data207
 cavestory_banner_data208
 cavestory_banner_data209
 cavestory_banner_data210
 cavestory_banner_data211
 cavestory_banner_data212
 cavestory_banner_data213
 cavestory_banner_data214
 cavestory_banner_data215
 cavestory_banner_data216
 cavestory_banner_data217
 cavestory_banner_data218
 cavestory_banner_data219
 cavestory_banner_data220
 cavestory_banner_data221
 cavestory_banner_data222
 cavestory_banner_data223
 cavestory_banner_data224
 cavestory_banner_data225
 cavestory_banner_data226
 cavestory_banner_data227
 cavestory_banner_data228
 cavestory_banner_data229
 cavestory_banner_data230
 cavestory_banner_data231
 cavestory_banner_data232
 cavestory_banner_data233
 cavestory_banner_data234
 cavestory_banner_data235
 cavestory_banner_data236
 cavestory_banner_data237
 cavestory_banner_data238
 cavestory_banner_data239
 cavestory_banner_data240
 cavestory_banner_data241
 cavestory_banner_data242
 cavestory_banner_data243
 cavestory_banner_data244
 cavestory_banner_data245
 cavestory_banner_data246
 cavestory_banner_data247
 cavestory_banner_data248
 cavestory_banner_data249
 cavestory_banner_data250
 cavestory_banner_data251
 cavestory_banner_data252
 cavestory_banner_data253
 cavestory_banner_data254
 cavestory_banner_data255
 cavestory_banner_data256
 cavestory_banner_data257
 cavestory_banner_data258
 cavestory_banner_data259
 cavestory_banner_data260
 cavestory_banner_data261
 cavestory_banner_data262
 cavestory_banner_data263
 cavestory_banner_data264
 cavestory_banner_data265
 cavestory_banner_data266
 cavestory_banner_data267
 cavestory_banner_data268
 cavestory_banner_data269
 cavestory_banner_data270
 cavestory_banner_data271
 cavestory_banner_data272
 cavestory_banner_data273
 cavestory_banner_data274
 cavestory_banner_data275
 cavestory_banner_data276
 cavestory_banner_data277
 cavestory_banner_data278
 cavestory_banner_data279
 cavestory_banner_data280
 cavestory_banner_data281
 cavestory_banner_data282
 cavestory_banner_data283
 cavestory_banner_data284
 cavestory_banner_data285
 cavestory_banner_data286
 cavestory_banner_data287
 cavestory_banner_data288
 cavestory_banner_data289
 cavestory_banner_data290
 cavestory_banner_data291
 cavestory_banner_data292
 cavestory_banner_data293
 cavestory_banner_data294
 cavestory_banner_data295
 cavestory_banner_data296
 cavestory_banner_data297
 cavestory_banner_data298
 cavestory_banner_data299
 cavestory_banner_data300
 cavestory_banner_data301
 cavestory_banner_data302
 cavestory_banner_data303
 cavestory_banner_data304
 cavestory_banner_data305
 cavestory_banner_data306
 cavestory_banner_data307
 cavestory_banner_data308
 cavestory_banner_data309
 cavestory_banner_data310
 cavestory_banner_data311
 cavestory_banner_data312
 cavestory_banner_data313
 cavestory_banner_data314
 cavestory_banner_data315
 cavestory_banner_data316
 cavestory_banner_data317
 cavestory_banner_data318
 cavestory_banner_data319
 cavestory_banner_data320
 cavestory_banner_data321
 cavestory_banner_data322
 cavestory_banner_data323
 cavestory_banner_data324
 cavestory_banner_data325
 cavestory_banner_data326
 cavestory_banner_data327
 cavestory_banner_data328
 cavestory_banner_data329
 cavestory_banner_data330
 cavestory_banner_data331
 cavestory_banner_data332
 cavestory_banner_data333
 cavestory_banner_data334
 cavestory_banner_data335
 cavestory_banner_data336

#addr RenderMap
 map0
 map1