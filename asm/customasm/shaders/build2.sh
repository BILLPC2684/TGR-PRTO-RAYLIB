../customasm ./shader-02.asm &&\
./extract.py ./shader-02.bin ./GPU_TEST2.asm &&\
../customasm ./GPU_TEST2.asm -o ./GPU_TEST2.tgr
