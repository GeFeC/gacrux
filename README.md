# **Gacrux**
OpenGL-based 2D rendering framework

## **Installation And Building**
**Tools needed:**<br>
* C++17 Compiler
* CMake
* Make (or other build system)

**Clone repository**<br>
First, You have to clone this repository to Your local computer. Use this command to download framework with all needed dependencies:
```
git clone --recurse-submodule https://github.com/GeFeC/gacrux.git
```

**CMake**<br>
Open the downloaded file, create new folder in it, for example: `build` and use this CMake command in this folder to generate build system files:
```
cmake ..
```
If it doesn't work don't worry. You just need to specify the generator with `-G` flag. For example: If You use Make as Your build system, this generator is probably "MinGw Makefiles" or "Unix Makefiles". Here is how to build the project with the generator specified:
```
cmake .. -G "MinGw Makefiles"
```

**Building**<br>
Now the only thing You have to do is to build the entire project:
```
cmake --build .
```
And You're done! Your project should be built!