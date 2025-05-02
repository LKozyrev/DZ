#include<iostream>
#include <random>
#include <chrono>
#include "Header.h"
int main() {
	const int size = 10000;
    std::vector<int> numbers(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, size);
    for (int& num : numbers) {
        num = dist(gen);
    }

    auto start1 = std::chrono::high_resolution_clock::now();
    QuickSort(numbers);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto ms1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    std::cout << "Quick sort: Time of execution = " << ms1.count() << " ms" << std::endl;


    auto start2 = std::chrono::high_resolution_clock::now();
    mergeSort(numbers);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "Merge sort: Time of execution = " << ms2.count() << " ms" << std::endl;

    auto start3 = std::chrono::high_resolution_clock::now();
    InsertionSort(numbers);
    auto end3 = std::chrono::high_resolution_clock::now();
    auto ms3 = std::chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
    std::cout << "Insertion sort: Time of execution = " << ms3.count() << " ms" << std::endl;

    auto start4 = std::chrono::high_resolution_clock::now();
    BubbleSort(numbers);
    auto end4 = std::chrono::high_resolution_clock::now();
    auto ms4 = std::chrono::duration_cast<std::chrono::milliseconds>(end4 - start4);
    std::cout << "Bubble sort: Time of execution = " << ms4.count() << " ms" << std::endl;

    auto start5 = std::chrono::high_resolution_clock::now();
    Mixed(numbers);
    auto end5 = std::chrono::high_resolution_clock::now();
    auto ms5 = std::chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
    std::cout << "Mixed quick and insertion sort: Time of execution = " << ms5.count() << " ms" << std::endl;
}