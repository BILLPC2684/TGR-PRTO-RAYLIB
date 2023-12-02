# TGR-PRTO-RAYLIB

TheGameRazer is a modern, retro styled 16-bit emulator(Fantasy Console) made in C using RayLib, this is still in prototype stages...

### Want to help Support this project?

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/billpc2684)

Every little bit helps!! :3

# Links:

Official Website: [Koranva-Forest.com](https://Koranva-Forest.com)

TGR Page: [Koranva-Forest/TheGameRazer](https://Koranva-Forest.com/TheGameRazer/)

Discord Server: [TheGameRazer Official Discord](https://discord.gg/PWAf8ek)

Offical ROMs: ~~[Koranva-Forest/TGR ROMs](https://Koranva-Forest.com/TheGameRazer/ROMs)~~ Not setted up yet! [404]

3rd Party ROMS: ~~[Koranva-Forest/feed/TGR_ROMS](https://Koranva-Forest.com/feed?search=#TGR&#ROM)~~ Not setted up yet! [404]



## Current Build: v0.0.47c Alpha (goal: v0.0.50x Alpha)

- Compile Errors: `No` Just some redudant warning from gcc

- Runnable Build: `Mostly` Functional, working on it...

- CPU Utilization: `Unstable` Functional, Not Finished Implementing Yet!! (still adding functionality to instructions)

- Stable Memory: `Yes` 128 MB of RAM | 64 MB of VRAM

- Has Video: `No` Using raylib window | GPU pipeline is Unfinished (will be worked on soon)

- Has Audio: `No` Requesting Help!!!

- Has Inputs: `Yes`  Using raylib input | Check the [Settings.cfg](./Settings.cfg) File (if generated)

- Has Network: `Somewhat` Networking is usable but not connected to Utilization

- SAV-able data: `Yes` Note: all ROMs ran will generate 8MiB files

- Compiler Status: `Inactive` This project is currently on hold, Please Wait...

### NOTE: if theres emulation errors, crashes or glitch out, check your ROM before reporting... (if someone else made the ROM then contact them first)



## Why does GitHub updates take so long?

- I myself(Maren/BILLPC2684) is mostly the only one working on this project, so it's a slow process

- Life issues and other projects blocking me from getting work done

### PLEASE BE PATIENT... Updates will come ASAP on schedule(hopefully)



## Are ROMs free?

Yes for the most part, now people can charge or setup a donation system for their ROMs

### We have no responsibility if your ROM gets hacked/modded or republished without your permission



# Before You Build

Please make sure the following libraries are installed at:

### Windows (Mingw)

Make sure you have `git`, `wget`, `tar` and mingw's `make` and `gcc` installed,

and have a bash supported terminal installed (like [git-cmd/bash](https://github.com/git-for-windows/git/releases) or [W64Devki [raylib recommends]](https://github.com/skeeto/w64devkit))

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

##### \\`cJSON`: `.\bin\cJSON\` [GitHub@DaveGamble/cJSON](https://github.com/DaveGamble/cJSON) (clone & compile)

```shell
git clone https://github.com/DaveGamble/cJSON
mkdir cJSON/build
cd cJSON/build
cmake ..
make
cd ../..
```

##### \\`netlib.dll`: `.\` [GitHub@univrsal/netlib](https://github.com/univrsal/netlib/releases) (extract)

```shell
wget https://github.com/univrsal/netlib/releases/download/v0.2/netlib.0.2.win64.zip
tar -zxvf netlib.0.2.win64.zip netlib.dll
mv netlib.dll ..

rm netlib.0.2.win64.zip # optional clean up

cd ..
```

### Linux

Make sure you have `git`, `build-essentials`, `wget` and `tar` installed

```shell
git clone https://github.com/BILLPC2684/TGR-PRTO-RAYLIB
cd TGR-PRTO-RAYLIB/bin
```

##### \\`raylib`: [GitHub@raysan5/raylib](https://github.com/raysan5/raylib/) (clone & compile)

```shell
# for ubuntu
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# for fedora
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic

# for Arch
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama

git clone https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
sudo make install
cd ../..

rm -rf raylib # optional clean up
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
tar -zxvf netlib.0.2.linux64.zip libnetlib.so
sudo mv libnetlib.so /usr/lib/

rm netlib.0.2.linux64.zip # optional clean up

cd ..
```

### Mac

i assume the same as linux, but i have no mac to test on...

# Compiling TheGameRazer:

### Windows

```shell
# just run
./build-mingw.sh

# which should producde
./TGR.exe
```

### Linux

```shell
# just run
./build.sh

# which should producde
./TGR
```

### Mac

i assume the same as linux, but i have no mac to test on...

## How to load a rom?

The Open Menu currently not implemented yet but will be soon

So until then, just drag and drop you `.tgr` files into it

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
