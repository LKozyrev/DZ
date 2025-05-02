#pragma once
#include<vector>
#include<iostream>
void QuickSort(std::vector<int>& a);
void InsertionSort(std::vector<int>& a);
void merge(std::vector<int>& a, int left, int mid, int right);
void mergeSort(std::vector<int>& a, int left, int right);
void mergeSort(std::vector<int>& a);
void BubbleSort(std::vector<int>& a);
void Print(std::vector<int> a);
std::vector<int> InputArray();
void Mixed(std::vector<int>& a);
