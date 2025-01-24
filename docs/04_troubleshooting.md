---
title: Troubleshooting
subtitle: "gnuplot::log() function and >> operator"
subject: g3p Quickstart Tutorial
description: Describes how to fix problems with plots.
kernelspec:
  name: xcpp17
  display_name: C++17
---

# Troubleshooting

---

While tinkering with a plot, there are times that you get an unexpected output or not anything at all. G3P provides various ways to communicate with `gnuplot` instance to get more information and those are the subjects of the next sections.

(auto-assertion)=
## Auto-assertion in Jupyter Notebook

One common mistake when using [`C++` (`<<`)](#cpp_convention) offered by G3P is omitting the newline character at the end of a command. If that happens in a notebook's cell, G3P automatically asserts with an error message:

```{code-cell} cpp
#include <g3p/gnuplot>
```
+++
```{code-cell} cpp
:label: missing_newline
:tags: [hide-output, raises-exception]

g3p::gnuplot gp;
gp << "set key left box"
   << "set samples 200\n"
   << "plot [-30:20] besj0(x)*0.12e1 with impulses, (x**besj0(x))-2.5 with points\n"
```

(log_function)=
## `gnuplot::log()` function 

The above error doesn't tell you anything about the source of the problem. To find out what went wrong, you have to run `gnuplot::log()` function:

```{code-cell} cpp
:label: log_output
:tags: [hide-output]

gp.log()
```

As you can see in the output there's a missing newline character between `box` and `set`. There are also some gibberish texts at end of the output that you can safely ignore as they're necessary for G3P normal operation.

## Getting `Gnuplot` version information

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
+++
+++
```{code-cell} cpp
:tags: [hide-output]
std::to_string(gp.version())
```

## `>>` operator
