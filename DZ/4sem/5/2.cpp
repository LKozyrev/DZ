#include<iostream>
#include<vector>
#include<thread>
#include<random>

void FillArray(std::vector<int>& arr, int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 1000);

    for (int i = start; i < end; ++i) {
        arr[i] = dist(gen);
    }
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
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

        threads.emplace_back(FillArray, std::ref(arr), start, end);

        start = end;
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int i = 0; i < array_size; i++) {
        std::cout << arr[i] << std::endl;
    }


}