# Yet Another Project Template (YAPT)

This is a C++ project template with gitlab CI integration, unit tests, coverage, CMake, benchmark.
Everything to do the better projects the world has ever met.

# Installation Guide

We assume that you already have installed a decent version of **CMake** and **Git** on your computer.

## Install dependency libraries
You need to install the following dependencies:
- [Google Test](https://github.com/google/googletest)
- [Google Bench](https://github.com/google/benchmark)

You can either follow the official tutorials, or abruptly copy/paste the following into your terminal:

```bash
git clone https://github.com/google/benchmark.git
git clone https://github.com/google/googletest.git benchmark/googletest
cd benchmark
mkdir build && cd build
cmake ../ -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON
make -j 12
sudo make install
```
