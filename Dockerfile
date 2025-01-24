#
# Copyright (c) 2024-25 Armin Sobhani (arminms@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

#-- g3p image -----------------------------------------------------------------

FROM ubuntu:20.04 AS g3p

# change default shell to bash
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# install build-essential and other dependencies
RUN set -ex \
    && apt-get update && apt-get upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        ca-certificates \
        git \
        wget \
        pkg-config \
    && rm -rf /var/lib/apt/lists/*

# install CMake >= 3.19
RUN set -ex \
    && wget -qO- https://cmake.org/files/v3.25/cmake-3.25.2-linux-x86_64.tar.gz \
       | tar --strip-components=1 -xz -C /usr/local

# install xeus-cling
RUN set -ex \
    && mkdir -p /opt/xeus-cling \
    && cd /opt \
    && git clone -b devel https://github.com/arminms/g3p.git \
    && cd g3p \
    && cmake -S . -B build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/opt/xeus-cling \
      -DG3P_ENABLE_TESTS=OFF \
    && cmake --build build \
    && cmake --install build

#-- g3p-xeus-cling -----------------------------------------------------------------

FROM asobhani/xeus-cling-jupyter:latest AS g3p-xeus-cling

LABEL maintainer="Armin Sobhani <arminms@gmail.com>"
LABEL description="Docker image for g3p (gnuplot for Modern C++) with Xeus-Cling"

# change default shell to bash
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

USER root

# install Gnuplot
RUN set -ex \
    && apt-get update && apt-get upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        gnuplot \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# copy g3p
COPY --from=g3p /opt/xeus-cling /opt/xeus-cling

# switch back to jovyan
USER ${NB_USER}

# copy tutorial notebooks to the home directory
COPY --from=g3p --chown=${NB_UID}:${NB_GID} /opt/g3p/docs ${HOME}
