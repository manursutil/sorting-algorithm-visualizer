#include "visualizer.h"
#include "utils.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

void visualize_pause() {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

void bubble_sort_visual(std::vector<int> &a) {
  int n = static_cast<int>(a.size());
  std::cout << "Initial state:\n";
  print_vector(a);
  visualize_pause();

  for (int i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        std::swap(a[j], a[j + 1]);
        swapped = true;
        std::cout << "Swapped indices " << j << " and " << j + 1 << ":\n";
        print_vector(a, j, j + 1);
        visualize_pause();
      }
    }
    if (!swapped) {
      std::cout << "No swaps in this pass, array is sorted.\n";
      break;
    }
    std::cout << "End of pass " << i + 1 << ":\n";
    print_vector(a);
    visualize_pause();
  }

  std::cout << "Final sorted array:\n";
  print_vector(a);
}

void insertion_sort_visual(std::vector<int> &a) {
  int n = static_cast<int>(a.size());
  std::cout << "Initial state:\n";
  print_vector(a);
  visualize_pause();

  for (int i = 1; i < n; i++) {
    int temp = a[i];
    int j = i - 1;
    std::cout << "Inserting value " << temp << " at position " << i << ":\n";

    while (j >= 0 && a[j] > temp) {
      a[j + 1] = a[j];
      j--;
      print_vector(a, j + 1, j + 2);
      visualize_pause();
    }
    a[j + 1] = temp;
    std::cout << "Placed " << temp << " at index " << j + 1 << ":\n";
    print_vector(a, j + 1);
    visualize_pause();
  }

  std::cout << "Final sorted array:\n";
  print_vector(a);
}

void merge_visual(std::vector<int> &a, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++) {
    L[i] = a[left + i];
  }
  for (int j = 0; j < n2; j++) {
    R[j] = a[mid + 1 + j];
  }

  int i = 0;
  int j = 0;
  int k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      a[k] = L[i];
      i++;
    } else {
      a[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    a[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    a[k] = R[j];
    j++;
    k++;
  }

  std::cout << "Merged segment [" << left << ", " << right << "]:\n";
  print_vector(a);
  visualize_pause();
}

void merge_sort_visual(std::vector<int> &a, int left, int right, int depth) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;

  merge_sort_visual(a, left, mid, depth + 1);
  merge_sort_visual(a, mid + 1, right, depth + 1);
  std::cout << std::string(depth * 2, ' ') << "Merging range [" << left << ", " << right << "]\n";
  merge_visual(a, left, mid, right);
}

int partition_visual(std::vector<int> &a, int low, int high, int depth) {
  int pivot = a[high];
  std::cout << std::string(depth * 2, ' ') 
            << "Partitioning range [" << low << ", " << high 
            << "], pivot = " << pivot << " at index " << high
            << "\n";

  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (a[j] < pivot) {
      i++;
      std::swap(a[i], a[j]);
      std::cout << std::string(depth * 2, ' ') 
                << "Swapped " << a[i] << " and " << a[j] 
                << " (indices " << i << ", " << j << "):\n";
      print_vector(a, i, j, high);
      visualize_pause();
    }
  }

  std::swap(a[i + 1], a[high]);
  std::cout << std::string(depth * 2, ' ') << "Placed pivot at index " << i + 1 << ":\n";
  print_vector(a, i + 1, -1, i + 1);
  visualize_pause();

  return i + 1;
}

void quick_sort_visual(std::vector<int> &a, int low, int high, int depth) {
  if (low < high) {
    int pivot_index = partition_visual(a, low, high, depth);
    quick_sort_visual(a, low, pivot_index - 1, depth + 1);
    quick_sort_visual(a, pivot_index + 1, high, depth + 1);
  }
}