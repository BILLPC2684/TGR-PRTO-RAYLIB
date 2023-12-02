#!/bin/bash
windres ./bin/for-windows.rc ./bin/for-windows.rc.data
if gcc src/main.c -o TGR.exe -I./src/include -Ibin/raylib/src -Ibin/raylib/src/external -Ibin/raylib/src/external/glfw/include -Lbin/raylib/src -L./bin ./bin/for-windows.rc.data -Ibin/cJSON -Lbin/cJSON -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP -lcjson -lm -lpthread -g ./netlib.dll; then
 echo -e "\n[✓] Build for TGR.exe was Successful"
else
 echo -e "\n[X] Build for TGR.exe was Unsuccessful"
 echo "Please make sure the following libraries are installed at:"
 echo "\\raylib:     .\\bin\\raylib\\ https://github.com/raysan5/raylib"
 echo "\\cJSON:      .\\bin\\cJSON\\  https://github.com/DaveGamble/cJSON"
 echo "\\netlib.dll: .\\            https://github.com/univrsal/netlib/releases"
fi
