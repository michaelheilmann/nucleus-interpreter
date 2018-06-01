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

## Build instructions
  
Download or checkout the source code from [https://github.com/primordialmachine/nucleus-interpreter](https://github.com/primordialmachine/nucleus-interpreter).
See below for build instructions for some of the individual environments.

**The following build instructions and build options pertain to all products from the Nucleus series.
  All products accept the build options described here.
  The description of additional build options specific to a product are described in its documentation.
  The name of this product in the build system is `Nucleus.Interpreter`.*

* [Windows 10/Visual Studio Community 2017](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-windows-10-visual-studio-community-2017.md)
* [Windows 10/Cygwin/GCC](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-windows-10-cygwin-gcc.md)
* [Linux/GCC](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-linux-gcc.md)
* [Linux/Clang](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-linux-clang.md)
* [macOS/Clang](https://github.com/primordialmachine/nucleus/blob/master/documentation/building-under-macos-clang.md)


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
