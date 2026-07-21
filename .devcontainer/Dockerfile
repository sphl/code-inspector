FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

ENV LLVM_VERSION=12
ENV SVF_VERSION=2.2

ENV SVF_DIR=/opt/svf-${SVF_VERSION}

# Core build dependencies
RUN apt-get update -qq \
    && apt-get install -qqy \
        build-essential \
        ca-certificates \
        cmake \
        git \
        gnupg \
        libboost-all-dev \
        libz3-dev \
        lsb-release \
        ninja-build \
        rapidjson-dev \
        software-properties-common \
        wget \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# LLVM (compiler + clang-format + clang-tidy)
RUN wget -qO /tmp/llvm.sh https://apt.llvm.org/llvm.sh \
    && chmod +x /tmp/llvm.sh \
    && /tmp/llvm.sh ${LLVM_VERSION} all \
    && rm /tmp/llvm.sh \
    && update-alternatives --install /usr/bin/clang        clang        /usr/bin/clang-${LLVM_VERSION}        100 \
    && update-alternatives --install /usr/bin/clang++      clang++      /usr/bin/clang++-${LLVM_VERSION}      100 \
    && update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-${LLVM_VERSION} 100 \
    && update-alternatives --install /usr/bin/clang-tidy   clang-tidy   /usr/bin/clang-tidy-${LLVM_VERSION}   100 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

ENV CC=clang
ENV CXX=clang++

# SVF
WORKDIR /opt
RUN wget -q "https://github.com/SVF-tools/SVF/archive/refs/tags/SVF-${SVF_VERSION}.tar.gz" \
    && tar xf "SVF-${SVF_VERSION}.tar.gz" \
    && rm "SVF-${SVF_VERSION}.tar.gz" \
    && mv "SVF-SVF-${SVF_VERSION}" "${SVF_DIR}"

WORKDIR ${SVF_DIR}
RUN LLVM_DIR=/usr/lib/llvm-${LLVM_VERSION} ./build.sh

WORKDIR /
