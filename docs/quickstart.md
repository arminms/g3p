---
title: Start using G3P
subject: g3p Quickstart
subtitle: CMake integration and rapid prototyping with Jupyter
short_title: Get Started
description: G3P is available through GitHub.
kernelspec:
  name: xcpp17
  display_name: C++17
---

# Start using G3P

---

## Requirements

- <wiki:Gnuplot> (4 or higher) must be already installed and added to the `$PATH` environment variable
- <wiki:C++> compiler supporting the `C++17` standard (e.g. [GCC](wiki:GNU_Compiler_Collection) 9.3 or higher)

(developing_with_g3p)=
## Developing with G3P

The single required file is [](https://github.com/arminms/g3p/blob/main/include/g3p/gnuplot) which is [released here](https://github.com/arminms/g3p/releases). You need to add:

```cpp
#include <g3p/gnuplot>
```

At the begining of your code and set the necessary switches to enable `C++17` (e.g. `-std=c++17` for [GCC](wiki:GNU_Compiler_Collection) and <wiki:Clang>).

(cmake)=
### CMake

Alternatively, you can use <wiki:CMake> 3.19+ to install G3P on your computer with the following commands and then include `<g3p/gnuplot>` in your program:

```{code} bash
:label: cmake-build
git clone https://github.com/arminms/g3p.git
cd g3p
cmake -S . -B build && cmake --build build
cmake --install build
```

::::{attention} Installing into non system folders 🖥️

The last command on <wiki:Linux> or <wiki:macOS> must be preceded by `sudo`, and on <wiki:Windows> must be run as an administrator unless you add `--prefix` option at the end to change the default installation path to a none system folder (e.g. `cmake --install build --prefix ~/.local`).
::::

::::{hint} Running unit tests 🧪
:class: dropdown

Use the following command after building if you like to run the unit tests as well:

```bash
cmake --build build -t test
```
::::

G3P exports a (namespaced) <wiki:CMake> target (`g3p::g3p`) and also <wiki:CMake> config scripts for downstream applications. This means if your project also relies on <wiki:CMake> and G3P has been installed on your system, a better option is to use [`find_package()`](xref:cmake#command/find_package) in the project's `CMakeLists.txt` as shown below:

```cmake
find_package(g3p REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE g3p::g3p)
```

::::{note} Embedding with CMake 📥

To embed the library directly into an existing <wiki:CMake> project, you can mix [`find_package()`](xref:cmake#command/find_package) with [`FetchContent`](xref:cmake#module/FetchContent) module available on <wiki:CMake> `3.14` and higher:

```cmake
include(FetchContent)
find_package(g3p CONFIG)
if(NOT g3p_FOUND)
    FetchContent_Declare(
      g3p
      GIT_REPOSITORY https://github.com/arminms/g3p.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(g3p)
endif()
```

The above approach first tries to find an installed version of G3P and if it cannot then tries to fetch it from the repository. You can find a complete example of the above approach in the [`example`](https://github.com/arminms/g3p/blob/main/example/CMakeLists.txt#L5-L19) folder.
::::

(jupyter-rapid-prototyping)=
## Rapid prototyping with *Jupyter*
One of the coolest features of G3P is the ability to embed plots in [Jupyter](wiki:Project_Jupyter) notebooks with [Xeus-Cling](xref:xeus-cling) kernel for rapid prototyping. That's a very convenient way to tinker with each and every plot parameters to get the desired output without the hassle of compilation for each step of the way.

```{image} ./images/xeus-cling.png
:label: xeus-cling
:align: center
```

---

Depending on your preference, you can use one/all of the following methods to work with G3P in Jupyter.

### Creating a Conda/Mamba environment

The easiest way to install [Xeus-Cling](xref:xeus-cling) is to create an environment named `cling` using [Mamba](xref:mamba#installation/mamba-installation):

```bash
mamba create -n cling
mamba activate cling
```

Then you can install [Xeus-Cling](xref:xeus-cling) in this environment and its dependencies:

```bash
mamba install xeus-cling -c conda-forge
```

Next, you can use `mamba env list` command to find where the `cling` environment is installed and use the following commands to install G3P in the `cling` environment:

```{code} bash
:label: g3p-zip
wget https://github.com/arminms/g3p/releases/latest/download/install.zip
unzip install.zip -d <PATH/TO/CLING/ENV>
```

Now you can launch *Jupyter* with `jupyter lab` command and test your setup by copy/pasting the following demo plot in a `C++17` notebook and pressing {kbd}`Shift`+{kbd}`Enter` in the last cell:

```{code-cell} cpp
:tags: [hide-output]
#include <g3p/gnuplot>

g3p::gnuplot gp;
gp << "set samples" << 200 << "\n"
   << "set style data points\n"
   << "plot [-10:10] sin(x),atan(x),cos(atan(x))\n"
```

(python_ve)=
### Creating a Python environment

If you're more adventurous, you can build [Xeus-Cling](xref:xeus-cling) along with all the dependencies from the source in a Python virtual environment using the bash script available [here](xref:jupyter-xc#build_virtual_env). As a bonus, you will get a newer version of `cling` (`1.0~dev`) based on `llvm 13.0` that supports <wiki:OpenMP> and <wiki:CUDA>.

Once done, you can install G3P in your Python environment by unpacking the [zip file](#g3p-zip) or using [CMake](#cmake-build):

```bash
git clone https://github.com/arminms/g3p.git
cd g3p
cmake -S . -B build && cmake --build build
cmake --install build --prefix /path/to/python/virtual/environment
```

The same approach was used to build the container images below.

(containers)=
### Using pre-built container images

#### [Docker](wiki:Docker_(software))
```bash
docker run -p 8888:8888 -it --rm asobhani/g3p
```
If you like to work with your notebooks outside the container (e.g. current folder), you can use the following command instead:
```bash
docker run -v $PWD:/home/jovyan -p 8888:8888 -it --rm asobhani/g3p
```
You can also use the above container image as the starting point for your custom-made docker image (e.g. `FROM asobhani/g3p:latest`).

#### [Apptainer](wiki:Singularity_(software))

If you're working on an HPC cluster, you can use [Apptainer](wiki:Singularity_(software)) instead:

```bash
apptainer run docker://asobhani/g3p:latest
```
