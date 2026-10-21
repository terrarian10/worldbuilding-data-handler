#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using modif = std::vector<std::pair<std::string, double>>;

struct slider {
	double minimum;
	double maximum;
	modif minimumEffect;
	modif maximumEffect;
	modif getEffect(double value) {
		modif ret;
		if (value < minimum) {
			value = minimum;
		} else if (value > maximum) {
			value = maximum;
		}
		if (value < 0) {
			for (auto& val : minimumEffect) {
				ret.emplace_back(val.first, val.second * (value / -100));
			}
		} else {
			for (auto& val : maximumEffect) {
				ret.emplace_back(val.first, val.second * (value / 100));
			}
		}
		return ret;
	}
};

std::map<std::string, slider> sliderParser(
    std::filesystem::path path,
    std::map<std::string, modif> modifiers) {
	std::map<std::string, slider> ret;
	for (const auto& entry :
	     std::filesystem::recursive_directory_iterator(path)) {
		std::string name;
		if (!entry.is_regular_file()) continue;

		if (entry.path().extension() != ".sld") continue;

		// gets .sld
		std::filesystem::path sldPath = entry.path();
		std::ifstream file(sldPath);
		// checks
		slider i;
		std::string line;
		if (!file.is_open()) {
			std::cout << "Couldn't Open slider file at " << sldPath;
			continue;
		}
		int j = 0;
		// Parse slider
		std::vector<std::pair<std::string, std::string>> parsedLines;
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
				std::cerr << "Warning: Invalid slider line in " << sldPath
				          << ": \"" << line << "\"\n";
				continue;
			}
			std::pair<std::string, std::string> values;
			values.first = words.at(0);
			values.second = words.at(1);
			parsedLines.emplace_back(values);
		}
		// Parse values
		for (auto& v : parsedLines) {
			if (v.first == "minimum" || v.first == "maximum") {
				try {
					std::size_t pos = 0;
					double value = std::stod(v.second, &pos);

					// std::stod("123abc") succeeds and returns 123,
					// so make sure the ENTIRE string was a number.
					if (pos != v.second.size()) {
						std::cerr << "Warning: '" << v.second
						          << "' is not a valid number for '" << v.first
						          << "'. Skipping.\n";
						continue;
					}

					if (v.first == "minimum") {
						i.minimum = value;
					} else {
						i.maximum = value;
					}

				} catch (const std::invalid_argument&) {
					std::cerr << "Warning: '" << v.second
					          << "' is not a valid number for '" << v.first
					          << "'. Skipping.\n";
					continue;

				} catch (const std::out_of_range&) {
					std::cerr << "Warning: number '" << v.second
					          << "' is out of range for '" << v.first
					          << "'. Skipping.\n";
					continue;
				}
			}

			else if (v.first == "minimumEffect" || v.first == "maximumEffect") {
				auto modifier = modifiers.find(v.second);

				if (modifier == modifiers.end()) {
					std::cerr << "Warning: modifier '" << v.second
					          << "' does not exist for '" << v.first
					          << "'. Skipping.\n";
					continue;
				}

				if (v.first == "minimumEffect") {
					i.minimumEffect = modifier->second;
				} else {
					i.maximumEffect = modifier->second;
				}
			}

			else {
				std::cerr << "Warning: unknown property '" << v.first
				          << "'. Skipping.\n";
				continue;
			}
		}
		ret[name] = i;
	}
	return ret;
}