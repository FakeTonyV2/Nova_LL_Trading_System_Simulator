# Low Latency Trading System Simulator

A deterministic, event-driven trading system simulator designed to study latency, throughput, and concurrency tradeoffs in performance-critical infrastructure

---
## Motivation
I'm aiming to build a simulated exchange + trading engine capable of processing millions of events per second while maintaining predictable latency under load. This project intentionally explores: predictable latency, memory efficiency, and scalability under sustained load.

The goal is not to produce profitable trading strategies, but to design and evaluate a system that resembles the core execution path of real trading infrastructure. 

As a note, this project will run entirely on commodity hardware and focuses on architectural and algorithmic trade-offs rather than hardware-specific optimizations.

---
## Design Goals
1. Build a C++ system capable of processing 1 million+ events per second with a deterministic P99 latency of <10 microseconds.
2. Deterministic latency behavior under load
3. Bounded memory allocation during steady state operation
4. Clear ownership of concurrency primitives
5. Observable performance characteristics
6. Reproducible benchmarking
   
--- 
## Non Goals
1. No live trading
2. No Exchange Connectivity (may be implemented later)
3. No Alpha Research
4. Minimal to no Machine Learning Models

