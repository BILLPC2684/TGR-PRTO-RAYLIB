#!/bin/bash
echo -e "\e[34mChecking and Grabbing Missing Dependecies...\e[m"
cd bin
echo -e "\n\e[33mChecking raylib...\e[m"
if [ -d ./raylib ]; then
 echo -e "\e[32;1m[✓] raylib was found!\e[m"
else
 echo -e "\e[31;1m[X] raylib Was not found! \e[33mGrabbing now...\e[m"
 git clone https://github.com/raysan5/raylib/
 cd raylib/src
 mingw32-make PLATFORM=PLATFORM_DESKTOP
 echo -e "\n\e[32;1m[✓] raylib is now acquired!\e[m"
 cd ../..
fi
echo -e "\n\e[33mChecking cJSON...\e[m"
if [ -d ./cJSON ]; then
 echo -e "\e[32;1m[✓] cJSON was found!\e[m"
else
 echo -e "\e[31;1m[X] cJSON Was not found! \e[33mGrabbing now...\e[m"
 git clone https://github.com/DaveGamble/cJSON
 cd cJSON
 make
 echo -e "\n\e[32;1m[✓] cJSON is now acquired!\e[m"
 cd ..
fi
echo -e "\n\e[33mChecking netlib.dll...\e[m"
if [ -f ../netlib.dll ]; then
 echo -e "\e[32;1m[✓] netlib.dll was found!\e[m"
else
 echo -e "\e[31;1m[X] netlib.dll Was not found! \e[33mGrabbing now...\e[m"
 wget https://github.com/univrsal/netlib/releases/download/v0.2/netlib.0.2.win64.zip
 unzip netlib.0.2.win64.zip netlib.dll
 mv netlib.dll ..
 rm netlib.0.2.win64.zip
 echo -e "\n\e[32;1m[✓] netlib.dll is now acquired!\e[m"
fi
cd ..
echo -e "\n\e[32;1m[✓] All Dependencies were acquired!\e[m"
