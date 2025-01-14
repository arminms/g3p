---
title: Overview
description: g3p is a header-only Modern C++ interface library for gnuplot
---

g3p is tiny but mighty <wiki:header-only> modern <wiki:C++> interface library for <wiki:Gnuplot>. It is the most natural and intuitive way of adding <wiki:Gnuplot> support into any C++ program.

::::{important} Try g3p with Docker
:class: dropdown

If you have [Docker](wiki:Docker_(software)), you can start tinkering with g3p by running the prebuilt container:
```bash
docker run -p 8888:8888 -t -i asobhani/g3p
```
::::

::::{tip} Try g3p on Binder
:class: dropdown

If you don't have Docker, an easier but much slower (sometimes take several minutes to start) way is to click on [![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/arminms/g3p/HEAD?labpath=g3p_by_examples.ipynb) badge to launch it on [Binder](wiki:Binder_Project).
::::

## Cool g3p Features 🪄

::::{grid} 1 1 2 2

:::{card}
:header: 📊 [Rapid prototyping with Jupyter](./quickstart#jupyter-rapid-prototyping)
:footer: [Learn more »](./quickstart#jupyter-rapid-prototyping)

Using g3p you can embed plots in [Jupyter](wiki:Project_Jupyter) notebooks running on <xref:xeus-cling> kernel
:::

:::{card}
:header: 🏃 [Animated plots](./quickstart#jupyter-rapid-prototyping)
:footer: [Learn more »](./quickstart#jupyter-rapid-prototyping)

g3p supports embedding animated plots into [Jupyter](wiki:Project_Jupyter) notebooks in two different ways
:::

::::

(features)=
## Key Features
- 🖥️ Multiplatform (Linux/macOS/Windows)
- 💥 No dependencies (except <wiki:Gnuplot>)
- 🖇️ Header-only (only one header file)
- 🪶 Lightweight (~300 lines of code)
- ⚡ Fast (all i/o implemented with `C` API and `C++11` threading)
- 📊 Support embedding plots/animations in *Jupyter `C++` Notebooks* backed by [xeus-cling](https://github.com/jupyter-xeus/xeus-cling) kernel
- 🏫 Easy to learn. If you know <wiki:Gnuplot>, you're already set.
- 📥 Easily integrates with existing libraries and code (via CMake configs)
- ➡️ Support [fluent interface](https://en.wikipedia.org/wiki/Fluent_interface)
- 🔀 Support both C (`%d`,`%f`, ...) and C++ (`<<`) conventions for passing arguments to <wiki:Gnuplot>
- 🧪 Include [Catch2](https://github.com/catchorg/Catch2) unit tests
- 📖 Well documented
