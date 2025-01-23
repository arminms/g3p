---
title: g3p
subtitle: The Modern C++ interface to Gnuplot
description: g3p is a header-only Modern C++ interface library for gnuplot
---

[![GitHub Release](https://img.shields.io/github/v/release/arminms/g3p?logo=github&logoColor=lightgray)](https://github.com/arminms/g3p/releases)
[![Build and Test (Linux/macOS/Windows)](https://github.com/arminms/g3p/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/arminms/g3p/actions/workflows/cmake-multi-platform.yml)
[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=tutorial.ipynb)

---

::::{grid} 1 1 2 2

:::{grid-item}

g3p is a tiny but mighty <wiki:header-only> modern <wiki:C++> interface library for <wiki:Gnuplot>.

It's the most natural and intuitive way of adding <wiki:Gnuplot> support into any <wiki:C++> program.

It's also one of few <wiki:C++> libraries to support embedding of plots in [Jupyter](wiki:Project_Jupyter) notebooks.

:::

:::{grid-item}

```{image} images/g3p_logo.svg
```

:::

::::

:::::{aside}

::::{important} Try g3p with Docker
:class: dropdown

If you have [Docker](wiki:Docker_(software)), you can start tinkering with g3p by running the prebuilt container:
```bash
docker run -p 8888:8888 -it --rm asobhani/g3p
```
::::

:::::{seealso} Try g3p on Binder
:class: dropdown

An easier but slower way is to click the *launch binder* badge below to launch it on [Binder](wiki:Binder_Project) :

::::{grid} 2 2 2 2

:::{grid-item}
👉   [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=tutorial.ipynb)
:::

:::{grid-item}
_Be advised sometimes it takes several minutes to start!_
:::

::::

:::::

---

## Cool g3p Features 🪄

::::{grid} 1 1 2 2

:::{card}
:header: 📊 [Rapid prototyping with Jupyter](#jupyter-rapid-prototyping)
:footer: [Learn more »](#jupyter-rapid-prototyping)

Using g3p you can embed plots in [Jupyter](wiki:Project_Jupyter) notebooks running on <xref:xeus-cling> kernel.
:::

:::{card}
:header: 🏃 [Animated plots](#sine_wave)
:footer: [Learn more »](#gif_animations)

g3p supports embedding animated plots into [Jupyter Notebooks](wiki:Project_Jupyter) in several ways.
:::

:::{card}
:header: 🔀 [C/C++ conventions support](#conventions_tab)
:footer: [Learn more »](#conventions)

Both [`C` (`%d`,`%f`, ...)](#c_convention) and [`C++` (`<<`)](#cpp_convention) conventions for passing arguments to <wiki:Gnuplot> are supported. You can even [mix and match](#datablock_plot) them.
:::

:::{card}
:header: 📈 [Interactive plots in Jupyter](#sine_wave_interactive)
:footer: [Learn more »](#interactive_plots)

g3p in combination with [xwidgets](https://github.com/jupyter-xeus/xwidgets) can produce interactive plots in a [Jupyter Notebook](wiki:Project_Jupyter).
:::

::::

:::::{aside}
::::{note} Background 📚
:class: dropdown
:open:

> The initial idea about g3p sparked in my mind back in 2022 after attending a SHARCNET's General Interest webinar by my colleague Ge Baolai about [realtime display with Gnuplot](https://youtu.be/A9YPibAEXEE)
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
