# Event-Loop Toolkit

A small C++ toolkit that demonstrates three reusable patterns:

- Event-driven processing with a thread-safe queue (`EventLoop`)
- Observable state with change notifications (`Watchable`)
- Strategy-based generic sorting (`Sorter`)

The project is intentionally compact and educational, with minimal dependencies and simple APIs.

## Modules

- [EventLoop](EventLoop/README.md): Event queue + handlers + graceful stop
- [Watchable](Watchable/README.md): Observable values and watcher callbacks
- [Sorter](Sorter/README.md): Runtime-selectable sort strategies

## Build

Use the helper script at the project root:

```bash
./build.sh all
./build.sh eventloop
./build.sh watchable
./build.sh sorter
```

Executables are generated in the root `bin/` folder.

## Run

```bash
./bin/eventloop_demo
./bin/watchable_demo
./bin/sorter_demo
```

## Repository notes

Build artifacts should not be committed (`build*`, `bin`).
Use a `.gitignore` to keep generated files out of the repository.
