# Sorting Algorithm Visualizer

A small C++ command-line tool to run, verify and compare the performance of common sorting algorithms.

## Features

- Bubble Sort (O(n²))
- Insertion Sort (O(n²))
- Merge Sort (O(n log n))
- Quick Sort (O(n log n) average)
- Built-in timing helper (`time_sort`) and verification (`is_sorted`)
- Compare mode: run all algorithms on the same input and print their times with correctness status

## Modules

- `main.cpp`: CLI entry point that gathers user choices, sets up runs, and delegates to sorting/visualization helpers.
- `sorts.h/cpp`: Pure algorithm implementations for bubble, insertion, merge, and quick sort.
- `visualizer.h/cpp`: Step-by-step visual versions of each algorithm with pauses and annotated output.
- `utils.h/cpp`: Shared helpers for generating random data, printing arrays, timing, displaying results, and benchmarking.

## Building

Compile with a C++17-compatible compiler. Optimized builds are recommended for realistic timings:

```bash
g++ -std=c++17 -O2 -o sorting main.cpp sorts.cpp visualizer.cpp utils.cpp
```

- Execution times are measured in milliseconds with precision to 3 decimal places
- Arrays are generated with random integers between 1 and 100

## Usage

Run the program:

```bash
./sorting
```

Menu options:
- `[1]` Bubble sort — run and show sorted array + time
- `[2]` Insertion sort — run and show sorted array + time
- `[3]` Merge sort — run and show sorted array + time
- `[4]` Quick sort — run and show sorted array + time
- `[5]` Compare all algorithms and display their execution times with verification

When prompted, enter the array size (positive integer). The program generates a random array of integers in range [1, 100].

Behavior notes:
- For readability, the program only prints the initial array when the length is <= 50.
- Single-algorithm choices print the sorted array (from a copy used for timing) and the measured time in milliseconds.
- Choice `5` (compare mode) runs each algorithm on a copy of the same input, times it using the `time_sort` helper (which measures only the sort call), and prints each algorithm's time followed by `(OK)` or `(FAILED)` depending on whether the result is sorted.
- Timing precision: times are printed in milliseconds with three decimal places.

## Example (compare mode)

User selects option 5 and array length 100:

```
========== Sorting algorithm visualizer ==========
What sorting algorithm do you want to see?
[1] Bubble sort
[2] Insertion sort
[3] Merge sort
[4] Quick sort
[5] Sorting algorithms benchmark
Enter choice: 5
Choose the length of the random array to sort: 100

Algorithm           Time (ms)      Status
---------------------------------------------
1. Quick sort        0.022          OK
2. Insertion sort    0.061          OK
3. Bubble sort       0.150          OK
4. Merge sort        0.177          OK
```

## Notes & recommendations

- Complexity matters: bubble/insertion are O(n²) and will be extremely slow for very large arrays (e.g. 1,000,000 elements). Prefer merge/quick or `std::sort` for large inputs.
- Always compile with optimizations (`-O2` / `-O3`) when measuring performance.
- For more stable numbers, run multiple trials and average or report median/stddev. I can add a benchmarking mode that repeats each sort and reports statistics if you want.
