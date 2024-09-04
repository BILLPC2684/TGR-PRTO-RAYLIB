#!/bin/bash
windres ./bin/for-windows.rc ./bin/for-windows.rc.data
if gcc src/main.c -o TGR.exe -pg -I./src/include -I./bin/raylib/src -I./bin/raylib/src/external -I./bin/raylib/src/external/glfw/include -L./bin/raylib/src -L./bin ./bin/for-windows.rc.data -I./bin/cJSON -L./bin/cJSON -mwin32 -lraylib -lopengl32 -lgdi32 -lwinmm -DPLATFORM_DESKTOP -lcjson -lm -lpthread -g ./netlib.dll -I./bin/discord_game_sdk/c/ ./bin/discord_game_sdk/lib/x86_64/discord_game_sdk.dll -Wl,-Bstatic -Wno-int-conversion -Wno-implicit-function-declaration -Wno-incompatible-pointer-types -g -pg; then
 echo -e "\n\e[32;1m[✓] \e[33mBuild for TGR was \e[32;1mSuccessful\e[33m!\e[m"
else
 echo -e "\n\e[31;1m[X] \e[33mBuild for TGR was \e[31;1mUnsuccessful\e[33m...\e[m"
 echo "Please make sure the following libraries are installed at:"
 echo "\\raylib:           .\\bin\\raylib\\         https://github.com/raysan5/raylib"
 echo "\\cJSON:            .\\bin\\cJSON\\          https://github.com/DaveGamble/cJSON"
 echo "\\Discord Game SDK: .\\bin\\discord_game_sdk https://discord.com/developers/docs/developer-tools/game-sdk"
 echo "\\netlib.dll:       .\\                      https://github.com/univrsal/netlib/releases"
fi
