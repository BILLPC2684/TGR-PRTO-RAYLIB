GPU_X  = 0 ;16-bit X[1/4]
GPU_X2 = 1 ;16-bit X[2/4]
GPU_Y  = 2 ;16-bit Y[1/4]
GPU_Y2 = 3 ;16-bit Y[2/4]
GPU_IP = 4 ;28-bit Instuction Pointer (Write to to JUMP)
GPU_SP = 5 ;28-bit Stack Pointer (Read-Only)
GPU_sp = 6 ;28-bit Sprite Pointer (Read From)
GPU_cp = 7 ;28-bit Canvas Pointer (Write  To)
GPU_R  = 8 ;\
GPU_G  = 9 ; \8-bit RGBA Color Value
GPU_B  = 10; /
GPU_A  = 11;/
GPU_E  = 12;\
GPU_I  = 13; \28-bit General Purpose Registers
GPU_O  = 14; /
GPU_U  = 15;/

NULL = 0

SPRITE_CP = 0x00
SPRITE_CP8 = 0x01
SPRITE_RGB = 0x02
SPRITE_RGBA = 0x03
SPRITE_CP_CENTER = 0x04
SPRITE_CP8_CENTER = 0x05
SPRITE_RGB_CENTER = 0x06
SPRITE_RGBA_CENTER = 0x07

PALETTE_WRITE = 0
PALETTE_READ = 1

CPLength = 0x5A0
PtrLenth  = 40
OAMObjects = 13*0xFFFF
ProgramAddr = CPLength+PtrLenth+OAMObjects+1

#ruledef taylor_GPU {
 GPU_load {A}, {IMM} => 0x00 @ A`4 @ 0`8 @ IMM`28
 GPU_mov  {A}, {B}   => 0x01 @ A`4 @ B`4 @ 0`32
 
 GPU_add  {A}, {B},   {C} => 0x02 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_addi {A}, {IMM}, {C} => 0x02 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_sub  {A}, {B},   {C} => 0x03 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_subi {A}, {IMM}, {C} => 0x03 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_mul  {A}, {B},   {C} => 0x04 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_muli {A}, {IMM}, {C} => 0x04 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_div  {A}, {B},   {C} => 0x05 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_divi {A}, {IMM}, {C} => 0x05 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_mod  {A}, {B},   {C} => 0x06 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_modi {A}, {IMM}, {C} => 0x06 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_and  {A}, {B},   {C} => 0x07 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_andi {A}, {IMM}, {C} => 0x07 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_or   {A}, {B},   {C} => 0x08 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_ori  {A}, {IMM}, {C} => 0x08 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_xor  {A}, {B},   {C} => 0x09 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_xori {A}, {IMM}, {C} => 0x09 @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_bsl  {A}, {B},   {C} => 0x0A @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_bsli {A}, {IMM}, {C} => 0x0A @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_bsr  {A}, {B},   {C} => 0x0B @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_bsri {A}, {IMM}, {C} => 0x0B @ A`4 @ 0`4 @ C`4 @ IMM`28
 
 GPU_not  {A} => 0x0C @ A`4 @ 0`28
 
 GPU_cmpeq  {A},  {B},   {C} => 0x0D @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_cmpeqi {A},  {IMM}, {C} => 0x0D @ A`4 @ 0`4 @ C`4 @ 1`1 @  IMM`27
 
 GPU_cmplt  {A},  {B},   {C} => 0x0E @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_cmplti {A},  {IMM}, {C} => 0x0E @ A`4 @ 0`4 @ C`4 @ 1`1 @  IMM`27
 
 GPU_cmpgt  {A},  {B},   {C} => 0x0F @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_cmpgti {A},  {IMM}, {C} => 0x0F @ A`4 @ 0`4 @ C`4 @ 1`1 @  IMM`27
 
 GPU_split  {A}, {B}, {C}, 8 => 0x10 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_split  {A}, {B}, {C}, 4 => 0x10 @ A`4 @ B`4 @ C`4 @ 1`28
 
 GPU_comb   {A}, {B}, {C}, 8 => 0x11 @ A`4 @ B`4 @ C`4 @ 0`28
 GPU_comb   {A}, {B}, {C}, 4 => 0x11 @ A`4 @ B`4 @ C`4 @ 1`28
 
 GPU_wmem  {A}, {B}   => 0x12 @ A`4 @ B`4 @ 0`4 @ 0x4000000`28
 GPU_wmemi {A}, {IMM} => 0x12 @ A`4 @ 0`8 @ IMM`28
 
 GPU_rmem  {A}, {B}   => 0x13 @ A`4 @ B`4 @ 0`4 @ 0x4000000`28
 GPU_rmemi {A}, {IMM} => 0x13 @ A`4 @ 0`8 @ IMM`28
 
 GPU_halt  {A} => 0x14 @ A`4 @ 0`36
 GPU_hlt   {A} => 0x14 @ A`4 @ 0`36
 
 GPU_disp  {A}           => 0x15 @ A`4 @ 0`36
 GPU_disp  {A}, {B}      => 0x15 @ A`4 @ B`4 @ 1`32
 GPU_disp  {A}, {B}, {C} => 0x15 @ A`4 @ B`4 @ C`4 @ 2`28
 
 GPU_core  {A}, {B}, {IMM} => 0x16 @ A`4 @ B`4 @ 0`4 @ IMM`28
 
 GPU_push {A}   => 0x17 @ A`4 @ 0`36
 GPU_pop  {A}   => 0x18 @ A`4 @ 0`36
 
 GPU_call  {A}   => 0x19 @ A`4 @ 0`36
 GPU_calli {IMM} => 0x19 @ 0`12 @ IMM`28
 
 GPU_ret  => 0x1A @ 0`40
 
 GPU_swap => 0x1B @ 0`40
 
 GPU_led {IMM}         => 0x1C @ 0`12 @ IMM`28
 GPU_led {A}, {B}, {C} => 0x1C @ A`4 @ B`4 @ C`4 @ 0`28
 
 GPU_clk {A},{RESET} => 0x1D @ A`4 @ 0`8 @ 0`27 @ RESET`1
 
 GPU_wait {A} => 0x1E @ A`4 @ 0`36
 
 GPU_break {IMM} => 0x1F @ 0`12 @ IMM`28

 GPU_rgba {IMM}  => 0x20 @ 0`8 @ IMM`32

 GPU_layer {A} => 0x6E @ A`4 @ 0`36
 
 GPU_resl {A} => 0x6F @ A`4 @ 0`36
 
 GPU_plot => 0x70 @ 0`40
 
 GPU_line => 0x71 @ 0`40
 
 GPU_rect => 0x72 @ 0`40
 
 GPU_frect => 0x73 @ 0`40
 
 GPU_crcl => 0x74 @ 0`40
 
 GPU_fcrcl => 0x75 @ 0`40
 
 GPU_setout => 0x76 @ 0`40
 
 GPU_getout => 0x77 @ 0`40
 
 GPU_copy {A} => 0x78 @ A`4 @ 0`36
 
 GPU_palt {A}, {IMM} => 0x7C @ A`4 @ 0`8 @ IMM`28

 GPU_sprite {A}, {IMM} => 0x7D @ A`4 @ 0`8 @ IMM`28
 GPU_sprite {A}        => 0x7D @ A`4 @ 0`36

 GPU_setfps => 0x7E @ 0`40

 GPU_render => 0x7F @ 0`40
 
 GPU_nop => 0xFF @ 0`40
}
