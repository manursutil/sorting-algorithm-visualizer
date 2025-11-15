#include <iostream>
#include <random>
#include <ratio>
#include <utility>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

void bubble_sort(std::vector<int>& a) {
    int n = static_cast<int>(a.size());
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
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
        int piv = partition(a, low, high);
        quick_sort(a, low, piv - 1);
        quick_sort(a, piv + 1, high);
    }
}

std::vector<int> generate_random_vector(int length);
void print_vector(std::vector<int> vec);

int main() {
    int choice;
    std::cout << "========== Sorting algorithm visualizer ==========\n";
    std::cout << "What sorting algorithm do you want to see?\n" << 
    "[1] Bubble sort\n" << 
    "[2] Insertion sort\n" << 
    "[3] Merge sort\n" << 
    "[4] Quick sort\n" <<
    "[5] Compare time of all sorting algorithms\n" <<
    "Enter choice: ";
    std::cin >> choice;
    
    int length;
    std::cout << "Choose the length of the random array to sort: ";
    std::cin >> length;
    
    std::vector<int> vector_to_sort = generate_random_vector(length);
    std::cout << "Initial array:\n";
    print_vector(vector_to_sort);

    if (choice == 1) {
        std::cout << "Bubble sort:\n";

        auto start = std::chrono::high_resolution_clock::now();
        bubble_sort(vector_to_sort);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        print_vector(vector_to_sort);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << elapsed.count() << " ms\n";
    } else if (choice == 2) {
        std::cout << "Insertion sort:\n";

        auto start = std::chrono::high_resolution_clock::now();
        insertion_sort(vector_to_sort);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        print_vector(vector_to_sort);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << elapsed.count() << " ms\n";
    } else if (choice == 3) {
        std::cout << "Merge sort:\n";

        auto start = std::chrono::high_resolution_clock::now();
        merge_sort(vector_to_sort, 0, length - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        print_vector(vector_to_sort);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << elapsed.count() << " ms\n";
    } else if (choice == 4) {
        std::cout << "Quick sort:\n";

        auto start = std::chrono::high_resolution_clock::now();
        quick_sort(vector_to_sort, 0, length - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        print_vector(vector_to_sort);
        std::cout << "Time: " << std::fixed << std::setprecision(3) << elapsed.count() << " ms\n";
    } else if (choice == 5) {
        // Bubble sort
        auto bubble_input = vector_to_sort;
        auto start_bubble = std::chrono::high_resolution_clock::now();
        bubble_sort(bubble_input);
        auto end_bubble = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_bubble = end_bubble - start_bubble;

        // Insertion sort
        auto insertion_input = vector_to_sort;
        auto start_insertion = std::chrono::high_resolution_clock::now();
        insertion_sort(insertion_input);
        auto end_insertion = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_insertion = end_insertion - start_insertion;

        // Merge sort
        auto merge_input = vector_to_sort;
        auto start_merge = std::chrono::high_resolution_clock::now();
        merge_sort(merge_input, 0, length - 1);
        auto end_merge = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_merge = end_merge - start_merge;

        // Quick sort
        auto quick_input = vector_to_sort;
        auto start_quick = std::chrono::high_resolution_clock::now();
        quick_sort(quick_input, 0, length - 1);
        auto end_quick = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed_quick = end_quick - start_quick;

        // Print only times
        std::cout << "Bubble sort time: " << std::fixed << std::setprecision(3) << elapsed_bubble.count() << " ms\n";
        std::cout << "Insertion sort time: " << std::fixed << std::setprecision(3) << elapsed_insertion.count() << " ms\n";
        std::cout << "Merge sort time: " << std::fixed << std::setprecision(3) << elapsed_merge.count() << " ms\n";
        std::cout << "Quick sort time: " << std::fixed << std::setprecision(3) << elapsed_quick.count() << " ms\n";
    } else {
        std::cout << "Error. Option not available\n";
    }
   
    return 0;
}

std::vector<int> generate_random_vector(int length) {
    std::vector<int> random_vector;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < length; i++) {
        int random_number = dist(gen);
        random_vector.push_back(random_number);
    }

    return random_vector;
}

void print_vector(std::vector<int> vec) {
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}
