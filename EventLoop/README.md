# EventLoop Feature

This module provides a basic event loop implementation with:

- A thread-safe event queue
- Event handlers registered by event type
- Blocking wait for incoming events
- Graceful loop shutdown through a stop event

## What it demonstrates

- Producer/consumer style event posting
- Coordination with `std::mutex` and `std::condition_variable`
- Dispatching events to user-defined callbacks

## Build only this feature

```bash
./build.sh eventloop
```

## Run

```bash
./bin/eventloop_demo
```

The demo posts a few events from a worker thread and then stops the loop.
