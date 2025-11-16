#ifndef SORTS_H
#define SORTS_H

#include <vector>

void bubble_sort(std::vector<int> &a);
void insertion_sort(std::vector<int> &a);
void merge_sort(std::vector<int> &a, int left, int right);
void quick_sort(std::vector<int> &a, int low, int high);

#endif