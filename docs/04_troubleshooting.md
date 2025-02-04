---
title: Troubleshooting
subtitle: Communicating with Gnuplot
subject: g3p Quickstart Tutorial
description: Describes how to fix problems with plots.
kernelspec:
  name: xcpp17
  display_name: C++17
---

# Troubleshooting

---

While tinkering with a plot, there are times that you get an unexpected output or anything at all. G3P provides various ways to communicate with `gnuplot` instance to get more information and those are the subjects of the next sections.

(auto-assertion)=
## Auto-assertion in Jupyter Notebook

When you [display a plot](#display-the-plot) in a [Jupyter Notebook](wiki:Project_Jupyter), if there was an error reported by <wiki:Gnuplot>, G3P shows it as the output of the cell. Let's demonstrate this with an example.

One common mistake when using G3P's [C++ convention](#cpp_convention) is to forget the newline character at the end of a command. If that happens in a notebook's cell, G3P automatically asserts with an error message:

```{code-cell} cpp
#include <g3p/gnuplot>

g3p::gnuplot gp;
```
+++
```{code-cell} cpp
:label: missing_newline
:tags: [hide-output, raises-exception]

gp << "set key left box"
   << "set samples 200\n"
   << "plot [-30:20] besj0(x)*0.12e1 with impulses, (x**besj0(x))-2.5 with points\n"
```

(log_function)=
## `gnuplot::log()` function 

The above error doesn't tell you anything about where that happened. To find out what went wrong, you have to run `gnuplot::log()` function:

```{code-cell} cpp
:label: log_output
:tags: [hide-output]

gp.log()
```

As you can see in the output there's a missing newline character between `box` and `set`. There are also some gibberish texts at end of the output that you can safely ignore as they're necessary for G3P normal operation.

## Getting `Gnuplot` version information

Depending on the version of <wiki:Gnuplot>, the same sequence of commands may generate different plots. You can use `g3p::gnuplot`'s family of `version()` functions to switch to the right sequence of commands accordingly (for example, see [version-based switching of terminals](#version-based-switching)):

```{code-cell} cpp
:tags: [hide-output]
gp.version_string()
```
+++
```{code-cell} cpp
:tags: [hide-output]
gp.version()
```
+++
```{code-cell} cpp
:tags: [hide-output]
gp.patchlevel()
```

## Communicating with Gnuplot

<wiki:Gnuplot> has a long list of [`show`](http://gnuplot.info/docs_6.0/loc10320.html) commands that report various settings and also a [`print`](http://gnuplot.info/docs_6.0/loc10069.html) command that can show the value of an expression. Using `g3p::gnuplot` overloaded `>>` , you can extract the information you need.

For example, here's how you can find the current terminal:

```{code-cell} cpp
:tags: [hide-output]

std::string term;
gp("print GPVAL_TERM") >> 1 >> term;
term
```

The immediate number after the first `>>` is the number of lines to read from the end of the output.

For our next example, we use a multi-line output. We'll extract the rotation around x axis as a `float` value. To show the current view's settings, we have to use `show view` command in <wiki:Gnuplot>. Here's the verbatim output of `show view` command:
```
	view is 60 rot_x, 30 rot_z, 1 scale, 1 scale_z
		 axes are independently scaled
		 azimuth 0
 
```
So, we have to extract 4 lines. Then, starting from the first line, skip twice to get our value:

```{code-cell} cpp
:tags: [hide-output]

std::string skip;
float x_rot;
gp("show view") >> 4 >> skip >> skip >> x_rot;
x_rot
```

