ARGS="main.asm -o RAM_TEST.tgr"
OS=$(uname -o)
if [ $OS == "Msys" ]; then
 ../customasm.exe $ARGS
else
 ../customasm $ARGS
fi