# Nucleus: Interpreter

Nucleus: Interpreter is an interpreter for scripting languages and an execution environment for C programs fulfilling
certain requirements. Its primary purpose is that of a the execution environment. Such C programs attain      several
features in usually not provided by in plain C programs which (among others) are:

- implicit memory management functionality through garbage collection
- advanced error raising and handling functionality

## Building under Windows/Visual Studio
Visual Studio is currently *still* supported.

Open the console.

Change the directory to the directory of this file.

Enter
```
cmake -a Win32 CMakeLists.txt
```
to generate the project files for Win32.

Enter
```
cmake -a x64 CMakeLists.txt
```
to generate the project files for x64.

Open the files using Visual Studio 2017 and build all configurations.

To execute the unit tests for a particular configuration, enter
```
ctest -C <configuration>
```

```configuration``` is one of `Debug`, `Release`, `MinSizeRel`, `RelWithDebInfo`.

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

### Compilation options (Linux and Cygwin)
For Linux and Cygwin builds, certain CMake options are supported.
The currently supported options are `With-Debug-Information=(ON|OFF)`
and `With-Optimizations=(ON|OFF)`.

For example, to enable both optimizations and debug information enter
```
cmake -DWith-Optimizations=ON -DWith-Debug-Information=ON CMakeLists.txt
```

#### Continuous Integrations Status Maxtrix

|              | master                                                                                                                                                                                      | develop |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------- |
| **Travis**   | [![Build Status](https://travis-ci.org/primordialmachine/nucleus-interpreter.svg?branch=master)](https://travis-ci.org/primordialmachine/nucleus-interpreter)                               |    -    |
| **AppVeyor** | [![Build status](https://ci.appveyor.com/api/projects/status/u49v9c293mcsnfos/branch/master?svg=true)](https://ci.appveyor.com/project/primordialmachine/nucleus-interpreter/branch/master) |    -    |
