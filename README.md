# Nucleus: Interpreter

Nucleus: Interpreter is a C cross-platform interpreter/execution environment for Windows, Linux, and OS X.
Nucleus is made available publicly under the
[MIT license](https://github.com/primordialmachine/nucleus-interpreter/blob/master/LICENSE.md)
on
[Github](https://github.com/primordialmachine/nucleus-interpreter).

Its current features encompass
- implicit memory management functionality through garbage collection
- advanced error raising and handling functionality.

Nucleus: Interpreter depends on [Nucleus](https://github.com/primordialmachine/nucleus).


## Building under Windows/Visual Studio
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake -G "Visual Studio 15 2017" CMakeLists.txt
```
to generate the project files for Win32.

Enter
```
cmake -G "Visual Studio 15 2017 Win64" CMakeLists.txt
```
to generate the project files for x64.

Open the files using Visual Studio 2017 and build all configurations.

To execute the unit tests for a particular configuration, enter
```
ctest -C <configuration>
```

```configuration``` is one of `Debug`, `Release`, `MinSizeRel`, `RelWithDebInfo`.

### Compilation options (Visual Studio)

#### `With-Static-Runtime`
For Visual Studio builds, the option `With-Static-Runtime=(ON|OFF)` is supported.
`ON` enables static linking with the C runtime, `OFF` enables dynamic linking with the runtime.
The default value is `ON`.

For example, to enable dynamic linking with the runtime enter
```
cmake -DWith-Static-Runtime=OFF CMakeLists.txt
```

## Building und Linux and Cygwin
Open the console.

Change the directory to the directory of this file.

Enter
```
cmake CMakeLists.txt 
```
to generate the project files.

Enter
```
make all
```
to build.

To execute the unit tests, enter
```
ctest
```

You can find the build products under `products/<platform>/(bin|lib)`
where `<platform>` is one of `x86` or `x64`.

### Compilation options (Linux and Cygwin)
For Linux and Cygwin builds, certain CMake options are supported.
The currently supported options are `With-Debug-Information=(ON|OFF)`
and `With-Optimizations=(ON|OFF)`.

For example, to enable both optimizations and debug information enter
```
cmake -DWith-Optimizations=ON -DWith-Debug-Information=ON CMakeLists.txt
```

## Out of source builds
The above build instruction for
Visual Studio 2017/Windows,
GCC/Linux, and
GCC/Cygwin
use CMake to generate project files for in-source builds.
However, it is recommended to use CMake to generate project files for out-of-source builds.

To generate project files for an out-of-source build,
simple enter some directory (which should be empty).
This directory is called the build directory.
In that directory enter the CMake command with options and generators to your liking as described above.
However, instead of writing `CMakeLists.txt` in the end, enter the path to the CMakeLists.txt file of
Nucleus - relative to your build directory.

For example, if you are in the source directory and you want the project files for Visual Studio to be generated
in `./build/visualstudio`, then simply enter `mkdir build; cd build; mkdir visualstudio`. Then tell CMake to
generate the build files in there by invokin

```
cmake -G "Visual Studio 15 2017 Win64" . ./../../CMakeLists.txt
```

## Documentation
The documentation of Nucleus: Interpreter is not yet publicly available.

#### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                                      | develop |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/nucleus-interpreter.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus-interpreter)                               |    -    |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/u49v9c293mcsnfos/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus-interpreter/branch/master) |    -    |
