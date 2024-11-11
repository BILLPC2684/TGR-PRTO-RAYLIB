handle SIGINT nostop print pass
set args ./asm/customasm/shaders/GPU_TEST2.tgr -dg
start
watch sys.MEM[0x9800000+0x1F80000-3]
