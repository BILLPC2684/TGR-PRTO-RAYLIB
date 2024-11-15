#!/bin/bash
if gcc src/main.c -o TGR -pg -I./src/include -lraylib -lcjson -lGL -lm -lpthread -ldl -lrt -lX11 -g -I./bin/raylib/src/ /usr/lib/libnetlib.so -I./bin/discord_game_sdk/c/ ./bin/discord_game_sdk/lib/x86_64/discord_game_sdk.so -Wformat-overflow=0 --debug; then
 echo -e "\n\e[32;1m[✓] \e[33mBuild for TGR was \e[32;1mSuccessful\e[33m!\e[m"
else
 echo -e "\n\e[31;1m[X] \e[33mBuild for TGR was \e[31;1mUnsuccessful\e[33m...\e[m"
 echo "Please make sure the following libraries are installed:"
 echo "\\raylib:                     https://github.com/raysan5/raylib"
 echo "\\cJSON:                      https://github.com/DaveGamble/cJSON"
 echo "\\Discord Game SDK: at ./bin/ https://discord.com/developers/docs/developer-tools/game-sdk"
 echo "\\libnetlib.so: at /usr/lib/  https://github.com/univrsal/netlib/releases"
fi
