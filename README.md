# Rust-vs-OpenMP-Benchmarking-Code
This repository consists of different programs written for benchmarking Rust and C++.

The Generic Project Structure is as follows:

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

Steps to run the code on Crunchy1:
```
1. SSH into cims using: ssh <netID>@access.cims.nyu.edu
2. SSH into crunchy1 using: ssh crunchy1
3. Once the zip file is unzipped, and the contents are available, we will load the latest gcc module.
4. Load gcc-11.2 using: module load gcc-11.2
5. To compile matrix_multiplication.cpp, use: g++ -fopenmp -o <objectname> matrix_multiplication.cpp
6. To measure the time, use the following command: time ./<objectname> <square_matrix_length> <num_threads>
7. To compile merge_sort.cpp, use: g++ -fopenmp -o <objectname> merge_sort.cpp -lgomp
8. To measure the time, use the following command: time ./<objectname> <array_size> <num_threads>
9. To compile the Rust Code for matrix_multiplication, go into Rust\Scalability\matrix_multiplication.
10. Build release version using: cargo build --release
11. Run this release version using: cargo run --release <square_matrix_length> <num_threads>
12. To compile the Rust Code for merge_sort, go into Rust\Scalability\merge_sort.
13. Build release version using: cargo build --release
14. Run this release version using: cargo run --release <array_size> <num_threads>
```