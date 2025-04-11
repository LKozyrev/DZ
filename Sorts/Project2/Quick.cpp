#include<random>
#include <algorithm>
#include "Header.h"


void QuickSort(std::vector<int>& a) {
    if (a.size() <= 1) return;
//Генерация пивота
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<int> dist(0, a.size()-1);
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
    if (less.size() > 1) QuickSort(less);
    if (bigger.size() > 1) QuickSort(bigger);

 // Сборка результата
    a.clear();
    a.insert(a.end(), less.begin(), less.end());
    a.insert(a.end(), equal.begin(), equal.end());
    a.insert(a.end(), bigger.begin(), bigger.end());

}