FROM qt-wasm-base

# Install Neovim
RUN curl -LO https://github.com/neovim/neovim/releases/download/v0.11.6/nvim-linux-x86_64.tar.gz \
    && tar -C /usr/local --strip-components 1 -xzf nvim-linux-x86_64.tar.gz \
    && rm nvim-linux-x86_64.tar.gz

# Install Node.js 22
RUN curl -fsSL https://deb.nodesource.com/setup_22.x | bash \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

USER ubuntu

