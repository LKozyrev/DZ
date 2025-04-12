#include<iostream>
#include<vector>
#include<thread>
#include<random>
#include <unordered_set>

void Search(std::vector<int>& b, int start, int end, int target) {
    std::vector<int> a(b.begin() + start, b.begin() + end);
    for (int i = 0; i<a.size(); i++) {
        if (a[i] == target) {
            std::cout << target << " on position " << i << std::endl;
        }
    }
    std::copy(a.begin(), a.begin() + (end - start), b.begin() + start);
}



void SortArray(std::vector<int>& b, int start, int end) {
    std::vector<int> a(b.begin() + start, b.begin() + end);
    if (a.size() <= 1) return;
    //Генерация пивота
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, a.size() - 1);
    int pivotnumber = dist(gen);
    int pivot = a[pivotnumber];

    //Разделение массива

    std::vector<int> less, bigger, equal;
    for (int num : a) {
        if (num < pivot) {
            less.push_back(num);
        }
        else if (num == pivot) {
            equal.push_back(num);
        }
        else {
            bigger.push_back(num);
        }
    }
    //Рекурсия
    if (less.size() > 1) SortArray(less, 0, less.size());
    if (bigger.size() > 1) SortArray(bigger, 0, bigger.size());

    // Сборка результата
    a.clear();
    a.insert(a.end(), less.begin(), less.end());
    a.insert(a.end(), equal.begin(), equal.end());
    a.insert(a.end(), bigger.begin(), bigger.end());

    std::copy(a.begin(), a.begin() + (end - start), b.begin() + start);
}

int main() {
    int array_size, num_of_threads;
    std::cout << "Input array size: ";
    std::cin >> array_size;
    std::cout << "Input number of threads: ";
    std::cin >> num_of_threads;

    std::vector<int> arr(array_size);
    std::vector<std::thread> threads;



    int part_size = array_size / num_of_threads;
    int remaining = array_size % num_of_threads;

    int start = 0;
    for (int i = 0; i < num_of_threads; ++i) {
        int end = start + part_size + (i < remaining ? 1 : 0);

        threads.emplace_back(SortArray, std::ref(arr), start, end);

        start = end;
    }

    for (auto& t : threads) {
        t.join();
    }






    std::vector<std::thread> threads_search;

    for (int i = 0; i < num_of_threads; ++i) {
        int end = start + part_size + (i < remaining ? 1 : 0);

        threads_search.emplace_back(Search, std::ref(arr), start, end, i);

        start = end;
    }
}
