#include "sorts.h"
#include <algorithm>
#include <utility>

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