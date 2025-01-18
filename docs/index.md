---
title: g3p
subtitle: The Modern C++ interface to Gnuplot
description: g3p is a header-only Modern C++ interface library for gnuplot
---

---

::::{grid} 1 1 2 2

:::{grid-item}

g3p is tiny but mighty <wiki:header-only> modern <wiki:C++> interface library for <wiki:Gnuplot>.

It's the most natural and intuitive way of adding <wiki:Gnuplot> support into any <wiki:C++> program.

It's also one of few <wiki:C++> libraries to support embedding of plots in [Jupyter](wiki:Project_Jupyter) notebooks.

:::

:::{grid-item}

```{image} images/g3p_logo.svg
```

:::

::::

::::{important} Try g3p with Docker
:class: dropdown

If you have [Docker](wiki:Docker_(software)), you can start tinkering with g3p by running the prebuilt container:
```bash
docker run -p 8888:8888 -t -i asobhani/g3p
```
::::

::::{seealso} Try g3p on Binder
:class: dropdown

If you don't have [Docker](wiki:Docker_(software)), an easier but much slower way (sometimes takes several minutes to start) is to click on [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=g3p_by_examples.ipynb) badge to launch it on [Binder](wiki:Binder_Project).

::::

---

## Cool g3p Features 🪄

::::{grid} 1 1 2 2

:::{card}
:header: 📊 [Rapid prototyping with Jupyter](#jupyter-rapid-prototyping)
:footer: [Learn more »](#jupyter-rapid-prototyping)

Using g3p you can embed plots in [Jupyter](wiki:Project_Jupyter) notebooks running on <xref:xeus-cling> kernel
:::

:::{card}
:header: 🏃 [Animated plots](#sine_wave)
:footer: [Learn more »](#gif_animations)

g3p supports embedding animated plots into [Jupyter Notebooks](wiki:Project_Jupyter) in two different ways
:::

:::{card}
:header: 🔀 [C/C++ conventions support](#conventions_tab)
:footer: [Learn more »](#conventions)

Both [`C` (`%d`,`%f`, ...)](#c_convention) and [`C++` (`<<`)](#cpp_convention) conventions for passing arguments to <wiki:Gnuplot> are supported
:::

::::

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
