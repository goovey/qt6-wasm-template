FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    python3 python3-pip python3-venv git curl tar cmake ninja-build \
    libglib2.0-0 libfontconfig1 libdbus-1-3 \
    libgl1-mesa-dev libxkbcommon-dev \
    sudo wget gnupg ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Install Clang 18 (Better for clangd/IntelliSense)
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
    && echo "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-18 main" > /etc/apt/sources.list.d/llvm.list \
    && apt-get update && apt-get install -y --no-install-recommends \
    clang-18 clangd-18 clang-format-18 \
    && ln -s /usr/bin/clang-18 /usr/bin/clang \
    && ln -s /usr/bin/clang++-18 /usr/bin/clang++ \
    && ln -s /usr/bin/clangd-18 /usr/bin/clangd \
    && rm -rf /var/lib/apt/lists/*

# the existing 'ubuntu' user sudo permissions
RUN echo ubuntu ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/ubuntu \
    && chmod 0440 /etc/sudoers.d/ubuntu

# Install aqtinstall
RUN pip3 install --break-system-packages aqtinstall

# Install Qt 6.8.0
RUN aqt install-qt linux desktop 6.8.0 linux_gcc_64 && \
    aqt install-qt all_os wasm 6.8.0 wasm_singlethread && \
    chown -R ubuntu:ubuntu /6.8.0

# Set up Emscripten (Pinned to 3.1.56)
ENV EMSDK_PATH=/opt/emsdk
RUN git clone https://github.com/emscripten-core/emsdk.git $EMSDK_PATH && \
    cd $EMSDK_PATH && \
    ./emsdk install 3.1.56 && \
    ./emsdk activate 3.1.56 && \
    chown -R ubuntu:ubuntu $EMSDK_PATH

ENV PATH="/6.8.0/wasm_singlethread/bin:/6.8.0/gcc_64/bin:/opt/emsdk:/opt/emsdk/upstream/emscripten:${PATH}"
ENV EMSDK="/opt/emsdk"
ENV Qt6_DIR="/6.8.0/wasm_singlethread/lib/cmake/Qt6"
ENV QT_HOST_PATH="/6.8.0/gcc_64"

 
