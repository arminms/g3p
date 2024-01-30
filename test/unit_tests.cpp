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
#include <catch2/catch_all.hpp>
#include <g3p/gnuplot>

TEST_CASE("log() function", "[gnuplot][log]")
{   SECTION("no argument")
    {   g3p::gnuplot gp;
        REQUIRE_NOTHROW(">>>>> g3p -- gnuplot log <<<<<\n \n" == gp.log());
    }
    SECTION("line count = 1")
    {   g3p::gnuplot gp;
        REQUIRE_NOTHROW(" \n" == gp.log(1));
    }
    SECTION("line count = 2")
    {   g3p::gnuplot gp;
        REQUIRE_NOTHROW(">>>>> g3p -- gnuplot log <<<<<\n \n" == gp.log(2));
    }
}

TEST_CASE("output stream operator", "[gnuplot]")
{   g3p::gnuplot gp;
    SECTION("whole output")
    {   auto out = gp >> 2;
        REQUIRE(">>>>> g3p -- gnuplot log <<<<<\n \n" == out.str());
    }
    SECTION("selective")
    {   std::string skip, gnuplot;
        gp >> 2 >> skip >> skip >> skip >> gnuplot;
        REQUIRE("--" == skip);
        REQUIRE("gnuplot" == gnuplot);
    }
}

TEST_CASE("passing strings", "[gnuplot][string]")
{   g3p::gnuplot gp;
    SECTION("string literal - c++ convention")
    {   gp << "t=" << "'test'" << "\n"
           << "print t\n"
        ;
        std::string t;
        gp >> 1 >> t;
        CHECK("test" == t);
    }
    SECTION("string literal - c convention")
    {   gp  ("t=%s", "'test'")
            ("print t")
        ;
        std::string t;
        gp >> 1 >> t;
        CHECK("test" == t);
    }
    SECTION("std::string - c++ convention")
    {   std::string t = "'test'";
        gp << "t=" << t << "\n"
           << "print t\n"
        ;
        gp >> 1 >> t;
        CHECK("test" == t);
    }
    SECTION("std::string - c convention")
    {   std::string t = "'test'";
        gp  ("t=%s", t.c_str())
            ("print t")
        ;
        gp >> 1 >> t;
        CHECK("test" == t);
    }
}

TEMPLATE_TEST_CASE("passing int values", "[gnuplot][int]", int, long)
{   typedef TestType T;
    T pi = T(314159), e = T(-271828);
    g3p::gnuplot gp;
    SECTION("c++ convention")
    {   gp << "x=" << pi << "; y=" << e << "\n"
           << "print x, y\n"
        ;
        T x, y;
        gp >> 1 >> x >> y;
        CHECK(pi == x);
        CHECK(e  == y);
    }
    SECTION("c convention")
    {   gp  ("x=%d; y=%d", pi, e)
            ("print x, y")
        ;
        T x, y;
        gp >> 1 >> x >> y;
        CHECK(pi == x);
        CHECK(e  == y);
    }
}

TEMPLATE_TEST_CASE("passing real values", "[gnuplot][real]", float, double)
{   typedef TestType T;
    T pi = T(3.141592654), e = T(2.718281828);
    g3p::gnuplot gp;
    SECTION("c++ convention")
    {   gp << "x={" << pi << "," << e << "}\n"
           << "print x\n"
        ;
        char skip;
        T x1, x2;
        gp >> 1 >> skip >> x1 >> skip >> x2;
        CHECK(std::abs(pi - x1) < 0.0001);
        CHECK(std::abs(e  - x2) < 0.0001);
    }
    SECTION("c convention")
    {   gp  ("x={%f,%f}", pi, e)
            ("print x")
        ;
        char skip;
        T x1, x2;
        gp >> 1 >> skip >> x1 >> skip >> x2;
        CHECK(std::abs(pi - x1) < 0.0001);
        CHECK(std::abs(e  - x2) < 0.0001);
    }
}
