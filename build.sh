#!/bin/bash
if gcc src/main.c -o TGR.o -lraylib -lcjson -lGL -lm -lpthread -ldl -lrt -lX11 -g; then
 echo -e "\n[✓] Build for TGR.o was Successful"
else
 echo -e "\n[X] Build for TGR.o was Unsuccessful"
fi
