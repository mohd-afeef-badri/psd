FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive
ENV OMPI_ALLOW_RUN_AS_ROOT=1
ENV OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1
ENV PREFIXPSD=/opt/psd

RUN apt-get update && apt-get install -y \
    freeglut3-dev \
    liblapack-dev \
    libhdf5-dev \
    libgsl-dev \
    cmake \
    libopenmpi-dev \
    libtirpc-dev \
    autoconf \
    automake \
    libtool \
    make \
    python3 \
    g++ \
    gcc \
    gfortran \
    wget \
    git \
    flex \
    bison \
    unzip \
    patch \
    pkg-config \
    libxrender1 \
    libxcursor1 \
    libxfixes3 \
    libxft2 \
    libxinerama1 \
    libxrandr2 \
    libxdamage1 \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /usr/local/src/psd
COPY . .

RUN autoreconf -ivf && \
    ./configure --prefix=${PREFIXPSD} --with-dependencies && \
    make  && \
    make install

ENV PATH="${PREFIXPSD}/bin:${PATH}"
ENV OMP_NUM_THREADS=1

CMD ["bash"]

