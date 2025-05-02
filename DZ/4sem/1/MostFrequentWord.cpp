#include<iostream>
#include<map>
#include<string>
#include<algorithm>
int main() {
	std::map<std::string, int> frequency;
	std::string word;
	while (std::cin >> word) {
		frequency[word]++;
	}
	auto most_freq_it = std::max_element(frequency.begin(), frequency.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
		}
	);

	std::cout<<"Most frequent word is " << most_freq_it->second;
}