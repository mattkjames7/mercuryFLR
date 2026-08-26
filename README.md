# mercuryFLR
OpenGL/Qt5 app to create simple visualisation of FLRs in Mercury's magnetosphere.

## Host dependencies

This is a C++ Qt 5 project built with CMake. To build it from source, install:

- A C++ compiler and `make`
- CMake
- Qt 5 development headers, including Qt Widgets
- OpenGL development headers and libraries
- FLTK development headers
- GLUT development headers
- Cairo development headers
- `pkg-config`, used by CMake to find Cairo's include path and linker flags

On Debian or Ubuntu:

```sh
sudo apt install build-essential cmake pkg-config qtbase5-dev libgl1-mesa-dev libfltk1.3-dev freeglut3-dev libcairo2-dev
```

On Fedora:

```sh
sudo dnf install gcc-c++ make cmake pkgconf-pkg-config qt5-qtbase-devel mesa-libGL-devel fltk-devel freeglut-devel cairo-devel
```

On Arch Linux:

```sh
sudo pacman -S base-devel cmake pkgconf qt5-base mesa fltk freeglut cairo
```

## Build

Configure and build from the repository root:

```sh
cmake -S . -B build
cmake --build build
```

The build produces the `mercuryFLR` executable under `build/`.

For a parallel build, pass build-tool arguments after `--`:

```sh
cmake --build build -- -j$(nproc)
```

## Run

```sh
./build/mercuryFLR
```
