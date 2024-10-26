# TGR-PRTO-RAYLIB
TheGameRazer is a modern, retro styled 16-bit emulator(Fantasy Console) made in C using RayLib, this is still in prototype stages...

### Want to help Support this project?
[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/BILLPC2684)

Every little bit helps!! :3
If you are a programmer, feel free to critice with a helpful push in the right direction!

# Links:
Official Website: [Koranva-Forest.com](https://Koranva-Forest.com)\
TGR Page: [Koranva-Forest/TheGameRazer](https://Koranva-Forest.com/TheGameRazer)\
Discord Server: [TheGameRazer Official Discord](https://discord.gg/PWAf8ek)\
Official Wiki Page: [FantasyConsole/TheGameRazer](https://fantasyconsoles.org/wiki/TheGameRazer)\
Official ROMs: ~~[Koranva-Forest/Shop/TGR-Cartriges](https://Koranva-Forest.com/shop/cartriges)~~ Not setted up yet! [404]\
3rd Party ROMS: ~~[Koranva-Forest/feed/TGR_ROMS](https://Koranva-Forest.com/feed?search=#TGR&#ROM)~~ Not setted up yet! [404]

## Current Build: v0.0.47e Alpha Nightly 5 (goal: v0.0.50x Alpha for Jun/2025)
- Compile Errors: `No`  Just some redudant warning from gcc
- Runnable Build: `Yes` Functional (For both windows and linux)
- CPU Utilization: `Unstable` Functional, Not Finished Implementing Yet!! (still adding functionality to instructions)
- Stable Memory: `Yes` 128 MB of RAM total | 64 MB of VRAM total
- Has Video: `Yes` Using raylib window | GPU pipeline is Unfinished (will be worked on soon)
- Has Audio: `No` Requesting Help!!!
- Has Inputs: `Yes`  Using raylib input | Check the [Settings.cfg]() File (if generated)
- Has Network: `Somewhat` Networking will be underway but not connected to Utilization
- SAV-able data: `Somewhat` Yes, haven't tested | Note: all ROMs ran will generate 8 MiB files
- Compiler Status: `Inactive` This project is currently on hold, Please Wait... Please use CustomASM for now

### NOTE: if theres emulation errors, crashes or glitch out, check your ROM before reporting... (if someone else made the ROM then contact them first)

## Can't find [Settings.cfg]()?
After Compiling you can simply run `./TGR(.exe) --configure` and it will return, the path of the config file!


## Why does GitHub updates take so long?
- I myself(Maren/BILLPC2684) is mostly the only one working on this project, so it's a slow process
- Life issues and other projects blocking me from getting work done
PLEASE BE PATIENT... Updates will come ASAP on schedule(hopefully)

### Are ROMs free?
Yes they can be, but this doesn't people can't setup a donation system for or straight up sell their ROMs
### We have no responsibility if your ROM gets hacked/modded or republished without your permission

# Before You Build
Please make sure the following libraries are installed at:

### Windows (Mingw)
Make sure you have `git`, `wget`, `unzip` and mingw's `make` and `gcc` installed,\
and have a bash supported terminal installed (like [git-cmd/bash [recommended]](https://github.com/git-for-windows/git/releases) or [W64Devki](https://github.com/skeeto/w64devkit))

#### * Automattic
Just run in your terminal:
```shell
./get-deps-mingw.sh
```

#### * Manual
Run these in your terminal:
```shell
git clone https://github.com/BILLPC2684/TGR-PRTO-RAYLIB
cd TGR-PRTO-RAYLIB/bin
```
And follow these steps for the following dependecies

##### \\`raylib` at `.\bin\raylib\` [GitHub@raysan5/raylib](https://github.com/raysan5/raylib/) (clone & compile)
```shell
git clone https://github.com/raysan5/raylib/ # or download and extract Source code from releases
cd raylib/src
mingw32-make PLATFORM=PLATFORM_DESKTOP
cd ../..
```

##### \\`Discord Game SDK`: `.\bin\raylib\` [Discord-Developer-Tools/Game-SDK]( https://discord.com/developers/docs/developer-tools/game-sdk) (extract)
```shell
wget https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip
unzip discord_game_sdk.zip -d discord_game_sdk
ln discord_game_sdk/lib/x86_64/discord_game_sdk.dll ../discord_game_sdk.dll #you neex this to run
rm discord_game_sdk.zip
```

##### \\`cJSON`: `.\bin\cJSON\` [GitHub@DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) (clone & compile)
```shell
git clone https://github.com/DaveGamble/cJSON
cd cJSON
mingw32-make
cd ..
```

##### \\`netlib.dll`: `.\` [GitHub@univrsal/netlib](https://github.com/univrsal/netlib/releases) (extract)

```shell
wget https://github.com/univrsal/netlib/releases/download/v0.2/netlib.0.2.win64.zip
unzip netlib.0.2.win64.zip netlib.dll
mv netlib.dll ..

rm netlib.0.2.win64.zip # optional clean up

cd ..
```
* If eny of these dependencies go missing, run: `./get-deps-mingw.sh` or redo the manual steps\
  `get-deps-mingw.sh` will automatticly grab and acquire missing dependencies!

### Linux
#### * Automatic
Just run in your terminal: (Currently only works for `Debian`/`Ubuntu`, `Fedora`, and `Arch`!)
```shell
./get-deps.sh
```

#### * Manual
Make sure you have `git`, `build-essentials`, `wget` and `unzip` installed\
Run these in your terminal:
```shell
git clone https://github.com/BILLPC2684/TGR-PRTO-RAYLIB
cd TGR-PRTO-RAYLIB/bin
```

##### \\`raylib`: [GitHub@raysan5/raylib](https://github.com/raysan5/raylib/) (clone & compile)
```shell
# for debian/ubuntu
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# for fedora
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic

# for Arch
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama

# for Other Please refure to looking up Raylib Dependencies for your system

git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP -j 8
sudo make install
cd ../..

rm -rf raylib # optional clean up
```

##### \\`Discord Game SDK` at `.\bin\raylib\` [Discord-Developer-Tools/Game-SDK](https://discord.com/developers/docs/developer-tools/game-sdk) (extract)
```shell
wget https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip
unzip discord_game_sdk.zip -d discord_game_sdk
rm discord_game_sdk.zip
```

##### \\`cJSON`: [GitHub@DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) (clone & compile)
```shell
git clone https://github.com/DaveGamble/cJSON
mkdir cJSON/build
cd cJSON/build
cmake .. -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make DESTDIR=$pkgdir install
cd ../..

rm -rf cJSON # optional clean up
```

##### \\`libnetlib.so`: `/usr/lib/` [GitHub@univrsal/netlib](https://github.com/univrsal/netlib/releases) (extract)
```shell
wget https://github.com/univrsal/netlib/releases/download/v0.2/netlib.0.2.linux64.zip
unzip netlib.0.2.linux64.zip libnetlib.so
sudo mv libnetlib.so /usr/lib/

rm netlib.0.2.linux64.zip # optional clean up

cd ..
```
- If eny of these dependencies go missing run: `./get-deps.sh` or redo the manual steps\
  `get-deps.sh` will automatticly grab and acquire missing dependencies!\
  (If your distro is not supported, make a issue please)

### Mac
I assume the same as linux, but i have no mac to test on...

# Compiling TheGameRazer:
### Windows
```shell
# just run
./build-mingw.sh

# which should produce
./TGR.exe
```

### Linux
```shell
# just run
./build.sh

# which should produce
./TGR
```

### Mac
i assume the same as linux, but i have no mac to test on...

## Whats with the "No Tape" text on the VCR like screen?
Back in the day we used to have these things called Video Cassettes, Video Tapes, or VHS'\
The goal of Tapes is to be a way to record your gameplay as a video, which you can play, rewind, fast forward and even overwrite\
Tapes will also act as rewindable savestates, when recording it takes a snapshot of the system after a period of time (atmost per 5 seconds)

## How to load a ROM?
The Open Menuis currently not implemented yet but will be soon\
You can open a ROM by dragging and dropping your `.tgr` file into the window\
or you can simply run it with TGR via terminal with: `./TGR(.exe) <.tgr>`

# How to make Programs Assembly Files and Compile ROMs:
Check out the WorkingInProgress Tutorials... (this should have everything you need)## Note: not all links are ready
- Tutorials: ~~[Koranva-Forest/TGR Tutorials](http://Koranva-Forest.com/TheGameRazer/Tutorials)~~ [404]
- 1. Assembly Basics: ~~[Koranva-Forest/TGR Tutorials/1_AssemblyBasics](http://Koranva-Forest.com/TheGameRazer/Tutorials/1_AssemblyBasics)~~ [404]
- 2. Create your First Program: ~~[Koranva-Forest/TGR Tutorials/2_FirstProgram](http://Koranva-Forest.com/TheGameRazer/Tutorials/2_FirstProgram)~~ [404]
- 3. Compile Your Program: ~~[Koranva-Forest/TGR Tutorials/3_CompileProgram](http://Koranva-Forest.com/TheGameRazer/Tutorials/3_CompileProgram)~~ [404]
- 4. Adding File To Program: ~~[Koranva-Forest/TGR Tutorials/4_AddingFiles](http://Koranva-Forest.com/TheGameRazer/Tutorials/4_AddingFiles)~~ [404]
- 5. Dealing with Errors: ~~[Koranva-Forest/TGR Tutorials/5_ErrorDealing](http://Koranva-Forest.com/TheGameRazer/Tutorials/5_ErrorDealing)~~ [404]
- 6. Assembler Flags: ~~[Koranva-Forest/TGR Tutorials/6_AssembleFlags](http://Koranva-Forest.com/TheGameRazer/Tutorials/6_AssembleFlags)~~ [404]
- 7. Interacting with Components: ~~[Koranva-Forest/TGR Tutorials/7_Components](http://Koranva-Forest.com/TheGameRazer/Tutorials/7_Components)~~ [404]
- 8. Still Need Help?: ~~[Koranva-Forest/TGR Tutorials/8_NeedHelp](http://Koranva-Forest.com/TheGameRazer/Tutorials/8_NeedHelp)~~ [404]
- Cheat Sheat: ~~[Koranva-Forest/TGR Tutorials/CheatSheat](http://Koranva-Forest.com/TheGameRazer/Tutorials/CheatSheat)~~ [404]
