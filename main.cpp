#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <utility>
#include <vector>

void bubble_sort(std::vector<int> &a) {
  int n = static_cast<int>(a.size());
  for (int i = 0; i < n - 1; ++i) {
    bool swapped = false;
    for (int j = 0; j < n - i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        std::swap(a[j], a[j + 1]);
        swapped = true;
      }
    }
    if (!swapped)
      break;
  }
}

void insertion_sort(std::vector<int> &a) {
  int n = a.size();

  for (int i = 1; i < n; i++) {
    int temp = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > temp) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = temp;
  }
}

void merge(std::vector<int> &a, int left, int mid, int right) {
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
}

void merge_sort(std::vector<int> &a, int left, int right) {
  if (left >= right) {
    return;
  }

  int mid = left + (right - left) / 2;
  merge_sort(a, left, mid);
  merge_sort(a, mid + 1, right);
  merge(a, left, mid, right);
}

int partition(std::vector<int> &a, int low, int high) {
  int pivot = a[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (a[j] < pivot) {
      i++;
      std::swap(a[i], a[j]);
    }
  }

  std::swap(a[i + 1], a[high]);
  return i + 1;
}

void quick_sort(std::vector<int> &a, int low, int high) {
  if (low < high) {
    int pivot_index = partition(a, low, high);
    quick_sort(a, low, pivot_index - 1);
    quick_sort(a, pivot_index + 1, high);
  }
}

// Helper functions
std::vector<int> generate_random_vector(int length);
void print_vector(const std::vector<int> &vec, 
                  int highlight1 = -1,
                  int highlight2 = -1, 
                  int pivotIndex = -1);
template <typename Func> double time_sort(Func function, std::vector<int> &a);
bool is_sorted(const std::vector<int> &vec);
void display_sort_result(const std::vector<int> &vec, double time);
void run_benchmark(const std::vector<int> &data);

void visualize_pause() {
  std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

// Visual version of algorithms
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

void merge_sort_visual(std::vector<int> &a, int left, int right,
                       int depth = 0) {
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

void quick_sort_visual(std::vector<int> &a, int low, int high, int depth = 0) {
  if (low < high) {
    int pivot_index = partition_visual(a, low, high, depth);
    quick_sort_visual(a, low, pivot_index - 1, depth + 1);
    quick_sort_visual(a, pivot_index + 1, high, depth + 1);
  }
}

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

template <typename Func> double time_sort(Func function, std::vector<int> &a) {
  auto start = std::chrono::high_resolution_clock::now();
  function(a);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  return elapsed.count();
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
