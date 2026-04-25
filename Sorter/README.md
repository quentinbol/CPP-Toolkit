# Sorter Feature

This module provides a strategy-based sorter with runtime strategy selection.

Core components:

- `ISorterStrategy`: interface for strategy implementations
- `QuickSort<T>` and `BubbleSort<T>` strategies
- `Sorter`: singleton entry point that delegates to the active strategy

## What it demonstrates

- Strategy pattern in modern C++
- Generic sorting over user-defined types
- Passing comparators at runtime

## Build only this feature

```bash
./build.sh sorter
```

## Run

```bash
./bin/sorter_demo
```

The demo sorts users/products with different comparators.
