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
#include <cstdlib>
#include <type_traits>

#ifdef __CLING__
#   include <random>
#   include <algorithm>
#   include <functional>
#   include <chrono>
#   include <thread>
#   include <fstream>
#   include <filesystem>
#   include <g3p/json.hpp>
#endif //__CLING__
namespace g3p {

class gnuplot
{
    // disabling copy constructor and assignment operator
    gnuplot(const gnuplot&) = delete;
    void operator= (const gnuplot&) = delete;

    template<typename T>
    void ostream_opr_impl(T arg, std::true_type) const
    {   std::string s(arg);
        fprintf(_gp, " %s", s.c_str());
    }

    template<typename T>
    void ostream_opr_impl(T arg, std::false_type) const
    {   fprintf(_gp, " %s", std::to_string(arg).c_str());   }

    FILE* _gp;

public:
    gnuplot(bool persist = true)
    {
        const char* gnuplot_path = std::getenv("G3P_GNUPLOT_PATH");
        std::string gnuplot_cmd = gnuplot_path ? gnuplot_path : "gnuplot";
        if (persist) gnuplot_cmd += " -persist";
#ifdef _MSC_VER // possibly _WIN32 for MingW-64?
        _gp = _popen
#else
        _gp =  popen
#endif //_MSC_VER
            (gnuplot_cmd.c_str(), "w");
        if (nullptr == _gp)
            throw std::domain_error("gnuplot -- failed");
#ifdef __CLING__
        fprintf(_gp, "set terminal unknown\n");
#endif //__CLING__
    }

    ~gnuplot()
#ifdef _MSC_VER
    {   if (_gp) _pclose(_gp);   }
#else
    {   if (_gp) pclose(_gp);   }
#endif //_MSC_VER

#ifdef __GNUG__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat-security"
#endif //__GNUG__
    template<typename... Args>
    const gnuplot& operator() (Args&&... args) const
    {   fprintf(_gp, std::forward<Args>(args)...);
        fprintf(_gp, "\n");
        return *this;
    }
#ifdef __GNUG__
#   pragma GCC diagnostic pop
#endif //__GNUG__

    template<typename T>
    const gnuplot& operator<< (T arg) const
    {   ostream_opr_impl(arg, std::is_compound<T>());
        return *this;
    }

    const gnuplot& endl() const
    {   fprintf(_gp, "\n");
        return *this;
    }

    const gnuplot& end() const
    {   fprintf(_gp, "e\n");
        return *this;
    }

    const gnuplot& flush() const
    {   fflush(_gp);
        return *this;
    }

    template<typename InputT1, typename InputT2>
    const gnuplot& interleave(InputT1 x, InputT2 y, size_t n) const
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
    const gnuplot& interleave
    (   InputT1 x
    ,   InputT2 y
    ,   InputT3 z
    ,   size_t n
    ,   size_t s = 0
    ) const
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
    const gnuplot& interleave
    (   InputT1 x
    ,   InputT2 y
    ,   InputT3 z
    ,   InputT4 w
    ,   size_t n
    ,   size_t s = 0
    ) const
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

#ifdef __CLING__
    nlohmann::json mime_bundle_repr(const gnuplot& gp)
    {
        std::string name(32, ' ');
        name[0] = 'g'; name[1] = '3'; name[2] = 'p';
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(48, 57);
        std::generate_n(std::begin(name) + 3, 29, std::bind(dis, std::ref(gen)));
        auto tmp{std::filesystem::temp_directory_path()};
        std::string plot{tmp.c_str()};
        plot += '/' + name + ".svg";
        gp
        ( "set term push" )
        ( "set term svg dynamic mouse standalone enhanced" )
        ( "set output \"%s\"", plot.c_str())
        ( "replot" )
        ( "set term pop" ).flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::ifstream fin(plot, std::ios::binary);
        std::stringstream buffer;
        buffer << fin.rdbuf();
        auto bundle = nlohmann::json::object();
        bundle["image/svg+xml"] = buffer.str();
        std::filesystem::path file(plot);
        std::filesystem::remove(file);
        return bundle;
    }
#endif //__CLING__

} // end g3p namespace

#endif  // _G3P_GNUPLOT_HPP_
