#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <vector>

void bubble_sort_visual(std::vector<int> &a);
void insertion_sort_visual(std::vector<int> &a);
void merge_sort_visual(std::vector<int> &a, int left, int right, int depth = 0);
void quick_sort_visual(std::vector<int> &a, int low, int high, int depth = 0);

#endif