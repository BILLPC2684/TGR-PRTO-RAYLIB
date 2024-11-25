../customasm ./shader-01.asm --debug-iters &&\
./extract.py ./shader-01.bin ./GPU_TEST.asm &&\
../customasm ./GPU_TEST.asm -o ./GPU_TEST.tgr --debug-iters
