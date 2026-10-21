#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using modif = std::vector<std::pair<std::string, double>>;
std::map<std::string, modif> getModifiers(std::filesystem::path path) {
	std::map<std::string, modif> modifiers;

	for (const auto& entry :
	     std::filesystem::recursive_directory_iterator(path)) {
		std::string name;
		if (!entry.is_regular_file()) continue;

		if (entry.path().extension() != ".mod") continue;

		// gets .mod
		std::filesystem::path modPath = entry.path();
		std::ifstream file(modPath);
		// extracts modifier
		modif i;
		std::string line;
		if (!file.is_open()) {
			std::cout << "Couldn't Open .mod file at " << modPath;
			continue;
		}
		int j = 0;
		while (std::getline(file, line)) {
			// Sets name
			if (j == 0) {
				name = line;
				j++;
				continue;
			}
			// Gets line and puts it in vector seperated by whitespace
			std::stringstream ss(line);

			std::string word;
			std::vector<std::string> words;
			while (ss >> word) {
				words.emplace_back(word);
			}
			if (words.size() < 2) {
				std::cerr << "Warning: Invalid modifier line in " << modPath
				          << ": \"" << line << "\"\n";
				continue;
			}
			std::pair<std::string, double> values;
			values.first = words.at(0);

			try {
				values.second = std::stod(words.at(1));
			} catch (const std::invalid_argument&) {
				std::cerr << "Warning: Invalid modifier value in " << modPath
				          << ": " << words.at(1) << '\n';
				continue;
			} catch (const std::out_of_range&) {
				std::cerr << "Warning: Modifier value out of range in "
				          << modPath << ": " << words.at(1) << '\n';
				continue;
			}

			i.emplace_back(values);
			i.emplace_back(values);
		}
		modifiers[name] = i;
	}

	return modifiers;
}
