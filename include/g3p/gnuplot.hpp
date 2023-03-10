#ifndef _G3P_GNUPLOT_HPP_
#define _G3P_GNUPLOT_HPP_

#include <cstdio>
#include <stdexcept>
#include <string>

class gnuplot
{
    FILE* _gp;

public:
    gnuplot(bool persist = true)
    {
        _gp = popen
        (   persist
        ?   GNUPLOT" -persist"
        :   GNUPLOT
        ,   "w"
        );
        if (nullptr == _gp)
            throw std::domain_error("gnuplot -- failed");
    }

    ~gnuplot()
    {   if (_gp) pclose(_gp);   }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
    template<typename... Args>
    gnuplot& operator() (Args&&... args)
    {   fprintf(_gp, std::forward<Args>(args)...);
        fprintf(_gp, "\n");
        return *this;
    }
#pragma GCC diagnostic pop

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

#endif  // _G3P_GNUPLOT_HPP_
