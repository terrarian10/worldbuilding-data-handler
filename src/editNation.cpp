#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void nationEdit(std::filesystem::path nation) {
	std::cout << "Nation link established. Type help for a list of commands, "
	             "or quit to quit"
	          << std::endl;
	std::string c;
	while (c != "quit") {
		// Parse string
		std::cin >> c;
		std::stringstream ss(c);
		std::vector<std::string> cmd;
		while (ss >> c) {
			cmd.emplace_back(c);
		}

		// Execute commands
		if (cmd.at(0) == "province") {
			if (cmd.at(1) == "-c") {
				std::cout << "Initializing province creator \n";

			} else if (cmd.at(1) == "-r") {
				int status =
				    std::filesystem::remove(nation / "provinces" / cmd.at(2));
				if (status != 0) {
					std::cout << "Error deleting file "
					          << nation / "provinces" / cmd.at(2) << std::endl;
				}
			} else {
				std::cout << "Invalid modifier provided. Use -c or -r"
				          << std::endl;
			}
		}
	}
}