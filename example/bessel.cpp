//
// Copyright (c) 2023 Armin Sobhani
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include <iostream>
#include <g3p/gnuplot.hpp>

int main(int argc, char* argv[])
{
    try
    {
        g3p::gnuplot gp;
        gp
        // based on https://gnuplotting.org/animation-gif/
        ("set palette rgb 3,9,9")
        ("unset key; unset colorbox; unset border; unset tics")
        ("set lmargin at screen 0.03")
        ("set bmargin at screen 0")
        ("set rmargin at screen 0.97")
        ("set tmargin at screen 1")
        ("set parametric")

        // Bessel function, which is moving in time
        ("bessel(x,t) = besj0(x) * cos(2*pi*t)")

        // calculate the zeros for the bessel function (see Watson,
        // "A Treatise on the heory of Bessel Functions", 1966, page 505)
        ("n = 6 # number of zeros")
        ("k = (n*pi-1.0/4*pi)")
        ("u_0 = k + 1/(8*k) - 31/(384*k)**3 + 3779/(15360*k)**5")
        ("set urange [0:u_0]")
        ("set vrange[0:1.5*pi]")
        ("set cbrange [-1:1]")
        ("set zrange[-1:1]")
        ("set isosamples 200,100")
        ("set pm3d depthorder")
        ("set view 40,200");

        for (float t = 0.0f; t < 2.0f; t += 0.02f)
            gp("splot u*sin(v),u*cos(v),bessel(u,%f) w pm3d ls 1", t);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}