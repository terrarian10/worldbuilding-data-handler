#include "biome.cpp"
#include "buildings.cpp"
#include "consts.cpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct province {
	std::string name;
	bool isOwned = true;
	bool isCore = true;
	biome terrain;
	int populationBase = 0;
	int population = 0;
	int carryingCapacity;
	std::vector<building> buildings;
	std::string resource;
	int buildingSlots = 0;
	double autonomy = 0.0;
	double unrest = 0.0;
	double defenseMod = 1.0;
	province() = default;
	province(const std::filesystem::path& path) {
		std::fstream file(path);
		if (!file.is_open()) {
			std::cout << "Invalid Path " << path << " Creating empty province";
			return;
		}
		std::map<std::string, std::vector<std::string>> parsed;
		std::string line;
		int j = 0;
		// Generate Parsed
		while (std::getline(file, line)) {
			if (j == 0) {
				j++;
				name = line;
				continue;
			}
			std::vector<std::string> words;
			std::string heading;
			int z = 0;
			std::stringstream ss(line);
			std::string word;
			while (ss >> word) {
				if (z == 0) {
					z++;
					heading = word;
					continue;
				}
				words.emplace_back(word);
			}
			parsed[heading] = words;
		}
		try {
			populationBase = std::stoi(parsed["populationBase"].at(0));
			terrain = stringToBiome[parsed["biome"].at(0)];
			resource = parsed["resource"].at(0);
			for (auto& z : parsed["building"]) {
				buildings.emplace_back(stringToBuilding[z]);
			}
			isCore = (parsed["core"].at(0) == "true") ? true : false;
			isOwned = (parsed["owned"].at(0) == "true") ? true : false;
			population = std::stoi(parsed["population"].at(0));
			autonomy = std::stod(parsed["autonomy"].at(0));
			unrest = std::stod(parsed["unrest"].at(0));
			defenseMod = 1;
			defenseMod *= terrain.defenseMod;
			for (auto& b : buildings) {
				defenseMod *= b.defenseMod;
			}
		} catch (const std::invalid_argument&) {
			std::cout << "Invalid Province File " << path
			          << " Creating empty province";
		}
	}
};
