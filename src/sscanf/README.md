# sccanf

Testing parsing string with sscanf.

Trying the c method sscanf to understand why [bitwise](https://github.com/mellowcandle/bitwise) did not parse input on mac.

Turns out (which clang-tidy also warns for) that "%m" is not supported by all libc implementations. Bitwise project now updated!
