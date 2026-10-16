#include "editNation.cpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	// These MUST happen before generating provinces.
	std::cout << "Welcome to the Worldbuilding Tool! Type new to create a new "
	             " nation, type [strname of nation] to edit an existing one"
	          << std::endl;
	std::string val;
	std::cin >> val;
	if (val == "new") {
		std::cout
		    << "Enter the strname of your nation. Must be in all lowercase "
		       "with no special characters or spaces ex. kyrakan, not Kyrakan"
		    << std::endl;
		std::cin >> val;
		std::filesystem::create_directory(std::filesystem::path(val));
		std::filesystem::create_directory(std::filesystem::path(val) /
		                                  "provinces");
		std::filesystem::create_directory(std::filesystem::path(val) /
		                                  "characters");
	}
	nationEdit(std::filesystem::path(val));
	return 0;
}