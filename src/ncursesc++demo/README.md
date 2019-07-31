# ncurses c++

This is the "official" c++ demo that comes with the ncurses dist, slightly modified to compile stand alone. There's something that broke while I copied it so it's not quite working. However it still gives a few hints how the C++ wrapper can be used.

## Compiling

Building is done via the main build script, like so

```bash
git checkout demo/ncursesc++demo
mkdir build && cd build
cmake ...
build ncursesc++demo
```
