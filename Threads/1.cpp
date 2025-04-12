#include<iostream>
#include<vector>
#include<thread>

void PrintThread(int thread_id, const int number_of_threads) {
	std::cout << "Thread ID = " << thread_id << std::endl;
	std::cout << "Total number of threads = " << number_of_threads << std::endl;
	std::cout << "Hello world" << std::endl;
}

int main() {
	int number_of_threads;
	std::cout << "input the number of threads: ";
	std::cin >> number_of_threads;

	std::vector<std::thread> threads;
	std::cout << "Input threads ID: " << std::endl;
	for (int i = 0; i < number_of_threads; i++) {
		int id;
		std::cin >> id;
		threads.emplace_back(PrintThread, id, number_of_threads);
	}

	for (auto& thread : threads){
		thread.join();
	}

}

