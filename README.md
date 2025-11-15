# Sorting Algorithm Visualizer

A C++ command-line tool to visualize and compare the performance of different sorting algorithms.

## Features

- **Bubble Sort**: Classic O(n²) sorting algorithm
- **Insertion Sort**: Efficient for small datasets, O(n²) worst case
- **Merge Sort**: Divide-and-conquer approach, O(n log n)
- **Quick Sort**: Fast average-case algorithm, O(n log n)
- **Performance Comparison**: Run all algorithms on the same dataset and compare execution times

## Building

Compile with C++17 or later:

```bash
g++ -std=c++17 -O2 main.cpp -o main
```

## Usage

Run the program:

```bash
./main
```

Then select which sorting algorithm to visualize:
- `[1]` Bubble sort
- `[2]` Insertion sort
- `[3]` Merge sort
- `[4]` Quick sort
- `[5]` Compare all algorithms and display their execution times

Enter the array size when prompted. The program will generate a random array, sort it, and display:
- The initial array
- The sorted array (for single algorithm selections)
- Execution time in milliseconds

## Example

```
========== Sorting algorithm visualizer ==========
What sorting algorithm do you want to see?
[1] Bubble sort
[2] Insertion sort
[3] Merge sort
[4] Quick sort
[5] Compare time of all sorting algorithms
Enter choice: 5
Choose the length of the random array to sort: 100

Initial array:
89 98 37 90 50 1 35 1 3 85 35 84 68 32 56 2 13 28 39 66 5 30 10 1 32 88 51 24 63 47 59 47 9 27 9 99 10 73 95 53 74 51 60 74 10 40 19 40 97 31 86 71 58 86 56 67 14 96 86 35 92 96 81 46 87 31 6 87 9 56 29 79 74 83 39 75 66 47 54 68 96 83 92 74 4 59 38 12 39 33 94 86 69 1 19 25 11 35 10 28 

Bubble sort time: 0.058 ms
Insertion sort time: 0.024 ms
Merge sort time: 0.074 ms
Quick sort time: 0.011 ms
```

## Requirements

- C++17 compatible compiler (g++, clang, etc.)
- Standard C++ library

## Notes

- Execution times are measured in milliseconds with precision to 3 decimal places
- Arrays are generated with random integers between 1 and 100
- For very large arrays, bubble sort may take significantly longer than other algorithms
