#!/bin/bash
windres ./bin/for-windows.rc ./bin/for-windows.rc.data
if gcc src/main.c -o TGR.exe -I./src/include -Ic:/raylib/src -Ic:/raylib/src/external -Ic:/raylib/src/external/glfw/include -Lc:/raylib/src -L./bin ./bin/for-windows.rc.data -Ic:/cJSON -Lc:/cJSON -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP -lcjson -lm -lpthread -g ./netlib.dll; then
 echo -e "\n[✓] Build for TGR.exe was Successful"
else
 echo -e "\n[X] Build for TGR.exe was Unsuccessful"
 echo "Please make sure the following libraries are installed at:"
 echo "\\raylib:     C:\\raylib\\ https://github.com/raysan5/raylib/releases"
 echo "\\cJSON:      C:\\cJSON\\  https://github.com/DaveGamble/cJSON/releases"
 echo "\\netlib.dll: .\\         https://github.com/univrsal/netlib/releases"
fi
