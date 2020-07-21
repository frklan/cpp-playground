# C++ Playground

A playground for testing and playing with C++ snippet.

N.B. Clang-tidy will be run on all source files at build time.

## Usage

Either add a file in ```src/```or a full mini project in a subfolder to ```src/```.

## Compiling

```bash
mkdir build && cd build
cmake ...
build
```

### Verbose build

```bash
mkdir build && cd build
cmake -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON ..
make
```

### Debug build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Programs/projects

***N.B.*** Since this repo have grown quite a bit and have a fair amount of dependencies, we're starting with a clean slate. All the old code is save at commit [7e30b8314df55f8d53b44b16510979c3a1998225](https://github.com/frklan/cpp-playground/tree/7e30b8314df55f8d53b44b16510979c3a1998225).

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
