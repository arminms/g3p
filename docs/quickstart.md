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

(integration)=
## Integration

The single required file is [](https://github.com/arminms/g3p/blob/main/include/g3p/gnuplot) which is [released here](https://github.com/arminms/g3p/releases). You need to add:

```cpp
#include <g3p/gnuplot>
```

At the begining of your code and set the necessary switches to enable `C++17` (e.g. `-std=c++17` for [GCC](wiki:GNU_Compiler_Collection) and <wiki:Clang>).

(cmake)=
### CMake

Alternatively, you can use <wiki:CMake> 3.19+ to install G3P on your computer with the following commands and then including `<g3p/gnuplot>` in your program:

```bash
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

G3P exports a (namespaced) <wiki:CMake> target (`g3p::g3p`) and also <wiki:CMake> config scripts for downstream applications. This means that if G3P has been installed on a system, in case your project also relies on <wiki:CMake>, a better option is to use [`find_package()`](xref:cmake#command/find_package) in project's `CMakeLists.txt` as shown below:

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
### Rapid prototyping with *Jupyter*
A cool feature of G3P is the ability to embed plots in [Jupyter](wiki:Project_Jupyter) notebooks backed by <xref:xeus-cling> kernel for rapid prototyping:

```{image} ./images/xeus-cling.png
:label: xeus-cling
:align: center
```
---

#### Installing G3P in a xeus-cling environment

The easiest way to install [xeus-cling](xref:xeus-cling) is to create an environment named `cling` using [Mamba](xref:mamba#installation/mamba-installation):

```bash
mamba create -n cling
mamba activate cling
```

Then you can install [xeus-cling](xref:xeus-cling) in this environment and its dependencies:

```bash
mamba install xeus-cling -c conda-forge
```

Next, you can use `mamba env list` command to find where the `cling` environment is installed and use the following commands to install G3P in the `cling` environment:

```bash
wget https://github.com/arminms/g3p/releases/latest/download/install.zip
unzip install.zip -d <PATH_TO_CLING_ENV>
```

Now you can launch *Jupyter* with `jupyter lab` command and test your setup by copy/paste the following demo plot in a `C++17` notebook and pressing {kbd}`Shift`+{kbd}`Enter` in the last cell:

```{code-cell} cpp
:tags: [hide-output]
#include <g3p/gnuplot>

g3p::gnuplot gp;
gp << "set samples" << 200 << "\n"
   << "set style data points\n"
   << "plot [-10:10] sin(x),atan(x),cos(atan(x))\n"
```

![](xref:jupyter-xc#build_virtual_env)