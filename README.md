# Oops! All Collisions

## Overview
**Oops! All Collisions** is a small “collision lab” written in C++23. It’s a sandbox for experimenting with **broad‑phase** and **narrow‑phase** collision detection techniques in 2D, built for UF’s **COP3530 (Data Structures and Algorithms)**. The current focus is **research, visualization, and benchmarking** of data structures—not a full tower‑defense engine.

The simulation drives autonomous entities and visualizes behavior so you can observe how different structures scale and fail under load. The code is modular: you can run headless for tests/benchmarks or enable a lightweight visualizer to debug and teach concepts.

---

## What It Does
- Runs a deterministic simulation of moving entities with **AABB** colliders.
- Implements multiple **broad‑phase** structures to reduce pairwise checks before the narrow phase:
  - **Naive all‑pairs baseline** (unordered array; O(n²))
  - **Sweep‑and‑Prune (SAP)** on one axis (sorted endpoints + single sweep)
  - **Spatial Hash (uniform grid)** with coarse neighborhood queries
  - **Multi‑Level Quadtree** (data may be stored at any node level)
- Uses a simple **AABB–AABB** narrow‑phase overlap check by default.
- Offers an optional **Raylib** visualization with overlays (entities, partitions, debug stats).
- Provides unit tests for critical behaviors (AABB overlap, SAP ordering, grid hashing, pair de‑dup).

> Note: **BVH is not currently implemented**. Earlier drafts mentioned it as a future idea; it is not part of the current codebase.

---

## Project Goals
1. Measure and compare **throughput and candidate‑pair quality** across structures.
2. Keep the library **modular** so it can run **headless** for tests or with a **visualizer** for interactive study.
3. Serve as a clear reference implementation for common spatial data structures in games and simulations.

---

## Build & Run

This project uses **CMake** and modern C++ (C++23). External dependencies (Raylib, Catch2, range‑v3 where used) are fetched with **FetchContent** from the top‑level CMake files.

### Build
```bash
# Clone
git clone https://github.com/elleburkhalter/Oops-All-Collisions.git
cd Oops-All-Collisions

# Configure + build (tests and visualizer enabled by default in the provided CMake)
cmake -S . -B build
cmake --build build --config Release

# The build can be found in /build/Release/oops_executable.exe
#   You can change the data structure in simulation_main.cpp to 
#   change the visualizer.
# Relevant constants, such as the number of entities, can be 
#   found in /include/constants.h
```

### Run
- **Visualizer / Demo:** Build generates a demo executable that, when run, displays entities and optional debug overlays. Exact binary name and CLI flags may vary by platform/generator (see build output and `app/` sources).
- **Tests:**
  ```bash
  ctest --test-dir build --output-on-failure
  ```

> Tip: If you prefer a pure headless run, disable the visualizer in CMake or run the tests/benchmarks directly.

---

## Dependencies
- **Core:** C++23, CMake (version per toolchain; 3.20+ recommended)
- **Visualization (optional):** Raylib (fetched via FetchContent when enabled)
- **Testing:** Catch2 v3 (fetched via FetchContent)
- **Utilities:** range‑v3 (where iterator/view ergonomics are used)

All third‑party libraries are automatically fetched; no manual installation is required for typical builds.

---

## Algorithms & Data Structures (Implemented)
- **Naïve baseline:** unordered array + all‑pairs checks; useful as a correctness oracle.
- **Sweep‑and‑Prune:** maintain sorted endpoints along one axis; sweep once to generate candidate pairs; leverages temporal coherence for near‑linear updates.
- **Spatial Hash (uniform grid):** hash AABBs to one or more cells; only test local neighborhoods.
- **Multi‑Level Quadtree:** adaptive partition; store objects at the lowest level that fully contains them (or at a parent if they straddle boundaries).

**Narrow‑phase:** AABB–AABB overlap; additional shapes can be added via a `ColliderInterface` pattern.

---

## Repository Layout (high‑level)
```
Oops-All-Collisions/
├── app/                 # Demo/visualizer entry points
├── include/             # Public headers
│   ├── collision/       # AABB and collision primitives
│   ├── data_structures/ # Naive, SAP, SpatialHash, MultiLevelGrid
│   ├── game_object/     # Entity interfaces and implementations
│   ├── renderer/        # Renderer interface + Raylib impl
│   ├── random/          # RNG / distributions
│   ├── spatial/         # Points, bounding boxes
│   └── statistics/      # Metrics (WIP)
├── src/                 # Implementations mirroring include/
├── tests/               # Unit tests (Catch2 v3)
└── CMakeLists.txt       # FetchContent, targets, options
```

> The “tower_defense_collision” folder name in older READMEs was a placeholder. The correct repo root is **`Oops-All-Collisions/`**.

---

## Current Status
The project is a working sandbox with multiple broad‑phase methods, a simple AABB narrow phase, unit tests, and an optional visualizer. It is actively evolving toward better instrumentation (candidate pairs, true positives, maintenance costs) and more robust maintenance policies (e.g., quadtree hysteresis, loose quadtrees).

---

## TODOs (Near‑Term)
- **Documentation**
  - Add per‑structure README pages with complexity analyses and gotchas.
  - Document CLI flags for the demo (visual layers, toggles, seeding).
- **Instrumentation**
  - Log candidate pairs, true collisions, rebuild/maintenance time per frame.
  - Export CSV for easy plotting.
- **Data Structures**
  - Add hysteresis thresholds and “loose” bounds to the quadtree.
  - Auto‑tune Spatial Hash cell size from runtime telemetry.
  - Consider hybrid SAP+Grid for long, thin objects.
- **Testing / CI**
  - Expand edge‑case tests (teleports, clustering, boundary jitter).
  - Add static analysis and sanitizers in CI (ASan/UBSan where available).
- **Headless Mode**
  - Provide dedicated benchmark targets without visualization.
  - Stabilize deterministic seeds and scenario presets.
- **Stretch**
  - Experiment with R‑Tree or Dynamic BVH (not implemented today).
  - Parallelize broad‑phase on large scenes.

---

## License
See `LICENSE` for terms.
