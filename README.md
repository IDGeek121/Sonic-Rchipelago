# Sonic Rchipelago
This is a Sonic R (PC, 2004) Archipelago client implementation. It currently supports the following:

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

# Building
The CMake project is based off ClassicSpeed's sadx-classic-randomizer. It depends on APCpp (modified to build statically, but I see there's an official static build branch that I'm going to test soon) and the Sonic R Mod Loader repository.

This CMake project has only been validated for building on Arch Linux with MinGW. Variables for cross compiling are set via the TC-mingw.cmake toolchain file. Other platforms with MinGW may work but will probably require creating a modified TC-mingw.cmake file. I plan to add support for MinGW on Windows via MSYS and MSVC at some point in the future.

With MinGW installed, in the root of this repository, run the following to configure the project:

    cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=./TC-mingw.cmake

Then, run the following to build the project under the "build" directory:

    cmake --build build

The output file is in at ./build/Sonic-Rchipelago/Sonic-Rchipelago.dll

Supporting files for the mod loader will be provided once this is ready for release, but you can make a config.ini, configschema.xml, and mod.ini based off the files here.
