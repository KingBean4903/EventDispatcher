# EventDispatcher

A **header-only**, **type-safe**, and **multithreaded** C++ Event Dispatcher system, designed to register, store, and invoke callbacks (subscribers) for custom event types. It supports both **synchronous** and **asynchronous** event dispatching.

---

## Features

- ✅ Header-only, easy to integrate
- ✅ Type-safe event registration via C++ templates
- ✅ Unique subscription tokens for unsubscribing
- ✅ Supports synchronous and asynchronous dispatch
- ✅ Thread-safe operations
- ✅ Benchmarking with Google Benchmark
- ✅ Tested with Catch2

---


---

## Getting Started

### Requirements

- C++20 or newer
- CMake ≥ 3.15
- Google Benchmark (via FetchContent)
- Catch2 (via FetchContent)

### Build

```bash
git clone https://github.com/yourname/EventDispatchert.git
cd EventDispatcherProject
mkdir build && cd build
cmake ..
make
