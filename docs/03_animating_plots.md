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

(gif_animations)=
## GIF animations

<wiki:Gnuplot> supports a large number of [output formats (i.e. terminals)](http://gnuplot.info/docs_5.5/Terminals.html). A few of them can be embedded in a Jupyter Notebook: [gif](http://gnuplot.info/docs_5.5/loc20476.html), [jpeg](http://gnuplot.info/docs_5.5/loc21075.html), [png](http://gnuplot.info/docs_5.5/loc21756.html), [pngcairo](http://gnuplot.info/docs_5.5/loc21831.html), and last but not least [svg](http://gnuplot.info/docs_5.5/loc22578.html). The default terminal used by G3P for a new `g3p::gnuplot` instance in a Jupyter Notebook is [pngcairo](http://gnuplot.info/docs_5.5/loc21831.html).

Based on your plotting needs, you can switch to any other formats mentioned in the above list. One particularly important one is the [gif terminal](http://gnuplot.info/docs_5.5/loc20476.html) because it's the only format that supports animation out of the box. Let's change the [Simple Plot](https://gnuplot.sourceforge.net/demo_5.4/simple.html) to show a moving sine wave using [gif terminal](http://gnuplot.info/docs_5.5/loc20476.html):

::::{attention} Be patient ⏲️
:class: dropdown

Depending on the frame size and the number of frames, it may take a while for a GIF animation to appear in the notebook cell. No worries though, as the following example takes less than a second to appear. 😉
::::

```{code-cell} cpp

#include <g3p/gnuplot>
```
+++

```{code-cell} cpp
:label: sine_wave

g3p::gnuplot gp;
gp ("set term gif enhanced transparent animate")
   ("set nokey")
   ("set samples 200")
   ("set style data points");
for (float i = 0; i < 19; i += 0.2)
    gp("plot [-10:10] sin(x + %f) lw 2.0", i);
gp
```

(g3p_display)=
## Using `g3p::display()` in a loop

`g3p::display()` function has an optional 2{sup}`nd` argument for choosing if the previous output should be cleared or not. It's on by default, meaning if we don't provide it, the new plot will replace the previous one. We can use this feature to create a dynamic animation effect. The are two downsides for this approach:

- It can only be used in Jupyter notebooks. For instance, on a static web page like this you may only see the last frame. 
- It cannot be played in an endless loop.

That being said, here's the same sine wave animation implemented using `g3p::display()` in a loop:

```{code-cell} cpp
:label: sine_wave_g3p_display
:tags: [skip-execution]

#include <chrono> // for chrono_literals
#include <thread> // for sleep_for()

using namespace std::chrono_literals;

g3p::gnuplot gp;
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

We can use the approach mentioned in the [previous section](#g3p_display) to produce an interactive plot with xwidgets that shifts our sine wave using a slider.

```{code-cell} cpp
:label: sine_wave_interactive
:tags: [skip-execution]

#include <xwidgets/xslider.hpp>
#include <xwidgets/ximage.hpp>

g3p::gnuplot gp;
gp ("set nokey")
   ("set samples 200")
   ("set style data points");

auto slider = xw::slider<float>::initialize()
  .min(0.0f)
  .max(100.0f)
  .finalize();

auto plot = xw::image_from_file(gp.plotfile()).finalize();

XOBSERVE
(   slider
,   value
,   [&](const auto& s)
    {   std::ostringstream value;
        value << s.value;
        gp("plot [-10:10] sin(x + %s) lw 2.0", value.str().c_str()).sync();
        plot.value = xw::read_file(gp.plotfile());
        std::filesystem::path f(gp.plotfile());
        std::filesystem::remove(f);
        gp("reset errors;set output \"%s\"", gp.plotfile().c_str());
    }
);

slider.style().handle_color = "purple";
slider.value=0.0f;

plot.display();
slider.display();
```

::::{dropdown} Output
:open:
:label: slider_output
:::{figure} ./videos/slider.mp4
:label: slider_video
:::
::::
