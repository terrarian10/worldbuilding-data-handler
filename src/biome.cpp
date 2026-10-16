#include <map>
#include <string>
struct biome {
	std::string name;
	double defenseMod;
	double populationMod;
	double baseSlots;
};

std::map<std::string, biome> stringToBiome = {
	{ "forest", biome{ "forest", 1.5, 1, 3 } },
	{ "grassland", biome{ "grassland", 1, 1.9, 4 } },
	{
	    "mountain",
	    biome{ "mountain", 2, 0.5, 2 },
	},
	{ "marsh", biome{ "marsh", 2.5, 0.25, 1 } },
	{ "" }
};