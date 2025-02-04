---
title: Gallery
subtitle: Showcase of Cool Plots
subject: g3p Showcase
description: A showcase of all the plots in the guide and some more.
kernelspec:
  name: xcpp17
  display_name: C++17
---

`````{div}
:class: col-gutter-left align-middle
````{figure} #datablock_plot
:label: fig_datablock_plot
:width: 75%
````
`````
`````{div}
:class: col-body-right

## Matlab Peaks
````{dropdown} Code
```{embed} #datablock_plot
:remove-input: false
:remove-output: true
```
````
````{dropdown} Output
```{embed} #fig_datablock_plot
```
````
`````

`````{div}
:class: col-gutter-left align-middle
````{figure} #g3p_logo_plot
:label: fig_g3p_logo
:width: 75%
````
`````
`````{div}
:class: col-body-right

## G3P Logo
````{dropdown} Code
```{embed} #g3p_logo_plot
:remove-input: false
:remove-output: true
```
````
````{dropdown} Output
```{embed} #fig_g3p_logo
```
````
`````

`````{div}
:class: col-gutter-left align-middle
````{figure} #bessel_anim
:label: fig_bessel_anim
:width: 75%
````
`````
`````{div}
:class: col-body-right

## Bessel animation
````{dropdown} Code
```{embed} #bessel_anim
:remove-input: false
:remove-output: true
```
````
````{dropdown} Output
```{embed} #fig_bessel_anim
```
````
`````

%-- G3P Logo -------------------------------------------------------------------

```{code-cell} cpp
:tags: [remove-cell]

#include <g3p/gnuplot>

g3p::gnuplot gp;
gp ( "set border 31 linecolor '#555555'" )
   ( "set key textcolor '#555555' box lc '#555555'" )
   ( "set title tc '#555555'" )
   ( "set style line 101 lt 1 lc '#555555' dt '. '" )
   ( "set grid ls 101" )
;
```
+++
```{code-cell} cpp
:label: g3p_logo_plot
:tags: [remove-cell]
std::vector<float>
    g //x    y    z
    {   1,   1,   1
    , 8.3,   1,   1
    , 8.3,   1,   9
    ,   1,   1,   9
    ,   1,   1, 4.5
    , 8.3,   1, 4.5
    }
,   e //x    y    z
    {   1, 2.5,   9
    ,   1,   9,   9
    , 4.5,   9,   9
    , 4.5, 2.5,   9
    , 4.5,   9,   9
    ,   8,   9,   9
    ,   8, 2.5,   9
    }
,   p //x    y    z
    { 9.3,   1,   1
    , 9.3,   1,   9
    , 9.3,   9,   9
    , 9.3,   9, 4.5
    , 9.3,   1, 4.5
    }
;
auto lg = make_data_block(gp, g, 3);
auto l3 = make_data_block(gp, e, 3);
auto lp = make_data_block(gp, p, 3);
gp  << "set view 55,44,0.9,1.72\n"
    << "set border linecolor 'grey'\n"
    << "set border 895-32\n"
    << "set xrange [0:10]\n"
    << "set yrange [0:10]\n"
    << "set zrange [0:10]\n"
    << "set grid x y z\n"
    << "unset key\n"
    << "set style line 1 lt rgb 'red' lw 20\n"
    << "set style line 2 lt rgb 'green' lw 20\n"
    << "set style line 3 lt rgb 'blue' lw 20\n"
    << "set ticslevel 0\n"
    << "set format x ''; set format y ''; set format z ''\n"
;
gp << "splot"
    << lg << "u 1:2:3 w l ls 1,"
    << l3 << "u 1:2:3 w l ls 2,"
    << lp << "u 1:2:3 w l ls 3" 
    << g3p::endl
```
%-- Bessel ---------------------------------------------------------------------

```{code-cell} cpp
:label: bessel_anim
:tags: [remove-cell]
g3p::gnuplot gp;
gp ( "set term gif enhanced transparent animate" )
   ( "set palette rgb 3,9,9" )
   ( "unset key; unset colorbox; unset border; unset tics" )
   ( "set lmargin at screen 0.03" )
   ( "set bmargin at screen 0" )
   ( "set rmargin at screen 0.97" )
   ( "set tmargin at screen 1" )
   ( "set parametric" )
   // Bessel function, which is moving in time
   ( "bessel(x,t) = besj0(x) * cos(2*pi*t)" )
   // calculate the zeros for the bessel function (see Watson,
   // "A Treatise on the heory of Bessel Functions", 1966, page 505)
   ( "n = 6 # number of zeros" )
   ( "k = (n*pi-1.0/4*pi)" )
   ( "u_0 = k + 1/(8*k) - 31/(384*k)**3 + 3779/(15360*k)**5" )
   ( "set urange [0:u_0]" )
   ( "set vrange[0:1.5*pi]" )
   ( "set cbrange [-1:1]" )
   ( "set zrange[-1:1]" )
   ( "set isosamples 200,100" )
   ( "set pm3d depthorder" )
   ( "set view 40,200" )
;
for (float t = 0; t < 2; t += 0.02)
    gp ( "splot u*sin(v),u*cos(v),bessel(u,%f) w pm3d ls 1", t);

gp ("unset output")
```