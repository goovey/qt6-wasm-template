# Variables
IMAGE=qt-wasm-base
BUILD_DIR=build
UID=$(shell id -u)
GID=$(shell id -g)

MODE ?= release

# Logic to select the correct pair of presets based on MODE
ifeq ($(MODE),release)
    CONF_PRESET=qt-wasm-release
    BUILD_PRESET=release
else
    # Defaulting to dev settings
    CONF_PRESET=qt-wasm-dev
    BUILD_PRESET=dev
endif

.PHONY: all clean push server help

all: ## Build the WebAssembly application (Default MODE=dev, or MODE=release)
	@echo "Targeting MODE: $(MODE)"
	@echo "Using Configure Preset: $(CONF_PRESET)"
	@echo "Using Build Preset: $(BUILD_PRESET)"
	
	docker run --rm -v $(shell pwd):/project -w /project \
		--user $(UID):$(GID) \
		$(IMAGE) \
		/bin/bash -c "cmake --preset $(CONF_PRESET) && \
		              cmake --build --preset $(BUILD_PRESET)"
	
	@echo "Build successful. Artifacts are in $(BUILD_DIR)/"

clean: ## Remove the build directory
	rm -rf $(BUILD_DIR)

push:
	docker tag qt-wasm-base:latest ghcr.io/goovey/wasm-test/qt6-wasm:latest
	docker push ghcr.io/goovey/wasm-test/qt6-wasm:latest

server: ## Start the local Python test server
	python3 server.py

help: ## Show this help message
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-15s\033[0m %s\n", $$1, $$2}'