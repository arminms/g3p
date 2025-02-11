---
title: Animating Plots
subtitle: GIF animation and beyond
subject: g3p Quickstart Tutorial
description: Describes different ways to animate plots.
kernelspec:
  name: xcpp17
  display_name: C++17
---

# Animating Plots

---

(animate_terminals)=
## Terminals supporting animation

<wiki:Gnuplot> supports a large number of [output formats (i.e. terminals)](http://gnuplot.info/docs_5.5/Terminals.html). For a compiled <wiki:C++> program, G3P doesn't change the default terminal and you can use any of them. On a desktop environment like <wiki:Linux>, it's most probably [Qt terminal](http://gnuplot.info/docs_5.5/loc22399.html). In that case, for animating your plots, the only thing you have to do is to start ploting in a loop and your animation will show up in a pop-up window.

:::{important} Run `bessel.cpp` 🛠️
:class: dropdown

Build and run [](https://github.com/arminms/g3p/blob/main/examples/bessel.cpp) on your computer using the following commands to see the bessel animation in a pop-up window:

```bash
git clone https://github.com/arminms/g3p.git
cd g3p/examples
cmake -S . -B build && cmake --build build
./bessel
```
:::

On the other hand, only few of the terminals can produce images/animations suitable for embedding in a [Jupyter Notebook](wiki:Project_Jupyter) (i.e. [gif](http://gnuplot.info/docs_5.5/loc20476.html), [jpeg](http://gnuplot.info/docs_5.5/loc21075.html), [png](http://gnuplot.info/docs_5.5/loc21756.html), [pngcairo](http://gnuplot.info/docs_5.5/loc21831.html), [svg](http://gnuplot.info/docs_5.5/loc22578.html) and recently [webp](http://gnuplot.info/docs_6.0/loc22961.html) [^1]) and G3P supports all of them. That's why when you create a new `g3p::gnuplot` instance in a [Jupyter Notebook](wiki:Project_Jupyter), in order to make the output embeddable in a notebook cell, G3P sets the terminal to [pngcairo](http://gnuplot.info/docs_5.5/loc21831.html) and pushes the default one by `set term push` command. But you can switch to any of the above-mentioned terminals based on your needs.

[^1]: <wiki:Gnuplot> *6.0* or higher.

:::{hint} Switching back
:class: dropdown
:open:

You can even switch back to the default desktop terminal to force the output appear in a pop-up window rather than a notebook cell by running the following:
```{code} cpp
gp("set term pop");
```
:::

[gif](#gif_animations) and [webp](#webp_animations) are the only two terminals that can embed an animation into a web page and we're going to cover them next.

(gif_animations)=
## GIF animations

Let's change the [Simple Plot](https://gnuplot.sourceforge.net/demo_5.4/simple.html) to show a moving sine wave using [gif terminal](http://gnuplot.info/docs_5.5/loc20476.html):

::::{attention} Be patient ⏳
:class: dropdown

Depending on the frame size and the number of frames, it may take a while for a GIF animation to appear in the notebook cell. No worries though, as the following example takes less than a second to appear. 😉
::::

```{code-cell} cpp
#include <g3p/gnuplot>

g3p::gnuplot gp;
```
+++

```{code-cell} cpp
:label: sine_wave_gif

gp ("set term gif enhanced transparent animate")
   ("set nokey")
   ("set samples 200")
   ("set style data points");
for (float i = 0; i < 6; i += 0.2)
    gp("plot [-10:10] sin(x + %f) lw 2.0", i);
gp
```

(webp_animations)=
## Animated webp

Starting version 6, <wiki:Gnuplot> added [webp terminal](http://gnuplot.info/docs_6.0/loc22961.html) that like [gif terminal](http://gnuplot.info/docs_5.5/loc20476.html) supports animations. The quality is generally better than animated GIF but you have to switch the transparency off as it doesn't clear the previous frames (probably a bug).
You also have to unset the output when you're finished with the frames to signal it's done.

Here's the way you can do the sine wave example using [webp terminal](http://gnuplot.info/docs_6.0/loc22961.html):


```{code-cell} cpp
:label: sine_wave_webp

gp ("set term webp enhanced notransparent animate delay 100");
// turning off transparency ------^

for (float i = 0; i < 6; i += 0.2)
    gp("plot [-10:10] sin(x + %f) lw 2.0", i);

// signaling the animation sequence is terminated
gp ("unset output") // <-- dropping semicolon to show the animation
```

::::{hint} Version-based switching of terminals 🔀
:label: version-based-switching
You can use `gnuplot::version()` function to switch between terminals based on the <wiki:Gnuplot> version:

``` cpp
gp( "set term %s enhanced animate" ), (gp.version() < 6) ? "gif" : "webp" );
```
::::

(g3p_display)=
## Using `g3p::display()` in a loop

`g3p::display()` function has an optional 2{sup}`nd` argument for choosing if the previous output should be cleared or not. It's on by default, meaning if we don't provide it, the new plot will replace the previous one. We can use this feature to create a dynamic animation effect. There are two downsides for this approach:

- It can only be used in _Jupyter Notebooks_.
- It cannot be played in an endless loop.

That being said, here's the same sine wave animation implemented using `g3p::display()` in a loop:

```{code-cell} cpp

// start with a new instance to reset the terminal back
g3p::gnuplot gp;
```
+++
```{code-cell} cpp
:label: sine_wave_g3p_display
:tags: [skip-execution]

#include <chrono> // for chrono_literals
#include <thread> // for sleep_for()

using namespace std::chrono_literals;

gp ("set nokey")
   ("set samples 200")
   ("set style data points");
for (float i = 0; i < 19; i += 0.2)
{   gp("plot [-10:10] sin(x + %f) lw 2.0", i);
    std::this_thread::sleep_for(100ms);
    g3p::display(gp);
}
```

(interactive_plots)=
## Interactive plots

We can use the approach mentioned in the [previous section](#g3p_display) to produce an interactive plot with [xwidgets](https://xwidgets.readthedocs.io/en/latest) that shifts our sine wave using a slider.

```{code-cell} cpp
:label: sine_wave_interactive
:tags: [skip-execution]

#include <xwidgets/xslider.hpp>
#include <xwidgets/ximage.hpp>

// enable the key
gp("set key");

// creating the slider widget
auto slider = xw::slider<float>::initialize()
  .min(0.0f)
  .max(100.0f)
  .finalize();

// converting the plot to a widget
auto plot = xw::image_from_file(gp.plotfile()).finalize();

XOBSERVE
(   slider
,   value
,   [&](const auto& s)
    {   std::ostringstream value;
        value << s.value;
        gp("plot [-10:10] sin(x + %s) lw 2.0", value.str().c_str()).sync();
        plot.value = xw::read_file(gp.plotfile());
        gp("unset output;set output \"%s\"", gp.plotfile().c_str());
    }
);

slider.style().handle_color = "purple";
slider.value=0.0f;

plot.display();
slider.display();
```

::::{grid} 2 2 2 2

:::{card}
:link: ./02_embedding_plot_data.ipynb
<div style="text-align: left">⬅️ Previous</div>
<div style="text-align: left">Embedding Plot Data</div>
:::

:::{card}
:link: ./04_troubleshooting.ipynb
<div style="text-align: right">Next ➡️</div>
<div style="text-align: right">Troubleshooting</div>
:::

::::
