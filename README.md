# A Simple Raycaster in CopperSpice

![Raycaster in Action](Bildschirmfoto_20260203_144348.png)

## Introduction

This project was primarily written for the exam of the Lecture : Object Orientierte Programmierung from Stephan Bökelmann at THGA.

The project contains a cpp program that demonstrates how a simple RaycasterEngine Operates.
The most well known Computergame that used a Raycasterengine is WolfenStein 3D which Released in 1992.
[Learn more about Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D)

How ever this game engine is not truly a 3d Engine. It's more an 2D Game where Walls are drawn Vertically,
so that the View of the Player looks 3D Like.

Due to time constraints, this Version only renders walls, floor and ceiling in the most simple way.
How ever, I plan to implement Textures, Sprites and Enemies in the Future.
[Learn more about Raycasting](https://lodev.org/cgtutor/raycasting.html)

The Current version of this Raycaster is very "demo only", so feel free to add or improve this Code. (But not at this repo)

## Disclaimer:

This is definitely not an good example for an good C++ programming Style,
some stuff is good implemented, some is definitely not. However,
I want to leave the Code as it is, so that people who take Lectures from
Stephan Bökelmann have an good example, what an OOP Project could be.
In the future, I may consider to do a fork, so if you want to improve something,
or add something. Do it there. (Excluding spelling or wrong data in the Readme)

## Compiling

For compilation you need to have CopperSpice Installed on your machine.
This setup is tested on Linux. There is no guarantee that the program runs on any other System than Linux.
[Don't know how to Install CopperSpice?](https://github.com/STEMgraph/abe720ad-32b4-4303-9b61-5875f592c05c/blob/master/README.md)

In order to run properly, the `CMakeLists.txt` file needs the path of your CopperSpice directories.
On the current `CMakeLists.txt` are the paths of my directories included. In order to run the program,
you have to change the following lines in the `CMakeLists.txt`:


Line 11:
```Line 11:
set(CopperSpice_DIR "/home/phil/cpplibs/cs2.0_libs/lib/cmake/CopperSpice") 
```

Line 63:
```Line 63:
include_directories(
    "/home/phil/cpplibs/cs2.0_libs/include"
    "/home/phil/cpplibs/cs2.0_libs/include/QtCore"
    "/home/phil/cpplibs/cs2.0_libs/include/QtGui"
    "/home/phil/cpplibs/cs2.0_libs/include/QtNetwork"
    "lib"

)
```

You also have to make sure that you have the following programs installed :
- CMake(Version 3.18 or newer)
- make
- gcc(version 12 or newer)



If you fill the prerequisites you are now able to build the program. 
Execute the following Commands in the `FistPersonCSLib` directory:

Creating the build directory:
```bash
cmake -B build
```
Compiling:
```bash
cmake --build build
```
Installing the CS needed binaries into the deploy directory:
```bash 
cmake --install build --prefix deploy
```
Running the program:
```bash
./deploy/CopperSpiceTest
```


