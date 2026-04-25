# Watchable Feature

This module implements observable values and a watch system.

Core concepts:

- `Watchable`: owns watchers and dispatches notifications
- `Watched<T>`: wraps a value and notifies its owner on assignment
- Dependency keys (for example `"health"`, `"name"`) to target callbacks

## What it demonstrates

- Reactive-style updates in plain C++
- Value change hooks (`onChanged`) for logging or side effects
- Small, composable watcher callbacks

## Build only this feature

```bash
./build.sh watchable
```

## Run

```bash
./bin/watchable_demo
```

The demo updates player state and triggers watchers/logging automatically.
