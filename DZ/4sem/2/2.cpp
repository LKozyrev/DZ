#include<iostream>
#include<map>

class TelephoneDirectory{
private:
	std::map<std::string, std::string> contacts;
public:
	void Add(std::string name, std::string number) {
		contacts.emplace(name, number);
	}
	void Delete(std::string name) {
		contacts.erase(name);
	}
	std::string Search(std::string name) {
		return contacts[name];
	}
	void Input() {
		for (auto it = contacts.begin(); it != contacts.end(); ++it) {
			std::cout << "Name = " << it->first << ", number = " << it->second << std::endl;
		}
	}
};

int main() {
	unsigned n;
	std::cout << "Input the number of contacts: ";
	std::cin >> n;

	TelephoneDirectory directory;

	for (unsigned i = 0; i < n; i++) {
		std::string name, number;
		std::cout << "Input name: ";
		std::cin >> name;
		std::cout << "Input number : ";
		std::cin >> number;
		directory.Add(name, number);
	}

	std::cout << std::endl;

	directory.Input();
	std::cout << std::endl;

	std::cout << std::endl << "Number of Alexander is " << directory.Search("Alexander") << std::endl;

	directory.Add("Pedro", "4787187481");
	directory.Input();
	std::cout << std::endl;

	directory.Delete("Messi");
	directory.Input();
}