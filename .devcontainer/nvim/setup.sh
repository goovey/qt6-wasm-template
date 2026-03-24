#!/bin/bash
# ==============================================================================
# Setup Script for Qt6-WASM + Neovim Dev Container
# Location: .devcontainer/nvim/setup.sh
# ==============================================================================
set -e # Exit immediately if a command exits with a non-zero status
set -u # Treat unset variables as an error

echo "--- Starting Post-Create Bootstrap ---"

# 1. Fix Permissions
# Docker volumes often mount as root. We must ensure the 'ubuntu' user
# owns these directories to allow Neovim to write swap/undo/plugin files.
echo "Fixing ownership for .config and .local..."
sudo chown -R ubuntu:ubuntu /home/ubuntu/.config /home/ubuntu/.local

# 2. Bootstrap Neovim Configuration
# Logic: If the persistent volume is empty, copy the host's config into it.
TARGET_CONFIG="/home/ubuntu/.config/nvim"
HOST_MOUNT="/home/ubuntu/.config/nvim_host"

if [ ! -f "$TARGET_CONFIG/init.lua" ]; then
  echo "Notice: init.lua not found. Initializing config from host mount..."
  if [ -d "$HOST_MOUNT" ]; then
    cp -r "$HOST_MOUNT/." "$TARGET_CONFIG/"
    echo "Config successfully synchronized."
  else
    echo "Warning: $HOST_MOUNT not found. Skipping config copy."
  fi
else
  echo "Notice: Existing Neovim configuration detected in volume. Skipping initialization."
fi

# 3. Synchronize Neovim Plugins (Lazy.nvim)
# Runs nvim in headless mode to install/update plugins without a UI.
if command -v nvim >/dev/null 2>&1; then
  echo "Synchronizing Neovim plugins via Lazy..."
  nvim --headless "+Lazy! sync" +qa
else
  echo "Error: Neovim binary not found in PATH."
  exit 1
fi

echo "--- Bootstrap Complete ---"
