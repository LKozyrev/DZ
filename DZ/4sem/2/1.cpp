#include<iostream>
#include <deque>
#include<vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>
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
	void Input() {
		std::cout << "Name = " << name << std::endl;
		std::cout << "Priority = " << priority;
	}
};
class queue_of_tasks {
private:
	std::deque<Task> tasks;
public:

	/*queue_of_tasks(std::deque<Task> taSk) {
		this->tasks = taSk;
	}
	queue_of_tasks(){}*/


	void add(Task task) {
		if (task.priority) {
			tasks.push_front(task);
		}
		else {
			tasks.push_back(task);
		}
	}
	void complete(int number) {
		tasks[number].Input();
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
	void Input_queue() {
		for (unsigned i{}; i < tasks.size(); i++) {
			tasks[i].Input();
			std::cout << std::endl;
		}
	}
};
int main() {
	int numberoftasks;
	std::cout << "Input the number of tasks: ";
	std::cin >> numberoftasks;
	std::cout << std::endl;

	std::vector<bool> priorities;
	for (int i = 0; i < numberoftasks; i++) {
		std::srand(std::time(0)); // »нициализаци€ генератора случайных чисел
		int random_number = std::rand() % (2) ;
		priorities.push_back(bool(random_number));
		std::cout <<"Priority = "<< priorities[i]<<std::endl;
	}

	queue_of_tasks Queue;

	for (int i = 0; i < numberoftasks; i++) {
		std::string name;
		std::cout << "Task name: ";
		std::cin >> name;
		Task task(name, priorities[i]);
		Queue.add(task);
	}

	Queue.Input_queue();

	Queue.complete(2);
	Queue.Size();
	std::cout << std::endl;
	Queue.Input_queue();
}