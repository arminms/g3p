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
#ifndef _G3P_GNUPLOT_HPP_
#define _G3P_GNUPLOT_HPP_

#include <cstdio>
#include <stdexcept>
#include <string>

#ifndef GNUPLOT
#   define GNUPLOT "gnuplot"
#endif  // GNUPLOT
namespace g3p {
class gnuplot
{
    FILE* _gp;

public:
    gnuplot(bool persist = true)
    {
#ifdef _MSC_VER
        _gp = _popen
        (   persist
        ?   "GNUPLOT -persist"
        :   "GNUPLOT"
        ,   "w"
        );
        if (nullptr == _gp)
            throw std::domain_error("GNUPLOT -- failed");
#else
        _gp = popen
        (   persist
        ?   GNUPLOT" -persist"
        :   GNUPLOT
        ,   "w"
        );
        if (nullptr == _gp)
            throw std::domain_error(GNUPLOT" -- failed");
#endif
    }

    ~gnuplot()
#ifdef _MSC_VER
    {   if (_gp) _pclose(_gp);   }
#else
    {   if (_gp) pclose(_gp);   }
#endif

#ifdef __GNUG__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat-security"
#endif
    template<typename... Args>
    gnuplot& operator() (Args&&... args)
    {   fprintf(_gp, std::forward<Args>(args)...);
        fprintf(_gp, "\n");
        return *this;
    }
#ifdef __GNUG__
#   pragma GCC diagnostic pop
#endif

    template<typename T>
    gnuplot& operator<< (T arg)
    {   fprintf(_gp, " %s", std::to_string(arg).c_str());
        return *this;
    }

    gnuplot& endl()
    {   fprintf(_gp, "\n");
        return *this;
    }

    gnuplot& end()
    {   fprintf(_gp, "e\n");
        return *this;
    }

    gnuplot& flush()
    {   fflush(_gp);
        return *this;
    }

    template<typename InputT1, typename InputT2>
    gnuplot& interleave(InputT1 x, InputT2 y, size_t n)
    {   for (size_t i = 0; i < n; ++i)
        {   fprintf
            (   _gp
            ,   "%s %s\n"
            ,   std::to_string(x[i]).c_str()
            ,   std::to_string(y[i]).c_str()
            );
        }
        return *this;
    }

    template
    <   typename InputT1
    ,   typename InputT2
    ,   typename InputT3
    >
    gnuplot& interleave
    (   InputT1 x
    ,   InputT2 y
    ,   InputT3 z
    ,   size_t n
    ,   size_t s = 0
    )
    {   for (size_t i = 0; i < n; ++i)
        {   if (s) fprintf(_gp, 0 == i % s ? " " : "\n");
            fprintf
            (   _gp
            ,   "%s %s %s\n"
            ,   std::to_string(x[i]).c_str()
            ,   std::to_string(y[i]).c_str()
            ,   std::to_string(z[i]).c_str()
            );
        }
        return *this;
    }

    template
    <   typename InputT1
    ,   typename InputT2
    ,   typename InputT3
    ,   typename InputT4
    >
    gnuplot& interleave
    (   InputT1 x
    ,   InputT2 y
    ,   InputT3 z
    ,   InputT4 w
    ,   size_t n
    ,   size_t s = 0
    )
    {   for (size_t i = 0; i < n; ++i)
        {   if (s) fprintf(_gp, 0 == i % s ? " " : "\n");
            fprintf
            (   _gp
            ,   "%s %s %s %s\n"
            ,   std::to_string(x[i]).c_str()
            ,   std::to_string(y[i]).c_str()
            ,   std::to_string(z[i]).c_str()
            ,   std::to_string(w[i]).c_str()
            );
        }
        return *this;
    }
};

} // end g3p namespace

#endif  // _G3P_GNUPLOT_HPP_
