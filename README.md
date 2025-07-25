# **Tower Defense Collision Library**

## **Overview**

Metaphorically, this project is a **"collision lab"**: a sandbox for experimenting with different data structures and techniques for broad-phase and narrow-phase collision detection.  

Literally, it is a **C++ library for fast 2D collision detection** using multiple spatial partitioning strategies. It is being developed as part of the **University of Florida’s COP3530 (Data Structures and Algorithms)** course and is still in active development.  

While the long-term vision could be a fully functional tower defense engine, the current focus is **research and benchmarking** of various collision detection algorithms.

---

## **What It Does**

- Provides a **simulation core** for moving agents (enemies, projectiles) and static obstacles.
- Implements multiple spatial partitioning data structures:
  - Uniform Grid / Spatial Hash
  - Quadtree
  - Sweep and Prune (SAP)
  - BVH (Bounding Volume Hierarchy)
- Tracks performance statistics (broad-phase checks, collisions, memory usage).
- Supports **optional visualization** with SFML to show:
  - Agents and projectiles
  - Partition boundaries (grid cells, quadtree nodes, etc.)
  - Debug information and live stats

---

## **Project Goals**
1. Compare efficiency and tradeoffs of different collision detection data structures.
2. Build a clean, modular library that can be used **headless (for testing)** or with visualization (for debugging/teaching).
3. Serve as a foundation for potential future game engine components (e.g., tower defense simulation).

---

## **Compiling & Build Options**

This project uses **CMake (>=3.15)** and supports several configuration options:

### **Build Options**
- `WITH_SFML` (**ON/OFF**, default ON)  
  - Enables or disables SFML-based visualization.  
  - If `OFF`, the project builds a headless simulation-only mode (no graphics).
- `WITH_TESTS` (**ON/OFF**, default ON)  
  - Enables building unit tests (Catch2).

### **Building**
```bash
# Clone the project
git clone https://github.com/elleburkhalter/Oops-All-Collisions.git
cd tower_defense_collision

# Configure and build (with visualization and tests)
cmake -B build -DWITH_SFML=ON -DWITH_TESTS=ON
cmake --build build
```

### **Running**
- **Simulation executable:**
  ```bash
  ./build/tower_defense [--visualize 1|0]
  ```
  - `--visualize=1`: Show SFML visualization (if built with SFML).  
  - `--visualize=0`: Run headless.

- **Tests:**
  ```bash
  cd build
  ctest --output-on-failure
  ```

---

## **Dependencies**

### **Core (always required)**
- C++23 or newer
- CMake >= 3.15

### **Optional (for visualization)**
- [SFML 3.0.1](https://github.com/SFML/SFML) (automatically fetched via CMake’s `FetchContent` if `WITH_SFML=ON`)

### **Testing**
- [Catch2 v3](https://github.com/catchorg/Catch2) (automatically fetched)

---

## **Project Structure**

```
tower_defense_collision/
├── app/           # Main executable(s)
├── include/        # Public headers
│   └── rendering/  # Renderer interface + implementations
├── src/            # Library sources
│   └── (WIP)
├── tests/          # Unit tests
└── CMakeLists.txt
```

---

## **Current Status**
- In infancy stages; creating basic visualizers and data structures.
- Unit tests will cover data structure integrity and collision edge cases.

> **Note:** This is a **course project** and subject to major changes as features are developed and refactored.

---

## **Planned Improvements**
- More data structures (R-Tree, Dynamic BVH).
- Parallelization for high agent counts (100k+).
- More detailed statistical collection and visualization overlays.
- (Long-term) Tower-defense-specific game loop integration.

---

## **License**
See LICENSE for license information.
