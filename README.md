# C++ Playground

 A playground for testing and playing with C++ snippet.

N.B. Clang-tidy will be run on all source files at build time.

## Usage

Eihter add a file in ```src/```or a full mini project in a subfiólder to ```src/```.

## Compiling

```bash
mkdir build && cd build
cmake ...
build
```

### Verbose build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
make
```

## Programs/projects

### helloworld.cpp

The mandatory hello world sample. Pretty useless..

### extra/

A slightly larget test, containing several cpp/h files and a separate CMakeLists.txt. Will build to a single executable.

## Contributing

Contributions are always welcome!

When contributing to this repository, please first discuss the change you wish to make via the issue tracker, email, or any other method with the owner of this repository before making a change.

Please note that we have a code of conduct, you are required to follow it in all your interactions with the project.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/frklan/[TBD]/tags).

## Authors

* **Fredrik Andersson** - *Initial work* - [frklan](https://github.com/frklan)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details