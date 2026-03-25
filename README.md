# Radar Single Target Test (Qt 6 WebAssembly)

A high-performance WebAssembly (WASM) application built with **Qt 6.8.0** and **C++17**. This project simulates a single radar target with real-time tracking data displayed in a web-optimized dashboard.

## 🚀 Key Features

* **Real-time Radar Simulation**: Synthetically generates range, azimuth, velocity, and SNR data.
* **Interactive Controls**: Dashboard includes **Start**, **Pause**, and **Stop** functionality to manage the simulation loop.
* **Dynamic Update Frequency**: Configurable calculation interval (minimum **10ms**) to test UI responsiveness and physics accuracy.
* **Containerized Toolchain**: Fully reproducible build environment using Docker, pinned to specific Qt and Emscripten versions.
* **Security-Hardened Server**: Includes a custom Python server that enforces **COOP/COEP** headers required for advanced WASM features.

## 🛠 Tech Stack

| Component | Technology | Source |
| :--- | :--- | :--- |
| **Framework** | Qt 6.8.0 (wasm_singlethread) | |
| **Language** | Modern C++17 | |
| **Compiler** | Clang 18 / Emscripten 3.1.56 | |
| **Build System** | CMake with Presets | |
| **Base OS** | Ubuntu 24.04 | |

## 📦 Getting Started

### 1. Build the Application
The project uses a `Makefile` to orchestrate Docker-based builds, ensuring you don't need to install Qt or Emscripten locally.

```bash
# Build for development (Debug)
make

# Build for production (Release with optimizations)
make MODE=release
```

### 2. Run the Local Server
WebAssembly requires specific security headers to run. Launch the provided Python server to host the `build/` directory.

```bash
make server
```
Access the app at: `http://localhost:3030/build/WasmTest.html`.

## 💻 Development Environments

This project is optimized for both **VS Code** and **Neovim** using Dev Containers:

* **VS Code**: Includes pre-configured `tasks.json` and `launch.json` for one-click building and debugging.
* **Neovim**: Features an automated bootstrap script (`setup.sh`) that installs plugins and synchronizes configurations within the container.

## 🤖 Continuous Integration

A GitHub Actions workflow is provided in `.github/workflows/wasm-build.yml`. It automatically:
1.  Loads the custom `qt6-wasm` Docker image.
2.  Compiles the application using the `release` preset.
3.  Uploads the `.wasm`, `.js`, and `.html` artifacts.
