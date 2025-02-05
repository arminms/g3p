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

#-- gnuplot-602 image ----------------------------------------------------------

FROM ubuntu:20.04 AS gnuplot-602

# change default shell to bash
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# install build-essential and other dependencies
RUN set -ex \
    && apt-get update && apt-get upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential \
        autotools-dev \
        automake \
        ca-certificates \
        git \
        libgd-dev \
        libcairo-dev \
        libwebp-dev \
        qtbase5-dev \
        qtbase5-dev-tools \
        qttools5-dev-tools \
        libqt5svg5-dev \
        libwebpmux3 \
        libpango1.0-dev \
    && rm -rf /var/lib/apt/lists/*

# build and install gnuplot 6.0.2
RUN set -ex \
    && git clone --depth 1 -b 6.0.2 https://git.code.sf.net/p/gnuplot/gnuplot-main \
    && cd gnuplot-main \
    && ./prepare \
    && ./configure --prefix=/opt/xeus-cling \
    && make -j \
    && make install

#-- g3p image ------------------------------------------------------------------

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

# install g3p
RUN set -ex \
    && mkdir -p /opt/xeus-cling \
    && cd /opt \
    && git clone https://github.com/arminms/g3p.git \
    && cd g3p \
    && cmake -S . -B build \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/xeus-cling \
        -DG3P_ENABLE_TESTS=OFF \
    && cmake --build build \
    && cmake --install build

#-- g3p-xeus-cling -------------------------------------------------------------

FROM asobhani/xeus-cling-jupyter:latest AS g3p-xeus-cling

LABEL maintainer="Armin Sobhani <arminms@gmail.com>"
LABEL description="Docker image for G3P (gnuplot for Modern C++) with Xeus-Cling"

# change default shell to bash
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

USER root

# install necessary libraries for gnuplot
RUN set -ex \
    && apt-get update && apt-get upgrade -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        libgd3 \
        libcairo2 \
        libwebp6 \
        libqt5svg5 \
        libwebpmux3 \
        libpango1.0 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# copy gnuplot
COPY --from=gnuplot-602 /opt/xeus-cling /opt/xeus-cling

# copy g3p
COPY --from=g3p /opt/xeus-cling /opt/xeus-cling

# switch back to jovyan
USER ${NB_USER}

# copy tutorial markdowns to the home directory and convert them to notebooks
COPY --chown=${NB_UID}:${NB_GID} docs/notebooks/*.md ${HOME}/
RUN set -ex \
    && cd ${HOME} \
    && jupytext --to notebook *.md \
    && rm -rf *.md