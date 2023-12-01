A = 0
B = 1
C = 2
D = 3
E = 4
F = 5
G = 6
H = 7

a = 0
b = 1
c = 2
d = 3
e = 4
f = 5
g = 6
h = 7

#ruledef taylor {
    HEADER0 => "\x00TGR\x00==[REPLACE ME]==v00.00.00   \xFF"
    HEADER1 => "\x01TGR\x00==[REPLACE ME]==v00.00.00   [---======[REPLACE ME]======---]\xFF"
    HEADER2 => "\x02TGR\x00==[REPLACE ME]==v00.00.00   [---======[REPLACE ME]======---][---======[REPLACE ME]======---]\xFF"

    mov  {A}, {B}   => 0x00 @ A`4 @ B`4 @ 1`4 @ 0`28
    load {A}, {IMM} => 0x00 @ A`4 @ 0`8 @ IMM`28  

    add  {A}, {B},   {C} => 0x01 @ A`4 @ B`4 @ C`4 @ 0`28
    addi {A}, {IMM}, {C} => 0x01 @ A`4 @ 0`4 @ C`4 @ IMM`28

    sub  {A}, {B},   {C} => 0x02 @ A`4 @ B`4 @ C`4 @ 0`28
    subi {A}, {IMM}, {C} => 0x02 @ A`4 @ 0`4 @ C`4 @ IMM`28

    mul  {A}, {B},   {C} => 0x03 @ A`4 @ B`4 @ C`4 @ 0`28
    muli {A}, {IMM}, {C} => 0x03 @ A`4 @ 0`4 @ C`4 @ IMM`28

    div  {A}, {B},   {C} => 0x04 @ A`4 @ B`4 @ C`4 @ 0`28
    divi {A}, {IMM}, {C} => 0x04 @ A`4 @ 0`4 @ C`4 @ IMM`28

    mod  {A}, {B},   {C} => 0x05 @ A`4 @ B`4 @ C`4 @ 0`28
    modi {A}, {IMM}, {C} => 0x05 @ A`4 @ 0`4 @ C`4 @ IMM`28

    and  {A}, {B},   {C} => 0x06 @ A`4 @ B`4 @ C`4 @ 0`28
    andi {A}, {IMM}, {C} => 0x06 @ A`4 @ 0`4 @ C`4 @ IMM`28

    or   {A}, {B},   {C} => 0x07 @ A`4 @ B`4 @ C`4 @ 0`28
    ori  {A}, {IMM}, {C} => 0x07 @ A`4 @ 0`4 @ C`4 @ IMM`28

    xor  {A}, {B},   {C} => 0x08 @ A`4 @ B`4 @ C`4 @ 0`28
    xori {A}, {IMM}, {C} => 0x08 @ A`4 @ 0`4 @ C`4 @ IMM`28

    bsl  {A}, {B},   {C} => 0x09 @ A`4 @ B`4 @ C`4 @ 0`28
    bsli {A}, {IMM}, {C} => 0x09 @ A`4 @ 0`4 @ C`4 @ IMM`28

    bsr  {A}, {B},   {C} => 0x0A @ A`4 @ B`4 @ C`4 @ 0`28
    bsri {A}, {IMM}, {C} => 0x0A @ A`4 @ 0`4 @ C`4 @ IMM`28

    not  {A} => 0x0B @ A`4 @ 0`36

    flag {A} => 0x0C @ A`4 @ 0`36

    jmp  {A}, {B} => 0x0D @ A`4 @ B`4 @ 1`4 @ 0`28
    jmp  {IMM}    => 0x0D @ 0`12 @ IMM`28

    cmpeq  {A}, {B},   {C} => 0x0E @ A`4 @ B`4 @ C`4 @ 0`28
    cmpeqi {A}, {IMM}, {C} => 0x0E @ A`4 @ 0`4 @ C`4 @ IMM`28

    cmplt  {A}, {B},   {C} => 0x0F @ A`4 @ B`4 @ C`4 @ 0`28
    cmplti {A}, {IMM}, {C} => 0x0F @ A`4 @ 0`4 @ C`4 @ IMM`28

    cmpgt  {A}, {B},   {C} => 0x10 @ A`4 @ B`4 @ C`4 @ 0`28
    cmpgti {A}, {IMM}, {C} => 0x10 @ A`4 @ 0`4 @ C`4 @ IMM`28
    
    split  {A}, {B}, {C}, 8 => 0x11 @ A`4 @ B`4 @ C`4 @ 0`28
    split  {A}, {B}, {C}, 4 => 0x11 @ A`4 @ B`4 @ C`4 @ 1`28

    comb   {A}, {B}, {C}, 8 => 0x12 @ A`4 @ B`4 @ C`4 @ 0`28
    comb   {A}, {B}, {C}, 4 => 0x12 @ A`4 @ B`4 @ C`4 @ 1`28

    wmem  {A}, {B}, {C} => 0x13 @ A`4 @ B`4 @ C`4 @ 0xD800000
    wmem  {A}, {IMM}    => 0x13 @ A`4 @ 0`8 @ IMM`28

    rmem  {A}, {B}, {C} => 0x14 @ A`4 @ B`4 @ C`4 @ 0xD800000
    rmem  {A}, {IMM}    => 0x14 @ A`4 @ 0`8 @ IMM`28

    halt  {A} => 0x15 @ A`4 @ 0`36
    hlt   {A} => 0x15 @ A`4 @ 0`36

    disp  {A}           => 0x16 @ A`4 @ 0`36
    disp  {A}, {B}      => 0x16 @ A`4 @ B`4 @ 1`32
    disp  {A}, {B}, {C} => 0x16 @ A`4 @ B`4 @ C`4 @ 2`28

    ipout {A}, {B}      => 0x17 @ A`4 @ B`4 @ 0`32

    page  {A}, {IMM} => 0x18 @ A`4 @ 0`8 @ IMM`28

    core  {A}, {B}, {IMM} => 0x19 @ A`4 @ B`4 @ 0`4 @ IMM`28

    push {A}   => 0x1A @ A`4 @ 0`36
    pop  {A}   => 0x1B @ A`4 @ 0`36

    call {A}, {B} => 0x1C @ A`4 @ B`4 @ 0`32
    call {IMM}    => 0x1C @ 0`8 @ 1`4 @ IMM`28

    ret  => 0x1D @ 0`40

    swap => 0x1E @ 0`40

    led {IMM}         => 0x1F @ 0`12 @ IMM`28
    led {A}, {B}, {C} => 0x1F @ A`4 @ B`4 @ C`4 @ 2`28

    clk {A},{IMM} => 0x20 @ A`4 @ 0`8 @ IMM`28

    wait {A} => 0x21 @ A`4 @ 0`36

    nop => 0xFF @ 0`40
}
