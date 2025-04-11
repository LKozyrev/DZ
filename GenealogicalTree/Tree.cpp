#include<iostream>
#include<vector>
#include<map>
#include <string>
#include<queue>
struct Person {
	std::string name;
	std::vector<std::string> children;
};
class GenTree {
private:
	std::map<std::string, Person> people;
	std::map<std::string, int> levels;
public:
	void AddPerson(std::string& name) {
		if (people.find(name) == people.end()) {
			people[name] = { name, {}};
		}
	}
	void ParentsAndChildren(std::string parent, std::string child) {
		if (people.find(parent) != people.end() && people.find(child) != people.end()) {
			people[parent].children.push_back(child);
		}
	}

	void calculateLevels() {
		if (people.empty()) return;

		std::vector<std::string> roots;
		for (auto it = people.begin(); it!=people.end(); it++) {
			std::string name = it->first;
			Person person = it->second;
			bool hasParent = false;
			for (auto it1 = people.begin(); it1 != people.end(); it1++) {
				Person person1 = it1->second;
				if (std::find(person1.children.begin(), person1.children.end(), name) != person1.children.end()) {
					hasParent = true;
					break;
				}
			}
			if (!hasParent) roots.push_back(name);
		}
		for (const auto& root : roots) {
			std::queue<std::string> q;
			q.push(root);
			levels[root] = 0;

			while (!q.empty()) {
				std::string current = q.front();
				q.pop();

				for (const auto& child : people[current].children) {
					levels[child] = levels[current] + 1;
					q.push(child);
				}
			}
		}
	}

	void Print() {
		for (auto it = people.begin(); it != people.end(); it++) {
			std::cout << "Name " << it->first << std::endl;
			std::cout << "Level = " << levels[it->first]<<std::endl;
			std::cout << std::endl;
			
		}
	}


};

int main() {
	GenTree tree;

	int number;
	std::cout << "Input the number of people: ";
	std::cin >> number;
	std::cin.ignore();

	for (int i = 0; i < number-1; i++) {
		std::string line;
		std::getline(std::cin, line);
		size_t space_pos = line.find(' ');
		std::string first = line.substr(0, space_pos); 
		std::string second = line.substr(space_pos + 1);


		tree.AddPerson(first);
		tree.AddPerson(second);
		tree.ParentsAndChildren(second, first);
		tree.calculateLevels();

	}
	tree.Print();
}