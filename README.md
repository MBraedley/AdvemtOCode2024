# Advent Of Code 2024

These are my solutions to the 2024 version of [Advent of Code](https://adventofcode.com/), written in C++

## Setup

This year, I've decided to start using third party libraries, in particular [Compile Time Regular Expressions](https://github.com/hanickadot/compile-time-regular-expressions),
and will be using the [Conan](https://conan.io/) package manager as I'm already famailiar with it and it allows me to use some Python utilities like [aocd](https://github.com/wimglenn/advent-of-code-data)

### Prerequisits:

- [Python](https://www.python.org/)
- [Conan](https://conan.io/) - `pip install conan`
- [CMake](https://cmake.org/) - `pip install cmake`
- [aocd](https://github.com/wimglenn/advent-of-code-data) - `pip install aocd`, `pip install browser-cookie3`

All other C++ dependencies (such as ctre) are gathered with Conan

### Build

Tested with Visual Studio 2022 Pro v17.11.6.  v17.12.1 will not properly load the folder as a CMake project, and conan dependencies won't be pulled in, however loading the generated solution should work.

Perform first time setup for aocd:  Log into Advent Of Code and run `aocd-token` to retrieve your personal authentication token.

Each day, perform a `conan install` to retrieve that day's input automatically.

```powershell
conan install .
cmake --preset conan-default
```

Open the folder in Visual Studio and build solution.

## Bugs and Issues

...will not be fixed.  Once a day has been solved the code will only receive, at best, cosmetic updates.
