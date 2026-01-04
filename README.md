# Cenwser (WIP)

A lightweight C++ browser project using **SDL2** for graphics and **libcurl** for HTTP requests.  
*HTML rendering is in progress — for now, it can fetch pages but will only show the raw html code.*

## Features
- Fetch web pages using HTTP (via libcurl)
- Basic window and input handling with SDL2
- Cross-platform build support
- Minimal dependencies

## Requirements
- C++17 compatible compiler (g++, clang++, or MSVC)
- [SDL2](https://www.libsdl.org/) development libraries
- [libcurl](https://curl.se/libcurl/) development libraries
- Make or another build system

### Installing Dependencies

#### Ubuntu
```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libcurl4-openssl-dev
```
### Windows (MSYS2)
```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-SDL2 mingw-w64-x86_64-curl
```
### MacOS (Homebrew)
```bash
brew install sdl2 curl
```
## How to build
Clone the repository:
```bash
https://github.com/CennacEh/Cenwser.git
cd Cenwser
```
Build the project with make:
```bash
make
```
> Make sure your compiler can find SDL2 and libcurl. Adjust include/lib paths in the Makefile if needed.
## License
This project is MIT Licensed
### Third party libraries used:
- [SDL2](https://www.libsdl.org/) – zlib License
- [libcurl](https://curl.se/libcurl/) - MIT License
