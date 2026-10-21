#include "epic_dude_nation.cpp"
#include "kyrakan.cpp"
#include <iostream>
int main(int argc, char* argv[]) {
	nation kyrakan = getKyrakan();
	nation epic_dude_nation = getEpicDudeNation();
	if (std::string(argv[1]) == "kra") {
		printNationStats(kyrakan);
	} else if (std::string(argv[1]) == "edn") {
		printNationStats(epic_dude_nation);
	}
	return 0;
}