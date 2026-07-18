# Nova L2

Nova L2 is a deterministic C++20 limit-order-book simulator for studying bounded allocation, event replay, and latency. It is deliberately a foundation: the matching path is single-threaded, while feed input and execution output use bounded SPSC queues so consumers can be decoupled from the matcher.

## Quick start

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
./build/nova_replay data/sample.csv
```

Replay rows use the normalized format `timestamp_ns,event_type,order_id,price,size,side[,order_type]`, where event types are `1=add`, `2=cancel`, `3=execute`, `4=delete`, sides are `1=buy`, `2=sell`, and order types are `1=limit`, `2=market`. The feed handler is intentionally non-real-time: timestamps are carried as the simulation clock and input is drained as fast as the consumer allows.

## Development

Open the repository in the supplied devcontainer, or use the CMake commands above. `NOVA_ENABLE_SANITIZERS=ON` enables ASan/UBSan for debug work. `nova_tests` covers the basic add, cross, fill-publication, and cancel path; `nova_benchmark` is a lightweight smoke benchmark, not a statistically rigorous latency claim.

`AsyncLogger` is provided for non-blocking producer-side logging: the matcher-side producer only enqueues a fixed-size record, while a background owner calls `drain()` and performs file I/O. The next planned slices are Prometheus text-file metrics, richer LOBSTER column mapping, and a Google Benchmark target. Any latency threshold must be calibrated per runner; CI should not claim a universal sub-microsecond guarantee on shared commodity runners.
