# mercuryFLR
OpenGL/Qt5 app to create simple visualisation of FLRs in Mercury's magnetosphere.

## Host dependencies

This is a C++ Qt 5 project built with qmake. To build it from source, install:

- A C++ compiler and `make`
- Qt 5 development tools and headers, including Qt Widgets and qmake
- OpenGL development headers and libraries
- FLTK development headers
- GLUT development headers
- Cairo development headers
- `pkg-config`, used by qmake to find Cairo's include path and linker flags

On Debian or Ubuntu:

```sh
sudo apt install build-essential pkg-config qtbase5-dev qtbase5-dev-tools libgl1-mesa-dev libfltk1.3-dev freeglut3-dev libcairo2-dev
```

On Fedora:

```sh
sudo dnf install gcc-c++ make pkgconf-pkg-config qt5-qtbase-devel mesa-libGL-devel fltk-devel freeglut-devel cairo-devel
```

On Arch Linux:

```sh
sudo pacman -S base-devel pkgconf qt5-base mesa fltk freeglut cairo
```

## Build

Build with qmake from the repository root:

```sh
qmake mercuryFLR.pro
make
```

If your system provides multiple Qt versions, use the Qt 5 qmake explicitly:

```sh
qmake-qt5 mercuryFLR.pro
make
```

The build produces the `mercuryFLR` executable in the repository root.

## Run

```sh
./mercuryFLR
```
