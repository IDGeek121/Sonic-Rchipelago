# Sonic Rchipelago
This is a Sonic R (PC, 2004) Archipelago client implementation. It currently supports the following:

Goal:
* Win Radiant Emerald as Super Sonic (i.e. watch Super Sonic credits)
** Sonic must be unlocked
** All 7 Chaos Emeralds must be found
** The four original courses must be won to unlock Radiant Emerald

Locations:
* Sonic Tokens
* Chaos Emeralds
* Grand Prix wins
* Challenge Race wins

Items:
* Progressive Sonic Tokens
* Chaos Emeralds
* Character Unlocks
* 50 Rings (filler)

## How to use
[Refer to the APWorld documentation for instructions on how to use.](https://github.com/IDGeek121/Archipelago/blob/main/worlds/sonic_r/docs/setup_en.md)

## Building
The CMake project is based off ClassicSpeed's sadx-classic-randomizer. It depends on APCpp (modified to build statically, but I see there's an official static build branch that I'm going to test soon) and the Sonic R Mod Loader repository.

This CMake project has only been validated for building on Arch Linux with MinGW. Variables for cross compiling are set via the TC-mingw.cmake toolchain file. Other platforms with MinGW may work but will probably require creating a modified TC-mingw.cmake file. I plan to add support for MinGW on Windows via MSYS at some point in the future (and maybe MSVC, but then I'd have to change how I'm doing assembly).

With MinGW installed, in the root of this repository, run the following to configure the project:

    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./TC-mingw.cmake

Then, run the following to build the project under the "build" directory:

    cmake --build build

The output file is:

    ./build/Sonic-Rchipelago/Sonic-Rchipelago.dll

Supporting files for the mod loader are located in:

    ./mods/Sonic-Rchipelago/

When the DLL is built, it should be copied into this directory as well, so you can zip this directory to make releases or copy it directly into your Sonic R mods directory.

## AI disclosure
LLMs/Generative AI _have not been used_ in the development of this client or the AP world. The code is all home-grown, with all my inconsistent code style choices visible for the world to see.

I have not used LLMs for reverse-engineering Sonic R 2004 either. I realize that the 1998 reverse engineering project is out, but I have not taken a deep look at it. I personally would not be against using that as a reference to compare to similar parts of the 2004 release. This AP implementation is mostly an exercise for me though, so I want to push on by myself as far as I can.
