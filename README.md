# Hardware Modeling Components

A collection of reusable components to model hardware. I add modules over time, with the long-term goal of building a set of usable building blocks for larger systems.

## Current Components
- `buffers/`: FIFO buffer implementation.
- `cache/`: Cache model with replacement policy support.
- `replacement_algorithms/`: Replacement policies (e.g., tree PLRU).

## Build
Each component has its own build/run setup (for example, see `cache/Makefile`).

## Notes
This repository is intentionally incremental—components are added as needed.