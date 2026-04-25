#!/usr/bin/env bash
set -euo pipefail

MODE="${1:-all}"
BUILD_DIR="${2:-}"

usage() {
  cat <<'EOF'
Usage:
  ./build.sh [mode] [build_dir]

Modes:
  all        Build EventLoop + Watchable + Sorter (default)
  eventloop  Build only EventLoop
  watchable  Build only Watchable
  sorter     Build only Sorter
  clean      Remove build directories and exit

Examples:
  ./build.sh
  ./build.sh watchable
  ./build.sh sorter build-sorter-debug
EOF
}

if [[ "$MODE" == "-h" || "$MODE" == "--help" ]]; then
  usage
  exit 0
fi

if [[ "$MODE" == "clean" ]]; then
  rm -rf build build-eventloop build-watchable build-sorter bin
  echo "Removed: build, build-eventloop, build-watchable, build-sorter, bin"
  exit 0
fi

if [[ -z "$BUILD_DIR" ]]; then
  case "$MODE" in
    all) BUILD_DIR="build" ;;
    eventloop) BUILD_DIR="build-eventloop" ;;
    watchable) BUILD_DIR="build-watchable" ;;
    sorter) BUILD_DIR="build-sorter" ;;
    *)
      echo "Unknown mode: $MODE"
      usage
      exit 1
      ;;
  esac
fi

case "$MODE" in
  all)
    cmake -S . -B "$BUILD_DIR" \
      -DBUILD_EVENTLOOP=ON \
      -DBUILD_WATCHABLE=ON \
      -DBUILD_SORTER=ON
    ;;
  eventloop)
    cmake -S . -B "$BUILD_DIR" \
      -DBUILD_EVENTLOOP=ON \
      -DBUILD_WATCHABLE=OFF \
      -DBUILD_SORTER=OFF
    ;;
  watchable)
    cmake -S . -B "$BUILD_DIR" \
      -DBUILD_EVENTLOOP=OFF \
      -DBUILD_WATCHABLE=ON \
      -DBUILD_SORTER=OFF
    ;;
  sorter)
    cmake -S . -B "$BUILD_DIR" \
      -DBUILD_EVENTLOOP=OFF \
      -DBUILD_WATCHABLE=OFF \
      -DBUILD_SORTER=ON
    ;;
  *)
    echo "Unknown mode: $MODE"
    usage
    exit 1
    ;;
esac

cmake --build "$BUILD_DIR" -j

echo "Build finished: mode=$MODE dir=$BUILD_DIR"
