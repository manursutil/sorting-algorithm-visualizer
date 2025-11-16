#include "utils.h"
#include "sorts.h"
#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

std::vector<int> generate_random_vector(int length) {
  std::vector<int> random_vector;
  random_vector.reserve(length);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 100);

  for (int i = 0; i < length; i++) {
    int random_number = dist(gen);
    random_vector.push_back(random_number);
  }

  return random_vector;
}

void print_vector(const std::vector<int> &vec, int highlight1, int highlight2, int pivotIndex) {
  for (std::size_t i = 0; i < vec.size(); ++i) {
    bool isHighlight = (static_cast<int>(i) == highlight1) || (static_cast<int>(i) == highlight2);
    bool isPivot = (static_cast<int>(i) == pivotIndex);

    if (isPivot) {
      std::cout << "{" << vec[i] << "} ";
    } else if (isHighlight) {
      std::cout << "[" << vec[i] << "] ";
    } else {
      std::cout << vec[i] << " ";
    }
  }
  std::cout << "\n";
}

bool is_sorted(const std::vector<int> &vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

void display_sort_result(const std::vector<int> &vec, double time) {
  if (!is_sorted(vec)) {
    std::cerr << "Error sorting the array\n";
    std::exit(1);
  }

  if (vec.size() <= 50) {
    print_vector(vec, -1, -1, -1);
  }

  std::cout << "\nTime: " << std::fixed << std::setprecision(3) << time << "ms\n";
}

void run_benchmark(const std::vector<int> &data) {
  struct SortResult {
    std::string name;
    double time;
    bool success;
  };

  std::vector<SortResult> results;

  auto bubble_input = data;
  double bubble_time =
      time_sort([](std::vector<int> &v) { bubble_sort(v); }, bubble_input);
  results.push_back({"Bubble sort", bubble_time, is_sorted(bubble_input)});

  auto insertion_input = data;
  double insertion_time = time_sort(
      [](std::vector<int> &v) { insertion_sort(v); }, insertion_input);
  results.push_back(
      {"Insertion sort", insertion_time, is_sorted(insertion_input)});

  auto merge_input = data;
  double merge_time = time_sort(
      [](std::vector<int> &v) {
        merge_sort(v, 0, static_cast<int>(v.size()) - 1);
      },
      merge_input);
  results.push_back({"Merge sort", merge_time, is_sorted(merge_input)});

  auto quick_input = data;
  double quick_time = time_sort(
      [](std::vector<int> &v) {
        quick_sort(v, 0, static_cast<int>(v.size()) - 1);
      },
      quick_input);
  results.push_back({"Quick sort", quick_time, is_sorted(quick_input)});

  std::sort(
      results.begin(), results.end(),
      [](const SortResult &a, const SortResult &b) { return a.time < b.time; });

  std::cout << "\nAlgorithm           Time (ms)      Status\n";
  std::cout << "---------------------------------------------\n";
  for (std::size_t i = 0; i < results.size(); i++) {
    std::cout << (i + 1) << ". " << std::setw(18) << std::left
              << results[i].name << std::setw(15) << std::fixed
              << std::setprecision(3) << results[i].time
              << (results[i].success ? "OK" : "FAILED") << "\n";
  }
}