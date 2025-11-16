#include "sorts.h"
#include "utils.h"
#include "visualizer.h"
#include <iostream>
#include <vector>

int main() {
  int choice;
  std::cout << "========== Sorting algorithm visualizer ==========\n";
  std::cout << "What sorting algorithm do you want to see?\n"
            << "[1] Bubble sort\n"
            << "[2] Insertion sort\n"
            << "[3] Merge sort\n"
            << "[4] Quick sort\n"
            << "[5] Sorting algorithms benchmark\n"
            << "Enter choice: ";
  std::cin >> choice;

  if (!std::cin || choice < 1 || choice > 5) {
    std::cerr << "Invalid choice\n";
    return 1;
  }

  int length;
  std::cout << "Choose the length of the random array to sort: ";
  std::cin >> length;

  if (!std::cin || length <= 0) {
    std::cerr << "Invalid length\n";
    return 1;
  }

  bool visualize = false;
  if (choice >= 1 && choice <= 4 && length <= 50) {
    char vis_choice;
    std::cout << "Enable step-by-step visualization? (y/n): ";
    std::cin >> vis_choice;
    visualize = (vis_choice == 'y' || vis_choice == 'Y');
  }

  std::vector<int> vector_to_sort = generate_random_vector(length);

  if (length <= 50 && !visualize) {
    std::cout << "\nInitial array:\n";
    print_vector(vector_to_sort);
  }

  switch (choice) {
  case 1: {
    std::cout << "\nBubble sort:\n";
    if (visualize && length <= 50) {
      bubble_sort_visual(vector_to_sort);
    } else {
      auto copy = vector_to_sort;
      double time = time_sort([](std::vector<int> &v) { bubble_sort(v); }, copy);
      display_sort_result(copy, time);
    }
    break;
  }
  case 2: {
    std::cout << "\nInsertion sort:\n";
    if (visualize && length <= 50) {
      insertion_sort_visual(vector_to_sort);
    } else {
      auto copy = vector_to_sort;
      double time = time_sort([](std::vector<int> &v) { insertion_sort(v); }, copy);
      display_sort_result(copy, time);
    }
    break;
  }
  case 3: {
    std::cout << "\nMerge sort:\n";
    if (visualize && length <= 50) {
      merge_sort_visual(vector_to_sort, 0, static_cast<int>(vector_to_sort.size()) - 1);
      std::cout << "Final sorted array:\n";
      print_vector(vector_to_sort);
    } else {
      auto copy = vector_to_sort;
      double time = time_sort(
          [&](std::vector<int> &v) {
            merge_sort(v, 0, static_cast<int>(v.size()) - 1);
          },
          copy);
      display_sort_result(copy, time);
    }
    break;
  }
  case 4: {
    std::cout << "\nQuick sort:\n";
    if (visualize && length <= 50) {
      quick_sort_visual(vector_to_sort, 0,
                        static_cast<int>(vector_to_sort.size()) - 1);
      std::cout << "Final sorted array:\n";
      print_vector(vector_to_sort);
    } else {
      auto copy = vector_to_sort;
      double time = time_sort(
          [&](std::vector<int> &v) {
            quick_sort(v, 0, static_cast<int>(v.size()) - 1);
          },
          copy);
      display_sort_result(copy, time);
    }
    break;
  }
  case 5: {
    run_benchmark(vector_to_sort);
    break;
  }
  default:
    std::cerr << "Error. Option not available\n";
    return 1;
  }

  return 0;
}