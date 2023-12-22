FROM quay.io/jupyter/base-notebook:latest

LABEL maintainer="Armin Sobhani <arminms@gmail.com>"

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

USER root

# Install all OS dependencies for a fully functional Server
RUN apt-get update --yes && \
    apt-get install --yes --no-install-recommends \
    # Common useful utilities
    curl \
    git \
    nano-tiny \
    tzdata \
    unzip \
    vim-tiny \
    # git-over-ssh
    openssh-client \
    # gnuplot for g3p
    gnuplot \
    # nbconvert dependencies
    # https://nbconvert.readthedocs.io/en/latest/install.html#installing-tex
    texlive-xetex \
    texlive-fonts-recommended \
    texlive-plain-generic \
    # Enable clipboard on Linux host systems
    xclip && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Switch back to jovyan to avoid accidental container runs as root
USER ${NB_UID}

# Install xeus-cling kernels and environment 
RUN mamba install -yn base nb_conda_kernels \
    && mamba create -yn xeus-cling xeus-cling \
    && mamba clean -qafy

# Install g3p header and the example notebook
RUN mkdir -p /opt/conda/envs/xeus-cling/include/g3p
COPY include/g3p/gnuplot.hpp /opt/conda/envs/xeus-cling/include/g3p
COPY doc/g3p_by_examples.ipynb ${HOME}
USER root
RUN chown -R ${NB_UID} ${HOME} /opt/conda/envs/xeus-cling/include/g3p
USER ${NB_USER}