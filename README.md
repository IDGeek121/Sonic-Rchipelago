# Sonic Rchipelago
This is a Sonic R (PC, 2004) Archipelago client implementation. It currently supports the following:

Locations:
* Sonic Tokens
* Chaos Emeralds
* Grand Prix wins

Items:
* Progressive Sonic Tokens
* Chaos Emeralds
* 50 Rings (filler)

# Building
This CMake project only builds on Linux with MinGW, and while I've confirmed it runs on Windows, building has only been validated on Arch Linux.

The CMake project is based off ClassicSpeed's sadx-classic-randomizer. It depends on APCpp (modified to build statically, but I see there's an official static build branch that I'm going to test soon) and the Sonic R Mod Loader repository.

With MinGW installed, in the root of this repository, run the following to configure the project:

    cmake -S . -B build

Then, run the following to build the project under the "build" directory:

    cmake --build build

Supporting files for the mod loader will be provided once this is ready for release, but you can make a config.ini, configschema.xml, and mod.ini based off the files here.
