---
title: The Basics
subtitle: C and C++ conventions
subject: g3p Quickstart Tutorial
description: Basic steps and concepts to work with G3P.
kernelspec:
  name: xcpp17
  display_name: C++17
---

# The Basics

---

(header_file)=
## The header file

The whole G3P library implemented as a single header file that you have to include it once in your <wiki:C++> code:

```{code-cell} cpp

#include <g3p/gnuplot>
```

:::::{seealso} `cling` include paths
:class: dropdown

If G3P is not installed in a standard folder for headers, you can add it to the [cling include paths](xref:cling#chapters/grammar) using one of the following methods:

::::{tab-set}
:::{tab-item} #pragma

```cpp
#pragma cling add_include_path("G3P_INCLUDE_DIR")
```
:::

:::{tab-item} .(command)

```cpp
.I G3P_INCLUDE_DIR
```

:::

::::

:::::

(gp_instance)=
## `gnuplot` instance

Now you can start with a `gnuplot` instance that is defined in `g3p` namespace. We name our instance `gp`:

```{code-cell} cpp

g3p::gnuplot gp;
```

:::::{aside}

::::{seealso} Start learning Gnuplot 📚
:class: dropdown
:open:

Here are some good resources to start with:
- [Gnuplot on-line documentation](http://gnuplot.info/docs_6.0/gnuplot6.html)
- [Zipped Jupyter notebooks](https://alogus.com/g5script/servefile/JupyterVersions.zip/dl/) from [Gnuplot 5 book](https://alogus.com/g5script/gnuplot5/)
- [Gnuplotting](https://gnuplotting.org/)
::::
:::::

(conventions)=
## C and C++ conventions

There are two ways to send string literals (e.g. `gnuplot` commands)  and variables to a `g3p::gnuplot` instance: `C` and `C++` conventions. You can even [mix and match](#datablock_plot) them.

[`Gnuplot`](http://www.gnuplot.info) comes with lots of demos that you can find them [here](http://gnuplot.info/demos). For our first plot we use almost a verbatim copy of the [Simple Plots](https://gnuplot.sourceforge.net/demo_5.4/simple.html) demo. Here are the G3P versions using both conventions along with the original <wiki:Gnuplot> version for the sake of comparisons:

::::{tab-set}
:label: conventions_tab
:::{tab-item} C convention

```{code-cell} cpp
:label: c_convention

int count = 200;
gp ( "set title 'Simple Plots ( %d points )' font ',20'", count )
   ( "set key left box" )
   ( "set samples %d", count)
   ( "set style data points" )
   ( "plot [-10:10] sin(x), atan(x),cos(atan(x))" )
```
:::

:::{tab-item} C++ convention

```{code-cell} cpp
:label: cpp_convention

int count = 200;
gp << "set title 'Simple Plots (" << count << " points )' font ',20'\n"
   << "set key left box\n"
   << "set samples" << count << "\n"
   << "set style data points\n"
   << "plot [-10:10] sin(x), atan(x),cos(atan(x))\n"
```

:::

:::{tab-item} gnuplot

```{code-cell} Gnuplot
:label: gnuplot_version
:tags: [skip-execution]

set title "Simple Plots ( 200 Points )" font ",20"
set key left box
set samples 200
set style data points

plot [-10:10] sin(x),atan(x),cos(atan(x))
```
![](#c_convention)
:::

::::

::::{important} Displaying the plot 📈

As you may have noticed in the previous example, to display a plot, you need to have a `gnuplot` instance without a semicolon as the last element of a code cell. So, to replot the previous one, you can type the name of the `gnuplot` instance without semicolon and then {kbd}`Shift`+{kbd}`Enter`:

```{code-cell} cpp
:tags: [hide-output]

gp
```

Another way to achieve this is the `g3p::display()` function. A subtle distinction between using `g3p::display()` and omitting the last semicolon is that the latter results in a cell output including a prompt number in a Jupyter notebook, while the former only shows the plot. This behavior is consistent with the Python kernel implementation.

```{code-cell} cpp
:tags: [hide-output]

g3p::display(gp);
```

::::

(newline)=
## Newline

As you may noticed in the above examples, one important difference between `C++` and `C` *conventions* is that a newline character will be added automatically at the end of a string literal for the latter. In G3P, there are various ways to send a newline to a `g3p::gnuplot` instance:

- **Implicit**
  - String literal in parenthesis (i.e. overloaded function operator): `gp("...")`
- **Explicit**
  - String literal: `gp << "\n"`
  - End-of-line member function: `gp.endl()`
  - End-of-line manipulator: `gp << g3p::endl`

::::{attention} Don't use single quotes 🚫

Unlike <wiki:C++> streams, single quotes are not valid for sending characters and you should use double quotes. So, `gp << '\n'` doesn't compile:

```{code-cell} cpp
:label: single_quotes
:tags: [hide-output, raises-exception]

gp << '\n'
```

::::

::::{seealso}

Like [`std::endl`](https://en.cppreference.com/w/cpp/io/manip/endl) manipulator for <wiki:C++> streams, `g3p::endl` inserts a newline character and also flushes it by calling `gnuplot::flush()`, which doesn't happen for other methods. See [](#flush) for more information.
::::

Let's try all of the above methods in the same order for our next plot:

```{code-cell} cpp
:label: newline_plot
:tags: [hide-output]

count = 100;
gp (  "set title 'Simple Plots ( %d points )", count ); // implicit
gp << "set key right nobox" << "\n";                    // explicit - string literal
gp <<  "set samples" << count;
gp.endl();                                              // explicit - member function
gp << "plot [-pi/2:pi] cos(x),-(sin(x) > sin(x+1) ? sin(x) : sin(x+1))"
   << g3p::endl                                         // explicit - manipulator
```

(flush)=
## Flush

G3P uses *buffered i/o* to communicate with `g3p::gnuplot` instances. That means the plotting commands you use in your `C/C++` code are not necessarily received by the `g3p::gnuplot` instance at any moment unless you ensure the buffer is flushed. That's particularly important after executing [`plot`](http://gnuplot.info/docs_5.5/loc7782.html), [`splot`](http://gnuplot.info/docs_5.5/loc17814.html) or [`replot`](http://gnuplot.info/docs_5.5/loc9853.html) commands to ensure the plot is displayed. Like [newline](#newline), there are various ways in G3P to flush the buffers:

- **Implicit** (available only in [Jupyter Notebooks](xref:jupyter#what-is-a-notebook))
  - Omitting semicolon from a `g3p::gnuplot` instance as the last element of a cell or using `g3p::display()`
- **Explicit**
  - End-of-line member function: `gp.endl()`
  - Flush member function: `gp.flush()`
  - Log member function: `gp.log()`
  - Flush manipulator: `gp << g3p::flush`
