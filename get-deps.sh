#!/bin/bash

ID_LIKE=$(grep -w "ID_LIKE" /etc/os-release)
if [[ "$ID_LIKE" == "" ]]; then
 ID_LIKE=$(grep -w "ID" /etc/os-release)
fi
if [[ "$ID_LIKE" == *"debian"* ]]; then
 echo -e "\e[1;34mDebian Detected! Installing pre-dependencies via apt...\e[m"
 sudo apt install git gcc wget unzip cmake make libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev
elif [[ "$ID_LIKE" == *"fedora"* ]]; then
 echo -e "\e[1;34mFedora Detected! Installing pre-dependencies via dnf...\e[m"
 sudo dnf install git gcc wget unzip cmake make alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
elif [[ "$ID_LIKE" == *"arch"* ]]; then
 echo -e "\e[1;34mArch Detected! Installing pre-dependencies via pacman...\e[m"
 sudo pacman -S git gcc wget unzip cmake make alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
else
 echo -e "\e[31;1mWarning: Unknown System, script could error!\e[m"
fi

echo -e "\n\e[34mChecking and Grabbing Missing Dependecies...\e[m"
cd bin

echo -e "\n\e[33mChecking raylib...\e[m"
if [ -f /usr/local/include/raylib.h ]; then
 echo -e "\e[32;1m[✓] raylib was found!\e[m"
else
 echo -e "\e[31;1m[X] raylib was not found! \e[33mGrabbing now...\e[m"
 git clone https://github.com/raysan5/raylib/
 cd raylib/src
 make PLATFORM=PLATFORM_DESKTOP -j 8
 sudo make install
 echo -e "\n\e[32;1m[✓] raylib is now acquired!\e[m"
 cd ../..
 rm -rf raylib
fi

echo -e "\n\e[33mChecking cJSON...\e[m"
if [ -f /usr/include/cjson/cJSON.h ]; then
 echo -e "\e[32;1m[✓] cJSON was found!\e[m"
else
 echo -e "\e[31;1m[X] cJSON was not found! \e[33mGrabbing now...\e[m"
 git clone https://github.com/DaveGamble/cJSON
 mkdir cJSON/build
 cd cJSON/build
 cmake .. -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DCMAKE_INSTALL_PREFIX=/usr
 make
 sudo make DESTDIR=$pkgdir install
 echo -e "\n\e[32;1m[✓] cJSON is now acquired!\e[m"
 cd ../..
 rm -rf cJSON
fi

echo -e "\n\e[33mChecking libnetlib.so...\e[m"
if [ -f /usr/lib/libnetlib.so ]; then
 echo -e "\e[32;1m[✓] libnetlib.so was found!\e[m"
else
 echo -e "\e[31;1m[X] libnetlib.so was not found! \e[33mGrabbing now...\e[m"
 wget https://github.com/univrsal/netlib/releases/download/v0.2/netlib.0.2.linux64.zip
 unzip netlib.0.2.linux64.zip libnetlib.so
 sudo mv libnetlib.so /usr/lib/
 rm netlib.0.2.linux64.zip
 echo -e "\n\e[32;1m[✓] libnetlib.so is now acquired!\e[m"
fi

echo -e "\n\e[33mBONUS: customasm...\e[m"
if [ -f ../asm/customasm/customasm ]; then
 echo -e "\e[32;1m[✓] BONUS: CustomASM was found!\e[m"
else
 echo -e "\e[31;1m[X] BONUS: CustomASM was not found! \e[33mGrabbing now...\e[m"
 wget https://github.com/hlorenzi/customasm/archive/refs/tags/v0.13.4.zip
 unzip v0.13.4.zip
 cd customasm-0.13.4
 if ! cargo -v &> /dev/null; then
  curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
 fi
 cargo build
 cd ..
 mv customasm-0.13.4/target/debug/customasm ../asm/customasm/customasm
 rm -r v0.13.4.zip customasm-0.13.4
 echo -e "\n\e[32;1m[✓] customasm is now acquired!\e[m"
fi

cd ..
echo -e "\n\e[32;1m[✓] All Dependencies were acquired!\e[m"