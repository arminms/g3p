//
// Copyright (c) 2023-24 Armin Sobhani
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
#include <vector>

#include <g3p/gnuplot>

int main(int argc, char* argv[])
{
    g3p::gnuplot gp;
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
    gp << "set view ,,,1.45\n"
       << "set border linecolor 'grey'\n"
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
       << g3p::endl;
    std::getchar();
}
