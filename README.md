# RM2024-Internal-Template

## Quick start guide

This is the internal template for RM2024 internal competition. To use this template, clone the template in your terminal with:

``` bash
git clone git@github.com:hkustenterprize/RM2024-Internal-Root.git
```

enter the directory with:

``` bash
cd RM2024-Internal-Root
```

compile with Makefile

``` bash
make -j
```

If you are first cloning this repository. You need to push this template into your team's own repository.

```bash
git remote set-url origin your-respository.git
```

And push it 

```bash
git push
```

## Structure

- The directory `RM2024-RDC-Core` contains the drivers and controller
- Within `./Core/Inc/AppConfig.h`, you could enable/disable certain drivers and configure them.
- Tasks are created in `./Core/Src/UserTask.cpp`.

