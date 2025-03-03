#include<iostream>
#include <deque>
#include<vector>
#include <algorithm>
#include <random>
class Task {
public:
	std::string name;
	bool priority;
	Task(std::string name, int priority) {
		this->name = name;
		this->priority = priority;
	}
	Task() {
		this->name = "Undefined"; 
		this->priority = false;
	}
};
class queue_of_tasks{
private:
	std::deque<Task> tasks;
public:

	queue_of_tasks(std::deque<Task> taSk) {
		this->tasks = taSk;
	}
	queue_of_tasks(){}
	

	void add(Task task) {
		if (task.priority) {
			tasks.push_front(task);
		}
		else {
			tasks.push_back(task);
		}
	}
	void complete(int number) {
		tasks.erase(tasks.begin() + number);
	}
	void Size() {
		if (tasks.empty()) {
			std::cout << "Queue is empty";
		}
		else {
			std::cout << "Size of queue = " << tasks.size();
		}
	}
}
int main() {
	int numberoftasks;
	std::cout << "Input the number of tasks: ";
	std::cin >> numberoftasks;
	std::cout << std::endl;

	std::vector<bool> priorities(numberoftasks);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);
	for (bool& value : priorities) {
		value = distrib(gen); // 0 -> false, 1 -> true
	}

	std::vector<Task> tasks;

	for (int i = 0; i < numberoftasks; i++) {
		std::string name;
		std::cout << "Task name: ";
		std::cin >> name;
		tasks

	}
}