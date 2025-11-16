#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <chrono>

std::vector<int> generate_random_vector(int length);
void print_vector(const std::vector<int> &vec, 
                  int highlight1 = -1,
                  int highlight2 = -1, 
                  int pivotIndex = -1);
bool is_sorted(const std::vector<int> &vec);
void display_sort_result(const std::vector<int> &vec, double time);
void run_benchmark(const std::vector<int> &data);

template <typename Func> 
double time_sort(Func function, std::vector<int> &a) {
  auto start = std::chrono::high_resolution_clock::now();
  function(a);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
}

#endif