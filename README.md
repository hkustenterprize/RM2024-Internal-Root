# RM2024-Internal-Template

## Quick start guide

This is a forked version of the RM2024 template. To keep up with the latest version, clone the project in your terminal with:

``` bash
git clone git@github.com:Hortaleza/RM2024-Internal-Root.git
```

enter the directory with:

``` bash
cd RM2024-Internal-Root
```

compile with Makefile

``` bash
make -j
```

## Structure

- The directory `RM2024-RDC-Core` contains the drivers and controller
- Within `./Core/Inc/AppConfig.h`, you could enable/disable certain drivers and configure them.
- Tasks are created in `./Core/Src/UserTask.cpp`.

