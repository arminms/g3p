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
#ifndef _G3P_GNUPLOT_HPP_
#define _G3P_GNUPLOT_HPP_

#include <cstdio>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <type_traits>

#ifdef __CLING__
#   include <fstream>
#   include <sstream>
#   include <chrono>
#   include <thread>
#   include <filesystem>
#   include <unordered_map>
#   include <any>
#   include <condition_variable>
#   include <xcpp/xdisplay.hpp>
#   include <nlohmann/json.hpp>
#endif //__CLING__

namespace g3p
{

// -- simulated ostream manipulators -------------------------------------------

    const std::string end("e\n");
    const std::string endl("_G3P_ENDL_");
    const std::string eod("EOD\n");
    const std::string flush("_G3P_FLUSH_");

    class gnuplot
    {
// -- disabled copy constructor and assignment operator -----------------------

        gnuplot(const gnuplot&) = delete;
        void operator= (const gnuplot&) = delete;

// -- ostream operator handlers ------------------------------------------------

        template<typename T>
        void ostream_opr_impl(T arg, std::true_type) const
        {   std::string s(arg);
            if ("_G3P_FLUSH_" == s)
                fflush(_gp);
            else if ("_G3P_ENDL_" == s)
            {   fprintf(_gp, "\n");
                fflush(_gp);
            }
            else
                fprintf(_gp, " %s", s.c_str());
        }
        template<typename T>
        void ostream_opr_impl(T arg, std::false_type) const
        {   fprintf(_gp, " %s", std::to_string(arg).c_str());   }

// -- member variables ---------------------------------------------------------

        FILE* _gp;
        std::string _logfile;
#ifdef __CLING__
        std::string _plotfile;
#endif  //__CLING__

    public:
        gnuplot(std::string logfile = {}, bool persist = true)
        :   _gp(nullptr)
        ,   _logfile(logfile)
        {
            const char* gnuplot_path = std::getenv("G3P_GNUPLOT_PATH");
            std::string gnuplot_cmd = gnuplot_path ? gnuplot_path : "gnuplot";
#ifdef __CLING__
            if (_logfile.empty())
                _logfile = tmpnam(NULL);
#endif  //__CLING__
            if (persist)
                gnuplot_cmd += " -persist";
            if (!_logfile.empty())
                gnuplot_cmd += " > " + _logfile + " 2>&1";
#ifdef _MSC_VER // possibly _WIN32 for MingW-64?
            _gp = _popen
#else
            _gp =  popen
#endif //_MSC_VER
                (gnuplot_cmd.c_str(), "w");
            if (nullptr == _gp)
                throw std::domain_error("gnuplot -- failed");
#ifdef __CLING__
            _plotfile = tmpnam(NULL);
            _plotfile += ".svg";
            fprintf(_gp, "set term push\n");
            fprintf(_gp, "set term svg standalone enhanced\n");
            fprintf(_gp, "set output \"%s\"\n", _plotfile.c_str());
#endif //__CLING__
        }

        ~gnuplot()
        {
#ifdef _MSC_VER
            if (_gp) _pclose(_gp);
#else
            if (_gp) pclose(_gp);
#endif //_MSC_VER
#ifdef __CLING__
            std::filesystem::path f(_logfile);
            std::filesystem::remove(f);
            f = _plotfile;
            std::filesystem::remove(f);
#endif //__CLING__
        }

#ifdef __CLING__

// -- log file (cling only) ----------------------------------------------------

        std::string log() const
        {   if (_logfile.empty())
                return _logfile;
            flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            std::ifstream fin(_logfile);
            std::stringstream log;
            log << fin.rdbuf();
            return log.str();
        }

// -- plot file (cling only) ---------------------------------------------------

        std::string plotfile() const
        {   return _plotfile;   }

#endif //__CLING__

#ifdef __GNUG__
#       pragma GCC diagnostic push
#       pragma GCC diagnostic ignored "-Wformat-security"
#endif //__GNUG__
        template<typename... Args>
        const gnuplot& operator() (Args&&... args) const
        {   fprintf(_gp, std::forward<Args>(args)...);
            fprintf(_gp, "\n");
            return *this;
        }
#ifdef __GNUG__
#       pragma GCC diagnostic pop
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
    };

    namespace detail
    {   std::string inline random_name(const int len)
        {   static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            std::string tmp_s;
            tmp_s.reserve(len);
            for (int i = 0; i < len; ++i)
                tmp_s += alpha[rand() % (sizeof(alpha) - 1)];
            return tmp_s;
        }
    }

    template<typename T>
    inline std::string make_data_block(const gnuplot& gp, const T& c)
    {   std::string name{" $"};
        name += detail::random_name(8);
        name += ' ';
        gp  ("%s<< EOD", name.c_str())
            ("%s\nEOD", c(gp).c_str());
        return name;
    }
    template<typename T>
    inline std::string make_data_block
    (   const gnuplot& gp
    ,   const T& c
    ,   typename T::size_type row 
    ,   typename T::size_type sep = 0 // separator
    )
    {   std::string name{" $"};
        name += detail::random_name(8);
        name += ' ';
        gp("%s<< EOD", name.c_str());
        auto it = std::begin(c);
        for (typename T::size_type i = 0; i < c.size(); ++i, ++it)
        {   if (sep && i && 0 == i % sep)
                gp.endl();
            if (0 == i % row)
                gp.endl();
            gp << *it;
        }
        gp("\nEOD");
        return name;
    }

#ifdef __CLING__
    namespace detail
    {   void wait_for_file(std::string tag, const gnuplot& gp)
        {   while (tag.npos == gp.log().rfind(tag))
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    nlohmann::json mime_bundle_repr(const gnuplot& gp)
    {   std::filesystem::path f(gp.plotfile());
        auto tag = detail::random_name(8);
        gp("print \"plot -> %s\"", tag.c_str()).flush();
        std::thread t(detail::wait_for_file, tag, std::ref(gp));
        t.join();
        if (0 == std::filesystem::file_size(f))
        {   tag = detail::random_name(8);
            gp  ("replot")
                ("print \"plot -> %s\"", tag.c_str()).flush();
            std::thread t(detail::wait_for_file, tag, std::ref(gp));
            t.join();
        }
        std::ifstream fin(gp.plotfile(), std::ios::binary);
        std::stringstream buffer;
        buffer << fin.rdbuf();
        auto bundle = nlohmann::json::object();
        bundle["image/svg+xml"] = buffer.str();
        std::filesystem::remove(f);
        gp("set output \"%s\"", f.c_str());
        return bundle;
    }
#endif //__CLING__

} // end g3p namespace

#endif  // _G3P_GNUPLOT_HPP_
