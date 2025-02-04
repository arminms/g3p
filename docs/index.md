---
title: G3P
subtitle: The Modern C++ interface to Gnuplot
description: G3P is a header-only Modern C++ interface library for gnuplot
---

[![GitHub Release](https://img.shields.io/github/v/release/arminms/g3p?logo=github&logoColor=lightgray)](https://github.com/arminms/g3p/releases)
[![GitHub License](https://img.shields.io/github/license/arminms/g3p?logo=github&logoColor=lightgrey&color=green)](https://github.com/arminms/g3p/blob/main/LICENSE)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=01_the_basics.ipynb)

---

::::{grid} 1 1 2 2

:::{grid-item}

G3P is a tiny but mighty <wiki:header-only> modern <wiki:C++> interface library for <wiki:Gnuplot>.

It's the most natural and intuitive way of adding <wiki:Gnuplot> support into any <wiki:C++> program.

It's also one of few <wiki:C++> libraries to support embedding of plots in [Jupyter](wiki:Project_Jupyter) notebooks.

:::

:::{grid-item}

```{image} images/g3p_logo_bold.svg
```

:::

::::

:::::{aside}

::::{important} Try G3P in a Container
:class: dropdown
[Docker:](wiki:Docker_(software))
```bash
docker run -p 8888:8888 -it --rm asobhani/g3p
```
[Apptainer:](wiki:Singularity_(software))
```bash
apptainer run docker://asobhani/g3p:latest
```
::::

:::::{seealso} Try G3P on Binder
:class: dropdown
::::{grid} 2 2 2 2
:::{grid-item}
👉   [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=01_the_basics.ipynb)
:::
:::{grid-item}
_Be advised sometimes it takes several minutes to start!_
:::
::::

:::::

---

## Cool G3P Features 🪄

::::{grid} 1 1 2 2

:::{card}
:header: 🪐 [Rapid Prototyping with Jupyter](#jupyter-rapid-prototyping)
:footer: [Learn more »](#jupyter-rapid-prototyping)

Using G3P you can embed plots in [Jupyter](wiki:Project_Jupyter) notebooks running on [Xeus-Cling](xref:xeus-cling) kernel.
:::

:::{card}
:header: 🏃 [Animated Plots](#sine_wave_gif)
:footer: [Learn more »](#animate_terminals)

G3P supports embedding animated plots into [Jupyter Notebooks](wiki:Project_Jupyter) in several ways.
:::

:::{card}
:header: 📈 [Interactive Plots in Jupyter](#slider_output)
:footer: [Learn more »](#interactive_plots)

G3P in combination with [xwidgets](https://github.com/jupyter-xeus/xwidgets) can produce interactive plots in a [Jupyter Notebook](wiki:Project_Jupyter).
:::

:::{card}
:header: 🔀 [C & C++ Conventions Support](#conventions_tab)
:footer: [Learn more »](#conventions)

Both [`C` (`%d`,`%f`, ...)](#c_convention) and [`C++` (`<<`)](#cpp_convention) conventions for passing arguments to <wiki:Gnuplot> are supported. You can even [mix and match](#datablock_plot) them.
:::

::::

:::::{aside}
::::{note} Background 📚
:class: dropdown
:open:

> The initial idea about G3P sparked in my mind back in 2022 after attending a SHARCNET's General Interest webinar by my colleague Ge Baolai about [realtime display with Gnuplot](https://youtu.be/A9YPibAEXEE)
>
> -- Armin Sobhani

````{seealso} Watch the video 📺
:class: dropdown
:open:

```{iframe} https://www.youtube.com/embed/A9YPibAEXEE
:width: 100%
```
````
::::
:::::

---

(features)=
## Key Features 🥇
- 🖥️ Multiplatform (<wiki:Linux>, <wiki:macOS>, <wiki:Windows>)
- 💥 No dependencies (except <wiki:Gnuplot>)
- 🖇️ Header-only (only one header file)
- 🪶 Lightweight (~300 lines of code excluding comments)
- ⚡ Fast (all i/o implemented with `C` API and `C++11` threading)
- 📊 Support [embedding plots in Jupyter Notebooks](./quickstart#jupyter-rapid-prototyping)
- 🏫 Easy to learn. If you know <wiki:Gnuplot>, you're already set.
- 📥 Easily integrates with existing libraries and code (via <wiki:CMake> configs)
- ➡️ Support [fluent interface](https://en.wikipedia.org/wiki/Fluent_interface)
- 🔀 Support both [`C` (`%d`,`%f`, ...)](#c_convention) and [`C++` (`<<`)](#cpp_convention) conventions for passing arguments
- 🧪 Include unit tests
- 📖 Well documented
