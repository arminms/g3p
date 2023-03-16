# What is g3p?
`g3p` (**G**nu**P**lot **P**lus **P**lus) is a modern header-only C++ interface
library for [gnuplot](http://www.gnuplot.info/). It is the most natural and
intuitive way of adding `gnuplot` support into any C++ program.
## Features
- Multiplatform (Linux/macOS/Windows)
- No dependencies (except [gnuplot](http://www.gnuplot.info/))
- Header-only (only one header file)
- Lightweight (~100 lines of code)
- Easy to use (via CMake configs)
- Automatic detection of `gnuplot` path
- Support [fluent interface](https://en.wikipedia.org/wiki/Fluent_interface)
- Use C++ exceptions
<!-- - Provides Unit tests -->
<!-- - Well documented -->
## Example usage
```c++
#include <g3p/gnuplot.hpp>

int main(int argc, char* argv[])
{
        g3p::gnuplot gp;
        gp  // based on http://gnuplotting.org/animation-gif
            ("set palette rgb 3,9,9")
            ("unset key; unset colorbox; unset border; unset tics")
            ("set lmargin at screen 0.03")
            ("set bmargin at screen 0")
            ("set rmargin at screen 0.97")
            ("set tmargin at screen 1")
            ("set parametric")
            ("bessel(x,t) = besj0(x) * cos(2*pi*t)")
            ("n = 6 # number of zeros")
            ("k = (n*pi-1.0/4*pi)")
            ("u_0 = k + 1/(8*k) - 31/(384*k)**3 + 3779/(15360*k)**5")
            ("set urange [0:u_0]")
            ("set vrange[0:1.5*pi]")
            ("set cbrange [-1:1]")
            ("set zrange[-1:1]")
            ("set isosamples 200,100")
            ("set pm3d depthorder")
            ("set view 40,200");

        for (float t = 0.0f; t < 2.0f; t += 0.02f)
            gp("splot u*sin(v),u*cos(v),bessel(u,%f) w pm3d ls 1", t);
}
```
Here's the output:  

![bessel](example/bessel.gif)

## How to use it
`g3p` is a header only library. That means you can just copy
[`include/g3p/gnuplot.hpp`](include/g3p/gnuplot.hpp)
to your project or one of the designated system folders for headers (e.g.
`/usr/include` or `/usr/local/include` on Linux systems)
and start using by including it. That being said, this approach doesn't
benefit from `g3p` ability to find the right path to `gnuplot` program on
different platforms.

A better approach but not ideal is to build and install `g3p` using the
following commands on any platform and then including `<g3p/gnuplot.hpp>`: 
```bash
git clone https://github.com/arminms/g3p.git
cd g3p
cmake -S . -B build
cmake --build build
sudo cmake --install build
```
*The last command on Linux/macOS must be preceded by `sudo` and on Windows
must be run as an administrator.*

Ideally you should be using `g3p` through its CMake integration. `g3p` exports
a (namespaced) CMake target (`g3p::g3p`) and also CMake config
scripts for downstream applications. This means that if `g3p` has been installed
on the system using the above commands, it should be enough to do:
```cmake
find_package(g3p REQUIRED)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE g3p::g3p)
```
*There is no need to add `find_package(Gnuplot)` as CMake config provided by
`g3p` will take care of that.*

Another possibility is to mix `find_package()` with
[FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
available on CMake 3.14 and higher:
```cmake
include(FetchContent)
find_package(
  g3p CONFIG
  HINTS $ENV{HOME} $ENV{HOME}/.local /usr/local /usr
)
if(NOT g3p_DIR)
    message(STATUS "Fetching g3p library...")
    include(FetchContent)
    FetchContent_Declare(
      g3p
      GIT_REPOSITORY https://github.com/arminms/g3p.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(g3p)
endif()
```
The above approach first tries to find an installed version of `g3p` and if not
then tries to fetch it from the repository. You can find a complete
example of the above approach in the [`example`](example/) folder.

<!-- https://sourceforge.net/projects/gnuplot/files/gnuplot/ -->