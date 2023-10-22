# RM2024-Internal-Template

## quick start guide

This is the internal template for RM2024 internal competition. To use this template, clone the template in your terminal with:

``` bash
git clone git@github.com:hkustenterprize/RM2024-Internal-Template.git
```

enter the directory with:

``` bash
cd RM2024-Internal-Template
```

compile with Makefile

``` bash
compiledb make -j
```

## Structure

- The directory `RM2024-Internal-Core` contains the drivers and control algorithm under `Drivers` and `Control` respectively.
- Within `./Core/Inc/AppConfig.h`, you could enable/disable certain drivers and configure them.
- Tasks are created in `./Core/Src/UserTask.cpp`.
