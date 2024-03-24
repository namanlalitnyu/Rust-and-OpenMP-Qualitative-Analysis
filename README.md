# Rust-vs-OpenMP-Benchmarking-Code
This repository consists of different programs written for benchmarking Rust and C++.

THe Generic Project Structure is as follows:

```bash
├───OpenMP
│   ├───<Benchmark Parameter 1>
│   │   ├───<benchmark_file_1.cpp>
│   │   └───<benchmark_file_2.cpp>
│   └───<Benchmark Parameter 2>
│       ├───<benchmark_file_1.cpp>
│       └───<benchmark_file_2.cpp>
├───Python - Test Case Builder
│   └───<python_helper_files.py>
├───Rust
│   ├───<Benchmark Parameter 1>
│   │   ├───<benchmark_file_1.rs>
│   │   └───<benchmark_file_2.rs>
│   └───<Benchmark Parameter 2>
│       ├───<benchmark_file_1.rs>
│       └───<benchmark_file_2.rs>
└───Test Inputs
    ├───<BenchmarkParameter_ProgramName_1.txt>
    └───<BenchmarkParameter_ProgramName_2.txt>
```
