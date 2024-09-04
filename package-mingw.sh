#!/bin/bash
echo -e "\e[34mPreping for Packaging...\e[m"
libwinpthread_1_dll="C:\msys64\mingw64\bin\libwinpthread-1.dll"
if [ -f $libwinpthread_1_dll ]; then
 echo -e "\e[32;1m[✓] $libwinpthread_1_dll was found!\e[m"
 if [ -d ./win-package ]; then rm -vr ./win-package; fi
 if [ -f ./TGR-win.zip ]; then rm -v  ./TGR-win.zip; fi
 echo -e "\e[34mPackaging windows tar...\e[m"
 mkdir win-package
 cp TGR.exe ./win-package
 cp $libwinpthread_1_dll ./win-package
 cp discord_game_sdk.dll ./win-package
 cp netlib.dll ./win-package
 cp "bin/URL Links/Support the project on Ko-fi!.url" ./win-package
 cp "bin/URL Links/Official Github - TGR-PRTO-RAYLIB.url" ./win-package
 cp "bin/URL Links/Official Wiki - Fantasy Console Wiki.url" ./win-package
 cd win-package
 tar.exe -czvf ../TGR-win.tar.gz *
 cd ..
 echo -e "\e[32;1m[✓] Done! \e[33mOutput should be ./TGR-win.tar.gz\e[m"
else
 echo -e "\e[31;1m[X] $libwinpthread_1_dll Was not found!\e[m"
 echo "Please Edit this file with the correct path, and ensure mingw64 is installed!"
fi
